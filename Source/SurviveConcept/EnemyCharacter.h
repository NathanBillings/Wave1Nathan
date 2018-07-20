// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurviveConceptCharacter.h"
#include "Engine.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVECONCEPT_API AEnemyCharacter : public ASurviveConceptCharacter
{
	GENERATED_BODY()
	
public:

	AEnemyCharacter();

	FTimerHandle MoveTimer;
	FTimerHandle FireTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USphereComponent* AggroSphere;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category=Gameplay)
	void MoveTowardCore();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Gameplay)
	void MoveTowardPlayer();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Gameplay)
	void AggroResponse(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Gameplay)
	void FireProjectile();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameplay)
	float MoveUpdateInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float FireInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float ShotSpread;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USceneComponent* MuzzlePoint;

protected:
	virtual void BeginPlay() override;

	//If true, enemy moves toward the core, else they chase the player
	bool bMovingTowardCore;
	
	virtual void MoveUpdate();
	
};
