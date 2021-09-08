////////////////////////////////////////////////////////////////////////////////
//
// "Weapon.cpp"
//		Weapon
//													�ۼ��� : searer
//													Last Update : 2000. 8. 4
//
////////////////////////////////////////////////////////////////////////////////

/// Includes ///////////////////////////////////////////////////////////////////

#include "Weapon.h"

/// Public macros & Constants //////////////////////////////////////////////////

/// Implementations ////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Weapon::~Weapon();
//		class Weapon �� �Ҹ���
//													�ۼ��� : searer
//													Last Update : 2000. 7. 26
//
////////////////////////////////////////////////////////////////////////////////

Weapon::~Weapon() {
}

////////////////////////////////////////////////////////////////////////////////
//
// Value* Weapon::Operation(char *lpszOpName, VoidList *lpvlArgument);
//		Operation �� �����ϴ� �Լ�
//													�ۼ��� : searer
//													Last Update : 2000. 8. 4
//
////////////////////////////////////////////////////////////////////////////////

Value* Weapon::Operation(char *lpszOpName, VoidList *lpvlArgument) {
	// Rotate
	if (!strcmp(lpszOpName, "Rotate")) {
		// ���� �и��ϱ�
		double dParam;

		dParam = ((RealValue*)lpvlArgument->lpveHead->lpElement)->r;

		// ����
		Rotate(dParam);

		// ���ϰ� �����
		Value *lpvReturn = new Value();
		lpvReturn->lpdt = new DataType();
		lpvReturn->lpdt->tcType = TC_VOID;

		return lpvReturn;
	}
	// Fire
	else if (!strcmp(lpszOpName, "Fire")) {
		// ����
		Fire();

		// ���ϰ� �����
		Value *lpvReturn = new Value();
		lpvReturn->lpdt = new DataType();
		lpvReturn->lpdt->tcType = TC_VOID;
		return lpvReturn;
	}
	// Target
	else if (!strcmp(lpszOpName, "Target")) {
		// ���� �и��ϱ�
		int nParam;

		nParam = ((IntValue*)lpvlArgument->lpveHead->lpElement)->n;

		// ����
		Target(nParam);

		// ���ϰ� �����
		Value *lpvReturn = new Value();
		lpvReturn->lpdt = new DataType();
		lpvReturn->lpdt->tcType = TC_VOID;

		return lpvReturn;
	}
	else
		return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// Value* Weapon::Attribute(char *lpszName);
//		Attribute �� �о���� �Լ�
//													�ۼ��� : searer
//													Last Update : 2000. 8. 4
//
////////////////////////////////////////////////////////////////////////////////

Value* Weapon::Attribute(char *lpszName) {
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// Weapon::Rotate(int nAimAngle);
//		���� ȸ�� ������ �����ִ� �Լ�
//													�ۼ��� : searer
//													Last Update : 2000. 8. 4
//
////////////////////////////////////////////////////////////////////////////////

void Weapon::Rotate(double dInAimAngle) {
	bRotate = true;
	dAimAngle = dInAimAngle;
}

////////////////////////////////////////////////////////////////////////////////
//
// Weapon::Fire();
//		�߻� flag �� set �� �ִ� �Լ�
//													�ۼ��� : searer
//													Last Update : 2000. 7. 26
//
////////////////////////////////////////////////////////////////////////////////

void Weapon::Fire() {
	bFire = true;
}

////////////////////////////////////////////////////////////////////////////////
//
// Weapon::Target(int nInFlyDistance);
//		���ư� �Ÿ��� �����ִ� �Լ�
//													�ۼ��� : searer
//													Last Update : 2000. 8. 4
//
////////////////////////////////////////////////////////////////////////////////

void Weapon::Target(int nInFlyDistance) {
	if (nRange <= nInFlyDistance)
		nFlyDistance = nRange;
	else
		nFlyDistance = nInFlyDistance;
}
