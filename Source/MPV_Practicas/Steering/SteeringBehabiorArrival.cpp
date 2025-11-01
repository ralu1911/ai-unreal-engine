// Fill out your copyright notice in the Description page of Project Settings.


#include "SteeringBehabiorArrival.h"
#include "../AICharacter.h"

SteeringBehabiorArrival::SteeringBehabiorArrival()
{
}

SteeringBehabiorArrival::~SteeringBehabiorArrival()
{
}

TAccelerationParams SteeringBehabiorArrival::GetSteering(const Params& _parameters)
{
    FVector posicion = _parameters.targetPosition;
    FVector DesiredDirection = (posicion - m_pCharacter->GetActorLocation()).GetSafeNormal();
    FVector DesiredVelocity;
    float maxAcceleration = _parameters.max_acceleration;
    float distance = (posicion - m_pCharacter->GetActorLocation()).Size();
    
    if (distance < _parameters.radius)
    {
        DesiredVelocity = DesiredDirection * _parameters.max_velocity * (distance / _parameters.radius);
    }
    else 
    {
        DesiredVelocity = DesiredDirection * _parameters.max_velocity;
    }
    FVector Acceleration = (DesiredVelocity - m_pCharacter->m_velocity);
    if (Acceleration.Size() > maxAcceleration)
    {
        Acceleration = Acceleration.GetSafeNormal() * maxAcceleration;
    }
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Velocity: %f, Acceleration: %f"), DesiredVelocity.Size(), Acceleration.Size()));
    TAccelerationParams param = TAccelerationParams();
    param.m_vLinearAcceleration = Acceleration;
    
    
    return param;
}
