// Fill out your copyright notice in the Description page of Project Settings.




#include "PlayerBullet.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
//#include "WhatTheBoxProjectCharacter.generated.h"
#include <GameFramework/ProjectileMovementComponent.h>

#include "Components/CapsuleComponent.h"
#include "WhatTheBoxProject/WhatTheBoxProjectCharacter.h"

// Sets default values
APlayerBullet::APlayerBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

		
		sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
		SetRootComponent(sphereComp);

		sphereComp->SetSphereRadius(8.0f);
		sphereComp->SetCollisionProfileName(TEXT("OverlapAll"));

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

		sphereComp->OnComponentBeginOverlap.AddDynamic(this, &APlayerBullet::OnOverlap);
		sphereComp->SetGenerateOverlapEvents(true);
	

}

void APlayerBullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Character = Cast<AWhatTheBoxProjectCharacter>(OtherActor);
	if(HasAuthority())
	{
	if(Character!=nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Bullet Attacked"))
		Character->curHP--;
		Character->BoxHit();
		if(Character->curHP<=0)			
		{
			FTimerHandle destroyTimerHandle;
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionParticle, Character->GetActorLocation(), FRotator::ZeroRotator, FVector(2), true);
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), explosionSound, Character->BoxBodyComp->GetComponentLocation(), FRotator::ZeroRotator, 0.5, 1, 0, nullptr, nullptr, true);

			Character->BoxBodyComp->SetVisibility(false);
			Character->DestroyedBoxBodyComp->SetVisibility(true);
			

			GetWorld()->GetTimerManager().SetTimer(destroyTimerHandle, FTimerDelegate::CreateLambda([this]()->void
				{
					Character->Destroy();

				}), 1.5f, false);
		}
	}
	this->Destroy();
	}
	
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

