#include "MyPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "HW07PlayerController.h"

AMyPawn::AMyPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(CapsuleComp);
	CapsuleComp->SetSimulatePhysics(false);
	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComp->SetupAttachment(CapsuleComp);
	SkeletalMeshComp->SetSimulatePhysics(false);
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(CapsuleComp);
	SpringArmComp->TargetArmLength = 300;
	SpringArmComp->bUsePawnControlRotation = true;
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp,USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	MovementSpeed = 500.0f;
	LookSensitivity = 100.0f;
}

void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AHW07PlayerController* PlayerController = Cast<AHW07PlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&AMyPawn::Move
				);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&AMyPawn::Look
				);
			}

			if (PlayerController->FlyAction)
			{
				EnhancedInput->BindAction(
					PlayerController->FlyAction,
					ETriggerEvent::Triggered,
					this,
					&AMyPawn::Fly
				);
			}

			if (PlayerController->RollAction)
			{
				EnhancedInput->BindAction(
					PlayerController->RollAction,
					ETriggerEvent::Triggered,
					this,
					&AMyPawn::Roll
				);
			}
		}
	}
}

void AMyPawn::Move(const FInputActionValue& value)
{
	const FVector2D MoveInput = value.Get<FVector2D>();
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddActorLocalOffset(GetActorForwardVector()*MoveInput.X*MovementSpeed*DeltaTime);
	}
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddActorLocalOffset(GetActorRightVector()*MoveInput.Y*MovementSpeed*DeltaTime);
	}
}


void AMyPawn::Look(const FInputActionValue& value)
{
	const FVector2D LookInput = value.Get<FVector2D>();
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	float NewYaw = LookInput.X * LookSensitivity * DeltaTime;
	float NewPitch = LookInput.Y * LookSensitivity * DeltaTime;

	if (!FMath::IsNearlyZero(NewYaw))
	{
		AddActorLocalRotation(FRotator(0.0f,NewYaw,0.0f));
	}

	if (!FMath::IsNearlyZero(NewPitch))
	{
		FRotator CurrentRotation = GetActorRotation();
		float LimitedPitch = CurrentRotation.Pitch + NewPitch;
		LimitedPitch = FMath::Clamp(LimitedPitch, -90.0f, 90.0f);
		SetActorRotation(FRotator(LimitedPitch,CurrentRotation.Yaw,CurrentRotation.Roll));
	}
}

void AMyPawn::Fly(const FInputActionValue& value)
{
	const float FlyInput = value.Get<float>();
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	if (!FMath::IsNearlyZero(FlyInput))
	{
		AddActorLocalOffset(FVector(0,0,FlyInput*MovementSpeed*DeltaTime));
	}
}

void AMyPawn::Roll(const FInputActionValue& value)
{
	const float RollInput = value.Get<float>();
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	float NewRoll = RollInput*LookSensitivity*DeltaTime;
	AddActorLocalRotation(FRotator(0.0f,0.0f,NewRoll));
}



