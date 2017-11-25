// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Components/PrimitiveComponent.h"

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

    if (PhysicsHandle->GetGrabbedComponent())
    {
        PhysicsHandle->SetTargetLocation(GetReachLineEnd());
    }
}

FHitResult UGrabber::GetFirstPhysicBodyInReach() const
{
    FHitResult HitResult;
    FString ObjectName = "NONE";

    if (GetWorld()->LineTraceSingleByObjectType(HitResult, GetReachLineStart(), GetReachLineEnd(), FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody)))
        ObjectName = HitResult.GetActor()->GetName();

    UE_LOG(LogTemp, Warning, TEXT("Object %s"), *ObjectName);

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
    FHitResult HitResult = GetFirstPhysicBodyInReach();
    UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
    AActor* HitActor = HitResult.GetActor();

    if (HitActor)
        PhysicsHandle->GrabComponent(ComponentToGrab, FName(TEXT("")), HitActor->GetActorLocation(), true);
}

void UGrabber::Release()
{
    PhysicsHandle->ReleaseComponent();
}

FVector UGrabber::GetReachLineStart() const
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

    return PlayerViewPointLocation;
}

FVector UGrabber::GetReachLineEnd() const
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

    return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Range;
}