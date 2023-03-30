// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "WTBoxGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class WHATTHEBOXPROJECT_API UWTBoxGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UWTBoxGameInstance();
	virtual void Init() override;

	IOnlineSessionPtr wtbSessionInterface;
	FName sessionID;
	TSharedPtr<FOnlineSessionSearch> sessionSearch;

	//세션이 나타날 최대 갯수
	UPROPERTY(EditDefaultsOnly, Category = GameSettings)
		int32 maxSearchCount = 20;

public:
	void CreatewtboxSession(FString roomName, int32 playerCount);

	UFUNCTION()
	void OnCreateSessionComplete(FName sessionName, bool bIsSuccess);

	void FindwtbSessions();
	
	void OnFindSessionComplete(bool bWasSuccessful);

	
};
