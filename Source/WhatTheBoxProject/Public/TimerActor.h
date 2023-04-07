// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerActor.generated.h"

UCLASS()
class WHATTHEBOXPROJECT_API ATimerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

		// 메인 위젯
	UPROPERTY(BlueprintReadWrite, Category = "Widget" , Replicated)
		class UBoxMainWidget* Main_UI;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UBoxMainWidget> MainWidget;

	// 게임오버위젯
	UPROPERTY(BlueprintReadWrite, Category = "Widget", Replicated)
		class UGameOverWidget* GameOver_UI;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameOverWidget> GameOverWidget;

	// 플레이어
	UPROPERTY(BlueprintReadWrite, Category = "Player")
		class AWhatTheBoxProjectCharacter* Player;

	// 게임모드베이스
	UPROPERTY(BlueprintReadWrite, Category = "Player")
		class AWhatTheBoxGameModeBase* GM;

		// 시간 초
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		int32 GameTimeSec = 1;
	// 시간 분
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		int32 GameTimeMin = 5;

		public:
	// 게임 시작시, 5분 카운트 다운
	void GameStartCountDown();
	
	//게임 시간 끝나면 결과창 팝업
//	void ShowResultUI();

	UFUNCTION(Server, UnReliable, WithValidation)
	void Server_GameStartCountDown();

	UFUNCTION(Server, UnReliable)
	void Server_UpdateTimerUI();

	UFUNCTION(NetMulticast, UnReliable)
	void Multicast_UpdateTimerUI();

	
	UFUNCTION(Server, UnReliable)
	void Server_ResultUI();
	
	UFUNCTION(NetMulticast, UnReliable)
	void Multicast_ResultUI();


	// GetLifetimeReplicatedprops
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated)
	FTimerHandle TimerHandle;
	FTimerHandle PlayTimeCount;

};
