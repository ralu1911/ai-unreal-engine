// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Condition.h"
#include "CoreMinimal.h"

/**
 * 
 */
class MPV_PRACTICAS_API DistanceCondition : public Condition
{
public:
	DistanceCondition(AActor* _self, AActor* _target, bool _inverse);
	~DistanceCondition();


  virtual bool GetCondition() override;

  bool m_bInverse;
  AActor* m_pThis;
  AActor* m_pTarget;

};
