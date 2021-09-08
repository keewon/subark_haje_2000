////////////////////////////////////////////////////////////////////////////////
//
// "ArmorManager.cpp"
//		장갑매니저
//												작성자 : oedalpha
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
// Part 의 하위클래스인 장갑 클래스의 생성자.
//												작성자 : oedalpha
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
// Part 의 하위클래스인 장갑 클래스의 소멸자.
//												작성자 : oedalpha
//												Last Update : 2000. 7.
////////////////////////////////////////////////////////////////////////////////
ArmorManager::~ArmorManager() {
}

////////////////////////////////////////////////////////////////////////////////
//
// Value* ArmorManager::Operation(char *lpszOpName, VoidList *lpvlArgument);
//
// Operation 을 실행하는 함수. Strip 밖에 없다.
//												작성자 : oedalpha
//												Last Update : 2000. 7.
////////////////////////////////////////////////////////////////////////////////
Value* 
ArmorManager::Operation(char *lpszOpName, VoidList *lpvlArgument) {
	if (!strcmp(lpszOpName, "Strip")) {
		//얘는 인자가 없다 아싸 신난다
		Strip();

		// 리턴값 (VOID) 만들기 아따 복잡하구만
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
// Attribute 를 읽어오는 함수
//												작성자 : oedalpha
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
//												작성자 : oedalpha
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
//												작성자 : oedalpha
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
// Armor 를 추가한다 // 게이머가 사용할 수는 없다 
//
// Stack 을 사용하여 Armor 관리
//
//												작성자 : oedalpha
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
// Armor 를 제거한다 // 게이머가 사용할 수는 없다 
// 제거후 최상위 Armor를 리턴 // 실패했으면 0 또는 NULL 이 리턴됨
//
// Stack 을 사용하여 Armor 관리
//												작성자 : oedalpha
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
// double 값만큼 최상위 아머의 HP 를 늘린다.
// 모든 repair 는 repair unit 에서 담당한다.
// 반면에 damage 는 armormanager 에서 담당한다.
// 설계가 이상한 건 알지만 어쩌다 보니 그렇게 되었다...
//												작성자 : oedalpha
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
// HP 가 꽉찼으면 true 아니면 false 를리턴
//												작성자 : oedalpha
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
// Armor의 개수를 넘겨준다
//												작성자 : oedalpha
//												Last Update : 2000. 8.
//
////////////////////////////////////////////////////////////////////////////////
int
ArmorManager::GetNumberOfArmor() {
	return nNumberOfArmor;
}

////////////////////////////////////////////////////////////////////////////////
//
// Armor에 Damage 를 주는 함수
// Explorer 에서 부르게 된다.
//
// 모든 repair 는 repair unit 에서 담당한다.
// 반면에 damage 는 armormanager 에서 담당한다.
// 설계가 이상한 건 알지만 어쩌다 보니 그렇게 되었다...
//
//												작성자 : oedalpha
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
// 현재 최상위 Armor의 int 값을 return 한다.
//												작성자 : oedalpha
//												Last Update : 2000. 10.
////////////////////////////////////////////////////////////////////////////////

/*int ArmorManager::GetCurrentArmor() {
	return ((Armor*)stackArmorList.Top->Data)->GetType();
}
*/


