// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "PlayerBullet.h"
#include "Components/Image.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ABoxPlayer::ABoxPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	CutterKnifeComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CutterKnifeComp"));
	CutterKnifeComp->SetupAttachment(BoxBodyComp, TEXT("KnifeSocket"));
	CutterKnifeComp->SetRelativeLocation(FVector(-76.92, -15.63, 2.06));
	CutterKnifeComp->SetRelativeRotation(FRotator(-51.73, 69.428, -67.26));
	FVector KnifeScale = FVector(0.08f, 0.1f, 0.05f);
	CutterKnifeComp->SetRelativeScale3D(KnifeScale);

	SetReplicateMovement(true);
	SetReplicates(true);
}

// Called when the game starts or when spawned
void ABoxPlayer::BeginPlay()
{
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
	HPUI = CreateWidget<UUserWidget>(GetWorld(), HPUIFactory);
	HPUI->AddToViewport();
	BulCountUI = CreateWidget<UUserWidget>(GetWorld(), BulCountUIFactory);
	BulCountUI->AddToViewport();

	curBulletCount = maxBulletCount;
}

// Called every frame
void ABoxPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABoxPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}

void ABoxPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABoxPlayer, CutterKnifeComp);
}

