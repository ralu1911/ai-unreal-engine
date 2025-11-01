// Fill out your copyright notice in the Description page of Project Settings.


#include "SteeringBehabiorAlignToMovement.h"

SteeringBehabiorAlignToMovement::SteeringBehabiorAlignToMovement()
    
{
    m_pAlignSteeringBehabior = new SteeringBehabiorAlign();
    m_pArrivalSteeringBehabior = new SteeringBehabiorArrival();
}

SteeringBehabiorAlignToMovement::~SteeringBehabiorAlignToMovement()
{
    delete m_pAlignSteeringBehabior;
    delete m_pArrivalSteeringBehabior;
}

TAccelerationParams SteeringBehabiorAlignToMovement::GetSteering(const Params& _parameters)
{
    TAccelerationParams param;
    param.m_vLinearAcceleration = m_pArrivalSteeringBehabior->GetSteering(_parameters).m_vLinearAcceleration;
    param.m_fAgularAcceleration = m_pAlignSteeringBehabior->GetSteering(_parameters).m_fAgularAcceleration;
    return param;
}

void SteeringBehabiorAlignToMovement::SetSteeringBehavior(AAICharacter* _character)
{
    m_pCharacter = _character;
    m_pAlignSteeringBehabior->SetSteeringBehavior(_character);
    m_pArrivalSteeringBehabior->SetSteeringBehavior(_character);

}
