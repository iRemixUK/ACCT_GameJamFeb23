// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomBasePawn.h"

// Sets default values
ACustomBasePawn::ACustomBasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACustomBasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACustomBasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bHasMoved = false;
}

// Called to bind functionality to input
void ACustomBasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}

void ACustomBasePawn::Move(const FVector3f& Direction, const float DeltaTime)
{
}

void ACustomBasePawn::OnColliderLeave_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ACustomBasePawn::OnColliderEnter_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ACustomBasePawn::OnInteractWithPlayer_Implementation()
{
}

void ACustomBasePawn::Attack_Implementation()
{
}

void ACustomBasePawn::Die_Implementation()
{
}

