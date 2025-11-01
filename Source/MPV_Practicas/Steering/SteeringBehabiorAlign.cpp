// Fill out your copyright notice in the Description page of Project Settings.


#include "SteeringBehabiorAlign.h"

SteeringBehabiorAlign::SteeringBehabiorAlign()
{
}

SteeringBehabiorAlign::~SteeringBehabiorAlign()
{
}

TAccelerationParams SteeringBehabiorAlign::GetSteering(const Params& _parameters)
{
    float goalAngle = _parameters.target_rotation;
    float playerRotation = m_pCharacter->GetActorAngle();
    float maxAcceleration = _parameters.max_angular_acceleration;
    float angularDistance = convertTo180(goalAngle - playerRotation);
    //FMath::UnwindDegrees(goalAngle - playerRotation);
    
    
    float DesiredVelocity;
    
    //angularDistance = MapToRange(angularDistance);
    
    if (abs(angularDistance) < _parameters.angular_arrive_radius)
    {
        DesiredVelocity = _parameters.max_angular_velocity * (abs(angularDistance) / _parameters.angular_arrive_radius);
    }
    else {
        DesiredVelocity = _parameters.max_angular_velocity;
    }
    DesiredVelocity = FMath::Sign(angularDistance) * DesiredVelocity;
    
    float acceleration = DesiredVelocity - m_pCharacter->m_angularVelocity;
    
    acceleration = FMath::ClampAngle(acceleration, -maxAcceleration, maxAcceleration);
    
    
    TAccelerationParams param = TAccelerationParams();
    param.m_fAgularAcceleration = acceleration;
    return param;
}
