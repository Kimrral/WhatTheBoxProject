// Fill out your copyright notice in the Description page of Project Settings.


#include "KnifeDamageBox.h"
#include "Kismet/GameplayStatics.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "WhatTheBoxProject/WhatTheBoxProjectCharacter.h"

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
	Character = Cast<AWhatTheBoxProjectCharacter>(OtherActor);
	
	if (Character != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Knife Attaked"))
		Character->curHP-=1;
		if (Character->curHP <= 0)
		{
			FTimerHandle destroyTimerHandle;
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionParticle, Character->GetActorLocation(), FRotator::ZeroRotator, FVector(2), true);
			Character->BoxBodyComp->SetVisibility(false);
			Character->DestroyedBoxBodyComp->SetVisibility(true);
			

			GetWorld()->GetTimerManager().SetTimer(destroyTimerHandle, FTimerDelegate::CreateLambda([this]()->void
			{
				Character->Destroy();
				
			}), 1.5f, false);



		}
	}

}

