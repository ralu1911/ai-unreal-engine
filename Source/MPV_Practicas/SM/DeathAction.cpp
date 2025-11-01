// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathAction.h"

DeathAction::DeathAction(AAICharacter* _self)
{
}

DeathAction::~DeathAction()
{
}

void DeathAction::DoAction()
{
  GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Muerto"));
  m_pCharacter->SetImage("/Game/PaperAssets/Golem/T_Golem_03_Dying_014");
}
