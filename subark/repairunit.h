////////////////////////////////////////////////////////////////////////////////
//
// "RepairUnit.h"
//		RepairUnit
//												�ۼ��� : oedalpha
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
// Part �� ����Ŭ������ ���� ������ Ŭ����
//												�ۼ��� : oedalpha
//												Last Update : 2000. 7.
//
////////////////////////////////////////////////////////////////////////////////

class RepairUnit : public Part{
	public:
		RepairUnit(ArmorManager* lpA, PowerTrain* lpP);
		~RepairUnit();						// �Ҹ���
		Value* Operation(char *lpszOpName, VoidList *lpvlArgument);
		Value* Attribute(char *lpszName);
		void Repair(int);
		void Stop();
		void Turn();
	private:
		double dRepairSpeed;					// ��ġ�� �ӵ� (�����/��)
		double dConsumeSpeed;				// �ѹ���ġ�µ� ��� ������ ��
		double dUnitFuel;					// ���������� ���� ������ ��

		int flagSelect;						// ������ �������� ����
			//0 == both, 1 == powertrain, 2 == armor
		int flagRepairState;				// ������ �� ������
			//0 == nonRepair, 1 == Repair
		ArmorManager *lpArmorManager;		// ��ĥ �ƸӸŴ���
		PowerTrain *lpPowerTrain;
};

#endif // _REPAIRUNIT_H_OEDALPHA_BECD_
