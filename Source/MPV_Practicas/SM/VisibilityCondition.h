// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Condition.h"

#include "CoreMinimal.h"

/**
 * 
 */
class MPV_PRACTICAS_API VisibilityCondition : public Condition
{
public:
	VisibilityCondition(AActor* _self, AActor* _target, bool _inversed);
	~VisibilityCondition();

  virtual bool GetCondition() override;

  bool m_bInverse = false;
  AActor* m_pTarget;
  AActor* m_pSelf;
};
