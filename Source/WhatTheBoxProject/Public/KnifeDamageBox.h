// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KnifeDamageBox.generated.h"

UCLASS()
class WHATTHEBOXPROJECT_API AKnifeDamageBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKnifeDamageBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=BoxSettings)
	class UBoxComponent* boxComp;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BoxSettings)
	class UParticleSystem* explosionParticle;

	class AWhatTheBoxProjectCharacter* Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USoundBase* explosionSound;

};
