// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../params/params.h"

/**
 * 
 */
class MPV_PRACTICAS_API PathfindingANavMesh
{
public:
	PathfindingANavMesh();
	~PathfindingANavMesh();

  struct FPathNode
  {
    int32 PolygonIndex;
    float CostSoFar;
    float EstimatedTotalCost;
    int32 ParentIndex;

    bool operator<(const FPathNode& Other) const
    {
      return EstimatedTotalCost > Other.EstimatedTotalCost; 
    }
  };

  float Heuristic(const FVector& A, const FVector& B);

  FVector PoligonCenter(const FNavMeshPolygon& Poly);

  bool FindPath(const FVector& start, const FVector& end, const FNavMeshData& navMesh, Path& Path_);

  bool PointInPolygon(const FVector& Point, const TArray<FVector>& Polygon);

  int FindPolygonContainingPoint(const FVector& Point, const FNavMeshData& NavMesh);

  FVector EdgeMidpoint(const FVector& A, const FVector& B);

  FVector GetEdgeMidpoint(const FNavMeshPolygon& Poly, int IndexA, int IndexB);


};
