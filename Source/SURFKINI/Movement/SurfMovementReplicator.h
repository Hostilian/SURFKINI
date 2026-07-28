// SURFKINI — Surf Movement Network Replicator Header
// Handles server authority, client prediction reconciliation, and rollback.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Movement/SurfMovementComponent.h"
#include "SurfMovementReplicator.generated.h"

USTRUCT()
struct FSurfStateCorrection
{
	GENERATED_BODY()

	UPROPERTY()
	int32 TickID = 0;

	UPROPERTY()
	FVector AuthoritativePosition = FVector::ZeroVector;

	UPROPERTY()
	FVector AuthoritativeVelocity = FVector::ZeroVector;

	UPROPERTY()
	ESurfMoveState AuthoritativeState = ESurfMoveState::Airborne;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURFKINI_API USurfMovementReplicator : public UActorComponent
{
	GENERATED_BODY()

public:
	USurfMovementReplicator();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Server RPC: receives client input packet */
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSendMove(int32 TickID, FVector WishDir, bool bJump, float DeltaSeconds);

	/** Client RPC: sends state correction when client prediction diverges > threshold */
	UFUNCTION(Client, Unreliable)
	void ClientCorrectState(FSurfStateCorrection Correction);

	/** Reconciles client predicted state against server authoritative state */
	void ReconcileClientState(const FSurfStateCorrection& Correction);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Replication")
	float ErrorTolerance = 0.005f; // Threshold position error before triggering rollback correction

private:
	UPROPERTY()
	USurfMovementComponent* SurfMovement;
};
