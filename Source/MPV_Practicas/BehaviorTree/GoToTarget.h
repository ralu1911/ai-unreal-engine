// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../AICharacter.h"
#include "../Steering/SteeringBehabiorArrival.h"
#include "Behavior.h"

/**
 * 
 */
class MPV_PRACTICAS_API GoToTarget : public Behavior
{
public:
	GoToTarget(AAICharacter* _self, AActor* _target);
	~GoToTarget();

protected:
  virtual void OnEnter() override;
  virtual EBehaviorStatus Update() override;

private:
  AActor* m_pTarget;
  AAICharacter* m_pSelf;

  IISteering* m_pSteering;
};
