// Fill out your copyright notice in the Description page of Project Settings.


#include "State.h"
#include "Action.h"


State::State()
{
  m_pStartAction = nullptr;
  m_pUpdateAction = nullptr;
  m_pEndAction = nullptr;
}

State::~State()
{
}

void State::Enter()
{
  if (m_pStartAction != nullptr)
  {
    m_pStartAction->DoAction();
  }
}

void State::Update()
{
  if (m_pUpdateAction != nullptr)
  {
    m_pUpdateAction->DoAction();
  }
}

void State::Exid()
{
  if (m_pEndAction != nullptr)
  {
    m_pEndAction->DoAction();
  }
}
