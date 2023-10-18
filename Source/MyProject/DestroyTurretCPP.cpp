// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyTurretCPP.h"

// Sets default values
ADestroyTurretCPP::ADestroyTurretCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	RootScene->SetupAttachment(RootComponent);

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootScene);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BodyAssets
	(TEXT("StaticMesh'/Game/Meshes/Turret/DestroyTurret.DestroyTurret'"));
	if (BodyAssets.Succeeded()) {
		Body->SetStaticMesh(BodyAssets.Object);
		Body->SetCollisionProfileName(TEXT("BlockAll"));
	}

}

// Called when the game starts or when spawned
void ADestroyTurretCPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestroyTurretCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

