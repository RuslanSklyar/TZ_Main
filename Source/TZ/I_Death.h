#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "I_Death.generated.h"

// --------------------------------------------------------------------------------

UINTERFACE(MinimalAPI)
class UI_Death : public UInterface
{
	GENERATED_BODY()
};

// --------------------------------------------------------------------------------
class TZ_API II_Death
{
	GENERATED_BODY()

public:
	virtual void Death() = 0;
	virtual bool GetIsDead() = 0;
};
