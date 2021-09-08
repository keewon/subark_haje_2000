////////////////////////////////////////////////////////////////////////////////
//
// "Sensor.h"
//		Sensor Part�� ���� Ŭ���� ����
//													�ۼ��� : searer
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
//		Sensor Part �� Ŭ����
//													�ۼ��� : searer
//													Last Update : 2000. 8. 4
//
////////////////////////////////////////////////////////////////////////////////

class Sensor : public Part {
	public:
		~Sensor();							// �Ҹ���
		Value* Operation(char *lpszOpName, VoidList *lpvlArgument);
		Value* Attribute(char *lpszName);

		int nMapData[MAX][MAX];				// ��ü �� ����

	protected:
		Explorer *lpexExplorer;				// Ž�缱�� ������
		Object *detectedEnemy[MAX];			// ���̵� ��, źȯ, ���� ���� ����
		Object **allEnemy;					// ��� ��, źȯ, ���� ���� ����
		int nEnemy;							// ���̵� ���� ����

		bool bTrigger;						// ���� �ߵ� ����
		bool bCrash;						// �浹 ����
		int nSensingRange;					// ���� ���� �Ÿ�
		int nSensingOption;					// ���� �ɼ�
		int nTurnType;						// �� Ÿ��
};

////////////////////////////////////////////////////////////////////////////////
//
// class NormalSensor
//		NormalSensor �� Ŭ����
//													�ۼ��� : searer
//													Last Update : 2000. 8. 17
//
////////////////////////////////////////////////////////////////////////////////

class NormalSensor : public Sensor {
	public:
		NormalSensor(Explorer *lpexExp);	// ������
		void Turn();						// turn
		void Draw();						// draw
};

////////////////////////////////////////////////////////////////////////////////
//
// class BlackSheepWall
//		BlackSheepWall �� Ŭ����
//													�ۼ��� : searer
//													Last Update : 2000. 8. 17
//
////////////////////////////////////////////////////////////////////////////////

class BlackSheepWall : public Sensor {
	public:
		BlackSheepWall();					// ������
		void Turn();						// turn
		void Draw();						// draw

	private:
		int nContinueTime;					// Ž�� ���� �ð�
		int nRemainingTime;					// ���� Ž�� �ð�
};

////////////////////////////////////////////////////////////////////////////////
//
// class WizardEye
//		WizardEye �� Ŭ����
//													�ۼ��� : searer
//													Last Update : 2000. 8. 17
//
////////////////////////////////////////////////////////////////////////////////

class WizardEye : public Sensor {
	public:
		WizardEye(Explorer *lpexExp);		// ������
		void Turn();						// turn
		void Draw();						// draw
		void QueryPosition(int*, int*);

	private:
		int nSensorX, nSensorY;				// ������ ��ġ
};

////////////////////////////////////////////////////////////////////////////////
//
// class Ambusher
//		Ambusher �� Ŭ����
//													�ۼ��� : searer
//													Last Update : 2000. 8. 17
//
////////////////////////////////////////////////////////////////////////////////

class Ambusher : public Sensor {
	public:
		Ambusher(Explorer *lpexExp);		// ������
		void Turn();						// turn
		void Draw();						// draw
		void QueryPosition(int*, int*);

	private:
		int nSensorX, nSensorY;				// ������ ��ġ
};

#endif	// _SENSOR_H_SEARER_BECD_
