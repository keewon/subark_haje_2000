////////////////////////////////////////////////////////////////////////////////
//
// "PowerTrain.h"
//		PowerTrain
//												�ۼ��� : oedalpha
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _POWERTRAIN_H_OEDALPHA_BECD_
#define _POWERTRAIN_H_OEDALPHA_BECD_

/// Includes ///////////////////////////////////////////////////////////////////
#include <math.h>						// cos �̶� sin �̶� ������ ����.
#include "DataType.h"
#include "Types.h"
#include "Value.h"
#include "Explorer.h"
#include "Map.h"
#include <stdio.h>

/// Public macros & Constants //////////////////////////////////////////////////
#ifndef PI
const double PI = 3.1415926;
#endif

const int TILE_SIZE = 20;

/// Class or functions /////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class PowerTrain
//
// Part �� ����Ŭ������ �Ŀ�Ʈ���� ������ Ŭ����
//												�ۼ��� : oedalpha
//
// ���⼭ �Ļ��Ǵ� Ŭ������ �װ����� �ִ�
//
// PTDragoon, PTTrike, PTCaterpillar, PTHover
// ���� Dragoon.cpp, Trike.cpp, Caterpillar.cpp, Hover.cpp �� ���������ִ�
//
// ������ �����δ� 360�� = �ѹ����Ǵ� ��(ȣ�й��ΰ�?)�� ����
// PI�� ������ const int PI = 3.1415926 ���� �����Ͽ��� (���� ������)
////////////////////////////////////////////////////////////////////////////////

class PowerTrain : public Part{
	public:
		Value* Operation(char *lpszOpName, VoidList *lpvlArgument);
		Value* Attribute(char *lpszName);
		// virtual void Turn();			// 2000.11.10. Turn ��ġ��.
		void Turn();
		virtual void Draw() = 0;

		// ��Ʈ�μ��� ���۷��̼�
		virtual void Rotate(double Angle, int RotateDirection);
		virtual void Stop();			// �����ַ� (����� �ٷ� ���߹Ƿ� ����)
		virtual void Move(double);		// ���̳� �ڳ�(�Ϲ�����) 
										// ��� ������ �����̷�(���)
										// virtual �� ����
		// ���� ���۷��̼�
		double Damage(int bulletType, double dDamage);
										// ���ݴ��� ��(���߾�)
										// HP�� ������.
		double GetHp();					// Hp ������
		double GetMaxHp();				// MaxHp ������
		bool IsHpFull();				// Hp �� ��á���� �ƴ��� ������.
		double Repair(double);			// �Ŀ�Ʈ���� ��ġ��
										// double ��ŭ 
										// Hp �� ������.
										// �ƸӸŴ����� �Լ��� �θ��Ե�
		void ReduceCurrentWeight(double);	// double��ŭ CurrentWeight ���̱�
		virtual void RecalcSpeed() = 0;	// Speed �� �ٽ� ����Ѵ�
										// Weight ���� ����Ǿ��� �� ���.

		Explorer* lpExplorer;			// �ڱⰡ ���� Ž�缱�� ���� ������
	protected
		:

		// �Ӽ�
		double dAlpha;					// ���ԵǴ� �ڿ� ������
		double dWeight;					// ��ü ����
		double dLimitCap;				// �Ѱ�뷮
		double dCurrentWeight;			// �ư� �ִ� ����
		double dLimitWeight;			// ��ƿ�� �ִ� ����
		double dSpeed;					// ���� �ӵ� weight�� alpha��
										// ��������
		double dAngularVelocity;		// ȸ�����ӵ�
		double dRotateSpeed;			// ȸ���� �ӵ�
		double dStopDistance;			// �����Ÿ�
		double dHP;						// HP
		double dDesertConst;			// �縷������ ���� ���� ����
		double dMaxHP;					// �ִ� HP ��.

		// �Ͽ��� ����ϴ� �÷���
		int flagRotateStatus;			// ���� rotate �ؾ��ϴ��� ����
		int flagMoveStatus;				// ���� move �ؾ��ϴ��� ����
										// 1 0 -1(brake �� ����)
		int flagRotateDirection; 		// rotate �� ���� 1 or -1
		int flagMoveDirection;			// �̵����� 1 or -1
		double dRotateAimAngle;			// ��ǥ����

		// ����
		double dCurrentAngle;			// ���� ����
		double dCurrentSpeed;			// ���� �ӷ�
		double dRemainedStopDistance;// ���� �̲����� �Ÿ�

		int idType;						// PI_HOVER PI_CATAPULT PI_DRAGOON PI_TRIKE

		int nSpriteStatus;				// ���� �׸� ��ȣ.. (0-3)

};

////////////////////////////////////////////////////////////////////////////////
//
// class PTDragoon
//
// Dragoon �� �ٸ� ���ֵ�� �� �ٸ���.
// �������� �Լ� �� ���� �Ļ��Ͽ� �����
//												�ۼ��� : oedalpha
//												Last Update : 2000. 8. 18.
//
////////////////////////////////////////////////////////////////////////////////
class PTDragoon : public PowerTrain {
public:
	PTDragoon(Explorer*, double d_CurrentWeight);
	void Move(double);			// ���밢���� �����δ�.
	void Rotate(double, int);	// ��밢���� �����δ�.
	void Stop();
	void RecalcSpeed();
	//void Turn();
	void Draw(void);
};

////////////////////////////////////////////////////////////////////////////////
//
// class PTTrike
//												�ۼ��� : oedalpha
//												Last Update : 2000. 8. 18.
//
////////////////////////////////////////////////////////////////////////////////
class PTTrike : public PowerTrain {
public :
	PTTrike(Explorer*, double d_CurrentWeight);
	void Rotate(double, int);
	void RecalcSpeed();
	//void Turn();
	void Draw(void);
};

////////////////////////////////////////////////////////////////////////////////
//
// class PTCaterpillar
//												�ۼ��� : oedalpha
//												Last Update : 2000. 8. 18.
//
////////////////////////////////////////////////////////////////////////////////
class PTCaterpillar : public PowerTrain {
public:
	PTCaterpillar(Explorer*, double);
	void RecalcSpeed();
	//void Turn();
	void Draw();
};

////////////////////////////////////////////////////////////////////////////////
//
// class PTHover
//												�ۼ��� : oedalpha
//												Last Update : 2000. 8. 18.
//
////////////////////////////////////////////////////////////////////////////////
class PTHover : public PowerTrain {
public:
	PTHover(Explorer*, double);
	void RecalcSpeed();
	//void Turn();
	void Draw();
};

#endif // _POWERTRAIN_H_OEDALPHA_BECD_
