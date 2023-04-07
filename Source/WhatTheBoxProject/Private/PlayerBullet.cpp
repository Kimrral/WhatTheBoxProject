// Fill out your copyright notice in the Description page of Project Settings.




#include "PlayerBullet.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
//#include "WhatTheBoxProjectCharacter.generated.h"
#include <GameFramework/ProjectileMovementComponent.h>

#include "BoxPlayer.h"
#include "Components/CapsuleComponent.h"
#include "Net/UnrealNetwork.h"
#include "WhatTheBoxProject/WhatTheBoxProjectCharacter.h"
// 점수를 위한 헤더추가
#include "GameFramework/PlayerState.h"
#include "GameFramework/GameState.h"

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

		SetReplicateMovement(true);
		SetReplicates(true);

}

void APlayerBullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetOwner() == nullptr)
	{
		return;
	}
	Character = Cast<AWhatTheBoxProjectCharacter>(OtherActor);

	if (OtherActor != GetOwner())
	{
		if (HasAuthority())
		{
			if (Character != nullptr && Character->GetController() != nullptr)
			{
				//if (Character->GetController()->IsLocalController() != false)
				//{
					if (Character->GetHealth() <= 1)
					{
						AWhatTheBoxProjectCharacter* myOwner = Cast<AWhatTheBoxProjectCharacter>(GetOwner());
						if (myOwner != nullptr)
						{
							myOwner->GetPlayerState()->SetScore(myOwner->GetPlayerState()->GetScore() + 1);
							UE_LOG(LogTemp, Warning, TEXT("%d"), myOwner->GetPlayerState()->GetScore());
						}
					}

					Character->ServerDamageProcess(-1);
					Destroy();
				//}
			}
		}
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

void APlayerBullet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APlayerBullet, meshComp);
}
