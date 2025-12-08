// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Monster.generated.h"

UENUM(BlueprintType)
enum class EMonsterState : uint8
{
	Normal = 0 UMETA(DisplayName = "Normal"),
	Chase = 1 UMETA(DisplayName = "Chase"),
	Battle = 2 UMETA(DisplayName = "Battle"),
	Death = 3 UMETA(DisplayName = "Death")
};

UENUM(BlueprintType)
enum class EBossSkill : uint8
{
	Attack = 0 UMETA(DisplayName = "Attack"),	
	Skiil = 10 UMETA(DisplayName = "Skill_10")
};

UCLASS()
class CAPSTONE_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	float CurrentHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	float MaxHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	EMonsterState CurrentState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	EBossSkill BossSkill;

	void SetState(EMonsterState NewState);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	void DoDeadEnd();

	UFUNCTION(BlueprintCallable)
	void DoDead();

	UFUNCTION(BlueprintCallable)
	virtual void SpawnHitEffect(FHitResult Hit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	TObjectPtr<UParticleSystem> BloodEffect;

	UFUNCTION(BlueprintCallable)
	void ChangeSpeed(float NewMaxSpeed);

	FORCEINLINE const EMonsterState GetCurrentState() { return CurrentState; }
};
