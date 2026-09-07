// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"


class ACatalystCharacter;
class USkeletalMeshComponent;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CATALYST_API UCombatComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCombatComponent();

protected:
    virtual void BeginPlay() override;

public:
    virtual void TickComponent(
        float DeltaTime,
        ELevelTick TickType,
        FActorComponentTickFunction* ThisTickFunction
    ) override;

    UFUNCTION(BlueprintCallable)
    void Shoot();
    UPROPERTY()
    class UCameraComponent* Camera;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Health;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxHealth = 100.0f;;

   
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ShootCooldown = 2.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UAnimationAsset* GunShoot;
private:
    UPROPERTY()
   ACatalystCharacter* Player;
   UPROPERTY()
   USkeletalMeshComponent* Gun;
    

private:

    bool bCanShoot = true;
    FTimerHandle ShootTimerHandle;
    FVector Start;
    FVector Forward;
    FVector End;
    FHitResult Hit;
    float TraceDistance;
    bool bHit = false;
    void LineTrace();
    void DebugTrace();
    void LineTraceLogic();
    void ResetShoot();
};
