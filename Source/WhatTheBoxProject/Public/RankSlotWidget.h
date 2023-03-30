// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RankSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class WHATTHEBOXPROJECT_API URankSlotWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_pingNumber;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* text_pingNumber;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_playerName;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* text_playerName;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_finalScore;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* text_finalScore;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_finalKillScore;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* text_finalKillScore;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_finalDeaths;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* text_finalDeaths;



};
