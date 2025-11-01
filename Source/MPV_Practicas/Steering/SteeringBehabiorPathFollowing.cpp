// Fill out your copyright notice in the Description page of Project Settings.


#include "SteeringBehabiorPathFollowing.h"
#include "SteeringBehabiorArrival.h"
#include "SteeringBehabiorSeekBase.h"
#include "../AICharacter.h"

SteeringBehabiorPathFollowing::SteeringBehabiorPathFollowing()
{
}

SteeringBehabiorPathFollowing::~SteeringBehabiorPathFollowing()
{
    if (arrival)
    {
        delete static_cast<SteeringBehabiorArrival*>(arrival);
    }
}

TAccelerationParams SteeringBehabiorPathFollowing::GetSteering(const Params& _parameters)
{
    FVector currentLocation =  m_pCharacter->GetActorLocation();
    FVector nearPoint = GetNearestPointInPath(m_pCharacter->m_path);
    Path Path = m_pCharacter->m_path;
    int index = Path.Path.IndexOfByKey(nearPoint);
    //GEngine->AddOnScreenDebugMessage(-1, 25.f, FColor::Red, FString::Printf(TEXT("x: %f, y: %f, z: %z"), nearPoint.X, nearPoint.Y, nearPoint.Z));
    if (index < Path.Path.Num() - 1)
    {
        //m_pCharacter->m_params.targetPosition = Path.Path[index];
        //GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Position x: %f z: %f"), m_pCharacter->m_params.targetPosition.X, m_pCharacter->m_params.targetPosition.Z));
        FVector PathVector = (Path.Path[index + 1] - Path.Path[index]);
        FVector PathDirection = PathVector.GetSafeNormal();
        FVector PointToCharacter = currentLocation - Path.Path[index];
        

        float distance = FVector::DotProduct(PointToCharacter, PathDirection);
        distance += _parameters.look_ahead;
        FVector SeekPoint = (PathDirection * distance) + Path.Path[index];

        if (fabsf(distance) > PathVector.Length() && index < Path.Path.Num() - 2)
        {
          PathVector = (Path.Path[index + 2] - Path.Path[index + 1]);
          PathDirection = PathVector.GetSafeNormal();
          PointToCharacter = currentLocation - Path.Path[index + 1];

          distance = FVector::DotProduct(PointToCharacter, PathDirection);
          distance += _parameters.look_ahead;
          SeekPoint = (PathDirection * distance) + Path.Path[index + 1];

        }
        else if (fabsf(distance) > PathVector.Length() && index >= Path.Path.Num() - 2)
        {
          SeekPoint = Path.Path[index + 1];
        }
        
        m_pCharacter->m_params.targetPosition = SeekPoint;
    }
    else
    {
        m_pCharacter->m_params.targetPosition = nearPoint;
    }
    TAccelerationParams params = arrival->GetSteering(_parameters);

    return params;
}

FVector SteeringBehabiorPathFollowing::GetNearestPointInPath(const Path& _parameters)
{
    FVector currentLocation = m_pCharacter->GetActorLocation();
    FVector nearest_ = m_pCharacter->m_params.targetPosition;
    float distance = 1000000;
    for (size_t i = 0; i < _parameters.Path.Num(); i++)
    {
        if (distance > FVector::Dist(currentLocation, _parameters.Path[i]))
        {
            distance = FVector::Dist(currentLocation, _parameters.Path[i]);
            nearest_ = _parameters.Path[i];
        }
    }
    return nearest_;
}

void SteeringBehabiorPathFollowing::SetSteeringBehavior(AAICharacter* _character)
{
    
    arrival = new SteeringBehabiorArrival();
    seek = new SteeringBehabiorSeekBase();

    arrival->SetSteeringBehavior(_character);
    seek->SetSteeringBehavior(_character);
    m_pCharacter = _character;
}
