// SURFKINI — Player Character Implementation

#include "SURFKINICharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"

// ─────────────────────────────────────────────────────────────────────────────
//  Constructor
// ─────────────────────────────────────────────────────────────────────────────

ASURFKINICharacter::ASURFKINICharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// ── Disable the default CharacterMovementComponent physics ──
	// Our SurfMovementComponent handles all physics.
	// We keep the capsule for collision shape but bypass CMC logic.
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	GetCharacterMovement()->GravityScale = 0.0f;

	// ── Capsule setup ──
	GetCapsuleComponent()->InitCapsuleSize(16.0f, 36.0f);

	// ── Create SurfMovementComponent ──
	SurfMovement = CreateDefaultSubobject<USurfMovementComponent>(TEXT("SurfMovement"));
	SurfMovement->UpdatedComponent = GetCapsuleComponent();

	// ── First Person Camera ──
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
	FirstPersonCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 30.0f)); // Eye height offset
	FirstPersonCamera->bUsePawnControlRotation = false; // We control rotation manually

	// ── Mesh ──
	// Hide the body mesh in first person (visible in 3rd person replays)
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -36.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	// Replication
	bReplicates = true;
	SetReplicateMovement(false); // We handle movement replication in SurfMovementComponent
}

// ─────────────────────────────────────────────────────────────────────────────
//  Lifecycle
// ─────────────────────────────────────────────────────────────────────────────

void ASURFKINICharacter::BeginPlay()
{
	Super::BeginPlay();
	VisualPosition = GetActorLocation();

	// Lock mouse cursor for FPS
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		PC->bShowMouseCursor = false;
		PC->SetInputMode(FInputModeGameOnly());
	}
}

void ASURFKINICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ── Visual Interpolation ──────────────────────────────────────
	// Physics runs at 60Hz fixed tick in SurfMovementComponent.
	// The visual position is interpolated here at the render rate (e.g. 144Hz)
	// to prevent judder on high-refresh displays.
	//
	// Physics body = actual capsule position (stepped at 60Hz)
	// VisualPosition = smoothly interpolated position for camera/mesh rendering

	const FVector PhysicsPosition = GetActorLocation();
	VisualPosition = FMath::VInterpTo(VisualPosition, PhysicsPosition,
	                                  DeltaTime, VisualLerpSpeed);

	// Apply visual position to camera (not capsule — capsule stays at physics pos)
	// In production: attach a visual anchor component instead of camera directly
	// to allow cinematic effects without disturbing the physics body.
}

// ─────────────────────────────────────────────────────────────────────────────
//  Input Binding
// ─────────────────────────────────────────────────────────────────────────────

void ASURFKINICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASURFKINICharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",   this, &ASURFKINICharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn",        this, &ASURFKINICharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp",      this, &ASURFKINICharacter::LookUp);

	PlayerInputComponent->BindAction("Jump", IE_Pressed,  this, &ASURFKINICharacter::OnJumpPressed);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ASURFKINICharacter::OnJumpReleased);
}

// ─────────────────────────────────────────────────────────────────────────────
//  Input Handlers
// ─────────────────────────────────────────────────────────────────────────────

void ASURFKINICharacter::MoveForward(float Value)
{
	if (FMath::Abs(Value) < SMALL_NUMBER) return;
	if (!SurfMovement) return;

	// Forward direction = camera horizontal forward (ignore pitch)
	const FRotator Yaw = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);
	const FVector  Dir = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);

	SurfMovement->AddWishDirection(Dir, Value);
}

void ASURFKINICharacter::MoveRight(float Value)
{
	if (FMath::Abs(Value) < SMALL_NUMBER) return;
	if (!SurfMovement) return;

	const FRotator Yaw = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);
	const FVector  Dir = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);

	SurfMovement->AddWishDirection(Dir, Value);
}

void ASURFKINICharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ASURFKINICharacter::LookUp(float Value)
{
	// Clamp pitch to prevent gimbal lock / backward flipping
	const float NewPitch = FMath::Clamp(CurrentPitch + Value, -MaxPitchDegrees, MaxPitchDegrees);
	const float Delta    = NewPitch - CurrentPitch;
	CurrentPitch         = NewPitch;

	if (FMath::Abs(Delta) > SMALL_NUMBER)
	{
		FirstPersonCamera->AddRelativeRotation(FRotator(Delta, 0.0f, 0.0f));
	}
}

void ASURFKINICharacter::OnJumpPressed()
{
	if (SurfMovement) SurfMovement->RequestJump();
}

void ASURFKINICharacter::OnJumpReleased()
{
	// Variable jump height can be implemented here (early release = lower jump)
	// For now: single fixed jump force
}
