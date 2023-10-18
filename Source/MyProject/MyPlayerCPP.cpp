// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerCPP.h"
#include "BulletCPP.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/NavMovementComponent.h"

// Sets default values
AMyPlayerCPP::AMyPlayerCPP()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FirePlaceScene = CreateDefaultSubobject<USceneComponent>(TEXT("FirePlaceScene"));
	FirePlaceScene->SetupAttachment(GetMesh());
	FirePlaceScene->SetRelativeLocation(FVector(100, 0, 0));

	Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Cam->SetupAttachment(GetMesh());
	
	GetCapsuleComponent()->SetCapsuleHalfHeight(34);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("BlockAll"));
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMyPlayerCPP::OnBoxBeginOverlap);

	GetCharacterMovement()->BrakingDecelerationFlying = 1000;
	GetCharacterMovement()->MaxFlySpeed = 300;

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
	Tags.Add(FName("Player"));

}

// Called when the game starts or when spawned
void AMyPlayerCPP::BeginPlay()
{
	Super::BeginPlay();

	MWidget = CreateWidget(GetWorld(), MainWidget);
	MWidget->AddToViewport();
	
}

// Called every frame
void AMyPlayerCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckPick();

}

// Called to bind functionality to input
void AMyPlayerCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveAxis", this, &AMyPlayerCPP::MoveAxis);
	PlayerInputComponent->BindAxis("RotateAxis", this, &AMyPlayerCPP::RotateAxis);
	PlayerInputComponent->BindAxis("ClimbAxis", this, &AMyPlayerCPP::ClimbAxis);
	PlayerInputComponent->BindAxis("MouseX", this, &AMyPlayerCPP::MouseX);
	PlayerInputComponent->BindAxis("MouseY", this, &AMyPlayerCPP::MouseY);
	PlayerInputComponent->BindAxis("PickUp", this, &AMyPlayerCPP::PickUp);
	PlayerInputComponent->BindAction("MouseAct", IE_Pressed, this, &AMyPlayerCPP::MouseAct);

}

void AMyPlayerCPP::MoveAxis(float Axis) {
	AddMovementInput(GetActorForwardVector() * Axis);
}

void AMyPlayerCPP::RotateAxis(float Axis) {
	AddMovementInput(GetActorRightVector() * Axis * -1);
}

void AMyPlayerCPP::ClimbAxis(float Axis) {
	AddMovementInput(GetActorUpVector() * Axis);
}

void AMyPlayerCPP::MouseX(float Axis)
{
	AddControllerYawInput(Axis);
}

void AMyPlayerCPP::MouseY(float Axis)
{
	AddControllerPitchInput(-Axis);
}

void AMyPlayerCPP::MouseAct()
{
	if (CountBullet > 0) {
		FActorSpawnParameters SpawnInfo;
		ABulletCPP* Bullet = GetWorld()->SpawnActor<ABulletCPP>(FirePlaceScene->GetComponentLocation(),
			GetActorRotation(), SpawnInfo);
		Bullet->Tags.Add("PlayerBullet");
		CountBullet--;
	}
}

void AMyPlayerCPP::PickUp(float Axis)
{
	if (Axis == 1) {
		if (Hit.GetActor() != nullptr) {
			if (ActorPick->ActorHasTag("AidKit")) {
				Health = 100;
				ActorPick->Destroy();
			}
			else if (ActorPick->ActorHasTag("AmmoKit")) {
				CountBullet += 5;
				ActorPick->Destroy();
			}
		}
	}
}

void AMyPlayerCPP::CheckPick()
{
	CollParam.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(Hit, FirePlaceScene->GetComponentLocation(),
		(FirePlaceScene->GetForwardVector() * 500) + FirePlaceScene->GetComponentLocation(),
		ECC_Visibility, CollParam);
	if (Hit.GetActor() != nullptr) {
		ActorPick = Hit.GetActor();
		CanPick = true;
	}
	else {
		CanPick = false;
	}
}

void AMyPlayerCPP::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("EnemyBullet")) {
		Health -= 10;
	}
}

