// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ISteering.h"

/**
 * 
 */
class MPV_PRACTICAS_API SteeringBehabiorPathFollowing : public IISteering
{
public:
	SteeringBehabiorPathFollowing();
	~SteeringBehabiorPathFollowing();

    virtual TAccelerationParams GetSteering(const Params& _parameters) override;

    FVector GetNearestPointInPath(const Path& _parameters);

    virtual void SetSteeringBehavior(AAICharacter* _character) override;

    IISteering* arrival;
    IISteering* seek;

};
