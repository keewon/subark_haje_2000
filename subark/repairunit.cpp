////////////////////////////////////////////////////////////////////////////////
//
// "RepairUnit.cpp"
//		RepairUnit
//												작성자 : oedalpha
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
// Part 의 하위클래스인 수리 유닛의 클래스의 생성자.
//
//												작성자 : oedalpha
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
// Part 의 하위클래스인 수리 유닛의 클래스의 소멸자.
//												작성자 : oedalpha
//												Last Update : 2000. 7.
////////////////////////////////////////////////////////////////////////////////
RepairUnit::~RepairUnit() {
}

////////////////////////////////////////////////////////////////////////////////
//
// Value* RepairUnit::Operation(char *lpszOpName, VoidList *lpvlArgument);
//
// Operation 을 실행하는 함수. Repair 와 Stop 두가지 종류가 있다.
//												작성자 : oedalpha
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
// Attribute 를 읽어오는 함수
//												작성자 : oedalpha
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
//												작성자 : oedalpha
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
//												작성자 : oedalpha
//												Last Update : 2000. 7.
////////////////////////////////////////////////////////////////////////////////
void RepairUnit::Stop() {
	flagRepairState = 0;
}

////////////////////////////////////////////////////////////////////////////////
//
// void RepairUnit::Turn();
//
//												작성자 : oedalpha
//												Last Update : 2000. 7.
////////////////////////////////////////////////////////////////////////////////
void RepairUnit::Turn() {
	// 리페어유닛의 연료가 바닥나면 더이상 고칠 수 없다.
	// 고치라는 플래그가 꺼져있으면 고치지 않는다.
	if (dUnitFuel <=0 || flagRepairState != 1) return;

	// 순서도에서는 일단 고치고 나중에 검사를 하였으나
	// 검사를 먼저하고 나중에 고치는 형식으로 하는 것이 더 나을 것 같아서
	// 그렇게 하려고 한다. (에너지 절감 차원에서)
	// 그리고 지금은 예를 들어 3만 고치면 꽉차는데도 10의 에너지를 소모하여
	// 고치게 된다. 아직 고려하지 않았으나 고려할 용의도 있다.
	// 그러려면 아머매니저와 파워트레인의 HP 를 알아보는 함수또는
	// 1씩 고치면서 계속적으로 Full 인지 검사하는 방법이 있겠다
	// 그러나 후자는 비효율적일 것이다.
	
	switch(flagSelect) {
		case 0: // 파워트레인, 장갑 둘다 고치기

			// 이미 HP 가 꽉찼다면 고칠 필요가 없겠죠.
			// 그걸 먼저 검사합시다
			if (lpPowerTrain->IsHpFull()){
				if (lpArmorManager->IsHpFull()){
					// 둘다 HP 가 꽉찬 경우
					flagRepairState = 0;
				}
				else{
					// PowerTrain 만 HP 가 꽉찬 경우
					// 일단 flag 를 변경한다.
					flagSelect = 2; //장갑만 고치기
					// 전력을 다해 장갑만 고친다
					dUnitFuel -= dConsumeSpeed;
					lpArmorManager->Repair(dRepairSpeed);
				}
			}
			else {
				if (lpArmorManager->IsHpFull()){
					// ArmorManager 만 HP 가 꽉찬 경우
					// 파워트레인만 고치기로 플래그 변환
					flagSelect = 1;
					// 전력을 다해 파워트레인만 고친다.
					dUnitFuel -= dConsumeSpeed;
					lpPowerTrain->Repair(dRepairSpeed);
				}
				else{
					// 둘다 HP 가 꽉 차지 않은 경우
					// 50:50 으로 양쪽 기계를 고친다.
					dUnitFuel -= dConsumeSpeed;
					lpPowerTrain->Repair(dRepairSpeed/2.);
					lpArmorManager->Repair(dRepairSpeed/2.);
				}
			}

			break;
		case 1: // 파워트레인만 고치기
			if (lpPowerTrain->IsHpFull()) {
				flagRepairState = 0;
				return;
			}
			else {
				dUnitFuel -= dConsumeSpeed;
				lpPowerTrain->Repair(dRepairSpeed);
			}

			break;
		case 2: // 장갑만 고치기
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

