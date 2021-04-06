// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //must be last

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	ATank* GetControlledTank() const;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	//start the tank moving barrel so that a shot would it where
	// the crosshair intersects the world
	void AimTowardsCrosshair();

	// Return an OUT paramater, true if hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	UPROPERTY(EditAnywhere)
		float CrosshairXLoaction = 0.5;

	UPROPERTY(EditAnywhere)
		float CrosshairYLoaction = 0.5;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
};
