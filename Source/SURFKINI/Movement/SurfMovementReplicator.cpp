// SURFKINI — Surf Movement Network Replicator Implementation

#include "Movement/SurfMovementReplicator.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"

USurfMovementReplicator::USurfMovementReplicator()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}

void USurfMovementReplicator::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (Owner)
	{
		SurfMovement = Owner->FindComponentByClass<USurfMovementComponent>();
	}
}

void USurfMovementReplicator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!SurfMovement || !GetOwner()) return;

	// Server validation check
	if (GetOwner()->HasAuthority())
	{
		// Process server side state checks
	}
}

bool USurfMovementReplicator::ServerSendMove_Validate(int32 TickID, FVector WishDir, bool bJump, float DeltaSeconds)
{
	// Validate input sanity
	return DeltaSeconds > 0.0f && DeltaSeconds < 0.2f;
}

void USurfMovementReplicator::ServerSendMove_Implementation(int32 TickID, FVector WishDir, bool bJump, float DeltaSeconds)
{
	if (!SurfMovement || !GetOwner()) return;

	// Server simulates tick using client inputs
	SurfMovement->AddWishDirection(WishDir, 1.0f);
	if (bJump) SurfMovement->RequestJump();

	const FVector ServerPos = GetOwner()->GetActorLocation();
	const FVector ServerVel = SurfMovement->GetVelocity();
	const ESurfMoveState ServerState = SurfMovement->GetMoveState();

	// If server detects significant error compared to reported client move, send correction
	const FSurfSavedMove& LatestClientMove = SurfMovement->GetLatestSavedMove();
	const float PositionError = FVector::Dist(ServerPos, LatestClientMove.Position);

	if (PositionError > ErrorTolerance)
	{
		FSurfStateCorrection Correction;
		Correction.TickID = TickID;
		Correction.AuthoritativePosition = ServerPos;
		Correction.AuthoritativeVelocity = ServerVel;
		Correction.AuthoritativeState = ServerState;

		ClientCorrectState(Correction);
	}
}

void USurfMovementReplicator::ClientCorrectState_Implementation(FSurfStateCorrection Correction)
{
	ReconcileClientState(Correction);
}

void USurfMovementReplicator::ReconcileClientState(const FSurfStateCorrection& Correction)
{
	if (!SurfMovement || !GetOwner()) return;

	// Snap position & velocity to server authoritative state
	GetOwner()->SetActorLocation(Correction.AuthoritativePosition);

	// Replay saved input buffer from Correction.TickID to current local tick
	// Rollback & re-simulation loop
}
