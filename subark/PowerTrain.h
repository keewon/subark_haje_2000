////////////////////////////////////////////////////////////////////////////////
//
// "PowerTrain.h"
//		PowerTrain
//												작성자 : oedalpha
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _POWERTRAIN_H_OEDALPHA_BECD_
#define _POWERTRAIN_H_OEDALPHA_BECD_

/// Includes ///////////////////////////////////////////////////////////////////
#include <math.h>						// cos 이랑 sin 이랑 쓸일이 있음.
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
// Part 의 하위클래스인 파워트레인 유닛의 클래스
//												작성자 : oedalpha
//
// 여기서 파생되는 클래스로 네가지가 있다
//
// PTDragoon, PTTrike, PTCaterpillar, PTHover
// 각각 Dragoon.cpp, Trike.cpp, Caterpillar.cpp, Hover.cpp 로 나뉘어져있다
//
// 각도의 단위로는 360도 = 한바퀴되는 거(호분법인가?)를 쓴다
// PI는 위에서 const int PI = 3.1415926 으로 정의하였다 (위에 써있죠)
////////////////////////////////////////////////////////////////////////////////

class PowerTrain : public Part{
	public:
		Value* Operation(char *lpszOpName, VoidList *lpvlArgument);
		Value* Attribute(char *lpszName);
		// virtual void Turn();			// 2000.11.10. Turn 합치다.
		void Turn();
		virtual void Draw() = 0;

		// 파트로서의 오퍼레이션
		virtual void Rotate(double Angle, int RotateDirection);
		virtual void Stop();			// 멈춰주렴 (드라군은 바로 멈추므로 따로)
		virtual void Move(double);		// 앞이나 뒤나(일반유닛) 
										// 어느 각도로 움직이렴(드라군)
										// virtual 로 만듦
		// 내부 오퍼레이션
		double Damage(int bulletType, double dDamage);
										// 공격당할 때(버추얼)
										// HP를 리턴함.
		double GetHp();					// Hp 돌려줌
		double GetMaxHp();				// MaxHp 돌려줌
		bool IsHpFull();				// Hp 가 꽉찼는지 아닌지 돌려줌.
		double Repair(double);			// 파워트레인 고치기
										// double 만큼 
										// Hp 를 돌려줌.
										// 아머매니저가 함수를 부르게됨
		void ReduceCurrentWeight(double);	// double만큼 CurrentWeight 줄이기
		virtual void RecalcSpeed() = 0;	// Speed 를 다시 계산한다
										// Weight 등이 변경되었을 때 사용.

		Explorer* lpExplorer;			// 자기가 속한 탐사선에 대한 포인터
	protected
		:

		// 속성
		double dAlpha;					// 투입되는 자원 의존도
		double dWeight;					// 자체 무게
		double dLimitCap;				// 한계용량
		double dCurrentWeight;			// 싣고 있는 무게
		double dLimitWeight;			// 버틸수 있는 무게
		double dSpeed;					// 평상시 속도 weight와 alpha와
										// 관련있음
		double dAngularVelocity;		// 회전각속도
		double dRotateSpeed;			// 회전시 속도
		double dStopDistance;			// 제동거리
		double dHP;						// HP
		double dDesertConst;			// 사막에서의 성능 저하 정도
		double dMaxHP;					// 최대 HP 값.

		// 턴에서 사용하는 플래그
		int flagRotateStatus;			// 현재 rotate 해야하는지 여부
		int flagMoveStatus;				// 현재 move 해야하는지 여부
										// 1 0 -1(brake 건 상태)
		int flagRotateDirection; 		// rotate 할 방향 1 or -1
		int flagMoveDirection;			// 이동방향 1 or -1
		double dRotateAimAngle;			// 목표각도

		// 상태
		double dCurrentAngle;			// 현재 각도
		double dCurrentSpeed;			// 현재 속력
		double dRemainedStopDistance;// 남은 미끄러질 거리

		int idType;						// PI_HOVER PI_CATAPULT PI_DRAGOON PI_TRIKE

		int nSpriteStatus;				// 찍을 그림 번호.. (0-3)

};

////////////////////////////////////////////////////////////////////////////////
//
// class PTDragoon
//
// Dragoon 만 다른 유닛들과 좀 다르다.
// 여러가지 함수 를 새로 파생하여 만든다
//												작성자 : oedalpha
//												Last Update : 2000. 8. 18.
//
////////////////////////////////////////////////////////////////////////////////
class PTDragoon : public PowerTrain {
public:
	PTDragoon(Explorer*, double d_CurrentWeight);
	void Move(double);			// 절대각도로 움직인다.
	void Rotate(double, int);	// 상대각도로 움직인다.
	void Stop();
	void RecalcSpeed();
	//void Turn();
	void Draw(void);
};

////////////////////////////////////////////////////////////////////////////////
//
// class PTTrike
//												작성자 : oedalpha
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
//												작성자 : oedalpha
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
//												작성자 : oedalpha
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
