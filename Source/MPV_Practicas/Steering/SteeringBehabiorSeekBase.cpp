// Fill out your copyright notice in the Description page of Project Settings.


#include "SteeringBehabiorSeekBase.h"
#include "../AICharacter.h"

SteeringBehabiorSeekBase::SteeringBehabiorSeekBase()
{

}

SteeringBehabiorSeekBase::~SteeringBehabiorSeekBase()
{
}

TAccelerationParams SteeringBehabiorSeekBase::GetSteering(const Params& _parameters)
{
    FVector posicion = _parameters.targetPosition;
    float maxVelocity = _parameters.max_velocity;
    float maxAcceleration = _parameters.max_acceleration;

    FVector DesiredVelocity = (posicion - m_pCharacter->GetActorLocation()).GetSafeNormal() * maxVelocity;
    FVector Acceleration = (DesiredVelocity - m_pCharacter->m_velocity);
    if (Acceleration.Size() > maxAcceleration)
    {
        Acceleration = Acceleration.GetSafeNormal() * maxAcceleration;
    }

    TAccelerationParams param = TAccelerationParams();
    param.m_vLinearAcceleration = Acceleration;

    return param;
}
