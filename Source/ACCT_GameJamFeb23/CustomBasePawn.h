// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CustomBasePawn.generated.h"

class USphereComponent;
class UCapsuleComponent;
class UNiagaraSystem;

UENUM()
enum class EDirection
{
	North,
	South,
	East,
	West
};

UCLASS(Blueprintable)
class ACCT_GAMEJAMFEB23_API ACustomBasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACustomBasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float MockCoro_FlipAnimation_ZAngle = 0.0f;
	bool MockCoro_FlipAnimation_TurningForward = false;
	bool MockCoro_FlipAnimation(const float DeltaTime);

	UPROPERTY(EditAnywhere)
		int Life = 100;

	UPROPERTY(EditAnywhere)
		int MaxLife = 100;

	UPROPERTY(EditAnywhere)
		int DamagePower = 5;

	UPROPERTY(EditAnywhere)
		float MovementSpeed = 1.0f;

	// SpriteSheet based
	UPROPERTY(VisibleAnywhere)
		int CurrentAnimationFrame = -1;

	UPROPERTY(VisibleAnywhere)
		float AnimationFrameTimer = 0.f;

	UPROPERTY(VisibleAnywhere)
		EDirection CompassDirection = EDirection::South;

	UPROPERTY(VisibleAnywhere)
		bool bHasMoved = false;

private:
	UFUNCTION()
		void UpdateMaterial(const float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Functionality
	UFUNCTION(BlueprintNativeEvent)
		void Die();

	UFUNCTION(BlueprintNativeEvent)
		void Attack();

	UFUNCTION(BlueprintNativeEvent)
		void Damage(const int ToDamage);

	UFUNCTION(BlueprintNativeEvent)
		void Heal(const int ToHeal);

	UFUNCTION(BlueprintNativeEvent)
		void OnInteractWithPlayer();

	UFUNCTION(BlueprintCallable)
		void Move(const FVector& Direction, const float DeltaTime);

	// Events
	UFUNCTION(BlueprintNativeEvent)
		void OnColliderEnter(
			UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult
		);

	UFUNCTION(BlueprintNativeEvent)
		void OnColliderLeave(
			UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex
		);

	// Components Hierarchy
	UPROPERTY(VisibleAnywhere)
		USphereComponent* Collider;

	UPROPERTY(VisibleAnywhere)
		UCapsuleComponent* CapsuleCollider;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* PlaneFront;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* PlaneBack;

	// Assets
	UPROPERTY(EditAnywhere)
		UTexture* CharacterSpritesheet;

	UPROPERTY(EditAnywhere)
		UMaterial* SpriteSheetMaterial;

	UPROPERTY(EditAnywhere)
		USoundBase* CharacterMovementSound;

	UPROPERTY(EditAnywhere)
		UNiagaraSystem* DieParticles;

	// Assets Instances
	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* MaterialInstance;

	// Properties
	UPROPERTY(EditAnywhere)
		int FramesInCycle = 4;

	UPROPERTY(EditAnywhere)
		float AnimationFrameTimeSpeed = 0.1f;
};
