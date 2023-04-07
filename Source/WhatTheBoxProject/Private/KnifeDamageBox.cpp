// Fill out your copyright notice in the Description page of Project Settings.


#include "KnifeDamageBox.h"
#include "Kismet/GameplayStatics.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Net/UnrealNetwork.h"
#include "WhatTheBoxProject/WhatTheBoxProjectCharacter.h"
// 점수추가
#include "GameFramework/PlayerState.h"

// Sets default values
AKnifeDamageBox::AKnifeDamageBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(7.0f));
	boxComp->SetCollisionProfileName(FName("OverlapAll"));

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AKnifeDamageBox::OnOverlap);
	boxComp->SetGenerateOverlapEvents(true);

	SetReplicateMovement(true);
	SetReplicates(true);

}

// Called when the game starts or when spawned
void AKnifeDamageBox::BeginPlay()
{
	Super::BeginPlay();



	this->SetLifeSpan(0.01f);
}

// Called every frame
void AKnifeDamageBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AKnifeDamageBox::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("aaa"));
	Character = Cast<AWhatTheBoxProjectCharacter>(OtherActor);

		if (HasAuthority())
		{
				Character->ServerDamageProcess(-3);
				Destroy();
		}

}

void AKnifeDamageBox::ChangeBoxMesh()
{
	ServerChangeBoxMesh();
}

void AKnifeDamageBox::ServerChangeBoxMesh_Implementation()
{
	MulticastChangeBoxMesh();
}

void AKnifeDamageBox::MulticastChangeBoxMesh_Implementation()
{
	Character->BoxBodyComp->SetVisibility(false);
	Character->DestroyedBoxBodyComp->SetVisibility(true);
}

void AKnifeDamageBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AKnifeDamageBox, boxComp);
}
