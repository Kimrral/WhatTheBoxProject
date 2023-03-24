// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBullet.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include <GameFramework/ProjectileMovementComponent.h>

// Sets default values
APlayerBullet::APlayerBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

		
		sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
		SetRootComponent(sphereComp);

		sphereComp->SetSphereRadius(5.0f);
		sphereComp->SetCollisionProfileName(TEXT("BlockAll"));

		meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
		meshComp->SetupAttachment(sphereComp);
		meshComp->SetRelativeScale3D(FVector(0.03f));
		meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("movementComp"));
		movementComp->SetUpdatedComponent(sphereComp);
		movementComp->InitialSpeed = 10000.0f;
		movementComp->MaxSpeed = 10000.0f;
		movementComp->ProjectileGravityScale = 0.1f;
		movementComp->bShouldBounce = false;
		
		
	

}

// Called when the game starts or when spawned
void APlayerBullet::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(2.0f);

}

// Called every frame
void APlayerBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

