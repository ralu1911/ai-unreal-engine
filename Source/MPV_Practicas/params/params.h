#ifndef __PARAMS_H__
#define __PARAMS_H__

#include <CoreMinimal.h>

struct Params
{
    FVector targetPosition;
    float max_velocity;
    float max_acceleration;
    float radius;

    float target_rotation;
    float max_angular_velocity;
    float max_angular_acceleration;
    float angular_arrive_radius;

    float look_ahead;
    float time_ahead;
};

struct Path
{
    TArray<FVector> Path;
};

struct Obstacle
{
  TArray<FVector> Locations;
  TArray<float> Radius;
};

struct Cells
{
  FVector m_vPos;
  int m_fWeight;
  int m_iPosX;
  int m_iPosY;
  bool m_bIsOccupied;

};
struct Grid
{
  TArray<TArray<Cells>> m_Grid;
  int colums;
  int rows;
  TMap<FString, int> m_weights;
  FVector m_vSize;
  FVector m_vGridOffset;

  FVector Location;
  FVector Destination;
};
struct FNavMeshPolygon
{
  TArray<FVector> m_aPoints;
};
struct FNavMeshLink
{

  int32 StartPolygon;

  int32 StartEdgeStart;

  int32 StartEdgeEnd;

  int32 EndPolygon;

  int32 EndEdgeStart;

  int32 EndEdgeEnd;
};
struct FNavMeshData
{

  TArray<FNavMeshPolygon> Polygons;

  TArray<FNavMeshLink> Links;
};





bool ReadGridData(const char* _filename, Grid& grid);
bool ReadGrid(const char* _filename, Grid& grid);
bool ReadParams(const char* filename, Params& params);
bool ReadPath(const char* _filename, Path& _path_);
bool ReadObstacle(const char* _filename, Obstacle& _Obstacles_);
bool ReadNavMesh(const char* _filename, FNavMeshData& _data);

#endif