
#pragma once
#include "CoreMinimal.h"
#include "UpgradeEffectBase.generated.h"

UCLASS(Abstract, BlueprintType, Blueprintable)
class ZOMBIEGAME_API UUpgradeEffectBase : public UObject
{
    GENERATED_BODY()

public:
    virtual void ApplyUpgrade(AActor* TargetActor, float EffectValue) PURE_VIRTUAL(UUpgradeEffectBase::ApplyUpgrade, );
};