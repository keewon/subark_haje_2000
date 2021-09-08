////////////////////////////////////////////////////////////////////////////////
//
// "RepairUnit.h"
//		RepairUnit
//												작성자 : oedalpha
//												Last Update : 2000. 7. 
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _REPAIRUNIT_H_OEDALPHA_BECD_
#define _REPAIRUNIT_H_OEDALPHA_BECD_

/// Includes ///////////////////////////////////////////////////////////////////
#include "DataType.h"
#include "Types.h"
#include "Value.h"
#include "Part.h"
#include "Armor.h"
#include "ArmorManager.h"
#include "PowerTrain.h"
/// Public macros & Constants //////////////////////////////////////////////////


/// Class or functions /////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
// class RepairUnit
//
// Part 의 하위클래스인 수리 유닛의 클래스
//												작성자 : oedalpha
//												Last Update : 2000. 7.
//
////////////////////////////////////////////////////////////////////////////////

class RepairUnit : public Part{
	public:
		RepairUnit(ArmorManager* lpA, PowerTrain* lpP);
		~RepairUnit();						// 소멸자
		Value* Operation(char *lpszOpName, VoidList *lpvlArgument);
		Value* Attribute(char *lpszName);
		void Repair(int);
		void Stop();
		void Turn();
	private:
		double dRepairSpeed;					// 고치는 속도 (연료양/턴)
		double dConsumeSpeed;				// 한번고치는데 드는 연료의 양
		double dUnitFuel;					// 수리유닛이 쓰는 연료의 양

		int flagSelect;						// 무엇을 수리할지 결정
			//0 == both, 1 == powertrain, 2 == armor
		int flagRepairState;				// 수리할 지 안할지
			//0 == nonRepair, 1 == Repair
		ArmorManager *lpArmorManager;		// 고칠 아머매니저
		PowerTrain *lpPowerTrain;
};

#endif // _REPAIRUNIT_H_OEDALPHA_BECD_
