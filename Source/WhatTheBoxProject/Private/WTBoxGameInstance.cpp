// Fill out your copyright notice in the Description page of Project Settings.


#include "WTBoxGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "TimerActor.h"


UWTBoxGameInstance::UWTBoxGameInstance()
{
	
}

void UWTBoxGameInstance::Init()
{
	Super::Init();

	IOnlineSubsystem* subsys = IOnlineSubsystem::Get();
	if(subsys)
	{
		wtbSessionInterface = subsys->GetSessionInterface();
		if(wtbSessionInterface)
		{
			wtbSessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UWTBoxGameInstance::OnCreateSessionComplete);
			wtbSessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UWTBoxGameInstance::OnFindSessionComplete);
			wtbSessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UWTBoxGameInstance::OnJoinSessionComplete);
		}
		/*¿¬°á ÇÃ·§Æû È®ÀÎ¿ë*/
		FString platformName = subsys->GetSubsystemName().ToString();
		UE_LOG(LogTemp, Warning, TEXT("PlatformName : %s"), *platformName);
		
	}
}

void UWTBoxGameInstance::CreatewtboxSession(FString roomName, int32 playerCount, int32 matchDurations)
{
	if(wtbSessionInterface != nullptr)
	{
		FOnlineSessionSettings sessionsettings;
		sessionsettings.bAllowInvites = true;
		sessionsettings.bAllowJoinInProgress = true;
		sessionsettings.bAllowJoinViaPresence = true;
		sessionsettings.bIsDedicated = false;
		sessionsettings.bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true : false;
		sessionsettings.NumPublicConnections = playerCount;
		sessionsettings.bShouldAdvertise = true;
		sessionsettings.Set(FName("KEY_RoomName"), roomName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
		sessionsettings.bShouldAdvertise = true;
		wtbSessionInterface->CreateSession(0, sessionID, sessionsettings);
	}
	
}

void UWTBoxGameInstance::OnCreateSessionComplete(FName sessionName, bool bIsSuccess)
{
	FString result = bIsSuccess ? TEXT("Create Success wtbox Session") : TEXT("Failed Create wtboxSession");

	if(bIsSuccess)
	{
		GetWorld()->ServerTravel("/Game/KHJContents/Maps/KHJTestMap?Listen");
	}
}

void UWTBoxGameInstance::OnFindSessionComplete(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		TArray<FOnlineSessionSearchResult> searchResults = sessionSearch->SearchResults;

		for (int32 i = 0; i < searchResults.Num(); i++)
		{
			FSessionInfo searchSessionInfo;
			FString roomName;
			searchResults[i].Session.SessionSettings.Get(FName("KEY_RoomName"), roomName);
			searchSessionInfo.roomName = roomName;
			searchSessionInfo.gamePlayTime = GetWorld()->GetDeltaSeconds();
			searchSessionInfo.maxPlayers = searchResults[i].Session.SessionSettings.NumPublicConnections;
			searchSessionInfo.currentPlayers = searchSessionInfo.maxPlayers - searchResults[i].Session.NumOpenPublicConnections;
			searchSessionInfo.ping = searchResults[i].PingInMs;
			searchSessionInfo.index = i;
			

			searchResultDele.Broadcast(searchSessionInfo);
		}
	}
}

void UWTBoxGameInstance::FindwtbSessions()
{
	sessionSearch = MakeShareable(new FOnlineSessionSearch());
	sessionSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";
	sessionSearch->MaxSearchResults = maxSearchCount;
	sessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	wtbSessionInterface->FindSessions(0, sessionSearch.ToSharedRef());
}

void UWTBoxGameInstance::JoinwtbSessions(int32 sessionIndex)
{
	FOnlineSessionSearchResult selectedSession = sessionSearch->SearchResults[sessionIndex];

	wtbSessionInterface->JoinSession(0, sessionID, selectedSession);
}

void UWTBoxGameInstance::OnJoinSessionComplete(FName sessionName, EOnJoinSessionCompleteResult::Type joinResult)
{
	FString joinAddress;
	wtbSessionInterface->GetResolvedConnectString(sessionName, joinAddress);

	if (APlayerController* pc = GetWorld()->GetFirstPlayerController())
	{
		pc->ClientTravel(joinAddress, ETravelType::TRAVEL_Absolute);
	}
}


void UWTBoxGameInstance::CreateMySessionServer(bool bIsSuccess)
{
	FString result = bIsSuccess ? TEXT("Create WTBox Game Session") : TEXT("Daaaang...");
	if(bIsSuccess)
	{
		GetWorld()->ServerTravel("/Game/KHJContents/Maps/KHJTestMap?Listen");		
	}
}
