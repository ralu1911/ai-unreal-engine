// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Behavior.h"

/**
 * 
 */
class MPV_PRACTICAS_API DetectEnemy : public Behavior
{
public:
	DetectEnemy(AActor* _self, AActor* _target);
	~DetectEnemy();
protected:
  virtual EBehaviorStatus Update() override;
  virtual void OnEnter() override;

private:
  AActor* m_pTarget;
  AActor* m_pSelf;
};
