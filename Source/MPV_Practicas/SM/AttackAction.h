// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Action.h"
#include "../AICharacter.h"
#include "CoreMinimal.h"

/**
 * 
 */
class MPV_PRACTICAS_API AttackAction : public Action
{
public:
	AttackAction(AAICharacter* _self);
	~AttackAction();

  virtual void DoAction() override;

  AAICharacter* m_pCharacter;
};
