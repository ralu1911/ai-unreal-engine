// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Action.h"
#include "../Steering/SteeringBehabiorArrival.h"
#include "../AICharacter.h"
#include "CoreMinimal.h"

/**
 * 
 */
class MPV_PRACTICAS_API MoveToAction : public Action
{
public:
	MoveToAction(AAICharacter* _character, AActor* _target);
	~MoveToAction();

  virtual void DoAction() override;


  AActor* m_pTarget;
  AAICharacter* m_pCharacter;
  IISteering* m_pSteering;
};
