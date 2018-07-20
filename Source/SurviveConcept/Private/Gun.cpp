// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"

// Sets default values
AGun::AGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	MuzzlePoint = CreateDefaultSubobject<USceneComponent>(TEXT("MUZZLE"));
	RootComponent = Mesh;
	MuzzlePoint->SetupAttachment(RootComponent);

	//default values
	bReplicates = true;
	bReplicateMovement = true;
	MaxEnergy = 32;
	Energy = MaxEnergy;
}
void AGun::FireProjectile_Implementation()
{
	if (Role < ROLE_Authority)
	{
		Server_FireProjectile();
	}
	if (Energy > 0)
	{
		AActor* SpawnedProjectile;
		Energy--;
		FireEffects();
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnedProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzlePoint->GetComponentLocation(), GetOwner()->GetInstigatorController()->GetControlRotation(), ActorSpawnParams);
		//SpawnedProjectile->SetOwner(this);
	}
}

void AGun::Server_FireProjectile_Implementation()
{
	AActor* SpawnedProjectile;
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnedProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzlePoint->GetComponentLocation(), GetOwner()->GetInstigatorController()->GetControlRotation(), ActorSpawnParams);
	//SpawnedProjectile->SetOwner(this);
}

bool AGun::Server_FireProjectile_Validate()
{
	return true;
}


void AGun::StartFireInput_Implementation()
{
	FireProjectile();
	if (Automatic)
	{
		GetWorldTimerManager().SetTimer(ShotTimer, this, &AGun::FireProjectile, FireInterval, true, .1f);
	}
}
void AGun::EndFireInput_Implementation()
{
	GetWorldTimerManager().ClearTimer(ShotTimer);
}
// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

int32 AGun::GetEnergy()
{
	return Energy;
}

int32 AGun::GetMaxEnergy()
{
	return MaxEnergy;
}


int32 AGun::SetEnergy(int32 inEnergy)
{
	Energy = inEnergy;
	return Energy;
}

void AGun::FireEffects_Implementation()
{
	
}

