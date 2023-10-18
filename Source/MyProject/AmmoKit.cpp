// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoKit.h"

// Sets default values
AAmmoKit::AAmmoKit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	RootScene->SetupAttachment(RootComponent);

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootScene);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BodyAssets
	(TEXT("StaticMesh'/Game/Meshes/AmmoKit/AmmoKit.AmmoKit'"));
	if (BodyAssets.Succeeded()) {
		Body->SetStaticMesh(BodyAssets.Object);
		Body->SetCollisionProfileName(TEXT("BlockAll"));
		Body->SetRelativeScale3D(FVector(4));
	}

	Tags.Add("AmmoKit");

}

// Called when the game starts or when spawned
void AAmmoKit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAmmoKit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

