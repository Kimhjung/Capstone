// Fill out your copyright notice in the Description page of Project Settings.


#include "MonAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"


void UMonAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());
	if (Monster)
	{
		Speed = Monster->GetCharacterMovement()->Velocity.Size2D();
		if (Monster->CurrentHP <= 0)
		{
			CurrentState = EMonsterState::Death;
		}
		else
		{
			CurrentState = Monster->CurrentState;
			BossSkill = Monster->BossSkill;
		}
		
	}

}
