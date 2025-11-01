// Fill out your copyright notice in the Description page of Project Settings.


#include "DetectEnemy.h"

DetectEnemy::DetectEnemy(AActor* _self, AActor* _target)
{
  m_pSelf = _self;
  m_pTarget = _target;
}

DetectEnemy::~DetectEnemy()
{
}

EBehaviorStatus DetectEnemy::Update()
{
  GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Detectando"));
  FVector Vision = m_pSelf->GetActorForwardVector();
  FVector VisibilityLine = m_pTarget->GetActorLocation() - m_pSelf->GetActorLocation();
  if (FVector::DotProduct(Vision, VisibilityLine) > 0)
  {
    return EBehaviorStatus::SUCCESS;
  }
  return EBehaviorStatus::FAIL;
}

void DetectEnemy::OnEnter()
{
  GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Detectando"));
}
