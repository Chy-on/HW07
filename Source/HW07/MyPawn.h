#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;

UCLASS()
class HW07_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:

	AMyPawn();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")
	UCapsuleComponent* CapsuleComp;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")
	USkeletalMeshComponent* SkeletalMeshComp;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	UCameraComponent* CameraComp;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Properties")
	float MovementSpeed;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Properties")
	float LookSensitivity;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);
	UFUNCTION()
	void Fly(const FInputActionValue& value);
	UFUNCTION()
	void Roll(const FInputActionValue& value);
};
