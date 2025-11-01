// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MPV_PRACTICAS_API Condition
{
public:
  Condition();
  ~Condition();

  virtual bool GetCondition() = 0;


};