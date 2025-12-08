// Fill out your copyright notice in the Description page of Project Settings.


#include "MonAIC.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "../Base/BaseChar.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster.h"

AMonAIC::AMonAIC()
{
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));

	UAISenseConfig_Sight* Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));
	Sight->SightRadius = 800.0f;
	Sight->LoseSightRadius = 900.0f;
	Sight->PeripheralVisionAngleDegrees = 45.f;
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;
	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(*Sight->GetSenseImplementation());
}

void AMonAIC::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//ensure(RunBTAsset); //Log
	//check(RunBTAsset); //우선 종료 후 로그 확인
	if (RunBTAsset)
	{
		RunBehaviorTree(RunBTAsset);
	}

	
	Perception->OnTargetPerceptionForgotten.AddDynamic(this, &AMonAIC::ProcessPerceptionForget);
	Perception->OnTargetPerceptionUpdated.AddDynamic(this, &AMonAIC::ProcessActorPerception);
	SetGenericTeamId(3);
}

void AMonAIC::OnUnPossess()
{
	Super::OnUnPossess();
}

void AMonAIC::ProcessPerception(const TArray<AActor*>& UpdatedActors)
{
	for (auto Actor : UpdatedActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("ProcessPerception %s"), *Actor->GetName());
	}
}

void AMonAIC::ProcessActorPerception(AActor* Actor, FAIStimulus Stimulus)
{
	//시야
	if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
	{
		if (Stimulus.WasSuccessfullySensed()) //봤을때
		{
			ABaseChar* Player = Cast<ABaseChar>(Actor);
			AMonster* Monster = Cast<AMonster>(GetPawn());
			if (Player && Monster)
			{
				if (Monster->GetCurrentState() == EMonsterState::Death)
				{
					return;
				}

				Blackboard->SetValueAsObject(TEXT("Target"), Player);
				SetState(EMonsterState::Chase);
				Monster->SetState(EMonsterState::Chase);
				Monster->ChangeSpeed(400.0f);
			}
		}
		else // 못봤을때
		{
			ABaseChar* Player = Cast<ABaseChar>(Actor);
			AMonster* Monster = Cast<AMonster>(GetPawn());
			if (Player && Monster)
			{
				if (Monster->GetCurrentState() == EMonsterState::Death)
				{
					return;
				}

				Blackboard->SetValueAsObject(TEXT("Target"), nullptr);
				//Blackboard->SetValueAsVector(TEXT("Destination"), Stimulus.StimulusLocation);
				SetState(EMonsterState::Normal);
				Monster->SetState(EMonsterState::Normal);
				Monster->ChangeSpeed(80.0f);
			}
		}
	}
}

void AMonAIC::ProcessPerceptionForget(AActor* Actor)
{
	UE_LOG(LogTemp, Warning, TEXT("ProcessPerceptionForget %s"), *Actor->GetName());

	//아까 봤던 곳 잊었을 때
	ABaseChar* Player = Cast<ABaseChar>(Actor);
	AMonster* Monster = Cast<AMonster>(GetPawn());
	if (Player && Monster)
	{
		if (Monster->GetCurrentState() == EMonsterState::Death)
		{
			return;
		}

		Blackboard->SetValueAsObject(TEXT("Target"), nullptr);
		SetState(EMonsterState::Normal);
		Monster->SetState(EMonsterState::Normal);
		Monster->ChangeSpeed(80.0f);
	}
}

void AMonAIC::ProcessActorPerceptionInfo(const FActorPerceptionUpdateInfo& UpdateInfo)
{
	UE_LOG(LogTemp, Warning, TEXT("ProcessPerceptionForget %s"), *(UpdateInfo.Target->GetName()));
}

void AMonAIC::SetState(EMonsterState NewState)
{
	Blackboard->SetValueAsEnum(TEXT("CurrentState"), (uint8)(NewState));
}
