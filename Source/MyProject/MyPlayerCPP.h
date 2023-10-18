// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "MyPlayerCPP.generated.h"

UCLASS()
class MYPROJECT_API AMyPlayerCPP : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayerCPP();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		USceneComponent* FirePlaceScene;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMeshComponent* Body;
	UPROPERTY(BlueprintReadWrite)
		UCameraComponent* Cam;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> MainWidget;
	UUserWidget* MWidget;

	UPROPERTY(BlueprintReadWrite)
		AActor* ActorPick;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Health = 100;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int CountBullet = 10;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool CanPick;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool CanPickAidKit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool CanPickAmmoKit;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FHitResult Hit;
	FCollisionQueryParams CollParam;

	void MoveAxis(float Axis);
	void RotateAxis(float Axis);
	void ClimbAxis(float Axis);
	void MouseX(float Axis);
	void MouseY(float Axis);
	void PickUp(float Axis);
	void MouseAct();

	UFUNCTION(BlueprintCallable)
		void CheckPick();

	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
