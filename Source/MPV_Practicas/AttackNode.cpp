// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackNode.h"

AttackNode::AttackNode(AAICharacter* _character)
{
  m_pCharacter = _character;
}

AttackNode::~AttackNode()
{
}

void AttackNode::OnEnter()
{
}

EBehaviorStatus AttackNode::Update()
{
  GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Attacking"));
  m_pCharacter->SetImage("/Game/PaperAssets/Golem/T_Golem_03_Attacking_008.T_Golem_03_Attacking_008");
  return EBehaviorStatus::SUCCESS;
}
