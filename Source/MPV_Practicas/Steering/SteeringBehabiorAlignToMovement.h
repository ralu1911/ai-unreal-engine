// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SteeringBehabiorAlign.h"
#include "SteeringBehabiorArrival.h"
#include "../AICharacter.h"
/**
 * 
 */
class MPV_PRACTICAS_API SteeringBehabiorAlignToMovement : public IISteering
{
public:
	SteeringBehabiorAlignToMovement();
	~SteeringBehabiorAlignToMovement();

    virtual TAccelerationParams GetSteering(const Params& _parameters) override;

    virtual void SetSteeringBehavior(AAICharacter* _character);

    SteeringBehabiorArrival* m_pArrivalSteeringBehabior;
    SteeringBehabiorAlign* m_pAlignSteeringBehabior;
};
