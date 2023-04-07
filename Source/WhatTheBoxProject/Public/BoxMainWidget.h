// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BoxMainWidget.generated.h"


// 플레이어 정보 구조체 공간
// USTRUCT(BlueprintType)
// struct FPlayerInfo
// {
// 	GENERATED_BODY()
// 
// 	UPROPERTY(BlueprintReadOnly)
// 	FString name;
// 	UPROPERTY(BlueprintReadOnly)
// 	float score;
// };

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
	// 킬 로그
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* TXT_KillLog;

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
public:
	// 게임모드
	UPROPERTY(BlueprintReadWrite, Category = "Settings")
		class AWhatTheBoxGameModeBase* GM;
	// 플레이어 컨트롤러
	UPROPERTY(BlueprintReadWrite, Category = "Settings")
		class ABoxPlayerController* PC;
// 	// 게임스테이트
// 	UPROPERTY(BlueprintReadWrite, Category = "Settings")
// 	class ABoxGameStateBase* GS;

	class UWTBoxGameInstance* gameInstance;

	//플레이어 점수정보 전역변수로 빼준 것
	int32 playerScore;
	FString playerName;

	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "Score")
	class UTextBlock* text_PlayerID;
	/*UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "Score")
	class UTextBlock* text_PlayerScore;*/

		// 타이머액터
		UPROPERTY(BlueprintReadWrite, Category = "Timer")
			class ATimerActor* inGameTimer;

		// 플레이어
		UPROPERTY()
		class AWhatTheBoxProjectCharacter* Player;
	//--------------------순위ui부분--------------------//
	UPROPERTY(EditAnywhere, meta = (BindWidget) , Category = "Score")
	class UScrollBox* sbox_RankBox;

	UPROPERTY(EditAnywhere, Category = "Score")
	TSubclassOf <class URealTimeRankWidget> realTimeRank;
	
	//랭크 슬롯 추가하기
	URealTimeRankWidget* rankSlot;


	UPROPERTY()
	TArray <UTextBlock*> textblockRankIdArray;
	UPROPERTY()
	TArray <UTextBlock*> textblockRankScoreArray;
	TArray <int> tempScoreArray;

	FString myID;
	FString winnerID;

	int tempScore1;
	int tempScore2;
	int tempScore3;
	int tempScore4;

	//--------------------순위ui부분--------------------//
// 함수 부분
	// 남은 시간 텍스트출력
	void PrintRemainingTime(int32 min, int32 sec);
	// 플레이어 죽을 시, 킬로그 출력
	void PrintKillLog(FString Killer, FString Victim);
	// 채팅 인풋에 채팅치면 채팅로그에 출력
	void PrintChatLog(FString Chat);
	// 채팅 입력창에 엔터키 누르면 이벤트 함수
	UFUNCTION()
	void OnChatInputEnter();

	void RankingRefresh();

	void ResetScoreBeforeGameEnd();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
	//UFUNCTION()
	//void	UpdateKillLog(const TArray<FString>& KillLog)
};

// 	// 채팅 입력창
// 	UPROPERTY(EditAnywhere, meta = (BindWidget))
// 	class UEditableTextBox* TXT_ChatInput;
// 
// 	// 채팅로그
// 	UPROPERTY(EditAnywhere, meta = (BindWidget))
// 	class UTextBlock* TXT_ChatLog;