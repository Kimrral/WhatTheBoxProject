// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BoxPlayer.generated.h"

UCLASS()
class WHATTHEBOXPROJECT_API ABoxPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABoxPlayer();

		/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* ChangeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* BoxBodyComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* CutterKnifeComp;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UUserWidget* crosshairUI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UUserWidget* BulCountUI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UUserWidget* HPUI;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> crosshairFactory;
		UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> HPUIFactory;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> BulCountUIFactory;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool isUsingKnife = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool bCanFire = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool bBoxCanMove = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 maxBulletCount = 3;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 curBulletCount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 maxHP = 3;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 curHP;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class APlayerBullet> bulletFactory;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
