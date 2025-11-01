// Fill out your copyright notice in the Description page of Project Settings.


#include "DistanceCondition.h"

DistanceCondition::DistanceCondition(AActor* _seft, AActor* _target, bool _inverse)
{
  m_pTarget = _target;
  m_pThis = _seft;
  m_bInverse = _inverse;
}

DistanceCondition::~DistanceCondition()
{
}

bool DistanceCondition::GetCondition()
{
  FVector vector = m_pTarget->GetActorLocation() - m_pThis->GetActorLocation();
  if (m_bInverse)
  {
    if (vector.Length() > 50)
    {
      return true;
    }
  }
  else
  {
    if (vector.Length() < 50)
    {
      return true;
    }
  }
  return false;
}
