// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAction.h"

AttackAction::AttackAction(AAICharacter* _self)
{
  m_pCharacter = _self;
}

AttackAction::~AttackAction()
{
}

void AttackAction::DoAction()
{
  GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Atacando"));
  m_pCharacter->SetImage("/Game/PaperAssets/Golem/T_Golem_03_Attacking_008");
}
