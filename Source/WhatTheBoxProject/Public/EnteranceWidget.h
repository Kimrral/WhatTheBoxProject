// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnteranceWidget.generated.h"

/**
 * 
 */
UCLASS()
class WHATTHEBOXPROJECT_API UEnteranceWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
		UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
		class UButton* btn_Play;

		UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
		class UButton* btn_Options;

		UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
		class UWidgetSwitcher* widgetSwitcher;

		UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
		class UButton* btn_KoreaServer;

private:
	UFUNCTION()
	void ClickPlay();


	
};
