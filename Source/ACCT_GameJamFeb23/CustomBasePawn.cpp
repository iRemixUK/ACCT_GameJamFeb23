// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomBasePawn.h"
#include "NiagaraFunctionLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ACustomBasePawn::ACustomBasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	SetRootComponent(CapsuleCollider);

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	Collider->SetupAttachment(CapsuleCollider);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ACustomBasePawn::OnColliderEnter);
	Collider->OnComponentEndOverlap.AddDynamic(this, &ACustomBasePawn::OnColliderLeave);

	PlaneFront = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneFront"));
	PlaneFront->SetupAttachment(CapsuleCollider);

	PlaneBack = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneBack"));
	PlaneBack->SetupAttachment(CapsuleCollider);
}

// Called when the game starts or when spawned
void ACustomBasePawn::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(SpriteSheetMaterial))
		MaterialInstance = UMaterialInstanceDynamic::Create(SpriteSheetMaterial, NULL);

	if (IsValid(PlaneFront))
		PlaneFront->SetMaterial(0, MaterialInstance);

	if (IsValid(PlaneBack))
		PlaneBack->SetMaterial(0, MaterialInstance);

	if (IsValid(CharacterSpritesheet) && IsValid(MaterialInstance))
		MaterialInstance->SetTextureParameterValue("SpriteSheet", CharacterSpritesheet);
}

void ACustomBasePawn::UpdateMaterial(const float DeltaTime)
{
	if (bHasMoved)
	{
		AnimationFrameTimer += DeltaTime;
		if (AnimationFrameTimer > AnimationFrameTimeSpeed)
		{
			AnimationFrameTimer = 0.f;
			CurrentAnimationFrame++;
			CurrentAnimationFrame %= FramesInCycle;
		}
	}
	else
	{
		AnimationFrameTimer = 0.f;
		CurrentAnimationFrame = -1;
	}

	if (IsValid(MaterialInstance))
	{
		MaterialInstance->SetScalarParameterValue("Direction", static_cast<float>(CompassDirection));
		MaterialInstance->SetScalarParameterValue("AnimationFrame", CurrentAnimationFrame);
		MaterialInstance->SetScalarParameterValue("MaxFrames", FramesInCycle);
	}
}

// Called every frame
void ACustomBasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateMaterial(DeltaTime);

	bHasMoved = false;
}

// Called to bind functionality to input
void ACustomBasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACustomBasePawn::Damage_Implementation(const int ToDamage)
{
	Life = Life - ToDamage;
	if (Life <= 0)
		Die();
}

void ACustomBasePawn::Heal_Implementation(const int ToHeal)
{
	Life = FMath::Min(Life + ToHeal, MaxLife);
}

void ACustomBasePawn::Move(const FVector& Direction, const float DeltaTime)
{
	if (bHasMoved || Direction.Length() < FLT_EPSILON)
		return;

	if (IsValid(CharacterMovementSound))
		UGameplayStatics::PlaySoundAtLocation(this, CharacterMovementSound, GetActorLocation());

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
	if (IsValid(DieParticles))
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, DieParticles, GetActorLocation());

	Destroy();
}

