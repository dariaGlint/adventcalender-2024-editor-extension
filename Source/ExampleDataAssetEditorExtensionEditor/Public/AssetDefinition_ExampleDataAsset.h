// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetDefinition.h"
#include "ExampleDataAsset.h"
#include "AssetDefinition_ExampleDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class EXAMPLEDATAASSETEDITOREXTENSIONEDITOR_API UAssetDefinition_ExampleDataAsset : public UAssetDefinition
{
	GENERATED_BODY()
public:
	virtual FText GetAssetDisplayName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_ExampleDataAsset", "ExampleDataAsset"); }
	virtual FLinearColor GetAssetColor() const override { return FLinearColor(FColor(162, 160, 35)); }

	virtual TSoftClassPtr<UObject> GetAssetClass() const override { return UExampleDataAsset::StaticClass(); }
	virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;
};
