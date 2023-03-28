// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerBullet.generated.h"

UCLASS()
class WHATTHEBOXPROJECT_API APlayerBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerBullet();

	UPROPERTY(EditAnywhere, Category = "Bullet Setting")
		class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, Category = "Bullet Setting")
		class USphereComponent* sphereComp;

	UPROPERTY(EditAnywhere, Category = "Bullet Setting")
		class UProjectileMovementComponent* movementComp;

		UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BoxSettings)
			class UParticleSystem* explosionParticle;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
