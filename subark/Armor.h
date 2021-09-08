////////////////////////////////////////////////////////////////////////////////
//
// "Armor.h"
//		장갑 과 장갑매니저(아머매니저)
//												작성자 : oedalpha
//												Last Update : 2000. 7. 
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _ARMOR_H_OEDALPHA_BECD_
#define _ARMOR_H_OEDALPHA_BECD_

/// Includes ///////////////////////////////////////////////////////////////////
#include "DataType.h"
#include "Types.h"
#include "Value.h"
#include "stack.h"
#include "Part.h"
#include "Explorer.h"

/// Public macros & Constants //////////////////////////////////////////////////


/// Class or functions /////////////////////////////////////////////////////////

//typedef enum { VOID, INTEGER, REALNUM, BOOLEAN, ARRAY, OBJECT } TypeCode;

////////////////////////////////////////////////////////////////////////////////
//
// class Armor
//
// Part 의 하위클래스인 장갑의 클래스
//
// Armor 의 종류는 고려하지 않기로 했다..
//												작성자 : oedalpha
//												Last Update : 2000. 10.
//
////////////////////////////////////////////////////////////////////////////////

class Armor : public Part{
	public:
		Armor();
		~Armor();
		Value* Operation(char *lpszOpName, VoidList *lpvlArgument);
		Value* Attribute(char *lpszName);

		//int GetType();					// 무슨 타입의 아머인지 돌려줌.
		double GetHp();					// Hp 돌려줌
		double GetMaxHp();				// MaxHp 돌려줌
		double Repair(double);			// Armor 도 고쳐야죠.
		virtual double Damage(int bulletType, double dDamage);
		void Turn() {}
		void Draw() {}
										// Type, Damage
		//int Damage(int bulletType, int);
										// int값만큼 공격당함 현재 Hp 를 돌려줌.
										// 탄환의 종류도 명시할 것.
	protected:
		double dMaxHP;				// 최대 HP 값.
		double dHP;				// Hit Point
		int nType;				// Armor Type
};

////////////////////////////////////////////////////////////////////////////////
//
// class ArmorLiquidMetal : public Armor
//
// 액체금속 아머
//												작성자 : oedalpha
//												Last Update : 2000. 8.
//
////////////////////////////////////////////////////////////////////////////////

class ArmorLiquidMetal : public Armor{
	public:
		ArmorLiquidMetal();
		double Damage(int bulletType, double dDamage);	
};

////////////////////////////////////////////////////////////////////////////////
//
// class ArmorDuralumin : public Armor
//
// 듀랄루민 아머
//												작성자 : oedalpha
//												Last Update : 2000. 8.
//
////////////////////////////////////////////////////////////////////////////////

class ArmorDuralumin : public Armor{
	public:
		ArmorDuralumin();
		double Damage(int bulletType, double dDamage);	
};

////////////////////////////////////////////////////////////////////////////////
//
// class ArmorCarbon : public Armor
//
// 카본 아머
//												작성자 : oedalpha
//												Last Update : 2000. 8.
//
////////////////////////////////////////////////////////////////////////////////

class ArmorCarbon : public Armor{
	public:
		ArmorCarbon();
		double Damage(int bulletType, double dDamage);	
};

////////////////////////////////////////////////////////////////////////////////
//
// class ArmorAluminum : public Armor
//
// Aluminum 아머
//												작성자 : oedalpha
//												Last Update : 2000. 8.
//
////////////////////////////////////////////////////////////////////////////////

class ArmorAluminum : public Armor{
	public:
		ArmorAluminum();
		double Damage(int bulletType, double dDamage);	
};

////////////////////////////////////////////////////////////////////////////////
//
// class ArmorSteel : public Armor
//
// 스틸 아머
//												작성자 : oedalpha
//												Last Update : 2000. 8.
//
////////////////////////////////////////////////////////////////////////////////

class ArmorSteel : public Armor{
	public:
		ArmorSteel();
		double Damage(int bulletType, double dDamage);	
};

#endif // _ARMOR_H_OEDALPHA_BECD_
