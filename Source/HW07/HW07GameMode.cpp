// Fill out your copyright notice in the Description page of Project Settings.


#include "HW07GameMode.h"

#include "HW07PlayerController.h"
#include "MyPawn.h"

AHW07GameMode::AHW07GameMode()
{
	DefaultPawnClass = AMyPawn::StaticClass();
	PlayerControllerClass = AHW07PlayerController::StaticClass();
}
