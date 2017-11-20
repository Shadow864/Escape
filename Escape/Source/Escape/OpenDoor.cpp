// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

    OpenDoorRotator = GetOwner()->GetActorRotation();
    CloseDoorRotator = GetOwner()->GetActorRotation();

    OpenDoorRotator.Add(0, OpenAngle, 0);

}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))
        OpenDoor();
    else
        CloseDoor();

}

void UOpenDoor::CloseDoor() const
{
    GetOwner()->SetActorRotation(CloseDoorRotator);
}

void UOpenDoor::OpenDoor() const
{
    GetOwner()->SetActorRotation(OpenDoorRotator);
}

