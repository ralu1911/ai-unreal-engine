// Fill out your copyright notice in the Description page of Project Settings.


#include "ISteering.h"
#include "../AICharacter.h"
// Add default functionality here for any IISteering functions that are not pure virtual.

void IISteering::SetSteeringBehavior(AAICharacter* _character)
{
    m_pCharacter = _character;
    m_position = m_pCharacter->GetParams().targetPosition;
}

void IISteering::SetPosition(FVector _position)
{


}
