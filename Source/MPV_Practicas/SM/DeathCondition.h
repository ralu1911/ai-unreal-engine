// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Condition.h"
#include "../AICharacter.h"
#include "CoreMinimal.h"

/**
 * 
 */
class MPV_PRACTICAS_API DeathCondition : public Condition
{
public:
	DeathCondition(AAICharacter* _self);
	~DeathCondition();

  virtual bool GetCondition() override;

  AAICharacter* m_pCharacter;
};
