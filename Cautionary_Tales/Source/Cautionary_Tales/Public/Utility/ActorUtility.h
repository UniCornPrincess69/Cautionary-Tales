// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

template <typename T>
T* FindObject(const FString ObjPath)
{
	return ConstructorHelpers::FObjectFinder<T>(*ObjPath).Object;
}

