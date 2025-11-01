// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class Action;
class StateMachine;
class Transition;
/**
 * 
 */
class MPV_PRACTICAS_API State
{
public:
	State();
	~State();

  void Enter();
  void Update();
  void Exid();

  Action* m_pStartAction;
  Action* m_pUpdateAction;
  Action* m_pEndAction;

  TArray<Transition*> m_transicion;
};
