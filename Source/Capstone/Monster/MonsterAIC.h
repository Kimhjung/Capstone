// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Monster.h"
#include "MonsterAIC.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API AMonsterAIC : public AAIController
{
	GENERATED_BODY()

public:
	AMonsterAIC();

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Component)
	TObjectPtr<UAIPerceptionComponent> Perception;

	UFUNCTION()
	void ProcessPerception(const TArray<AActor*>& UpdatedActors);

	UFUNCTION()
	void ProcessActorPerception(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	void ProcessPerceptionForget(AActor* Actor);

	UFUNCTION()
	void ProcessActorPerceptionInfo(const FActorPerceptionUpdateInfo& UpdateInfo);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	TObjectPtr<UBehaviorTree> RunBTAsset;

	void SetState(EMonsterState NewState);
};
