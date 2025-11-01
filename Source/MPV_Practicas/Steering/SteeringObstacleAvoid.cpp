// Fill out your copyright notice in the Description page of Project Settings.


#include "SteeringObstacleAvoid.h"
#include "../AICharacter.h"

SteeringObstacleAvoid::SteeringObstacleAvoid()
{
}

SteeringObstacleAvoid::~SteeringObstacleAvoid()
{
}

TAccelerationParams SteeringObstacleAvoid::GetSteering(const Params& _parameters)
{
  int index = m_pCharacter->m_obstacles.Locations.Num();
  bool Collides = false;

  TAccelerationParams Params = TAccelerationParams();
  Params.m_vLinearAcceleration = FVector(0,0,0);

  FVector PO;
  FVector Direction;
  FVector DirectionNormal;
  FVector I;
  FVector IO;
  FVector VelocityNormal = m_pCharacter->m_velocity.GetSafeNormal();
  float distanceToCollision;
  for (int i = 0; i < index; i++)
  {
    PO = m_pCharacter->m_obstacles.Locations[i] - m_pCharacter->GetActorLocation();
    Direction = m_pCharacter->m_params.targetPosition - m_pCharacter->GetActorLocation();
    
    DirectionNormal = Direction.GetSafeNormal();

    I = (DirectionNormal * FVector::DotProduct(DirectionNormal, PO)) + m_pCharacter->GetActorLocation();

    IO = m_pCharacter->m_obstacles.Locations[i] - I;
    //distanceToCollision = Direction.Length() < m_pCharacter->m_params.look_ahead ? Direction.Length() : m_pCharacter->m_params.look_ahead;
    distanceToCollision = Direction.Length();
    //distanceToCollision = m_pCharacter->m_velocity.Length();
    if (IO.Length() < m_pCharacter->m_obstacles.Radius[i] && distanceToCollision > PO.Length() - m_pCharacter->m_obstacles.Radius[i])
    {
      FVector OI = I - m_pCharacter->m_obstacles.Locations[i];
      FVector acceleration = OI.GetSafeNormal() * (m_pCharacter->m_obstacles.Radius[i] - OI.Length());

      GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Emerald, FString::Printf( TEXT("Entra, A objetivo: %f, A punto %f"), distanceToCollision, PO.Length() - m_pCharacter->m_obstacles.Radius[i]));
      Collides = true;
      //-IO.GetSafeNormal() * m_pCharacter->m_params.max_acceleration;
      float max = FMath::Clamp(acceleration.Length(), 0, m_pCharacter->m_params.max_acceleration);
      Params.m_vLinearAcceleration = acceleration.GetSafeNormal() * max;

      return Params;
    }
  }

  return Params;
}
