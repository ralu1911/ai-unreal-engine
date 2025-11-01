// Fill out your copyright notice in the Description page of Project Settings.


#include "VisibilityCondition.h"

VisibilityCondition::VisibilityCondition(AActor* _self, AActor* _target, bool _inversed)
{
  m_pSelf = _self;
  m_pTarget = _target;
  m_bInverse = _inversed;
}

VisibilityCondition::~VisibilityCondition()
{
}

bool VisibilityCondition::GetCondition()
{

  FVector Vision = m_pSelf->GetActorForwardVector();
  FVector VisibilityLine = m_pTarget->GetActorLocation() - m_pSelf->GetActorLocation();
  if (m_bInverse)
  {
    if (FVector::DotProduct(Vision, VisibilityLine) < 0)
    {
      return true;
    }
  }
  else
  {
    if (FVector::DotProduct(Vision, VisibilityLine) > 0)
    {
      return true;
    }
  }
  return false;
}
