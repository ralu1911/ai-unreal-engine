// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class State;
class Condition;
class Action;
class StateMachine;
/**
 * 
 */
class MPV_PRACTICAS_API Transition
{
public:
	Transition();
	~Transition();

  State* Trigger();

  FString m_pTargetState;
  Condition* m_pCondition;
  Action* m_pTriggerAction;
};
