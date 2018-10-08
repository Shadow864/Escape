// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
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
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (IsTriggerActivated())
    {
        OpenDoor();
        OpenTime = GetWorld()->GetTimeSeconds();
    }


    if (GetWorld()->GetTimeSeconds() - OpenTime > TimeToClose)
        CloseDoor();

}

void UOpenDoor::CloseDoor() const
{
    OnCloseRequest.Broadcast();
}

void UOpenDoor::OpenDoor() const
{
    OnOpenRequest.Broadcast();
}

bool UOpenDoor::IsTriggerActivated() const
{
    return GetWightOfCollapsingObject() >= TriggerMass;
}

float UOpenDoor::GetWightOfCollapsingObject() const
{
    if (PressurePlate == nullptr)
        return 0;

    TArray<AActor*> OverlappingActors;
    PressurePlate->GetOverlappingActors(OverlappingActors);

    float OverlappingActorsMass = 0;

    for (const auto& OverlappingActor : OverlappingActors)
    {
        UPrimitiveComponent* OverlappingPrimitveComponent = OverlappingActor->FindComponentByClass<UPrimitiveComponent>();
        if (OverlappingPrimitveComponent)
            OverlappingActorsMass += OverlappingPrimitveComponent->GetMass();
    }

    return OverlappingActorsMass;
}