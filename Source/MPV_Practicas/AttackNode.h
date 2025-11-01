// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Behavior.h"
#include "AICharacter.h"

/**
 * 
 */
class MPV_PRACTICAS_API AttackNode : public Behavior
{
public:
	AttackNode(AAICharacter* _character);
	~AttackNode();

protected:
  virtual void OnEnter() override;
  virtual EBehaviorStatus Update() override;
private:
  AAICharacter* m_pCharacter;
};
