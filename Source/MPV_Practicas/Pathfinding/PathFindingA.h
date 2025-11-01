// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../AICharacter.h"

struct PathFindingLocations
{
  int m_iPosX;
  int m_iPosY;
  float m_iTotalWeight;
  float m_iPathWeight;
  float m_iEuristicsWeight;
  PathFindingLocations* m_rootNode;
};
/**
 * 
 */
class MPV_PRACTICAS_API PathFindingA
{
public:
	PathFindingA();
	~PathFindingA();

  void PathFinding(Grid _grid, Path& _path);

  TArray<PathFindingLocations*> GetPosibleLocations(const Grid& _grid, PathFindingLocations* _locations);

  PathFindingLocations* FindBetterLocation();

  FVector GetWorldPathLocation(Grid _grid, PathFindingLocations* _loc);

  bool HasAlreadyBeenFound(int x, int y);


  TArray<PathFindingLocations*> m_aAnalizeLocationsLocations;
  TArray<PathFindingLocations*> m_aPosibleLocationsLocations;
  bool m_bPathFound;

};
