// Fill out your copyright notice in the Description page of Project Settings.


#include "HW07PlayerController.h"
#include "EnhancedInputSubsystems.h"

AHW07PlayerController::AHW07PlayerController()
	: InputMappingContext(nullptr),
		MoveAction(nullptr),
		LookAction(nullptr),
		FlyAction(nullptr),
		RollAction(nullptr)
{
}

void AHW07PlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext,0);
			}
		}
	}
}


