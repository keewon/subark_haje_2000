#ifndef _Map_
#define _Map_


#define MAX_ELE 100

class PartQueue;
class Object;
class Map  
{
private:
	int Row, Column;

public:
	int * * Geometry;
	PartQueue * PartList;
	Object *ObjectList[100];

	//oedalpha changed this
	Map(const int & RowSize = 60, const int & ColumnSize = 60);
	~Map(void);

	int xSize(void);
	int ySize(void);
	int QueryGeometry(int x, int y);
	Object ** getObject();
	void Append(Object *);
	void Delete(Object *);
};

#endif
