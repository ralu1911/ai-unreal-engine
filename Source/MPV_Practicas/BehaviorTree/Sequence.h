// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Group.h"

/**
 * 
 */
class MPV_PRACTICAS_API Sequence : public Group
{
public:
	Sequence();
	~Sequence();

protected:
  virtual void OnEnter() override;
  virtual EBehaviorStatus Update() override;

private:
  int m_iCurrentChildIndex;
};
