// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CombatComponent.h"
#include "Catalyst/CatalystCharacter.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{

		Super::BeginPlay();

		Player = Cast<ACatalystCharacter>(GetOwner());

		if (!Player)
		{
			UE_LOG(LogTemp, Error, TEXT("Player reference is nullptr"));
			return;
		}

		Gun = Player->GetGun();

		if (!Gun)
		{
			UE_LOG(LogTemp, Error, TEXT("Gun reference is nullptr"));
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
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("PLayer REF is nullptr"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Shooting"));
	Gun->PlayAnimation(GunShoot, false);

	
}

