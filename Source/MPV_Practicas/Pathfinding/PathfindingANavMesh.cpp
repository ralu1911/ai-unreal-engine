// Fill out your copyright notice in the Description page of Project Settings.



#include "PathfindingANavMesh.h"
#include "Containers/Queue.h"
PathfindingANavMesh::PathfindingANavMesh()
{
}

PathfindingANavMesh::~PathfindingANavMesh()
{
}

float PathfindingANavMesh::Heuristic(const FVector& A, const FVector& B)
{
  return FVector::Dist(A, B);
}

FVector PathfindingANavMesh::PoligonCenter(const FNavMeshPolygon& Poly)
{
  FVector Sum(0);
  for (const FVector& P : Poly.m_aPoints)
    Sum += P;
  return Sum / Poly.m_aPoints.Num();
}

bool PathfindingANavMesh::FindPath(const FVector& start, const FVector& end, const FNavMeshData& navMesh, Path& Path_)
{
  int StartPoly = FindPolygonContainingPoint(start, navMesh);
  int EndPoly = FindPolygonContainingPoint(end, navMesh);
  if (StartPoly == -1 || EndPoly == -1)
  {
    UE_LOG(LogTemp, Warning, TEXT("Start or End point not in any polygon."));
    return false;
  }

  TMap<int, FPathNode> Visited;
  TQueue<FPathNode> OpenSet;

  FVector EndCentroid = PoligonCenter(navMesh.Polygons[EndPoly]);

  OpenSet.Enqueue({ StartPoly, 0.f, Heuristic(PoligonCenter(navMesh.Polygons[StartPoly]), EndCentroid), -1 });

  while (!OpenSet.IsEmpty())
  {
    FPathNode Current;
    OpenSet.Dequeue(Current);

    if (Visited.Contains(Current.PolygonIndex))
      continue;

    Visited.Add(Current.PolygonIndex, Current);

    if (Current.PolygonIndex == EndPoly)
      break;

    for (const FNavMeshLink& Link : navMesh.Links)
    {
      if (Link.StartPolygon != Current.PolygonIndex)
        continue;

      int NextPoly = Link.EndPolygon;
      if (Visited.Contains(NextPoly))
        continue;

      FVector MidPoint = GetEdgeMidpoint(navMesh.Polygons[Link.StartPolygon], Link.StartEdgeStart, Link.StartEdgeEnd);
      float NewCost = Current.CostSoFar + FVector::Dist(PoligonCenter(navMesh.Polygons[Current.PolygonIndex]), MidPoint);
      FVector NextCentroid = PoligonCenter(navMesh.Polygons[NextPoly]);

      OpenSet.Enqueue({ NextPoly, NewCost, NewCost + Heuristic(NextCentroid, EndCentroid), Current.PolygonIndex });
    }
  }

  if (!Visited.Contains(EndPoly))
  {
    UE_LOG(LogTemp, Warning, TEXT("No path found."));
    return false;
  }

  TArray<FVector> ReversePath;
  int Trace = EndPoly;
  while (Trace != -1)
  {
    const FPathNode* Node = Visited.Find(Trace);
    if (!Node) break;
    ReversePath.Add(PoligonCenter(navMesh.Polygons[Trace]));
    Trace = Node->ParentIndex;
  }

  Algo::Reverse(ReversePath);

  if (ReversePath.Num() > 0)
    ReversePath[0] = start;
  ReversePath.Add(end);

  Path_.Path = ReversePath;
  return true;
}

bool PathfindingANavMesh::PointInPolygon(const FVector& Point, const TArray<FVector>& Polygon)
{
  int Num = Polygon.Num();
  if (Num < 3) return false;

  bool bInside = false;
  for (int i = 0, j = Num - 1; i < Num; j = i++)
  {
    const FVector& Pi = Polygon[i];
    const FVector& Pj = Polygon[j];

    if (((Pi.Z > Point.Z) != (Pj.Z > Point.Z)) &&
      (Point.X < (Pj.X - Pi.X) * (Point.Z - Pi.Z) / (Pj.Z - Pi.Z + SMALL_NUMBER) + Pi.X))
    {
      bInside = !bInside;
    }
  }
  return bInside;
}

int PathfindingANavMesh::FindPolygonContainingPoint(const FVector& Point, const FNavMeshData& NavMesh)
{
  for (int i = 0; i < NavMesh.Polygons.Num(); ++i)
  {
    if (PointInPolygon(Point, NavMesh.Polygons[i].m_aPoints))
    {
      return i;
    }
  }
  return -1;
}

FVector PathfindingANavMesh::EdgeMidpoint(const FVector& A, const FVector& B)
{
  return (A + B) * 0.5f;
}

FVector PathfindingANavMesh::GetEdgeMidpoint(const FNavMeshPolygon& Poly, int IndexA, int IndexB)
{
  if (!Poly.m_aPoints.IsValidIndex(IndexA) || !Poly.m_aPoints.IsValidIndex(IndexB))
  {
    return FVector::ZeroVector;
  }
  return EdgeMidpoint(Poly.m_aPoints[IndexA], Poly.m_aPoints[IndexB]);
}
