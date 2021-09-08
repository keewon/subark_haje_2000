////////////////////////////////////////////////////////////////////////////////
//
// "ArmorManager.cpp"
//		�尩�Ŵ���
//												�ۼ��� : oedalpha
//												Last Update : 2000. 7. 
//
////////////////////////////////////////////////////////////////////////////////

/// Includes ///////////////////////////////////////////////////////////////////
#include "ArmorManager.h"

/// Public macros & Constants //////////////////////////////////////////////////

/// Global variables ///////////////////////////////////////////////////////////

/// Local functinos ////////////////////////////////////////////////////////////

/// Implementations ////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// ArmorManager::ArmorManager();
// ArmorManager::ArmorManager(PowerTrain*);
//
// Part �� ����Ŭ������ �尩 Ŭ������ ������.
//												�ۼ��� : oedalpha
//												Last Update : 2000. 7.
////////////////////////////////////////////////////////////////////////////////
ArmorManager::ArmorManager(PowerTrain* lp_powertrain) {
	flagStrip = 0;
	nNumberOfArmor = 0;
	lpPowerTrain = lp_powertrain;
}

////////////////////////////////////////////////////////////////////////////////
//
// ArmorManager::~ArmorManager();
//
// Part �� ����Ŭ������ �尩 Ŭ������ �Ҹ���.
//												�ۼ��� : oedalpha
//												Last Update : 2000. 7.
////////////////////////////////////////////////////////////////////////////////
ArmorManager::~ArmorManager() {
}

////////////////////////////////////////////////////////////////////////////////
//
// Value* ArmorManager::Operation(char *lpszOpName, VoidList *lpvlArgument);
//
// Operation �� �����ϴ� �Լ�. Strip �ۿ� ����.
//												�ۼ��� : oedalpha
//												Last Update : 2000. 7.
////////////////////////////////////////////////////////////////////////////////
Value* 
ArmorManager::Operation(char *lpszOpName, VoidList *lpvlArgument) {
	if (!strcmp(lpszOpName, "Strip")) {
		//��� ���ڰ� ���� �ƽ� �ų���
		Strip();

		// ���ϰ� (VOID) ����� �Ƶ� �����ϱ���
		Value *lpvReturn = new Value();
		lpvReturn->lpdt = new DataType();
		lpvReturn->lpdt->tcType = TC_VOID;
		return lpvReturn;
	}
	else return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// Value* ArmorManager::Attribute(char *lpszName);
//
// Attribute �� �о���� �Լ�
//												�ۼ��� : oedalpha
//												Last Update : 2000. 7.
////////////////////////////////////////////////////////////////////////////////
Value* 
ArmorManager::Attribute(char *lpszName) {

	if (!strcmp(lpszName, "numberOfArmor")) {
		IntValue *lpivReturn = new IntValue();
		lpivReturn->n = nNumberOfArmor;
		return lpivReturn;
	}
	else return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// void ArmorManager::Strip();
//
//												�ۼ��� : oedalpha
//												Last Update : 2000. 7.
////////////////////////////////////////////////////////////////////////////////
void 
ArmorManager::Strip() {
	flagStrip = 1;
}

////////////////////////////////////////////////////////////////////////////////
//
// void ArmorManager::Turn();
//
//												�ۼ��� : oedalpha
//												Last Update : 2000. 7.
////////////////////////////////////////////////////////////////////////////////
void 
ArmorManager::Turn() {
	if (flagStrip == 1) {
		StripArmor();
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// void ArmorManager::AddArmor(Armor*)
//
// Armor �� �߰��Ѵ� // ���̸Ӱ� ����� ���� ���� 
//
// Stack �� ����Ͽ� Armor ����
//
//												�ۼ��� : oedalpha
//												Last Update : 2000. 7.
//
////////////////////////////////////////////////////////////////////////////////
void
ArmorManager::AddArmor(Armor* armor1) {
	stackArmorList.Add(armor1);
	nNumberOfArmor++;
	return;
}

////////////////////////////////////////////////////////////////////////////////
//
// ArmorManager::StripArmor()
//
// Armor �� �����Ѵ� // ���̸Ӱ� ����� ���� ���� 
// ������ �ֻ��� Armor�� ���� // ���������� 0 �Ǵ� NULL �� ���ϵ�
//
// Stack �� ����Ͽ� Armor ����
//												�ۼ��� : oedalpha
//												Last Update : 2000. 7.
//
////////////////////////////////////////////////////////////////////////////////
void 
ArmorManager::StripArmor() {
	if (nNumberOfArmor <= 0) {
	}
	else {
		nNumberOfArmor--;
		stackArmorList.Delete();

	}
}

////////////////////////////////////////////////////////////////////////////////
//
// double ArmorManager::Repair(double)
//
// double ����ŭ �ֻ��� �Ƹ��� HP �� �ø���.
// ��� repair �� repair unit ���� ����Ѵ�.
// �ݸ鿡 damage �� armormanager ���� ����Ѵ�.
// ���谡 �̻��� �� ������ ��¼�� ���� �׷��� �Ǿ���...
//												�ۼ��� : oedalpha
//												Last Update : 2000. 7.
//
////////////////////////////////////////////////////////////////////////////////
void
ArmorManager::Repair(double dHpPlus) {
	((stackArmorList.Top->Data)->Repair(dHpPlus));
}

////////////////////////////////////////////////////////////////////////////////
//
// bool ArmorManager::IsHpFull()
//
// HP �� ��á���� true �ƴϸ� false ������
//												�ۼ��� : oedalpha
//												Last Update : 2000. 7.
//
////////////////////////////////////////////////////////////////////////////////
bool 
ArmorManager::IsHpFull() {
	if ((stackArmorList.Top->Data)->GetMaxHp() <= (stackArmorList.Top->Data)->GetHp()) {
		return true;
	}
	else {
		return false;
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// int ArmorManager::GetArmorNumber()
//
// Armor�� ������ �Ѱ��ش�
//												�ۼ��� : oedalpha
//												Last Update : 2000. 8.
//
////////////////////////////////////////////////////////////////////////////////
int
ArmorManager::GetNumberOfArmor() {
	return nNumberOfArmor;
}

////////////////////////////////////////////////////////////////////////////////
//
// Armor�� Damage �� �ִ� �Լ�
// Explorer ���� �θ��� �ȴ�.
//
// ��� repair �� repair unit ���� ����Ѵ�.
// �ݸ鿡 damage �� armormanager ���� ����Ѵ�.
// ���谡 �̻��� �� ������ ��¼�� ���� �׷��� �Ǿ���...
//
//												�ۼ��� : oedalpha
//												Last Update : 2000. 10.
//
////////////////////////////////////////////////////////////////////////////////
void
ArmorManager::Damage(int bulletType, int nDamage) {
	
	double dArmorHp; 
	if (stackArmorList.Top == 0) {
		lpPowerTrain->Damage(bulletType, (double)nDamage);
	} else {
		dArmorHp = stackArmorList.Top->Data->GetHp();
		Armor armorNewTop;

		if (dArmorHp > (double)nDamage) {
			stackArmorList.Top->Data->Damage(bulletType, (double)nDamage );
		} else if (dArmorHp <= (double)nDamage) {
			stackArmorList.Top->Data->Damage(bulletType, dArmorHp);
			StripArmor();
		}
	}
}
////////////////////////////////////////////////////////////////////////////////
//
// int ArmorManager::GetCurrentArmor()
//
// ���� �ֻ��� Armor�� int ���� return �Ѵ�.
//												�ۼ��� : oedalpha
//												Last Update : 2000. 10.
////////////////////////////////////////////////////////////////////////////////

/*int ArmorManager::GetCurrentArmor() {
	return ((Armor*)stackArmorList.Top->Data)->GetType();
}
*/


