// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ISteering.h"
#include "../AICharacter.h"

/**
 * 
 */
class MPV_PRACTICAS_API SteeringBehabiorAlign : public IISteering
{
public:
	SteeringBehabiorAlign();
	~SteeringBehabiorAlign();

    virtual TAccelerationParams GetSteering(const Params& _parameters) override;
};
