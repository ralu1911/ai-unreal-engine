// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class EBehaviorStatus
{
  INVALID,
  SUCCESS,
  FAIL,
  RUNNING
};
/**
 * 
 */
class MPV_PRACTICAS_API Behavior
{
public:
	Behavior();
	~Behavior();
 

  EBehaviorStatus Tick();

protected:
  virtual void OnEnter();
  virtual void OnExit();
  virtual EBehaviorStatus Update();

  EBehaviorStatus m_eStatus;
};
