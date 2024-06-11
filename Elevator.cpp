// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"

// Sets default values
AElevator::AElevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
	PlatformVelocityA = PlatformVelocity;
	PlatformVelocityB = -PlatformVelocity;
	StartPoint = GetActorLocation();
	EndPoint = StartPoint + PlatformVelocity.GetSafeNormal()*MovedDistance;
}

// Called every frame
void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    
	float DistDifference = FVector::Dist(StartLocation, GetActorLocation());

    if (DistDifference > MovedDistance)
	
	{
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		// Calculates and sets the new StartLocation.
		StartLocation = StartLocation + MoveDirection * MovedDistance;
		SetActorLocation(StartLocation);
		// Reverses the actor's velocity.
		if(PlatformVelocity == PlatformVelocityA)
		{
			PlatformVelocity = PlatformVelocityB;
		}
		else
		{
			PlatformVelocity = PlatformVelocityA;
		}

	}
	else
	{
		if(SteppedOn && (PlatformVelocity == PlatformVelocityA))
		{
			FVector CurrentLocation = GetActorLocation();
			// Add vector to that location by getting the product of velocity and time between frames.
			CurrentLocation += (PlatformVelocity * DeltaTime);
			// Set the location
			SetActorLocation(CurrentLocation);
		}
		else if(SteppedOff && (PlatformVelocity == PlatformVelocityB))
		{
			FVector CurrentLocation = GetActorLocation();
			// Add vector to that location by getting the product of velocity and time between frames.
			CurrentLocation += (PlatformVelocity * DeltaTime);
			// Set the location
			SetActorLocation(CurrentLocation);
		}
		else if(SteppedOff && (PlatformVelocity == PlatformVelocityA))
		{
			if(GetActorLocation().Size() >= StartPoint.Size())
			{
				FVector CurrentLocation = GetActorLocation();
				// Add vector to that location by getting the product of velocity and time between frames.
				CurrentLocation += (PlatformVelocityB * DeltaTime);
				// Set the location
				SetActorLocation(CurrentLocation);
			}	
			else
			{
				SetActorLocation(StartPoint);
				SteppedOn = false;
				SteppedOff = false;

			}
			
		}
	}
	

}

