// Fill out your copyright notice in the Description page of Project Settings.


#include "Selector.h"

Selector::Selector()
{
}

Selector::~Selector()
{
}

void Selector::Reset()
{
  m_iCurrentChildIndex = 0;
}

EBehaviorStatus Selector::GetStatus()
{
  return m_eStatus;
}

void Selector::OnEnter()
{
  m_iCurrentChildIndex = 0;
}

EBehaviorStatus Selector::Update()
{
  while (m_iCurrentChildIndex < m_oChildren.Num())
  {
    EBehaviorStatus Status = m_oChildren[m_iCurrentChildIndex]->Tick();
    if (Status != EBehaviorStatus::FAIL)
    {
      return Status;
    }

    ++m_iCurrentChildIndex;
  }
  return EBehaviorStatus::FAIL;
}
