// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathCondition.h"

DeathCondition::DeathCondition(AAICharacter* _self)
{
  m_pCharacter = _self;
}

DeathCondition::~DeathCondition()
{
}

bool DeathCondition::GetCondition()
{
  if (m_pCharacter->m_iVida < 0)
  {
    return true;
  }
  return false;
}
