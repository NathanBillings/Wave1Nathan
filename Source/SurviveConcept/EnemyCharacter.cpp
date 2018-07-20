// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"

AEnemyCharacter::AEnemyCharacter()
{
	AggroSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AGGROSPHERE"));
	MuzzlePoint = CreateDefaultSubobject<USceneComponent>(TEXT("MUZZLE"));
	AggroSphere->SetupAttachment(RootComponent, NAME_None);
	MuzzlePoint->SetupAttachment(RootComponent, NAME_None);
	MoveUpdateInterval = 3.0f;
	bMovingTowardCore = true;
	AggroSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::AggroResponse);
	ShotSpread = 3.0f;
	FireInterval = 0.5f;
	bReplicates = true;
	bReplicateMovement = true;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(MoveTimer, this, &AEnemyCharacter::MoveUpdate, MoveUpdateInterval, true, .1f);
}

void AEnemyCharacter::MoveUpdate()
{
	if (bMovingTowardCore)
	{
		MoveTowardCore();
	}
	else 
	{
		MoveTowardPlayer();
	}
}

void AEnemyCharacter::MoveTowardCore_Implementation()
{
}

void AEnemyCharacter::MoveTowardPlayer_Implementation()
{
}

void AEnemyCharacter::AggroResponse_Implementation(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	bMovingTowardCore = false;
	MoveTowardPlayer();
	GetWorldTimerManager().SetTimer(FireTimer, this, &AEnemyCharacter::FireProjectile, FireInterval, true, .1f);
}

void AEnemyCharacter::FireProjectile_Implementation()
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FRotator SpawnRotation;
	FRotator RotTowardPlayer;
	FVector DeltaVector;
	//sanity checked location delta to prevent crashing
	if (UGameplayStatics::GetPlayerPawn(this, 0))
	{
		DeltaVector = FVector(UGameplayStatics::GetPlayerPawn(this, 0)->GetActorLocation() - GetActorLocation());
	}
	else
	{
		DeltaVector = FVector(0, 0, 0);
	}
	RotTowardPlayer = FRotationMatrix::MakeFromX(DeltaVector).Rotator();
	SpawnRotation = FRotator(FMath::FRandRange(ShotSpread*-1, ShotSpread) + RotTowardPlayer.Pitch, FMath::FRandRange(ShotSpread*-1,ShotSpread) + RotTowardPlayer.Yaw, FMath::FRandRange(ShotSpread*-1, ShotSpread) + RotTowardPlayer.Roll);
	//Fire the Projectile
	GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzlePoint->GetComponentLocation(), SpawnRotation, ActorSpawnParams);
}
