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

void ACustomBasePawn::Move(const FVector& Direction, const float DeltaTime)
{
	bHasMoved = true;

	constexpr float ToDeg = 180 / 3.14;
	const auto NorthVector = FVector(1.f, 0.f, 0.f);
	const double Angle = acosf(NorthVector.Dot(Direction.GetSafeNormal())) * ToDeg;
	
	if (Angle > 45.f && Angle < 135.f)
		CompassDirection = Direction.Y < 0.f ? EDirection::West : EDirection::East;
	else
		CompassDirection = Direction.X < 0.f ? EDirection::South : EDirection::North;

	const auto CurrentLocation = GetActorLocation();
	SetActorLocation(CurrentLocation + Direction * MovementSpeed * DeltaTime);
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

