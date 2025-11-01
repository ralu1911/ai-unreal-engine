// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"


#include "ISteering.generated.h"

struct TAccelerationParams
{
    FVector m_vLinearAcceleration;
    float m_fAgularAcceleration;
};

class AAICharacter;
struct Params;
struct Path;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UISteering : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MPV_PRACTICAS_API IISteering
{
	GENERATED_BODY()


	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:




    virtual void SetSteeringBehavior(AAICharacter* _character);
    virtual void SetPosition(FVector _position);

    virtual TAccelerationParams GetSteering(const Params& _parameters) = 0;

    AAICharacter* m_pCharacter;  

    FVector m_position = FVector(0,0,0);

};
