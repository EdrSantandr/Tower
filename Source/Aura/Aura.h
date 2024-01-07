// Copyright Eder

#pragma once

#include "CoreMinimal.h"

#define CUSTOM_DEPTH_RED 250
//It's channel 1 because it's the first we created
#define ECC_Projectile ECollisionChannel::ECC_GameTraceChannel1
//It's channel 2 because it's the second we created
#define ECC_Target ECollisionChannel::ECC_GameTraceChannel2