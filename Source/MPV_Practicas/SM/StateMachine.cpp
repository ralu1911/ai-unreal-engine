// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine.h"
#include "Transition.h"
#include "Condition.h"
#include "State.h"

StateMachine::StateMachine()
{
}

StateMachine::~StateMachine()
{
}

void StateMachine::Start()
{
  m_pCurrentState->Enter();
}

void StateMachine::Update()
{
  m_pCurrentState->Update();
  TArray<Transition*> transitions = m_pCurrentState->m_transicion;

  for (size_t i = 0; i < transitions.Num(); i++)
  {
    CheckTransition(transitions[i]);
  }
}

void StateMachine::End()
{
  m_pCurrentState->Exid();
}

void StateMachine::ChangeState(FString _state)
{
  if (m_mStates.Contains(_state))
  {
    State* nextState = *(m_mStates.Find(_state));
    m_pCurrentState->Exid();
    m_pCurrentState = nextState;
    m_pCurrentState->Enter();
  }
}

void StateMachine::CheckTransition(Transition* _transition)
{
  if (_transition->m_pCondition->GetCondition())
  {
    ChangeState(_transition->m_pTargetState);
  }
}
