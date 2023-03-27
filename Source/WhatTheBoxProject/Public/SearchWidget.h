// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SearchWidget.generated.h"

/**
 * 
 */
UCLASS()
class WHATTHEBOXPROJECT_API USearchWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UEditableText* editText_RoomName;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_QuickPlay;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_CreateRoom;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UButton* btn_BackToMenu;

	class UEnteranceWidget* enteranceWidget;

private:
	UFUNCTION()
		void BackToMenu();

};
