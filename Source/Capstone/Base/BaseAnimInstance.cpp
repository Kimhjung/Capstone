// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAnimInstance.h"
#include "BaseChar.h"
#include "Gameframework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ABaseChar* Char = Cast<ABaseChar>(TryGetPawnOwner());
	if(Char)
	{
		GroundSpeed = Char->GetCharacterMovement()->Velocity.Size2D();
		bSprint = Char->bSprint;
		Direction = UKismetAnimationLibrary::CalculateDirection(Char->GetCharacterMovement()->Velocity, Char->GetActorRotation());
		AimYaw = Char->GetBaseAimRotation().Yaw;
		AimPitch = Char->GetBaseAimRotation().Pitch;
		bAiming = Char->bAiming;
	}
}
