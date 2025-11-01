// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Behavior.h"

/**
 * 
 */
class MPV_PRACTICAS_API Group : public Behavior
{
public:
	Group();
	~Group();

protected:
  TArray<Behavior*> m_oChildren;
public:
  void AddChild(Behavior* Child);
};
