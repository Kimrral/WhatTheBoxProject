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
			class UScrollBox* sbox_RoomList;

		UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
		class UButton* btn_KoreaServer;

	/*Room Creation Widget*/
		UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
			class UEditableText* editText_RoomName;
		UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
			class USlider* slider_MatchDurations;
		UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
			class USlider* slider_MaxPlayers;
		UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
			class UEditableText* text_MatchDurations;
		UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
			class UEditableText* text_MaxPlayersCount;
		UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
			class UButton* btn_CreateRoom02;
		UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
			class UButton* btn_CreateRoomCancel;

		UPROPERTY(EditAnywhere)
	TSubclassOf<class USessionSlotWidget> searchListSlot;

		class UWTBoxGameInstance* gameInstance;


private:
	UFUNCTION()
	void ClickPlay();

	UFUNCTION()
	void CancelCreation();

	UFUNCTION()
	void OnMoveSlider(float value);

	UFUNCTION()
	void CreateSession();

	UFUNCTION()
	void AddRoomSlot(FSessionInfo sessionInfo);
	
};
