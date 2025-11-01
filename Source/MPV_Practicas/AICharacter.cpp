// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "params/params.h"
#include "debug/debugdraw.h"
#include "Steering/SteeringBehabiorSeekBase.h"
#include "Steering/SteeringBehabiorArrival.h"
#include "Steering/SteeringBehabiorAlign.h"
#include "Steering/SteeringBehabiorAlignToMovement.h"
#include "Steering/SteeringBehabiorPathFollowing.h"
#include "Steering/SteeringObstacleAvoid.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

#include "SM/AttackAction.h"
#include "SM/MoveToAction.h"
#include "SM/DeathAction.h"
#include "SM/VisibilityCondition.h"
#include "SM/DistanceCondition.h"
#include "SM/DeathCondition.h"
#include "SM/Transition.h"
#include "SM/State.h"

#include "BehaviorTree/Sequence.h"
#include "BehaviorTree/DetectEnemy.h"
#include "BehaviorTree/GoToTarget.h"
#include "AttackNode.h"



// Sets default values
AAICharacter::AAICharacter()
{
  // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
  //m_pSteeringBehabior = Cast<IISteering>(CreateDefaultSubobject<USteeringBehaviorSeek>("SteeringBehabior"));
  //m_pSteeringBehabior = static_cast<IISteering*>(new SteeringBehabiorAlignToMovement());
  m_pSteeringBehabior = static_cast<IISteering*>(new SteeringBehabiorPathFollowing());
  m_pSteeringAvoidance = static_cast<IISteering*>(new SteeringObstacleAvoid());



}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
  Super::BeginPlay();
  m_velocity = FVector(0, 0, 0);
  m_pSteeringBehabior->SetSteeringBehavior(this);
  m_pSteeringAvoidance->SetSteeringBehavior(this);
  m_pSteeringBehabior->SetPosition(GetActorLocation());
  ReadParams("params.xml", m_params);
  ReadGridData("GridData.xml", m_grid);
  //ReadGrid("Grid.xml", m_grid);
  ReadNavMesh("NavMesh.xml", NavMesh);

  UE_LOG(LogTemp, Warning, TEXT("Polígonos: %d"), NavMesh.Polygons.Num());
  UE_LOG(LogTemp, Warning, TEXT("Links: %d"), NavMesh.Links.Num());

  //m_params.targetPosition = (m_grid.Location * m_grid.m_vSize) + m_grid.m_vGridOffset;
  //ReadPath("Path.xml", m_path);
  //ReadObstacle("Obstacle.xml", m_obstacles);

  PathfindingANavMesh pathfinding;
  //bool result = pathfinding.FindPath(m_pathStart, m_pathEnd, NavMesh, m_path);
  //pathfinding.FindPath()
  //pathFindin.PathFinding(m_grid, m_path);
  //m_params.targetPosition = m_pathStart;
  m_pRoot = new Selector();

  Sequence* sequence = new Sequence();
  DetectEnemy* detectEnemy = new DetectEnemy(this, m_pTarget);
  GoToTarget* goToTarget = new GoToTarget(this, m_pTarget);
  AttackNode* attackNode = new AttackNode(this);

  m_pRoot->AddChild(sequence);

  sequence->AddChild(detectEnemy);
  sequence->AddChild(goToTarget);
  sequence->AddChild(attackNode);

}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  PlayerTick(DeltaTime);


  DrawDebug();
}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
  Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AAICharacter::PlayerTick(float DeltaTime)
{

  m_pRoot->Tick();
  if (m_pRoot->GetStatus() == EBehaviorStatus::FAIL)
  {
    m_pRoot->Reset();
  }

  current_angle = GetActorAngle();
  //TAccelerationParams param = m_pSteeringBehabior->GetSteering(m_params);
  //TAccelerationParams param2 = m_pSteeringAvoidance->GetSteering(m_params);
  // param.m_vLinearAcceleration +
  //+ param2.m_vLinearAcceleration
  //FVector acceleraction = param.m_vLinearAcceleration + param2.m_vLinearAcceleration * 1.5;
  FVector position = GetActorLocation();

  m_velocity += m_acceleration * DeltaTime;
  position += m_velocity * DeltaTime;

  SetActorLocation(position);
  //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, FString::Printf(TEXT("velocity: %f, acceleracion %f"), static_cast<float>(m_velocity.Size()), acceleraction.Size()));


  //float AngularAcceleration = param.m_fAgularAcceleration;
 // m_angularVelocity += AngularAcceleration * DeltaTime;
  FRotator Rotator = GetActorRotation();
  float angle = GetActorAngle();
  Rotator.Add(m_angularVelocity * DeltaTime, 0, 0);

  //m_angularVelocity += AngularAcceleration * DeltaTime;
  //angle += m_angularVelocity * DeltaTime;
  //
  //SetActorAngle(angle);
  //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, FString::Printf(TEXT("angle: %f, angularVelocity: %f, Objetivo: %f"), angle, m_angularVelocity, m_params.target_rotation));
}

void AAICharacter::SetImage(const FString& NewSpritePath)
{
  TArray<USceneComponent*> PawnComponents;
  GetComponents(UPaperSpriteComponent::StaticClass(), PawnComponents, true);
  // Check each component to find the PaperSpriteComponent
  for (USceneComponent* Component : PawnComponents)
  {
    UPaperSpriteComponent* PaperSpriteComponent =
      Cast<UPaperSpriteComponent>(Component);

    if (PaperSpriteComponent)
    {
      UPaperSprite* NewSprite = LoadObject<UPaperSprite>(nullptr,

        *NewSpritePath);
      if (NewSprite)
      {
        // Set the new sprite for the actor
        PaperSpriteComponent->SetSprite(NewSprite);
      }
      break;
    }
  }
}

void AAICharacter::OnClickedLeft(const FVector& mousePosition)
{
  SetActorLocation(mousePosition);
}

void AAICharacter::OnClickedRight(const FVector& mousePosition)
{
  m_params.targetPosition = mousePosition;

  GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, FString::Printf(TEXT("Velocity: %f, Acceleration: %f"), m_params.targetPosition.X, m_params.targetPosition.Y));
  FVector dir = (mousePosition - GetActorLocation()).GetSafeNormal();
  float angle = FMath::RadiansToDegrees(atan2(dir.Z, dir.X));
  m_params.target_rotation = angle;
}

void AAICharacter::DrawDebug()
{
  //TArray<FVector> Points =
  //{
  //	FVector(0.f, 0.f, 0.f),
  //	FVector(100.f, 0.f, 0.f),
  //	FVector(100.f, 0.f, 100.f),
  //	FVector(100.f, 0.f, 100.f),
  //	FVector(0.f, 0.f, 100.f)
  //};

  SetPath(this, TEXT("follow_path"), TEXT("path"), m_path.Path, 5.0f, PathMaterial);



  SetCircle(this, TEXT("targetPosition"), m_params.targetPosition, 20.0f);
  SetCircle(this, TEXT("EndTarget"), m_pathEnd, 20.0f);

  //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, FString::Printf(TEXT("Rotation: %f"), m_params.radius));
  SetCircle(this, TEXT("targetArrival"), GetActorLocation(), GetParams().radius);


  for (int i = 0; i < m_grid.rows; i++)
  {
    TArray<Cells> row = m_grid.m_Grid[i];
    for (size_t j = 0; j < m_grid.colums; j++)
    {

      row[j].m_vPos.X = (row[j].m_iPosX * m_grid.m_vSize.X) + m_grid.m_vGridOffset.X;
      row[j].m_vPos.Y = 0;
      row[j].m_vPos.Z = (row[j].m_iPosY * m_grid.m_vSize.Z) + m_grid.m_vGridOffset.Z;
      FLinearColor color = row[j].m_fWeight > 0 ? FLinearColor(0, 255, 0) : FLinearColor(255, 0, 0);
      //GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Blue, FString::Printf(TEXT("Entra y %f"), row[j].m_vPos.Z));
      SetCircle(this, FString::Printf(TEXT("Grid%i"), (i * m_grid.colums) + j), row[j].m_vPos, m_grid.m_vSize.X / 2, color);
    }
  }


  //SetCircle(this, TEXT("Path1"), m_path.Path[0], 50, FLinearColor::Blue);
  //SetCircle(this, TEXT("Path2"), m_path.Path[1], 50, FLinearColor::Blue);
  //SetCircle(this, TEXT("Path3"), m_path.Path[2], 50, FLinearColor::Blue);
  //SetCircle(this, TEXT("Path4"), m_path.Path[3], 50, FLinearColor::Blue);

  //SetCircle(this, TEXT("Obstacle"), m_obstacles.Locations[0], m_obstacles.Radius[0], FLinearColor::Red);
  //SetCircle(this, TEXT("Obstacle2"), m_obstacles.Locations[1], m_obstacles.Radius[1], FLinearColor::Red);


  for (const FNavMeshPolygon& Polygon : NavMesh.Polygons)
  {
    const TArray<FVector> Points = Polygon.m_aPoints;
    for (int32 i = 0; i < Points.Num(); ++i)
    {
      const FVector& P1 = Points[i];
      const FVector& P2 = Points[(i + 1) % Points.Num()];
      //GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Red, FString::Printf(TEXT("x:%f y:%f z:%f"), P1.X, P1.Y, P1.Z));
      //GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Blue, FString::Printf(TEXT("x:%f y:%f z:%f"), P2.X, P2.Y, P2.Z));
      //
      DrawDebugLine(GetWorld(), P1, P2, FColor::Red, false, 2.f, 0, 3.0f);
    }
  }

  FVector dir(cos(FMath::DegreesToRadians(m_params.target_rotation)), 0.0f, sin(FMath::DegreesToRadians(m_params.target_rotation)));
  SetArrow(this, TEXT("targetRotation"), dir, 80.0f);

  TArray<TArray<FVector>> Polygons = {
    { FVector(0.f, 0.f, 0.f), FVector(100.f, 0.f, 0.f), FVector(100.f, 0.f, 100.0f), FVector(0.f, 0.f, 100.0f) },
    { FVector(100.f, 0.f, 0.f), FVector(200.f, 0.f, 0.f), FVector(200.f, 0.f, 100.0f) }
  };
  SetPolygons(this, TEXT("navmesh"), TEXT("mesh"), Polygons, NavmeshMaterial);
}


