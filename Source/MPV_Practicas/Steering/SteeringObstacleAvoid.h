// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ISteering.h"

/**
 * 
 */
class MPV_PRACTICAS_API SteeringObstacleAvoid : public IISteering
{
public:
	SteeringObstacleAvoid();
	~SteeringObstacleAvoid();



  virtual TAccelerationParams GetSteering(const Params& _parameters);


};
