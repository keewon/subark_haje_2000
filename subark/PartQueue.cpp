#include "PartQueue.h"

PartQueue::PartQueue()
{
	int i;

	now = 0;
	last = 0;
	read_part = -1;

	for( i=0 ; i < MAX_PART_OBJECTS ; i++ )
	{
		PartsList[i] = NULL;
	}
}

PartQueue::~PartQueue()
{
}

bool PartQueue::Append(Part *AppendItem)
{
	if ( AppendItem == NULL )
		return false;
	if ( last >= MAX_PART_OBJECTS )
		return false;
	PartsList[ last ] = AppendItem;
	last++;
	return true;
}

Part *PartQueue::ReadHeader()
{
	if ( last == 0 )
		return NULL;
	now = 0;
	return PartsList[ 0 ];
}

Part *PartQueue::Read()
{
	if ( last == 0 ) {
		now = 0;
		return NULL;
	}

	read_part = now;
	now++;
	if ( now >= last)
		now -= last;

	return PartsList[ read_part ];
}

bool PartQueue::Delete()
{
	int i;
	if (last == 0 || read_part == -1) 
		return false;

	now = read_part;

	for( i = now ; i < last-2 ; i++ )
		PartsList[i] = PartsList[i+1];
	PartsList[ last-1 ] = NULL;

	last--;

	if (last == 0 )
		now = 0;
	else if (now >= last )
		now -= last;

	return true;
}

bool PartQueue::Delete(Part *target)
{
	int i, j;
	for( i = 0 ; i < last-1 ; i++ )
		if (PartsList[i] == target) {
			for( j = i ; j < last-2 ; j++ )
				PartsList[j] = PartsList[j+1];
			PartsList[ last - 1 ] = NULL;
			last--;

			return true;
		}
	return false;
}