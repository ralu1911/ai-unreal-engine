#include "params.h"

#include "XmlFile.h"
#include "Misc/DefaultValueHelper.h"
#include "HAL/PlatformProcess.h"
#include "Misc/Paths.h"


bool ReadParams(const char* filename, Params& params)
{
	FString CurrentDirectory = FPlatformProcess::GetCurrentWorkingDirectory();

	// Log or use the current working directory
	UE_LOG(LogTemp, Log, TEXT("Current working directory: %s"), *CurrentDirectory);

	FString ContentFolderDir = FPaths::ProjectContentDir();

	//FString FilePath(TEXT("./params.xml"));
	FString params_path = filename;
	FString FilePath = FPaths::Combine(*ContentFolderDir, *params_path);
	UE_LOG(LogTemp, Log, TEXT("Params Path: %s"), *FilePath);

	
	FXmlFile MyXml(FilePath, EConstructMethod::ConstructFromFile);
	
	if (MyXml.GetRootNode())
	{
		const FXmlNode* RootNode = MyXml.GetRootNode();
	
		const FString MyChildTag("params");
		const FXmlNode* MyChildNode = RootNode->FindChildNode(MyChildTag);

		const FXmlNode* paramElem = MyChildNode->FindChildNode(TEXT("max_velocity"));
		FString value;
		if (paramElem)
		{
			value = paramElem->GetAttribute("value");
			FDefaultValueHelper::ParseFloat(value, params.max_velocity);

		}

		paramElem = MyChildNode->FindChildNode(TEXT("max_acceleration"));
		if (paramElem)
		{
			value = paramElem->GetAttribute("value");
			FDefaultValueHelper::ParseFloat(value, params.max_acceleration);

		}

		paramElem = MyChildNode->FindChildNode(TEXT("targetPosition"));
		if (paramElem)
		{
			value = paramElem->GetAttribute("x");
			float x;
			FDefaultValueHelper::ParseFloat(value, x);
			params.targetPosition.X = x;
			value = paramElem->GetAttribute("z");
			float z;
			FDefaultValueHelper::ParseFloat(value, z);
			params.targetPosition.Z = z;
			params.targetPosition.Y = 0.0f;
		}
        paramElem = MyChildNode->FindChildNode(TEXT("dest_radius"));
        if (paramElem)
        {
            value = paramElem->GetAttribute("value");
            float x;
            FDefaultValueHelper::ParseFloat(value, x);
            params.radius = x;
        }

        paramElem = MyChildNode->FindChildNode(TEXT("max_angular_velocity"));
        if (paramElem)
        {
            value = paramElem->GetAttribute("value");
            float x;
            FDefaultValueHelper::ParseFloat(value, x);
            params.max_angular_velocity = x;
        }

        paramElem = MyChildNode->FindChildNode(TEXT("max_angular_acceleration"));
        if (paramElem)
        {
            value = paramElem->GetAttribute("value");
            float x;
            FDefaultValueHelper::ParseFloat(value, x);
            params.max_angular_acceleration = x;
        }
        paramElem = MyChildNode->FindChildNode(TEXT("angular_arrive_radius"));
        if (paramElem)
        {
            value = paramElem->GetAttribute("value");
            float x;
            FDefaultValueHelper::ParseFloat(value, x);
            params.angular_arrive_radius = x;
        }
        paramElem = MyChildNode->FindChildNode(TEXT("target_rotation"));
        if (paramElem)
        {
            value = paramElem->GetAttribute("value");
            float x;
            FDefaultValueHelper::ParseFloat(value, x);
            params.target_rotation = x;
        }
        paramElem = MyChildNode->FindChildNode(TEXT("look_ahead"));
        if (paramElem)
        {
            value = paramElem->GetAttribute("value");
            float x;
            FDefaultValueHelper::ParseFloat(value, x);
            params.look_ahead = x;
        }
        paramElem = MyChildNode->FindChildNode(TEXT("time_ahead "));
        if (paramElem)
        {
            value = paramElem->GetAttribute("value");
            float x;
            FDefaultValueHelper::ParseFloat(value, x);
            params.time_ahead = x;
        }

	}
	return true;
}

bool ReadGridData(const char* _filename, Grid& grid)
{

  FString CurrentDirectory = FPlatformProcess::GetCurrentWorkingDirectory();

  // Log or use the current working directory
  UE_LOG(LogTemp, Log, TEXT("Current working directory: %s"), *CurrentDirectory);

  FString ContentFolderDir = FPaths::ProjectContentDir();

  //FString FilePath(TEXT("./params.xml"));
  FString params_path = _filename;
  FString FilePath = FPaths::Combine(*ContentFolderDir, *params_path);
  UE_LOG(LogTemp, Log, TEXT("Params Path: %s"), *FilePath);


  FXmlFile MyXml(FilePath, EConstructMethod::ConstructFromFile);

  if (MyXml.GetRootNode())
  {
    const FXmlNode* RootNode = MyXml.GetRootNode();

    const FString MyChildTag("Grid");
    const FXmlNode* MyChildNode = RootNode->FindChildNode(MyChildTag);

    const FXmlNode* element = MyChildNode->FindChildNode("GridSize");

    FString string;
    if (element)
    {

      float x, y;
      FVector Size;
      
      string = element->GetAttribute("x");
      FDefaultValueHelper::ParseFloat(string, x);

      string = element->GetAttribute("y");
      FDefaultValueHelper::ParseFloat(string, y);

      Size = FVector(x, 0, y);
      grid.m_vSize = Size;
    }

    element = MyChildNode->FindChildNode("GridOffset");
    if (element)
    {

      float x, y;
      FVector Size;

      string = element->GetAttribute("x");
      FDefaultValueHelper::ParseFloat(string, x);

      string = element->GetAttribute("y");
      FDefaultValueHelper::ParseFloat(string, y);

      Size = FVector(x, 0, y);
      grid.m_vGridOffset = Size;
    }

    int value;
    element = MyChildNode->FindChildNode("X");
    if (element)
    {
      string = element->GetAttribute("value");
      FDefaultValueHelper::ParseInt(string, value);
      grid.m_weights.Add(TEXT("X"), value);
    }

    element = MyChildNode->FindChildNode("O");
    if (element)
    {
      string = element->GetAttribute("value");
      FDefaultValueHelper::ParseInt(string, value);
      grid.m_weights.Add(TEXT("O"), value);
    }


    element = MyChildNode->FindChildNode("Origin");
    if (element)
    {

      float x, y;
      FVector Size;

      string = element->GetAttribute("x");
      FDefaultValueHelper::ParseFloat(string, x);

      string = element->GetAttribute("y");
      FDefaultValueHelper::ParseFloat(string, y);

      Size = FVector(x, 0, y);
      grid.Location = Size;
    }

    element = MyChildNode->FindChildNode("Final");
    if (element)
    {

      float x, y;
      FVector Size;

      string = element->GetAttribute("x");
      FDefaultValueHelper::ParseFloat(string, x);

      string = element->GetAttribute("y");
      FDefaultValueHelper::ParseFloat(string, y);

      Size = FVector(x, 0, y);
      grid.Destination = Size;
    }

  }
  return true;
}

bool ReadGrid(const char* _filename, Grid& _grid)
{
  FString CurrentDirectory = FPlatformProcess::GetCurrentWorkingDirectory();

  // Log or use the current working directory
  UE_LOG(LogTemp, Log, TEXT("Current working directory: %s"), *CurrentDirectory);

  FString ContentFolderDir = FPaths::ProjectContentDir();

  //FString FilePath(TEXT("./params.xml"));
  FString params_path = _filename;
  FString FilePath = FPaths::Combine(*ContentFolderDir, *params_path);
  UE_LOG(LogTemp, Log, TEXT("Params Path: %s"), *FilePath);


  FXmlFile MyXml(FilePath, EConstructMethod::ConstructFromFile);

  if (MyXml.GetRootNode())
  {
    const FXmlNode* RootNode = MyXml.GetRootNode();

    const FString MyChildTag("Grid");
    const FXmlNode* MyChildNode = RootNode->FindChildNode(MyChildTag);

    const FXmlNode* element = MyChildNode->FindChildNode("Colums");
    if (element)
    {
      int value;
      FString data = element->GetAttribute("value");
      FDefaultValueHelper::ParseInt(data, value);
      _grid.colums = value;
    }

    element = MyChildNode->FindChildNode("Rows");
    if (element)
    {
      int value;
      FString data = element->GetAttribute("value");
      FDefaultValueHelper::ParseInt(data, value);
      _grid.rows = value;
    }

    Cells cell;
    FString Stringvalue;
    for (size_t i = 0; i < _grid.rows; i++)
    {
      TArray<Cells> m_cells;
      _grid.m_Grid.Add(m_cells);
      element = MyChildNode->FindChildNode(FString::Printf(TEXT("Row%i"), i));
      if (element)
      {
        FString data = element->GetAttribute("value");

        for (auto j = 0; j < _grid.colums; ++j)
        { 
          FString copy;
          copy.AppendChar(data[j]);
          if(_grid.m_weights.Contains(copy))
          { 
            cell.m_fWeight = *(_grid.m_weights.Find(copy));
            cell.m_iPosX = j;
            cell.m_iPosY = i;
            _grid.m_Grid[i].Add(cell);
          }
        }
      }
    }
  }
  return true;

}

bool ReadPath(const char* _filename, Path& _path_)
{

    FString CurrentDirectory = FPlatformProcess::GetCurrentWorkingDirectory();

    // Log or use the current working directory
    UE_LOG(LogTemp, Log, TEXT("Current working directory: %s"), *CurrentDirectory);

    FString ContentFolderDir = FPaths::ProjectContentDir();

    //FString FilePath(TEXT("./params.xml"));
    FString params_path = _filename;
    FString FilePath = FPaths::Combine(*ContentFolderDir, *params_path);
    UE_LOG(LogTemp, Log, TEXT("Params Path: %s"), *FilePath);


    FXmlFile MyXml(FilePath, EConstructMethod::ConstructFromFile);


    if (MyXml.GetRootNode())
    {
        const FXmlNode* RootNode = MyXml.GetRootNode();

        const FString MyChildTag("points");
        const FXmlNode* MyChildNode = RootNode->FindChildNode(MyChildTag);

        const FXmlNode* paramElem = MyChildNode->FindChildNode(TEXT("point1"));
        FString value;
        FVector point = FVector(0,0,0);
        float tempValue;
        if (paramElem)
        {
            value = paramElem->GetAttribute("x");
            FDefaultValueHelper::ParseFloat(value, tempValue);
            point.X = tempValue;
            value = paramElem->GetAttribute("y");
            FDefaultValueHelper::ParseFloat(value, tempValue);
            point.Z = tempValue;

            _path_.Path.Add(point);

        }

        paramElem = MyChildNode->FindChildNode(TEXT("point2"));
        if (paramElem)
        {
            value = paramElem->GetAttribute("x");
            FDefaultValueHelper::ParseFloat(value, tempValue);
            point.X = tempValue;
            value = paramElem->GetAttribute("y");
            FDefaultValueHelper::ParseFloat(value, tempValue);
            point.Z = tempValue;

            _path_.Path.Add(point);

        }

        paramElem = MyChildNode->FindChildNode(TEXT("point3"));
        if (paramElem)
        {
            value = paramElem->GetAttribute("x");
            FDefaultValueHelper::ParseFloat(value, tempValue);
            point.X = tempValue;
            value = paramElem->GetAttribute("y");
            FDefaultValueHelper::ParseFloat(value, tempValue);
            point.Z = tempValue;

            _path_.Path.Add(point);
        }
        paramElem = MyChildNode->FindChildNode(TEXT("point4"));
        if (paramElem)
        {
            value = paramElem->GetAttribute("x");
            FDefaultValueHelper::ParseFloat(value, tempValue);
            point.X = tempValue;
            value = paramElem->GetAttribute("y");
            FDefaultValueHelper::ParseFloat(value, tempValue);
            point.Z = tempValue;

            _path_.Path.Add(point);
        }

        paramElem = MyChildNode->FindChildNode(TEXT("point5"));
        if (paramElem)
        {
            value = paramElem->GetAttribute("x");
            FDefaultValueHelper::ParseFloat(value, tempValue);
            point.X = tempValue;
            value = paramElem->GetAttribute("y");
            FDefaultValueHelper::ParseFloat(value, tempValue);
            point.Z = tempValue;

            _path_.Path.Add(point);
        }

        paramElem = MyChildNode->FindChildNode(TEXT("point6"));
        if (paramElem)
        {
            value = paramElem->GetAttribute("x");
            FDefaultValueHelper::ParseFloat(value, tempValue);
            point.X = tempValue;
            value = paramElem->GetAttribute("y");
            FDefaultValueHelper::ParseFloat(value, tempValue);
            point.Z = tempValue;

            _path_.Path.Add(point);
        }

    }

    return true;
}

bool ReadObstacle(const char* _filename, Obstacle& _Obstacles_)
{
  FString CurrentDirectory = FPlatformProcess::GetCurrentWorkingDirectory();

  // Log or use the current working directory
  UE_LOG(LogTemp, Log, TEXT("Current working directory: %s"), *CurrentDirectory);

  FString ContentFolderDir = FPaths::ProjectContentDir();

  //FString FilePath(TEXT("./params.xml"));
  FString ObstaclesPath = _filename;
  FString FilePath = FPaths::Combine(*ContentFolderDir, *ObstaclesPath);
  UE_LOG(LogTemp, Log, TEXT("Params Path: %s"), *FilePath);


  FXmlFile MyXml(FilePath, EConstructMethod::ConstructFromFile);

  if (MyXml.GetRootNode())
  {
    const FXmlNode* RootNode = MyXml.GetRootNode();

    const FString MyChildTag("obstacles");
    const FXmlNode* MyChildNode = RootNode->FindChildNode(MyChildTag);

    const FXmlNode* paramElem = MyChildNode->FindChildNode(TEXT("obstacle1"));
    FString value;
    FVector point = FVector(0, 0, 0);
    float tempValue;

    if (paramElem)
    {
      value = paramElem->GetAttribute("x");
      FDefaultValueHelper::ParseFloat(value, tempValue);
      point.X = tempValue;
      value = paramElem->GetAttribute("y");
      FDefaultValueHelper::ParseFloat(value, tempValue);
      point.Z = tempValue;

      value = paramElem->GetAttribute("r");
      FDefaultValueHelper::ParseFloat(value, tempValue);

      GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("x: %f, y: %f, r: %f"), point.X, point.Z, tempValue));
      _Obstacles_.Radius.Add(tempValue);
      _Obstacles_.Locations.Add(point);

    }
    paramElem = MyChildNode->FindChildNode(TEXT("obstacle2"));

    if (paramElem)
    {
      value = paramElem->GetAttribute("x");
      FDefaultValueHelper::ParseFloat(value, tempValue);
      point.X = tempValue;
      value = paramElem->GetAttribute("y");
      FDefaultValueHelper::ParseFloat(value, tempValue);
      point.Z = tempValue;

      value = paramElem->GetAttribute("r");
      FDefaultValueHelper::ParseFloat(value, tempValue);


      GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("x: %f, y: %f, r: %f"), point.X, point.Z, tempValue));
      _Obstacles_.Radius.Add(tempValue);
      _Obstacles_.Locations.Add(point);

    }
  }
  return false;
}

bool ReadNavMesh(const char* _filename, FNavMeshData& _data)
{
  FString CurrentDirectory = FPlatformProcess::GetCurrentWorkingDirectory();

  // Log or use the current working directory
  UE_LOG(LogTemp, Log, TEXT("Current working directory: %s"), *CurrentDirectory);

  FString ContentFolderDir = FPaths::ProjectContentDir();

  //FString FilePath(TEXT("./params.xml"));
  FString ObstaclesPath = _filename;
  FString FilePath = FPaths::Combine(*ContentFolderDir, *ObstaclesPath);
  UE_LOG(LogTemp, Log, TEXT("Params Path: %s"), *FilePath);


  FXmlFile MyXml(FilePath, EConstructMethod::ConstructFromFile);

  if (MyXml.GetRootNode())
  {
    const FXmlNode* RootNode = MyXml.GetRootNode();
    const FXmlNode* PolygonsNode = RootNode->FindChildNode(TEXT("polygons"));
    if (PolygonsNode)
    {
      for (const FXmlNode* PolygonNode : PolygonsNode->GetChildrenNodes())
      {
        FNavMeshPolygon Polygon;
        for (const FXmlNode* PointNode : PolygonNode->GetChildrenNodes())
        {
          FString XStr = PointNode->GetAttribute(TEXT("x"));
          FString YStr = PointNode->GetAttribute(TEXT("y"));
          XStr.ReplaceInline(TEXT(","), TEXT("."));
          YStr.ReplaceInline(TEXT(","), TEXT("."));

          FVector Point;
          float value;
          bool conversion = FDefaultValueHelper::ParseFloat(XStr, value);
          Point.X = value;
          bool conversion2 = FDefaultValueHelper::ParseFloat(YStr, value);
          Point.Z = value;

          Polygon.m_aPoints.Add(Point);
        }
        _data.Polygons.Add(Polygon);
      }
    }

    const FXmlNode* LinksNode = RootNode->FindChildNode(TEXT("links"));
    if (LinksNode)
    {
      for (const FXmlNode* LinkNode : LinksNode->GetChildrenNodes())
      {
        FNavMeshLink Link;

        const FXmlNode* StartNode = LinkNode->FindChildNode(TEXT("start"));
        const FXmlNode* EndNode = LinkNode->FindChildNode(TEXT("end"));
        FString value;
        if (StartNode && EndNode)
        {
          value = StartNode->GetAttribute(TEXT("polygon"));
          FDefaultValueHelper::ParseInt(value, Link.StartPolygon);

          value = StartNode->GetAttribute(TEXT("edgestart"));
          FDefaultValueHelper::ParseInt(value, Link.StartEdgeStart);

          value = StartNode->GetAttribute(TEXT("edgeend"));
          FDefaultValueHelper::ParseInt(value, Link.StartEdgeEnd);

          value = EndNode->GetAttribute(TEXT("polygon"));
          FDefaultValueHelper::ParseInt(value, Link.EndPolygon);


          value = EndNode->GetAttribute(TEXT("edgestart"));
          FDefaultValueHelper::ParseInt(value, Link.EndEdgeStart);


          value = EndNode->GetAttribute(TEXT("edgeend"));
          FDefaultValueHelper::ParseInt(value, Link.EndEdgeEnd);

          _data.Links.Add(Link);
        }
      }
    }
  }

  return false;
}
