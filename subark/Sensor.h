////////////////////////////////////////////////////////////////////////////////
//
// "Sensor.h"
//		Sensor Part에 대한 클래스 선언
//													작성자 : searer
//													Last Update : 2000. 8. 4
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _SENSOR_H_SEARER_BECD_
#define _SENSOR_H_SEARER_BECD_

/// Includes ///////////////////////////////////////////////////////////////////

#include "Part.h"
#include "Value.h"
#include "Explorer.h"
#include <string.h>

/// Public macros & Constants //////////////////////////////////////////////////

#define MAX		100
#define UNKNOWN	10
#define FOG		20

/// Class or functions /////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class Sensor
//		Sensor Part 의 클래스
//													작성자 : searer
//													Last Update : 2000. 8. 4
//
////////////////////////////////////////////////////////////////////////////////

class Sensor : public Part {
	public:
		~Sensor();							// 소멸자
		Value* Operation(char *lpszOpName, VoidList *lpvlArgument);
		Value* Attribute(char *lpszName);

		int nMapData[MAX][MAX];				// 전체 맵 정보

	protected:
		Explorer *lpexExplorer;				// 탐사선의 포인터
		Object *detectedEnemy[MAX];			// 센싱된 적, 탄환, 센서 등의 정보
		Object **allEnemy;					// 모든 적, 탄환, 센서 등의 정보
		int nEnemy;							// 센싱된 적의 개수

		bool bTrigger;						// 센서 발동 여부
		bool bCrash;						// 충돌 여부
		int nSensingRange;					// 센싱 가능 거리
		int nSensingOption;					// 센싱 옵션
		int nTurnType;						// 턴 타입
};

////////////////////////////////////////////////////////////////////////////////
//
// class NormalSensor
//		NormalSensor 의 클래스
//													작성자 : searer
//													Last Update : 2000. 8. 17
//
////////////////////////////////////////////////////////////////////////////////

class NormalSensor : public Sensor {
	public:
		NormalSensor(Explorer *lpexExp);	// 생성자
		void Turn();						// turn
		void Draw();						// draw
};

////////////////////////////////////////////////////////////////////////////////
//
// class BlackSheepWall
//		BlackSheepWall 의 클래스
//													작성자 : searer
//													Last Update : 2000. 8. 17
//
////////////////////////////////////////////////////////////////////////////////

class BlackSheepWall : public Sensor {
	public:
		BlackSheepWall();					// 생성자
		void Turn();						// turn
		void Draw();						// draw

	private:
		int nContinueTime;					// 탐지 지속 시간
		int nRemainingTime;					// 남은 탐지 시간
};

////////////////////////////////////////////////////////////////////////////////
//
// class WizardEye
//		WizardEye 의 클래스
//													작성자 : searer
//													Last Update : 2000. 8. 17
//
////////////////////////////////////////////////////////////////////////////////

class WizardEye : public Sensor {
	public:
		WizardEye(Explorer *lpexExp);		// 생성자
		void Turn();						// turn
		void Draw();						// draw
		void QueryPosition(int*, int*);

	private:
		int nSensorX, nSensorY;				// 센서의 위치
};

////////////////////////////////////////////////////////////////////////////////
//
// class Ambusher
//		Ambusher 의 클래스
//													작성자 : searer
//													Last Update : 2000. 8. 17
//
////////////////////////////////////////////////////////////////////////////////

class Ambusher : public Sensor {
	public:
		Ambusher(Explorer *lpexExp);		// 생성자
		void Turn();						// turn
		void Draw();						// draw
		void QueryPosition(int*, int*);

	private:
		int nSensorX, nSensorY;				// 센서의 위치
};

#endif	// _SENSOR_H_SEARER_BECD_
