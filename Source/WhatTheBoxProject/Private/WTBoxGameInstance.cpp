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

void UWTBoxGameInstance::CreatewtboxSession(FString roomName, int32 playerCount)
{
	if(wtbSessionInterface != nullptr)
	{
		FOnlineSessionSettings sessionsettings;
		sessionsettings.bAllowInvites = true;
		sessionsettings.bAllowJoinInProgress = true;
		sessionsettings.bAllowJoinViaPresence = false;
		sessionsettings.bIsDedicated = false;
		sessionsettings.bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true : false;
		sessionsettings.NumPublicConnections = playerCount;
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
	wtbSessionInterface->FindSessions(0, sessionSearch.ToSharedRef());
}

void UWTBoxGameInstance::OnFindSessionComplete(bool bWasSuccessful)
{
}
