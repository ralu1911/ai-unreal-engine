// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Action.h"
#include "CoreMinimal.h"

/**
 * 
 */
class MPV_PRACTICAS_API SetTargetAction : public Action
{
public:
	SetTargetAction();
	~SetTargetAction();

  virtual void DoAction() override;
};
