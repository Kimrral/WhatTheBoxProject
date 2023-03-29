// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BoxMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class WHATTHEBOXPROJECT_API UBoxMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// 남은 시간 초 텍스트
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* TXT_GameTimeSec;
	// 남은 시간 분 텍스트
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* TXT_GameTimeMin;

// 	// 채팅 입력창
// 	UPROPERTY(EditAnywhere, meta = (BindWidget))
// 	class UEditableTextBox* TXT_ChatInput;
// 
// 	// 채팅로그
// 	UPROPERTY(EditAnywhere, meta = (BindWidget))
// 	class UTextBlock* TXT_ChatLog;

	// 킬 로그
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* TXT_KillLog;

	virtual void NativeConstruct() override;
	public:
		// 게임모드
		UPROPERTY(BlueprintReadWrite, Category = "GameMode")
			class AWhatTheBoxGameModeBase* GM;
		// 플레이어
		UPROPERTY()
		class AWhatTheBoxProjectCharacter* Player;

	// 남은 시간 텍스트출력
	void PrintRemainingTime();
	// 플레이어 죽을 시, 킬로그 출력
	void PrintKillLog(FString Killer, FString Victim);
	// 채팅 인풋에 채팅치면 채팅로그에 출력
	void PrintChatLog(FString Chat);
	// 채팅 입력창에 엔터키 누르면 이벤트 함수
	UFUNCTION()
		void OnChatInputEnter();
	//UFUNCTION()
	//void	UpdateKillLog(const TArray<FString>& KillLog)
};
