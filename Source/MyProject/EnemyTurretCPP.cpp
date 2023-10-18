// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTurretCPP.h"
#include "MyPlayerCPP.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "BulletCPP.h"
#include "DrawDebugHelpers.h"
#include "DestroyTurretCPP.h"
#include "ExplosionCPP.h"

// Sets default values
AEnemyTurretCPP::AEnemyTurretCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	RootScene->SetupAttachment(RootComponent);

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootScene);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BodyAssets
	(TEXT("StaticMesh'/Game/Meshes/Turret/Turret_turret.Turret_turret'"));
	if (BodyAssets.Succeeded()) {
		Body->SetStaticMesh(BodyAssets.Object);
		Body->SetCollisionProfileName(TEXT("BlockAll"));
		Body->OnComponentBeginOverlap.AddDynamic(this, &AEnemyTurretCPP::OnBodyBeginOverlap);
	}

	RotateGunScene = CreateDefaultSubobject<USceneComponent>(TEXT("RotateGunScene"));
	RotateGunScene->SetupAttachment(Body);
	RotateGunScene->SetRelativeLocation(FVector(-4.097717, 0, 116.362244));

	Gun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun"));
	Gun->SetupAttachment(RotateGunScene);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> GunAssets
	(TEXT("StaticMesh'/Game/Meshes/Turret/Turret_turret_001.Turret_turret_001'"));
	if (GunAssets.Succeeded()) {
		Gun->SetStaticMesh(GunAssets.Object);
		Gun->SetRelativeLocation(FVector(4.097717, 0, -116.362244));
	}

	FireScene = CreateDefaultSubobject<USceneComponent>(TEXT("FirePlace"));
	FireScene->SetupAttachment(Gun);
	FireScene->SetRelativeLocation(FVector(153.886841, 0, 142.14859));

	FireEmitter = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireEmitter"));
	FireEmitter->SetupAttachment(RootScene);
	static ConstructorHelpers::FObjectFinder<UParticleSystem>
		ParticleSystemClass(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
	FireEmitter->SetTemplate(ParticleSystemClass.Object);
	FireEmitter->SetRelativeScale3D(FVector(5));
	FireEmitter->SetVisibility(false);

	Tags.Add(FName("Enemy"));
}

// Called when the game starts or when spawned
void AEnemyTurretCPP::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AMyPlayerCPP>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	CollParam.AddIgnoredActor(this);
}

// Called every frame
void AEnemyTurretCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetDistanceTo(Player) < 5000) {

		SetActorRotation(FRotator(0, FMath::RInterpConstantTo(GetActorRotation(),
			UKismetMathLibrary::FindLookAtRotation
			(GetActorLocation(), Player->GetActorLocation()), DeltaTime, 50).Yaw, 0));

		RotateGunScene->SetRelativeRotation(FRotator(FMath::RInterpConstantTo(
			RotateGunScene->GetRelativeRotation(), UKismetMathLibrary::FindLookAtRotation
			(FireScene->GetComponentLocation(),
				Player->GetActorLocation()), DeltaTime, 10).Pitch, 0, 0));

		CollParam.AddIgnoredActor(this);
		GetWorld()->LineTraceSingleByChannel(Hit, FireScene->GetComponentLocation(),
			(FireScene->GetForwardVector() * 5000) + FireScene->GetComponentLocation(),
			ECC_Visibility, CollParam);

		if (Hit.Actor == Player && bCanFire) {
			AActor* Bullet = GetWorld()->SpawnActor<ABulletCPP>(FireScene->GetComponentLocation(),
				FireScene->GetComponentRotation(), SpawnInfo);
			Bullet->Tags.Add("EnemyBullet");
			AActor* ShotExplosion = GetWorld()->SpawnActor<AExplosionCPP>(FireScene->GetComponentLocation(),
				GetActorRotation(), SpawnInfo);
			bCanFire = false;
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemyTurretCPP::Fire, 1, false);
		}
	}

	if (Health <= 0) {
		GetWorld()->SpawnActor<ADestroyTurretCPP>(GetActorLocation(),
			GetActorRotation(), SpawnInfo);
		AActor* Explosion = GetWorld()->SpawnActor<AExplosionCPP>(GetActorLocation(),
			GetActorRotation(), SpawnInfo);
		Explosion->SetActorScale3D(FVector(5));
		Destroy();
	}
	else if (Health <= 50) {
		FireEmitter->SetVisibility(true);
	}
}

void AEnemyTurretCPP::Fire() {
	bCanFire = true;
}

void AEnemyTurretCPP::OnBodyBeginOverlap(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("PlayerBullet")) {
		Health -= 50;
	}
}

