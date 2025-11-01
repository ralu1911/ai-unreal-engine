// Fill out your copyright notice in the Description page of Project Settings.


#include "PathFindingA.h"

PathFindingA::PathFindingA()
{
}

PathFindingA::~PathFindingA()
{
}

void PathFindingA::PathFinding(Grid _grid, Path& _path)
{

  if (_grid.Location == _grid.Destination)
  {
    return;
  }
  m_bPathFound = false;
  
  TArray<PathFindingLocations*> aTempLocations;
  PathFindingLocations* location = new PathFindingLocations();
  location->m_iPosX = _grid.Destination.X;
  location->m_iPosY = _grid.Destination.Z;
  
  m_aPosibleLocationsLocations.Add(location);

  
  while (!m_bPathFound)
  {
    aTempLocations = GetPosibleLocations(_grid, location);
    m_aPosibleLocationsLocations.Append(aTempLocations);
    location = FindBetterLocation();

    aTempLocations.Empty();
    if (location->m_iPosX == _grid.Location.X && location->m_iPosY == _grid.Location.Z)
    {
      m_bPathFound = true;
    }
  }


  bool pathEnd = false;
  while (!pathEnd)
  {
    _path.Path.Add(GetWorldPathLocation(_grid, location));
    if (location->m_rootNode)
    {
      location = location->m_rootNode;
    }
    else
    {
      pathEnd = true;
    }
  }

  m_aAnalizeLocationsLocations.Empty();
  m_aPosibleLocationsLocations.Empty();
}

TArray<PathFindingLocations*> PathFindingA::GetPosibleLocations(const Grid& _grid, PathFindingLocations* _locations)
{
  m_aAnalizeLocationsLocations.Add(_locations);
  m_aPosibleLocationsLocations.Remove(_locations);

  TArray<PathFindingLocations*> aPosibleLocation;
  int iNumX[4] = { 1, 0, -1, 0 };
  int iNumY[4] = { 0, 1, 0, -1 };
  
  int iNextLocationX;
  int iNextLocationY;

  for (int i = 0; i < 4; i++)
  {
    iNextLocationX = iNumX[i] + _locations->m_iPosX;
    iNextLocationY = iNumY[i] + _locations->m_iPosY;
    if (iNextLocationX >= _grid.colums || iNextLocationX < 0 || iNextLocationY >= _grid.rows || iNextLocationY < 0)
    {
      continue;
    }
    TArray<Cells> _rows = _grid.m_Grid[iNextLocationY];
    if (_rows[iNextLocationX].m_fWeight < 0 || _rows[iNextLocationX].m_bIsOccupied)
    {
      continue;
    }
    if (HasAlreadyBeenFound(iNextLocationX, iNextLocationY))
    {
      continue;
    }
    PathFindingLocations* loc = new PathFindingLocations();
    loc->m_iPosX = iNextLocationX;
    loc->m_iPosY = iNextLocationY;
    loc->m_rootNode = _locations;
    loc->m_iPathWeight = _locations->m_iPathWeight + _rows[iNextLocationX].m_fWeight;
    loc->m_iEuristicsWeight = FVector(loc->m_iPosX - _grid.Location.X, 0, loc->m_iPosY - _grid.Location.Y).Length();
    loc->m_iTotalWeight = loc->m_iPathWeight + loc->m_iEuristicsWeight;

    aPosibleLocation.Add(loc);
  }
  return aPosibleLocation;
}

PathFindingLocations* PathFindingA::FindBetterLocation()
{
  int baseWeight = 10000;
  PathFindingLocations* loc = nullptr;
  for (auto it = m_aPosibleLocationsLocations.begin(); it != m_aPosibleLocationsLocations.end(); ++it)
  {
    if ((*it)->m_iTotalWeight < baseWeight)
    {
      baseWeight = (*it)->m_iTotalWeight;
      loc = (*it);
    }
  }

  return loc;
}

FVector PathFindingA::GetWorldPathLocation(Grid _grid, PathFindingLocations* _loc)
{
  FVector TempLoc = FVector(_loc->m_iPosX, 0, _loc->m_iPosY);
  FVector loc = (TempLoc * _grid.m_vSize) + _grid.m_vGridOffset;

  return loc;
}

bool PathFindingA::HasAlreadyBeenFound(int x, int y)
{
  bool found = false;
  for (auto it = m_aAnalizeLocationsLocations.begin(); it != m_aAnalizeLocationsLocations.end(); ++it)
  {
    if ((*it)->m_iPosX == x && (*it)->m_iPosY == y)
    {
      found = true;
    }
  }

  for (auto it = m_aPosibleLocationsLocations.begin(); it != m_aPosibleLocationsLocations.end(); ++it)
  {
    if ((*it)->m_iPosX == x && (*it)->m_iPosY == y)
    {
      found = true;
    }
  }

  return found;
}
