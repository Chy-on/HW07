#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HW07PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class HW07_API AHW07PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AHW07PlayerController();
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	UInputAction* FlyAction;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	UInputAction* RollAction;

	virtual void BeginPlay() override;
};
