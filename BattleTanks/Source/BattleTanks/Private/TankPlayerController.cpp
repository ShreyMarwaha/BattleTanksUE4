// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"



void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller not possesing tank"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller possessing: %s"), *(ControlledTank->GetName()))
	}
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) { return; }
	
	FVector OutHitLocation; //Out parameter
	if (GetSightRayHitLocation(OutHitLocation))
	{
		GetControlledTank()->AimAt(OutHitLocation);
			
		//TODO: Tell controlled tank to aim at this point
	}
	
}

//Get world location if linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const {
	 //find the cross hair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLoaction, ViewportSizeY * CrosshairYLoaction);
	

		// 'De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// line-trace along that LookDirection, and see waht we hit(up to max range)
		GetLookVectorLocation(LookDirection, OutHitLocation);
	}
		
	return true;
}


bool ATankPlayerController::GetLookVectorLocation(FVector LookDirection, FVector& OutHitLocation) const {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	return false; //Line trace didnt suceed
}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
	FVector CameraWorldLocation; // to be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

