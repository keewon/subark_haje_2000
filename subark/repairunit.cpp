////////////////////////////////////////////////////////////////////////////////
//
// "RepairUnit.cpp"
//		RepairUnit
//												�ۼ��� : oedalpha
//												Last Update : 2000. 7. 
//
////////////////////////////////////////////////////////////////////////////////

/// Includes ///////////////////////////////////////////////////////////////////
#include "RepairUnit.h"
#include <stdio.h>
/// Public macros & Constants //////////////////////////////////////////////////

/// Global variables ///////////////////////////////////////////////////////////

/// Local functinos ////////////////////////////////////////////////////////////

/// Implementations ////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// RepairUnit::RepairUnit();
//
// Part �� ����Ŭ������ ���� ������ Ŭ������ ������.
//
//												�ۼ��� : oedalpha
//												Last Update : 2000. 7.
////////////////////////////////////////////////////////////////////////////////
RepairUnit::RepairUnit(ArmorManager* lpA, PowerTrain* lpP) {
	lpArmorManager = lpA;
	lpPowerTrain = lpP;
}

////////////////////////////////////////////////////////////////////////////////
//
// RepairUnit::~RepairUnit();
//
// Part �� ����Ŭ������ ���� ������ Ŭ������ �Ҹ���.
//												�ۼ��� : oedalpha
//												Last Update : 2000. 7.
////////////////////////////////////////////////////////////////////////////////
RepairUnit::~RepairUnit() {
}

////////////////////////////////////////////////////////////////////////////////
//
// Value* RepairUnit::Operation(char *lpszOpName, VoidList *lpvlArgument);
//
// Operation �� �����ϴ� �Լ�. Repair �� Stop �ΰ��� ������ �ִ�.
//												�ۼ��� : oedalpha
//												Last Update : 2000. 7.
////////////////////////////////////////////////////////////////////////////////
Value* RepairUnit::Operation(char *lpszOpName, VoidList *lpvlArgument) {
	if (!strcmp(lpszOpName, "Repair")) {
		int nParam1;

		if (((Value*)lpvlArgument->lpveHead->lpElement)->lpdt->tcType == TC_INT)
			nParam1 = ((IntValue*)lpvlArgument->lpveHead->lpElement)->n;
		else
			nParam1 = -1;
		Repair(nParam1);

		Value *lpvReturn = new Value();
		lpvReturn->lpdt = new DataType();
		lpvReturn->lpdt->tcType = TC_VOID;
		return lpvReturn;
	}
	else if (!strcmp(lpszOpName, "Stop")) {
		Stop();

		Value *lpvReturn = new Value();
		lpvReturn->lpdt = new DataType();
		lpvReturn->lpdt->tcType = TC_VOID;
		return lpvReturn;
	}
	else {
		return NULL;
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// Value* RepairUnit::Attribute(char *lpszName);
//
// Attribute �� �о���� �Լ�
//												�ۼ��� : oedalpha
//												Last Update : 2000. 7.
////////////////////////////////////////////////////////////////////////////////
Value* RepairUnit::Attribute(char *lpszName) {
	if (!strcmp(lpszName, "state")) {
		IntValue *lpivReturn = new IntValue();
		lpivReturn->n = flagRepairState;
		return lpivReturn;
	}
	if (!strcmp(lpszName, "select")) {
		IntValue *lpivReturn = new IntValue();
		lpivReturn->n = flagSelect;
		return lpivReturn;
	}
	else if (!strcmp(lpszName, "fuel")) {
		IntValue *lpivReturn = new IntValue();
		lpivReturn->n = (int)dUnitFuel;
		return lpivReturn;
	}
	else {
		return NULL;
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// void RepairUnit::Repair(int _flagSelect);
//
//												�ۼ��� : oedalpha
//												Last Update : 2000. 7.
////////////////////////////////////////////////////////////////////////////////
void RepairUnit::Repair(int flag_Select) {
	flagSelect = flag_Select;
	flagRepairState = 1;
}

////////////////////////////////////////////////////////////////////////////////
//
// void RepairUnit::Stop();
//
//												�ۼ��� : oedalpha
//												Last Update : 2000. 7.
////////////////////////////////////////////////////////////////////////////////
void RepairUnit::Stop() {
	flagRepairState = 0;
}

////////////////////////////////////////////////////////////////////////////////
//
// void RepairUnit::Turn();
//
//												�ۼ��� : oedalpha
//												Last Update : 2000. 7.
////////////////////////////////////////////////////////////////////////////////
void RepairUnit::Turn() {
	// ����������� ���ᰡ �ٴڳ��� ���̻� ��ĥ �� ����.
	// ��ġ��� �÷��װ� ���������� ��ġ�� �ʴ´�.
	if (dUnitFuel <=0 || flagRepairState != 1) return;

	// ������������ �ϴ� ��ġ�� ���߿� �˻縦 �Ͽ�����
	// �˻縦 �����ϰ� ���߿� ��ġ�� �������� �ϴ� ���� �� ���� �� ���Ƽ�
	// �׷��� �Ϸ��� �Ѵ�. (������ ���� ��������)
	// �׸��� ������ ���� ��� 3�� ��ġ�� �����µ��� 10�� �������� �Ҹ��Ͽ�
	// ��ġ�� �ȴ�. ���� ������� �ʾ����� ����� ���ǵ� �ִ�.
	// �׷����� �ƸӸŴ����� �Ŀ�Ʈ������ HP �� �˾ƺ��� �Լ��Ǵ�
	// 1�� ��ġ�鼭 ��������� Full ���� �˻��ϴ� ����� �ְڴ�
	// �׷��� ���ڴ� ��ȿ������ ���̴�.
	
	switch(flagSelect) {
		case 0: // �Ŀ�Ʈ����, �尩 �Ѵ� ��ġ��

			// �̹� HP �� ��á�ٸ� ��ĥ �ʿ䰡 ������.
			// �װ� ���� �˻��սô�
			if (lpPowerTrain->IsHpFull()){
				if (lpArmorManager->IsHpFull()){
					// �Ѵ� HP �� ���� ���
					flagRepairState = 0;
				}
				else{
					// PowerTrain �� HP �� ���� ���
					// �ϴ� flag �� �����Ѵ�.
					flagSelect = 2; //�尩�� ��ġ��
					// ������ ���� �尩�� ��ģ��
					dUnitFuel -= dConsumeSpeed;
					lpArmorManager->Repair(dRepairSpeed);
				}
			}
			else {
				if (lpArmorManager->IsHpFull()){
					// ArmorManager �� HP �� ���� ���
					// �Ŀ�Ʈ���θ� ��ġ��� �÷��� ��ȯ
					flagSelect = 1;
					// ������ ���� �Ŀ�Ʈ���θ� ��ģ��.
					dUnitFuel -= dConsumeSpeed;
					lpPowerTrain->Repair(dRepairSpeed);
				}
				else{
					// �Ѵ� HP �� �� ���� ���� ���
					// 50:50 ���� ���� ��踦 ��ģ��.
					dUnitFuel -= dConsumeSpeed;
					lpPowerTrain->Repair(dRepairSpeed/2.);
					lpArmorManager->Repair(dRepairSpeed/2.);
				}
			}

			break;
		case 1: // �Ŀ�Ʈ���θ� ��ġ��
			if (lpPowerTrain->IsHpFull()) {
				flagRepairState = 0;
				return;
			}
			else {
				dUnitFuel -= dConsumeSpeed;
				lpPowerTrain->Repair(dRepairSpeed);
			}

			break;
		case 2: // �尩�� ��ġ��
			if (lpArmorManager->IsHpFull()) {
				flagRepairState = 0;
				return;
			}
			else {
				dUnitFuel -= dConsumeSpeed;
				lpArmorManager->Repair(dRepairSpeed);
			}

			break;
	}
	return;
}

