////////////////////////////////////////////////////////////////////////////////
//
// "Armor.h"
//		�尩 �� �尩�Ŵ���(�ƸӸŴ���)
//												�ۼ��� : oedalpha
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
// Part �� ����Ŭ������ �尩�� Ŭ����
//
// Armor �� ������ ������� �ʱ�� �ߴ�..
//												�ۼ��� : oedalpha
//												Last Update : 2000. 10.
//
////////////////////////////////////////////////////////////////////////////////

class Armor : public Part{
	public:
		Armor();
		~Armor();
		Value* Operation(char *lpszOpName, VoidList *lpvlArgument);
		Value* Attribute(char *lpszName);

		//int GetType();					// ���� Ÿ���� �Ƹ����� ������.
		double GetHp();					// Hp ������
		double GetMaxHp();				// MaxHp ������
		double Repair(double);			// Armor �� ���ľ���.
		virtual double Damage(int bulletType, double dDamage);
		void Turn() {}
		void Draw() {}
										// Type, Damage
		//int Damage(int bulletType, int);
										// int����ŭ ���ݴ��� ���� Hp �� ������.
										// źȯ�� ������ ����� ��.
	protected:
		double dMaxHP;				// �ִ� HP ��.
		double dHP;				// Hit Point
		int nType;				// Armor Type
};

////////////////////////////////////////////////////////////////////////////////
//
// class ArmorLiquidMetal : public Armor
//
// ��ü�ݼ� �Ƹ�
//												�ۼ��� : oedalpha
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
// ������ �Ƹ�
//												�ۼ��� : oedalpha
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
// ī�� �Ƹ�
//												�ۼ��� : oedalpha
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
// Aluminum �Ƹ�
//												�ۼ��� : oedalpha
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
// ��ƿ �Ƹ�
//												�ۼ��� : oedalpha
//												Last Update : 2000. 8.
//
////////////////////////////////////////////////////////////////////////////////

class ArmorSteel : public Armor{
	public:
		ArmorSteel();
		double Damage(int bulletType, double dDamage);	
};

#endif // _ARMOR_H_OEDALPHA_BECD_
