// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine.h"
#include "Auto_Turret.generated.h"

UCLASS()
class SURVIVECONCEPT_API AAuto_Turret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties 
	AAuto_Turret();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USphereComponent* AggroSphere;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Gameplay)
	void AggroResponse(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Gameplay)
	void EndAggro(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USceneComponent* MuzzlePoint;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* Mesh1P;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* Mesh2P;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Gameplay)
	void FireProjectile();

	UFUNCTION(Server, Reliable, WithValidation, Category = Gameplay)
	void Server_FireProjectile();

	bool Server_FireProjectile_Validate();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float FireInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float ShotSpread;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int32 ScrapCost;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	class UClass* ProjectileClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class AActor* TargetActor;

	FTimerHandle FireTimer;

	float SphereStartRadius;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
