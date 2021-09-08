////////////////////////////////////////////////////////////////////////////////
//
// "Weapon.cpp"
//		Weapon
//													작성자 : searer
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
//		class Weapon 의 소멸자
//													작성자 : searer
//													Last Update : 2000. 7. 26
//
////////////////////////////////////////////////////////////////////////////////

Weapon::~Weapon() {
}

////////////////////////////////////////////////////////////////////////////////
//
// Value* Weapon::Operation(char *lpszOpName, VoidList *lpvlArgument);
//		Operation 을 실행하는 함수
//													작성자 : searer
//													Last Update : 2000. 8. 4
//
////////////////////////////////////////////////////////////////////////////////

Value* Weapon::Operation(char *lpszOpName, VoidList *lpvlArgument) {
	// Rotate
	if (!strcmp(lpszOpName, "Rotate")) {
		// 인자 분리하기
		double dParam;

		dParam = ((RealValue*)lpvlArgument->lpveHead->lpElement)->r;

		// 실행
		Rotate(dParam);

		// 리턴값 만들기
		Value *lpvReturn = new Value();
		lpvReturn->lpdt = new DataType();
		lpvReturn->lpdt->tcType = TC_VOID;

		return lpvReturn;
	}
	// Fire
	else if (!strcmp(lpszOpName, "Fire")) {
		// 실행
		Fire();

		// 리턴값 만들기
		Value *lpvReturn = new Value();
		lpvReturn->lpdt = new DataType();
		lpvReturn->lpdt->tcType = TC_VOID;
		return lpvReturn;
	}
	// Target
	else if (!strcmp(lpszOpName, "Target")) {
		// 인자 분리하기
		int nParam;

		nParam = ((IntValue*)lpvlArgument->lpveHead->lpElement)->n;

		// 실행
		Target(nParam);

		// 리턴값 만들기
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
//		Attribute 를 읽어오는 함수
//													작성자 : searer
//													Last Update : 2000. 8. 4
//
////////////////////////////////////////////////////////////////////////////////

Value* Weapon::Attribute(char *lpszName) {
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// Weapon::Rotate(int nAimAngle);
//		포대 회전 각도를 정해주는 함수
//													작성자 : searer
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
//		발사 flag 를 set 해 주는 함수
//													작성자 : searer
//													Last Update : 2000. 7. 26
//
////////////////////////////////////////////////////////////////////////////////

void Weapon::Fire() {
	bFire = true;
}

////////////////////////////////////////////////////////////////////////////////
//
// Weapon::Target(int nInFlyDistance);
//		날아갈 거리를 정해주는 함수
//													작성자 : searer
//													Last Update : 2000. 8. 4
//
////////////////////////////////////////////////////////////////////////////////

void Weapon::Target(int nInFlyDistance) {
	if (nRange <= nInFlyDistance)
		nFlyDistance = nRange;
	else
		nFlyDistance = nInFlyDistance;
}
