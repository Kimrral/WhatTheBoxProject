// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "WTBoxGameInstance.generated.h"

/**
 * 
 */
USTRUCT()
struct FSessionInfo
{
	GENERATED_BODY()
	FString roomName;
	int32 currentPlayers;
	int32 maxPlayers;
	int32 gamePlayTime;
	int32 ping;
	int32 index;
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSearchResult, FSessionInfo, sessionInfo);

UCLASS()
class WHATTHEBOXPROJECT_API UWTBoxGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UWTBoxGameInstance();

	virtual void Init() override;

	FOnSearchResult searchResultDele;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class USessionSlotWidget> sessionSlot;
	IOnlineSessionPtr wtbSessionInterface;
	FName sessionID;
	TSharedPtr<FOnlineSessionSearch> sessionSearch;

	//세션이 나타날 최대 갯수
	UPROPERTY(EditDefaultsOnly, Category = GameSettings)
		int32 maxSearchCount = 20;

public:
	void CreatewtboxSession(FString roomName, int32 playerCount);
	void CreateMySessionServer(bool bIsSuccess);

	UFUNCTION()
	void OnCreateSessionComplete(FName sessionName, bool bIsSuccess);


	void FindwtbSessions();
	void OnFindSessionComplete(bool bWasSuccessful);

	void JoinwtbSessions(int32 sessionIndex);
	void OnJoinSessionComplete(FName sessionName, EOnJoinSessionCompleteResult::Type joinResult);
		
};
