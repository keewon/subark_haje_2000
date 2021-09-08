#include "Map.h"
#include "PartQueue.h"

Map::
Map(const int & RowSize, const int & ColumnSize): Row(RowSize), Column(ColumnSize)
{
	Geometry = new int *[Row];
	for (int i = 0; i < Row; ++i)
	{
		Geometry[i] = new int[Column];
		//for (int j = 0; j < Column; j++) Geometry[i][j] = 0;
	}

	PartList = new PartQueue();

	//object list initiate
	for (int i = 0; i < MAX_ELE; ++i)
		ObjectList[i] = 0;
}

Map::
~Map(void)
{
	for (int i = 0; i < Row; ++i)
		delete [] Geometry[i];
	delete [] Geometry;
}

int
Map::
xSize(void)
{
	return Column;
}

int
Map::
ySize(void)
{
	return Row;
}

int
Map::
QueryGeometry(int x, int y)
{
	if (x < 0 || Column <= x || y < 0 || Row <= y)
		return 1;
	else
		return Geometry[y][x];	
}
//	Geometry value information:
//		0 : Ground
//		1 : Mountain

Object **
Map::
getObject()
{
	return ObjectList;
}

void 
Map::
Append(Object *a)
{
	for (int i = 0; i < MAX_ELE; ++i)
		if (!ObjectList[i])
		{
			ObjectList[i] = a;
			break;
		}
}

void 
Map::
Delete(Object *a)
{
	for (int i = 0; i < MAX_ELE; ++i)
		if (ObjectList[i] == a)
		{
			ObjectList[i] = NULL;
			break;
		}
}