// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "params/params.h"
#include "GameFramework/PlayerController.h"
#include "util.h"
#include "Steering/ISteering.h"
#include "Pathfinding/PathFindingA.h"
#include "Pathfinding/PathfindingANavMesh.h"
#include "BehaviorTree/Selector.h"
#include "SM/StateMachine.h"


#include "AICharacter.generated.h"

UCLASS()
class MPV_PRACTICAS_API AAICharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAICharacter();

	/**  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIChar)
	uint32 bDoMovement : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIChar)
	float current_angle;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* PathMaterial;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* NavmeshMaterial;
  int m_iVida = 100;

  FVector m_acceleration;
  FVector m_velocity;
  
  float m_angularVelocity;
  Path m_path;
  Params m_params;
  Obstacle m_obstacles;
  Grid m_grid;
  FNavMeshData NavMesh;
  

  StateMachine m_stateMachine;

  Selector* m_pRoot;

  UPROPERTY(EditAnywhere)
  AActor* m_pTarget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


  UPROPERTY(EditAnywhere)
  AActor* DebugBlock;


  IISteering* m_pSteeringAvoidance;
  IISteering* m_pSteeringBehabior;
    
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

  void PlayerTick(float DeltaTime);

  
  void SetImage(const FString& NewSpritePath);

	UFUNCTION(BlueprintCallable, Category = "AIFunctions")
	void OnClickedLeft(const FVector& mousePosition);
	UFUNCTION(BlueprintCallable, Category = "AIFunctions")
	void OnClickedRight(const FVector& mousePosition);
	
  UPROPERTY(EditAnywhere, Category = "Pathfinding")
  FVector m_pathStart;
  UPROPERTY(EditAnywhere, Category = "Pathfinding")
  FVector m_pathEnd;

	const Params& GetParams() const { return m_params; }

	float GetActorAngle() const
	{
		FQuat currQuat = GetActorQuat();
		FVector axis;
		float axisAngle;
		currQuat.ToAxisAndAngle(axis, axisAngle);
		axisAngle = FMath::RadiansToDegrees(axisAngle);
		if (axis.Y > 0.0f)
			axisAngle = -axisAngle;

		axisAngle = convertTo360(axisAngle);
		return axisAngle;
	}
	void SetActorAngle(float angle) { FRotator newRot(angle, 0.0f, 0.0f); SetActorRotation(newRot); }

	void DrawDebug();




};
