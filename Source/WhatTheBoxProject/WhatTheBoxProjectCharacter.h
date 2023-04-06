// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "WhatTheBoxProjectCharacter.generated.h"


UCLASS(config=Game)
class AWhatTheBoxProjectCharacter : public ACharacter
{
	GENERATED_BODY()
public:
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
		class UStaticMeshComponent* DestroyedBoxBodyComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* CutterKnifeComp;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//class UUserWidget* crosshairUI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UUserWidget* BulCountUI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UUserWidget* HPUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* fireSound;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USoundBase* knifeOnSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USoundBase* reloadSound;



	//UPROPERTY(EditAnywhere)
		//TSubclassOf<class UUserWidget> crosshairFactory;
		UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> HPUIFactory;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> BulCountUIFactory;

	AWhatTheBoxProjectCharacter();

	void Tick(float DeltaSeconds);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool isUsingKnife = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool bCanFire = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool bIsBoxUp = false;	
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
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AKnifeDamageBox> knifeBoxFactory;
	UPROPERTY(EditAnywhere)
	class UParticleSystem* fireEmitterTemplate;

	
protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	void MoveRelease(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Fire();
	UFUNCTION(Server, Unreliable)
	void ServerFire();
	UFUNCTION(NetMulticast, Unreliable)
	void MulticastFire();


	void ChangeWeapon();

	UFUNCTION(BlueprintImplementableEvent)
	void ResetFireCoolDown();

	UFUNCTION(BlueprintImplementableEvent)
		void ResetKnifeCoolDown();

	UFUNCTION(BlueprintImplementableEvent)
		void ResetKnifeLocation();

	UFUNCTION(BlueprintImplementableEvent)
		void SetImageAlphaForCurBullets();

	UFUNCTION(BlueprintImplementableEvent)
		void SetImageAlphaForHP();

	UFUNCTION(BlueprintImplementableEvent)
		void BoxUp();
	UFUNCTION(BlueprintImplementableEvent)
		void BoxDown();


			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }


	UFUNCTION(BlueprintImplementableEvent)
		void BoxHit();

};

