// Copyright Epic Games, Inc. All Rights Reserved.

#include "WhatTheBoxProjectCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "PlayerBullet.h"
#include "KnifeDamageBox.h"
#include "Components/Image.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetSystemLibrary.h"


//////////////////////////////////////////////////////////////////////////
// AWhatTheBoxProjectCharacter

AWhatTheBoxProjectCharacter::AWhatTheBoxProjectCharacter()
{
	PrimaryActorTick.bCanEverTick=true;


	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(50.f, 50.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 250.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	FollowCamera->SetRelativeLocation(FVector(0, 0, 40));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	BoxBodyComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxBodyComp"));
	BoxBodyComp->SetupAttachment(RootComponent);
	BoxBodyComp->SetRelativeLocation(FVector(-4.46f, -146.21f, -90.0f));
	FVector boxScale = FVector(1, 2, 2.5);
	BoxBodyComp->SetRelativeScale3D(boxScale);

	DestroyedBoxBodyComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DestroyedBoxBodyComp"));
	DestroyedBoxBodyComp->SetupAttachment(RootComponent);
	DestroyedBoxBodyComp->SetRelativeLocation(FVector(-4.507673, -297.982111, -51.94783));
	FVector DestboxScale = FVector(10.25, 20.25, 34.5);
	DestroyedBoxBodyComp->SetRelativeScale3D(DestboxScale);
	DestroyedBoxBodyComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DestroyedBoxBodyComp->SetVisibility(false);

	CutterKnifeComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CutterKnifeComp"));
	CutterKnifeComp->SetupAttachment(BoxBodyComp, TEXT("KnifeSocket"));
	CutterKnifeComp->SetRelativeLocation(FVector(-76.92,-15.63, 2.06));
	CutterKnifeComp->SetRelativeRotation(FRotator(-51.73, 69.428, -67.26));
	FVector KnifeScale = FVector(0.08f, 0.1f, 0.05f);
	CutterKnifeComp->SetRelativeScale3D(KnifeScale);

	


}

void AWhatTheBoxProjectCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	GetCharacterMovement()->MaxWalkSpeed = 450.0f;

	CutterKnifeComp->SetVisibility(false);
	crosshairUI = CreateWidget<UUserWidget>(GetWorld(), crosshairFactory);
	crosshairUI->AddToViewport();


	curBulletCount = maxBulletCount;
	curHP = maxHP;


	
}


void AWhatTheBoxProjectCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	
	SetImageAlphaForHP();
}


//////////////////////////////////////////////////////////////////////////
// Input

void AWhatTheBoxProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AWhatTheBoxProjectCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AWhatTheBoxProjectCharacter::MoveRelease);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AWhatTheBoxProjectCharacter::Look);

		//Fire
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AWhatTheBoxProjectCharacter::Fire);
		
		//Change Weapon
		EnhancedInputComponent->BindAction(ChangeAction, ETriggerEvent::Triggered, this, &AWhatTheBoxProjectCharacter::ChangeWeapon);

	}

}

void AWhatTheBoxProjectCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}

	BoxUp();
	
	/*if(bIsBoxUp==false)
	{
		bIsBoxUp=true;
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		UKismetSystemLibrary::MoveComponentTo(BoxBodyComp, BoxBodyComp->GetRelativeLocation() + BoxBodyComp->GetUpVector() * 15.0f, BoxBodyComp->GetRelativeRotation(), false, false, 0.12f, false, EMoveComponentAction::Type::Move, LatentInfo);
		FTimerHandle boxHandle;
		GetWorldTimerManager().SetTimer(boxHandle, FTimerDelegate::CreateLambda([this]()->void
		{
				
				FLatentActionInfo LatentInfo1;
				LatentInfo1.CallbackTarget = this;
				UKismetSystemLibrary::MoveComponentTo(BoxBodyComp, BoxBodyComp->GetRelativeLocation() + BoxBodyComp->GetUpVector() * -15.0f, BoxBodyComp->GetRelativeRotation(), false, false, 0.12f, false, EMoveComponentAction::Type::Move, LatentInfo1);
				bIsBoxUp = false;
			
		}), 0.12f, false);
	}	*/


}

void AWhatTheBoxProjectCharacter::MoveRelease(const FInputActionValue& Value)
{
}

void AWhatTheBoxProjectCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AWhatTheBoxProjectCharacter::Fire()
{
	if(bCanFire==false)
	{
		return;
	}
	// if Player Using Knife
	if (isUsingKnife == true)
	{
		auto knifeSoc = BoxBodyComp->GetSocketByName(FName("KnifeSocket"));
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		FVector KnifeForward = BoxBodyComp->GetSocketLocation(FName("FireSocket"));
		FActorSpawnParameters params;		params.SpawnCollisionHandlingOverride=ESpawnActorCollisionHandlingMethod::AlwaysSpawn;		
		auto pastPos = CutterKnifeComp->GetRelativeTransform();
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), knifeSound, KnifeForward, FRotator::ZeroRotator, 1, 1, 0, nullptr, nullptr, true);
		UKismetSystemLibrary::MoveComponentTo(CutterKnifeComp, CutterKnifeComp->GetRelativeLocation(), FRotator(43.476491, -33.766974, -51.922897), false, false, 0.15f, true, EMoveComponentAction::Type::Move, LatentInfo);		

		GetWorld()->SpawnActor<AKnifeDamageBox>(knifeBoxFactory, KnifeForward+BoxBodyComp->GetForwardVector()*90.0f, FRotator::ZeroRotator, params);

		ResetKnifeLocation();



		
		/*UKismetSystemLibrary::MoveComponentTo(CutterKnifeComp, pastPos.GetLocation(), FRotator(-51.73, 69.428, -67.26), false, false, 0.3f, true, EMoveComponentAction::Type::Move, LatentInfo);*/
		
		bCanFire=false;
		ResetKnifeCoolDown();


	}
	// if Player Using Gun
	else
	{
		// if Player Using Gun and have ammo
		if (curBulletCount > 0)
		{
			
			FVector BulletForward = FollowCamera->GetComponentLocation() + FollowCamera->GetForwardVector() * 380.0f - FollowCamera->GetUpVector() * 30.0f;
			//FVector EmitterForward = FollowCamera->GetComponentLocation() + FollowCamera->GetForwardVector() * 300.0f - FollowCamera->GetUpVector() * 30.0f;
			FTransform EmitterTrans = BoxBodyComp->GetSocketTransform(FName("FireSocket"));
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), fireSound, BulletForward, FRotator::ZeroRotator, 1, 1, 0, nullptr, nullptr, true);
			GetWorld()->SpawnActor<APlayerBullet>(bulletFactory, BulletForward, FollowCamera->GetComponentRotation());
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), fireEmitterTemplate, EmitterTrans, true);
			curBulletCount--;
			SetImageAlphaForCurBullets();
			
		}
		// if Player Using Gun and have no ammo
		else
		{
			bCanFire = false;
			ResetFireCoolDown();
			//SetImageAlphaForCurBullets();
		
		}
	}
}

void AWhatTheBoxProjectCharacter::ChangeWeapon()
{
	if (isUsingKnife == false)
	{
		CutterKnifeComp->SetVisibility(true);
		isUsingKnife = true;
		GetCharacterMovement()->MaxWalkSpeed = 650.0f;
	}
	else
	{
		CutterKnifeComp->SetVisibility(false);
		isUsingKnife = false;
		GetCharacterMovement()->MaxWalkSpeed = 450.0f;
	}
}
