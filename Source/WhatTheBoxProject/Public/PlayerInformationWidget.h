// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerInformationWidget.generated.h"

/**
 * 
 */
UCLASS()
class WHATTHEBOXPROJECT_API UPlayerInformationWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class URadialSlider* HPSlider;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
		class URadialSlider* BulSlider;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UImage* CrosshairImage;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* curBulText;	


protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	class AWhatTheBoxProjectCharacter* player;
};
