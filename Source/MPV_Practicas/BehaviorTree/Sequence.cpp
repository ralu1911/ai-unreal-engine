// Fill out your copyright notice in the Description page of Project Settings.


#include "Sequence.h"

Sequence::Sequence()
{
}

Sequence::~Sequence()
{
}

void Sequence::OnEnter()
{
  m_iCurrentChildIndex = 0;
}

EBehaviorStatus Sequence::Update()
{
  while (m_iCurrentChildIndex < m_oChildren.Num())
  {
    EBehaviorStatus Status = m_oChildren[m_iCurrentChildIndex]->Tick();
    if (Status != EBehaviorStatus::SUCCESS)
    {
      return Status;
    }

    ++m_iCurrentChildIndex;
  }
  m_iCurrentChildIndex = 0;
  return EBehaviorStatus::SUCCESS;
}
