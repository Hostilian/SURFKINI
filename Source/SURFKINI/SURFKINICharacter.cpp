// SURFKINI — Player Character Implementation

#include "SURFKINICharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
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

	// Bypass default CharacterMovementComponent logic for custom SurfMovement
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	GetCharacterMovement()->GravityScale = 0.0f;

	// Capsule setup
	GetCapsuleComponent()->InitCapsuleSize(16.0f, 36.0f);

	// SurfMovementComponent
	SurfMovement = CreateDefaultSubobject<USurfMovementComponent>(TEXT("SurfMovement"));
	SurfMovement->UpdatedComponent = GetCapsuleComponent();

	// First Person Camera
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
	FirstPersonCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 30.0f));
	FirstPersonCamera->bUsePawnControlRotation = false;

	// Third Person Spring Arm & Camera
	ThirdPersonSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ThirdPersonSpringArm"));
	ThirdPersonSpringArm->SetupAttachment(GetCapsuleComponent());
	ThirdPersonSpringArm->TargetArmLength = 250.0f;
	ThirdPersonSpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 40.0f));
	ThirdPersonSpringArm->bUsePawnControlRotation = true;

	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	ThirdPersonCamera->SetupAttachment(ThirdPersonSpringArm, USpringArmComponent::SocketName);
	ThirdPersonCamera->bUsePawnControlRotation = false;
	ThirdPersonCamera->SetActive(false);

	// Mesh
	GetMesh()->SetOwnerNoSee(false);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -36.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	bReplicates = true;
	SetReplicateMovement(false);
}

void ASURFKINICharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		PC->bShowMouseCursor = false;
		PC->SetInputMode(FInputModeGameOnly());
	}
}

void ASURFKINICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

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
	PlayerInputComponent->BindAction("ToggleCamera", IE_Pressed, this, &ASURFKINICharacter::ToggleCameraView);
}

void ASURFKINICharacter::ToggleCameraView()
{
	bIsThirdPerson = !bIsThirdPerson;

	if (bIsThirdPerson)
	{
		FirstPersonCamera->SetActive(false);
		ThirdPersonCamera->SetActive(true);
	}
	else
	{
		ThirdPersonCamera->SetActive(false);
		FirstPersonCamera->SetActive(true);
	}
}

void ASURFKINICharacter::ApplyWallImpactDamage(float ImpactSpeed)
{
	// Gears Wall Slam Damage
	if (ImpactSpeed > 1000.0f)
	{
		float RawDmg = (ImpactSpeed - 1000.0f) * 0.05f;
		float ArmorDmg = RawDmg * 0.3f;
		float HealthDmg = RawDmg - ArmorDmg;

		PlayerArmor = FMath::Max(0.0f, PlayerArmor - ArmorDmg);
		PlayerHealth = FMath::Max(1.0f, PlayerHealth - HealthDmg);
	}
}

void ASURFKINICharacter::MoveForward(float Value)
{
	if (FMath::Abs(Value) < SMALL_NUMBER) return;
	if (!SurfMovement) return;

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
}
