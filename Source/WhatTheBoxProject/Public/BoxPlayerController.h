// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BoxPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class WHATTHEBOXPROJECT_API ABoxPlayerController : public APlayerController
{
	GENERATED_BODY()
	

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UBoxMainWidget> mainWidget;
};
