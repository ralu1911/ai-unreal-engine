// Fill out your copyright notice in the Description page of Project Settings.


#include "Transition.h"
#include "State.h"
#include "Action.h"
#include "Condition.h"

Transition::Transition()
{
  m_pCondition = nullptr;
  m_pTriggerAction = nullptr;
}

Transition::~Transition()
{
}

State* Transition::Trigger()
{
  if (m_pCondition->GetCondition())
  {
    
  }
  return nullptr;
}
