// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
class State;
class Transition;

/**
 * 
 */
class MPV_PRACTICAS_API StateMachine
{
public:
	StateMachine();
	~StateMachine();

  void Start();
  void Update();
  void End();

  void ChangeState(FString _state);
  void CheckTransition(Transition* _transition);

  State* m_pCurrentState;
  TMap<FString, State*> m_mStates;
};
