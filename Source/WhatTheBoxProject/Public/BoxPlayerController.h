// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BoxPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class WHATTHEBOXPROJECT_API ABoxPlayerController : public APlayerController
{
	GENERATED_BODY()
	



public:
	ABoxPlayerController();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	// 메인 위젯
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UBoxMainWidget> mainWidget;
	UPROPERTY(EditAnywhere)
	class UBoxMainWidget* Main_UI;

// 	// Enterance widget
// 	UPROPERTY(EditAnywhere)
// 	TSubclassOf<class UEnteranceWidget> EnterWidget;
// 	UPROPERTY(EditAnywhere)
// 	class UEnteranceWidget* Enter_UI;

	// Gamemodebase 
	UPROPERTY(BlueprintReadWrite, Category = "GameMode")
	class AWhatTheBoxGameModeBase* GM;

	// WTB게임인스턴스
	UPROPERTY()
	class UWTBoxGameInstance* BoxInstance;

	UFUNCTION(Server, Unreliable)
	void ServerSetName(const FString& name);
};
