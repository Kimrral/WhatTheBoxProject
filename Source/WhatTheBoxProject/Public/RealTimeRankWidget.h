// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RealTimeRankWidget.generated.h"

/**
 * 
 */
UCLASS()
class WHATTHEBOXPROJECT_API URealTimeRankWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "Score")
	class UTextBlock* text_PlayerID;
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "Score")
	class UTextBlock* text_PlayerScore;


};
