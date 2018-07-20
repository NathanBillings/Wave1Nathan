// Fill out your copyright notice in the Description page of Project Settings.

#include "TurretBase.h"
#include "CanonProjectile.h"

// Sets default values
ATurretBase::ATurretBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set size for collision capsule
	

	// init of default balance vars
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	FireInterval = 0.5f;

	//Component init
	Mesh1P = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Mesh2P = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("MESH2"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	FP_MuzzleLocation_1 = CreateDefaultSubobject<USceneComponent>(TEXT("LEFTMUZZLE"));
	FP_MuzzleLocation_2 = CreateDefaultSubobject<USceneComponent>(TEXT("RIGHTMUZZLE"));
	RootComponent = CollisionBox;
	CollisionBox->bVisible = true;
	CollisionBox->bHiddenInGame = true;

	//attachment order
	Mesh1P->SetupAttachment(RootComponent, NAME_None);
	Camera->SetupAttachment(RootComponent, NAME_None);
	Mesh2P->SetupAttachment(Camera, NAME_None);
	Camera->bUsePawnControlRotation = true;
	FP_MuzzleLocation_1->SetupAttachment(Mesh2P, NAME_None);
	FP_MuzzleLocation_2->SetupAttachment(Mesh2P, NAME_None);
}

// Called when the game starts or when spawned
void ATurretBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurretBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATurretBase::Fire_Implementation()
{
	//fire using the location of the turret and the control rotation of the player
	FActorSpawnParameters SpawnParams;
	SpawnParams.bNoFail = true;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//set the barrel we're using
	FVector SpawnLoc;
	if (bUseLeftBarrel)
	{
		SpawnLoc = FP_MuzzleLocation_1->GetComponentLocation();
	}
	else
	{
		SpawnLoc = FP_MuzzleLocation_2->GetComponentLocation();
	}
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLoc, UGameplayStatics::GetPlayerController(this, 0)->GetControlRotation(), SpawnParams);

	//switch the barrel for the next time we fire
	bUseLeftBarrel = !bUseLeftBarrel;
}
// Called to bind functionality to input
void ATurretBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATurretBase::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATurretBase::LookUpAtRate);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATurretBase::OnFireInput);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ATurretBase::OnFireRelease);
}
void ATurretBase::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATurretBase::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ATurretBase::OnFireInput()
{
	Fire();

	//loop a timer that fires the projectile on the time interval
	GetWorldTimerManager().SetTimer(ShotTimer, this, &ATurretBase::Fire, FireInterval, true, .1f);
}

void ATurretBase::OnFireRelease()
{
	//clear the timer so it stops shooting
	GetWorldTimerManager().ClearTimer(ShotTimer);
}

