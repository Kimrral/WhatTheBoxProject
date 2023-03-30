// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class WHATTHEBOXPROJECT_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class URankSlotWidget> rankSlotWidget;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UScrollBox* sbox_RankList;

	UFUNCTION()
	void AddNewSlot(float ping, FString playerName, int32 score, int32 killSocre, int32 death);

	
};
