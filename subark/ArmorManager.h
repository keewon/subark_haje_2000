////////////////////////////////////////////////////////////////////////////////
//
// "ArmorManager.h"
//		�尩�Ŵ���(�ƸӸŴ���)
//												�ۼ��� : oedalpha
//												Last Update : 2000. 10.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _ARMORMANAGER_H_OEDALPHA_BECD_
#define _ARMORMANAGER_H_OEDALPHA_BECD_

/// Includes ///////////////////////////////////////////////////////////////////
#include "DataType.h"
#include "Types.h"
#include "Value.h"
#include "Explorer.h"
#include "PowerTrain.h"
#include "Armor.h"

/// Public macros & Constants //////////////////////////////////////////////////


/// Class or functions /////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class ArmorManager
//
// Part �� ����Ŭ������ �尩������(�ƸӸŴ���)�� Ŭ����
//												�ۼ��� : oedalpha
//												Last Update : 2000. 10.
//
////////////////////////////////////////////////////////////////////////////////

class ArmorManager : public Part{
	public:
		ArmorManager(PowerTrain*);
		~ArmorManager();
		Value* Operation(char *lpszOpName, VoidList *lpvlArgument);
		Value* Attribute(char *lpszName);
		void Strip();				// Armor �� �����
		void Turn();
		void Draw() {}

		// ���� �Լ�
		void AddArmor(Armor*);	// Armor �� �߰��Ѵ�
									// ���̸Ӱ� ����� ���� ����
									// ����ڰ� �߰��� Armor�� ����
									// ������ �� ����ؾ��Ѵ�
		void StripArmor();		// Armor �� ����� ���θ��
									// �ֻ��� Armor �� �����Ѵ�
		int GetNumberOfArmor();		// Armor�� ������ �����Ѵ�
		void Repair(double);		// Armor �� ��ģ��.
		bool IsHpFull();			// Hp �� ��á���� �ƴ��� �����ش�
		void Damage(int, int);		// Damage �� �ش�. HP return
									// Hp�� 0�̸� �ڵ����� Armor����
									// Explorer ���� �θ��� �ȴ�.
		//int GetCurrentArmor();		// ���� Armor �� ������ Return

	private:
		Stack<Armor*> stackArmorList;
									// Armor ���� ����Ʈ �������� ����
		PowerTrain* lpPowerTrain;	// PowerTrain �� ������
		int flagStrip;				// 0 == ����. 1 == ������
		int nNumberOfArmor;			// �԰� �ִ� �Ƹ��� ����
};
#endif // _ARMORMANAGER_H_OEDALPHA_BECD_
