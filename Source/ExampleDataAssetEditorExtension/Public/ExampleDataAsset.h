// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ExampleDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class EXAMPLEDATAASSETEDITOREXTENSION_API UExampleDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> Values;
};
