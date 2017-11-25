// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

    FindPhysicsHandleComponent();
    SetupInputComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

FHitResult UGrabber::GetFirstPhysicBodyInReach() const
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);


    FVector LineBegin = PlayerViewPointLocation;
    FVector LineEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Range;


    DrawDebugLine(GetWorld(), LineBegin, LineEnd, FColor::Red, false, -1.f, 0, 10);

    FHitResult HitResult;

    FString ObjectName = "NONE";
    if (GetWorld()->LineTraceSingleByObjectType(HitResult, LineBegin, LineEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody)))
        ObjectName = HitResult.GetActor()->GetName();

    UE_LOG(LogTemp, Warning, TEXT("Location %s Rotation %s Object %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString(), *ObjectName);

    return HitResult;
}

void UGrabber::FindPhysicsHandleComponent()
{
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (PhysicsHandle)
    {

    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Missing PhysicHandleComponent"));
    }
}

void UGrabber::SetupInputComponent()
{
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (InputComponent)
    {
        InputComponent->BindAction(FName(TEXT("Grab")), EInputEvent::IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction(FName(TEXT("Grab")), EInputEvent::IE_Released, this, &UGrabber::Release);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Missing InputComponent"));
    }

}
void UGrabber::Grab()
{
    GetFirstPhysicBodyInReach();
}

void UGrabber::Release()
{

}

