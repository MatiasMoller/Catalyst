// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CombatComponent.h"
#include "Catalyst/CatalystCharacter.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UCombatComponent::BeginPlay()
{
    Super::BeginPlay();

    Health = MaxHealth;

    Player = Cast<ACatalystCharacter>(GetOwner());

    if (!Player)
    {
        UE_LOG(LogTemp, Error, TEXT("Player reference is nullptr"));
        return;
    }

    Gun = Player->GetGun();
    Camera = Player->GetCamera();

    if (!Gun)
    {
        UE_LOG(LogTemp, Error, TEXT("Gun reference is nullptr"));
        return;
    }

    if (!Camera)
    {
        UE_LOG(LogTemp, Error, TEXT("Camera reference is nullptr"));
        return;
    }
}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCombatComponent::Shoot()
{
    // Make sure we have a player
    if (!Player)
    {
        UE_LOG(LogTemp, Error, TEXT("Player reference is nullptr"));
        return;
    }

    // Make sure we aren't on cooldown
    if (!bCanShoot)
    {
        UE_LOG(LogTemp, Error, TEXT("Still on cooldown"));
        return;
    }

    // Lock shooting
    bCanShoot = false;

    UE_LOG(LogTemp, Warning, TEXT("SHOOTING"));

    // Play gun animation
    if (Gun)
    {
        Gun->PlayAnimation(GunShoot, false);
    }

    // Get camera position and direction
    FVector Start = Camera->GetComponentLocation();
    FVector Forward = Camera->GetForwardVector();

    // How far the shot can travel
    float TraceDistance = 10000.0f;

    FVector End = Start + (Forward * TraceDistance);

    // Store hit information
    FHitResult Hit;

    // Ignore the player who fired
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(Player);

    // Perform line trace
    bool bHit = GetWorld()->LineTraceSingleByChannel(
        Hit,
        Start,
        End,
        ECC_WorldStatic,
        QueryParams
    );

    // Debug
    if (bHit)
    {
       
        // Draw only until the thing we hit
        DrawDebugLine(
            GetWorld(),
            Start,
            Hit.ImpactPoint,
            FColor::Green,
            false,
            2.0f,
            0,
            2.0f
        );

        DrawDebugPoint(
            GetWorld(),
            Hit.ImpactPoint,
            15.0f,
            FColor::Yellow,
            false,
            2.0f
        );
    }
    else
    {
        // Didn't hit anything
        DrawDebugLine(
            GetWorld(),
            Start,
            End,
            FColor::Red,
            false,
            2.0f,
            0,
            2.0f
        );
    }

    // Check if we hit something
    {
        AActor* HitActor = Hit.GetActor();

        if (HitActor)
        {
            UE_LOG(
                LogTemp,
                Warning,
                TEXT("Hit: %s"),
                *HitActor->GetName()
            );

            // Look for a Combat Component on the actor we hit
            UCombatComponent* CombatComponent =
                HitActor->FindComponentByClass<UCombatComponent>();

            if (CombatComponent)
            {
                UE_LOG(
                    LogTemp,
                    Warning,
                    TEXT("Actor has Combat Component!")
                );

                CombatComponent->Health -= 50.0f;

                if (CombatComponent->Health <= 0.0f)
                {
                    HitActor->Destroy();
                }
            }
            else
            {
                UE_LOG(
                    LogTemp,
                    Warning,
                    TEXT("Actor DOES NOT have Combat Component!")
                );
            }
        }
    }

    // Start shooting cooldown
    GetWorld()->GetTimerManager().SetTimer(
        ShootTimerHandle,
        this,
        &UCombatComponent::ResetShoot,
        ShootCooldown,
        false
    );
}

void UCombatComponent::ResetShoot()
{
    bCanShoot = true;

    UE_LOG(LogTemp, Warning, TEXT("Shoot cooldown finished"));
}
