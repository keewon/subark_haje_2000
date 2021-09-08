#include "explorer.h"
#include "ArmorManager.h"

Explorer::Explorer(char *Filename)
{
	int i;

	PositionX = 100;
	PositionY = 100;
	NumberofParts = 0;
	PopNext = -1;

	for( i = 0 ; i < MAX_PARTS_OF_EXPLORER; i++ ) 
	{
		PartName[i] = NULL;
		PartofExplorer[i] = NULL;
	}

//	ReadExplorerfromFile(Filename);
}

Explorer::Explorer()
{
	int i;

	PositionX = 100;
	PositionY = 100;
	NumberofParts = 0;
	PopNext = -1;

	for( i = 0 ; i < MAX_PARTS_OF_EXPLORER; i++ ) 
	{
		PartName[i] = NULL;
		PartofExplorer[i] = NULL;
	}
}

Explorer::~Explorer()
{
	int i;

	for( i = 0 ; i < MAX_PARTS_OF_EXPLORER; i++ )
	{
		if (PartName[i] != NULL)
			delete (PartName[i]);
		if (PartofExplorer[i] != NULL)
			delete (PartofExplorer[i]);
	}
}

void Explorer::QueryPosition(int *x,int *y)
{
	*x = PositionX;
	*y = PositionY;
}

void Explorer::SetPosition(int x, int y)
{
	PositionX = x;
	PositionY = y;
}

Part* Explorer::QueryPart(char *PartsName)
{
	int i;
	
	for( i = 0 ; i < NumberofParts ; i++ )
	{
		if ( CheckbyName( i , PartsName ) ) {
			return (PartofExplorer[i]);
		}
	}

	return NULL;
}

Part* Explorer::PopaPart()
{
	if ( PopNext >= NumberofParts ) {
		InitializeofPoping();
		return NULL;
	}
	PopNext++;
	return ( PartofExplorer[ PopNext-1 ] );
}

bool Explorer::IsLastPart()
{
	if ( PopNext >= NumberofParts ) {
		InitializeofPoping();
		return true;
	}
	return false;
}

void Explorer::InitializeofPoping()
{
	PopNext = 0;
}

bool Explorer::GetMoveStatus()
{
	return bMoveStatus;
}

void Explorer::SetMoveStatus(int Status)
{
	if (Status == 0) {
		bMoveStatus = false;
	}
	else {
		bMoveStatus = true;
	}
}
/*
bool Explorer::ReadExplorerfromFile(char* FileName)
{
	File

}
*/

/*
bool Explorer::AppendParts(int PartTypeID, int PartID, char* PartName)
{
	PART *temp;
	switch (PartTypeID)
	{
		// Power Train
		case PT_POWER_TRAIN :
			switch (PartID)
			{
				case PI_TRIKE :
					temp = new PTTrike();
					break;
				case PI_CATAPULT :
					temp = new PTCaterpillar();
					break;
				case PI_DRAGOON :
					temp = new PTDragoon();
					break;
				case PI_HOVER :
					temp = new PTHover();
					break;
				default :
					return false;
			}
			break;

		// Weapon
/*		case PT_WEAPON :
			switch ( PartID - (int)(PartID / 100) * 100 )
			{
				case PI_STRAIGHT_CANNON :
					switch (PartID)
					{
						case PI_STRAIGHT_CANNON :
							break;
						case PI_VULCAN :
							break;
						case PI_RAIL_CANNON :
							break;
						case PI_STAIGHT_ENERGY_FIELD :
							break;
						default :
							return false;
					}
					break;
				case PI_ARTILERY_TYPE :
					switch (PartID)
					{
						case PI_ARTILERY_CANNON :
						case PI_SHOT_CANNON :
						case PI_METRO_CANNON :
						case PI_ENERGY_CANNON :
						default :
							return false;
					}
					break;
				case PI_MINE :
					switch (PartID)
					{
						case PI_NORMAL_MINE :
						case PI_METRO_MINE :
						case PI_ENERGY_MINE :
						default :
							return false;
					}
					break;
				case PI_SPECIAL :
					switch (PartID)
					{
						case PI_NUCLEAR_CONTROLLER :
						case PI_HOMING_MISSILE :
						default :
					}
					break;
				default : 
			}
			break; */

		// Sensor
/*		case PT_SENSOR :
			switch (PartID)
			{
				case PI_SENSOR_NORMAL :
					temp = new NormalSensor(this);
					break;
				case PI_BLACK_SHEEP_WALL :
					temp = new BlackSheepWall();
					break;
				case PI_WIZARD_EYE :
					temp = new WizardEye();
					break;
				case PI_AMBUSHER :
					temp = new Ambusher();
					break;
				default :
					return false;
			}
			break;

		// Memory
		case PT_MEMORY :
			switch (PartID)
			{
				case PI_MEMORY :
					temp = new Memory (Program *, nSize);
					break;
				default :
					return false;
			}
			break;

		// CPU
		case PT_CPU :
			switch (PartID)
			{
				case PI_CPU :
					break;
				default :
					return false;
			}
			break;

		// Armor
		case PT_ARMOR :
			switch (PartID)
			{
				case PI_LIQUID_METAL :
					temp = new ArmorLiquidMetal();
					break;
				case PI_DURALUMIN :
					temp = new ArmorDuralumin();
					break;
				case PI_CARBON_COATING :
					temp = new ArmorCarbon();
					break;
				case PI_ALUMINUM :
					temp = new ArmorAluminum();
					break;
				case PI_STEEL :
					temp = new ArmorSteel();
					break;
				default :
					return false;
			}
			break;

		// Repair Unit
		case PT_REPAIR_UNIT :
			switch (PartID)
			{
				case PI_REPAIR_ROBOT :
					temp = new RepairUnit();
					break;
				default :
					return false;
			}
			break;

		case PT_SPEACIAL_CHIPS :
			switch (PartID)
			{
				case PI_CHIP_NOTHING :
					return false;
				default :
					return false;
			}
			break;

		default :
			return false;
	}
	return true;
}*/

void Explorer::AppendParts(Part *RPartPtr, char *RPartName)
{
	PartName[NumberofParts] = RPartName;
	PartofExplorer[NumberofParts] = RPartPtr;
	NumberofParts++;
	
}

bool Explorer::CheckbyName(int NPart, char* TargetPartName)
{
	int i = 0;
	bool chk = true;
	char temp;

	while( ( temp = *( TargetPartName + i ) ) != '\0' && chk ) 
	{
		if ( *( PartName[NPart] + i ) != temp )
			chk = false;
		i++;
	}

	if ( *( PartName[NPart] + i ) != '\0' ) chk= false;

	return chk;
}

void Explorer::Turn()
{
	for (int i = 0; i < NumberofParts; i++) {
		PartofExplorer[i]->Turn();
	}
}

void Explorer::Draw()
{
	for (int i = 0; i < NumberofParts; i++) {
		PartofExplorer[i]->Draw();
	}
}

void Explorer::Damage(int nDamage) 
{
	ArmorManager* am = (ArmorManager*)QueryPart("ArmorManager");
	
	if (am != NULL) {
		am->Damage(1, nDamage);
	}
	else {
		// 원래는 PowerTrain에 Damage가 가게 하고 싶지만
		// PowerTrain의 이름은 정해진 것이 아니라서 그럴 수가 없다
	}
	
}
