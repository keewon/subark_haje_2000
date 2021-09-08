#ifndef _EXPLORER_H_
#define _EXPLORER_H_

/// Includes ///////////////////////////////////////////////////////////////////
#include "Object.h"
#include "Part.h"
// parts include
// #include "ArmorManager.h"

/// Defines ////////////////////////////////////////////////////////////////////
#define MAX_PARTS_OF_EXPLORER 20

#ifndef _PARTS_ID_DEFINE_
#define _PARTS_ID_DEFINE_

// Part Type Define --------------------------------------
#define PT_POWER_TRAIN			  0
#define PT_WEAPON				  1
#define PT_SENSOR				  2
#define PT_MEMORY				  3
#define PT_CPU					  4
#define PT_ARMOR				  5
#define PT_REPAIR_UNIT			  6
#define PT_SPEACIAL_CHIPS		  7
#define PT_TRANSMITTER			  8

// Part ID Define ----------------------------------------
// Power Train
#define PI_TRIKE				000
#define PI_CATAPULT				001
#define PI_DRAGOON				002
#define PI_HOVER				003

// Weapon - Sub Menu
#define PI_STRAIGHT_SHOOT		 00
#define PI_ARTILERY_TYPE		 10
#define PI_MINE					 20
#define PI_SPECIAL				 30

// Weapon - Straight Shooting Weapon
#define PI_STRAIGHT_CANNON		100
#define PI_VULCAN				101
#define PI_RAIL_CANNON			102
#define PI_STAIGHT_ENERGY_FIELD	103

// Weapon - Artilery Type
#define PI_ARTILERY_CANNON		110
#define PI_SHOT_CANNON			111
#define PI_METRO_CANNON			112
#define PI_ENERGY_CANNON		113

// Weapon - Mine
#define PI_NORMAL_MINE			120
#define PI_METRO_MINE			121
#define PI_ENERGY_MINE			122

// Weapon - Special
#define PI_NUCLEAR_CONTROLLER	130
#define PI_HOMING_MISSILE		131

// Sensor
#define PI_SENSOR_NORMAL		200
#define PI_BLACK_SHEEP_WALL		201
#define PI_WIZARD_EYE			202
#define PI_AMBUSHER				203

// Memory
#define PI_MEMORY				300

// CPU
#define PI_CPU					400

// Armor
#define PI_LIQUID_METAL			500
#define PI_DURALUMIN			501
#define PI_CARBON_COATING		502
#define PI_ALUMINUM				503
#define PI_STEEL				504

// Repair Unit
#define PI_REPAIR_ROBOT			600

// Special Chips
#define PI_CHIP_NOTHING			700

// Transmitter
#define PI_TRANSMITTER			800

#endif //_PARTS_ID_DEFINE_

/// Class or functions /////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class Explorer
//												ÀÛ¼ºÀÚ : felix
//												Last Update : 2000. 8. 22
//
////////////////////////////////////////////////////////////////////////////////

class Explorer : public Object {

//	Operations
	public:
		Explorer(char *);
		Explorer();
		~Explorer();

		void QueryPosition(int*, int*);
		void SetPosition(int, int);
		Part* QueryPart(char*);
		Part* PopaPart();
		void InitializeofPoping();
		bool IsLastPart();
		bool AppendParts(int, int, char*);
		void AppendParts(Part*, char*);

		bool GetMoveStatus();
		void SetMoveStatus(int);

// oedalpha added these one line
		void Damage(int);

// oedalpha added these two lines
		void Turn();
		void Draw();

	private:
		bool ReadExplorerfromFile(char*);
		bool CheckbyName(int, char*);

//  Variables
	private:
		int PositionX;
		int PositionY;
		int NumberofParts;
		int PopNext;
		char *PartName[MAX_PARTS_OF_EXPLORER];
		Part *PartofExplorer[MAX_PARTS_OF_EXPLORER];
		//readfile *Readfile;

		//oedalpha add this line
		bool bMoveStatus;

};

#endif  //_EXPLORER_H_
