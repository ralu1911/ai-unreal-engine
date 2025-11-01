// Fill out your copyright notice in the Description page of Project Settings.


#include "GoToTarget.h"

GoToTarget::GoToTarget(AAICharacter* _self, AActor* _target)
{
  m_pSelf = _self;
  m_pTarget = _target;
  m_pSteering = new SteeringBehabiorArrival();
  m_pSteering->SetSteeringBehavior(m_pSelf);
}

GoToTarget::~GoToTarget()
{
}

void GoToTarget::OnEnter()
{

}

EBehaviorStatus GoToTarget::Update()
{
  GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("Llendo al enemigo"));
  m_pSelf->m_params.targetPosition = m_pTarget->GetActorLocation();
  m_pSelf->m_acceleration = m_pSteering->GetSteering(m_pSelf->m_params).m_vLinearAcceleration;
  
  FVector CharacterLocation = m_pSelf->GetActorLocation();
  FVector TargetLocation = m_pTarget->GetActorLocation();
  if(FVector::Dist(CharacterLocation, TargetLocation) < 50)
  {
    return EBehaviorStatus::SUCCESS;
  }
  return EBehaviorStatus::RUNNING;
}
