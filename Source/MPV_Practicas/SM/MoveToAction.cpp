// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveToAction.h"

MoveToAction::MoveToAction(AAICharacter* _character, AActor* _target)
{
  m_pCharacter = _character;
  m_pSteering = new SteeringBehabiorArrival();
  m_pSteering->SetSteeringBehavior(m_pCharacter);
  m_pTarget = _target;
}

MoveToAction::~MoveToAction()
{
}

void MoveToAction::DoAction()
{
  m_pCharacter->m_params.targetPosition = m_pTarget->GetActorLocation();
  m_pCharacter->m_acceleration = m_pSteering->GetSteering(m_pCharacter->m_params).m_vLinearAcceleration;
}
