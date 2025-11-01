// Fill out your copyright notice in the Description page of Project Settings.


#include "Behavior.h"

Behavior::Behavior()
  : m_eStatus(EBehaviorStatus::INVALID)
{
}

EBehaviorStatus Behavior::Tick()
{
  if (m_eStatus == EBehaviorStatus::INVALID)
  {
    OnEnter();
  }

  m_eStatus = Update();

  if (m_eStatus != EBehaviorStatus::RUNNING)
  {
    OnExit();
  }

  return m_eStatus;
}

void Behavior::OnEnter()
{
}

void Behavior::OnExit()
{
}

EBehaviorStatus Behavior::Update()
{
  return EBehaviorStatus();
}

Behavior::~Behavior()
{
}
