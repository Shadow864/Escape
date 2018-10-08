// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

class ATriggerVolume;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    void OpenDoor() const;
    void CloseDoor() const;
    bool IsTriggerActivated() const;
    float GetWightOfCollapsingObject() const;
private:
	
    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate;

    UPROPERTY(EditAnywhere)
    float TriggerMass = 70;

    UPROPERTY(EditAnywhere)
    float TimeToClose = 1;
    
    UPROPERTY(BlueprintAssignable)
    FOnOpenRequest OnOpenRequest;

    UPROPERTY(BlueprintAssignable)
    FOnCloseRequest OnCloseRequest;

private:
    AActor* ActorThatOpens = nullptr;
    float       OpenTime = 0.f;


};
