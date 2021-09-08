////////////////////////////////////////////////////////////////////////////////
//
// "ArmorManager.h"
//		장갑매니저(아머매니저)
//												작성자 : oedalpha
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
// Part 의 하위클래스인 장갑관리자(아머매니저)의 클래스
//												작성자 : oedalpha
//												Last Update : 2000. 10.
//
////////////////////////////////////////////////////////////////////////////////

class ArmorManager : public Part{
	public:
		ArmorManager(PowerTrain*);
		~ArmorManager();
		Value* Operation(char *lpszOpName, VoidList *lpvlArgument);
		Value* Attribute(char *lpszName);
		void Strip();				// Armor 를 벗긴다
		void Turn();
		void Draw() {}

		// 내부 함수
		void AddArmor(Armor*);	// Armor 를 추가한다
									// 게이머가 사용할 수는 없다
									// 사용자가 추가한 Armor를 리턴
									// 조립할 때 사용해야한다
		void StripArmor();		// Armor 를 벗기는 내부명령
									// 최상위 Armor 를 리턴한다
		int GetNumberOfArmor();		// Armor의 개수를 리턴한다
		void Repair(double);		// Armor 를 고친다.
		bool IsHpFull();			// Hp 가 꽉찼는지 아닌지 돌려준다
		void Damage(int, int);		// Damage 를 준다. HP return
									// Hp가 0이면 자동으로 Armor벗음
									// Explorer 에서 부르게 된다.
		//int GetCurrentArmor();		// 현재 Armor 의 종류를 Return

	private:
		Stack<Armor*> stackArmorList;
									// Armor 들의 리스트 스택으로 구현
		PowerTrain* lpPowerTrain;	// PowerTrain 의 포인터
		int flagStrip;				// 0 == 벗음. 1 == 벗지마
		int nNumberOfArmor;			// 입고 있는 아머의 개수
};
#endif // _ARMORMANAGER_H_OEDALPHA_BECD_
