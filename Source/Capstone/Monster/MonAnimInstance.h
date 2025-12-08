// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Monster.h"
#include "MonAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API UMonAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	EMonsterState CurrentState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	EBossSkill BossSkill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	uint8 bIsDeath : 1;
};
