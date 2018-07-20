// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Engine.h"
#include "TurretBase.generated.h"

class UInputComponent;

UCLASS()
class SURVIVECONCEPT_API ATurretBase : public APawn
{
	GENERATED_BODY()

	

	

public:
	// Sets default values for this pawn's properties
	ATurretBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	
	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* FireAnimation;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Gameplay)
		void Fire();

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* Mesh1P;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* Mesh2P;

	//camera
	UPROPERTY(VisibleDefaultsOnly, Category = Gameplay)
		class UCameraComponent* Camera;

	//Projectile Class property to set what actor it shoots
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UClass* ProjectileClass;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* FP_Gun;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gameplay)
		class UBoxComponent* CollisionBox;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USceneComponent* FP_MuzzleLocation_1;


	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USceneComponent* FP_MuzzleLocation_2;

	FTimerHandle ShotTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float FireInterval;

protected:

	//which barrel to fire the projectile out of
	bool bUseLeftBarrel;

	/**
	* Called via input to turn at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/**
	* Called via input to turn look up/down at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void LookUpAtRate(float Rate);

	//Handle the fire input
	virtual void OnFireInput();

	//Handle releasing the fire input
	virtual void OnFireRelease();


protected:

	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:	

	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
	
};
