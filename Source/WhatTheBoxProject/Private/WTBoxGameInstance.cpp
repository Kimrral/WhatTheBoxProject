// Fill out your copyright notice in the Description page of Project Settings.


#include "WTBoxGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

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
		}
		
	}
}

void UWTBoxGameInstance::CreatewtboxSession(FString roomName)
{
	if(wtbSessionInterface != nullptr)
	{
		FOnlineSessionSettings sessionsettings;
		sessionsettings.bAllowInvites = true;
		sessionsettings.bAllowJoinInProgress = true;
		sessionsettings.bAllowJoinViaPresence = false;
		sessionsettings.bIsDedicated = false;
		sessionsettings.bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true : false;
		//sessionsettings.NumPublicConnections = playerCount;
		sessionsettings.Set(FName("Key_RoomName"), roomName);
		sessionsettings.bShouldAdvertise = true;
		wtbSessionInterface->CreateSession(0, sessionID, sessionsettings);
		sessionsettings.Set(FName("KEY_RoomName"), roomName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	}
}

void UWTBoxGameInstance::OnCreateSessionComplete(FName sessionName, bool bIsSuccess)
{
	FString result = bIsSuccess ? TEXT("Create Success wtbox Session") : TEXT("Failed Create wtboxSession");

	if(bIsSuccess)
	{
		GetWorld()->ServerTravel("/Game/KYEContents/Maps/LoginMap?Listen'");
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

void UWTBoxGameInstance::OnFindSessionComplete(bool bWasSuccessful)
{
	if(bWasSuccessful)
	{
		TArray<FOnlineSessionSearchResult> searchResults = sessionSearch->SearchResults;

		for(int32 i = 0; i < searchResults.Num(); i++)
		{
			FString roomName;
			searchResults[i].Session.SessionSettings.Get(FName("KEY_RoomName"), roomName);
			int32 maxPlayer = searchResults[i].Session.SessionSettings.NumPublicConnections;
			int32 currentPlayers = maxPlayer - searchResults[i].Session.NumOpenPublicConnections;
			int32 ping = searchResults[i].PingInMs;
			//searchResults.index = i;
			

		}
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
