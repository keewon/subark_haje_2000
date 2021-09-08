////////////////////////////////////////////////////////////////////////////////
//
// "Trike.cpp"
// �Ŀ�Ʈ������ ��ӹ��� Ʈ����ũ(Ÿ�̾��� �ڵ���)
//
//												�ۼ��� : oedalpha
//												Last Update : 2000. 8. 18
//
////////////////////////////////////////////////////////////////////////////////

/// Includes ///////////////////////////////////////////////////////////////////
#include "PowerTrain.h"
#include <string.h>
/// Public macros & Constants //////////////////////////////////////////////////

/// Global variables ///////////////////////////////////////////////////////////

/// Local functinos ////////////////////////////////////////////////////////////

/// Implementations ////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// PTTrike::PTTrike(Explorer* _lpExplorer, double, double);
//
// PowerTrain �� ��ӹ��� Trike �� ������
// �Һ��ڿ��̳� ���� ���� ������� �ʱ����.
// Sprite ���õ� ���� �ƴ� �� ����.
//
// dCurrentWeight �� �Ŀ�Ʈ���� ��ü���Ը� ������ ����
//
// �׸� ũ�� ����
// Trike00, 08.bmp -> 40x60
// Trike01, 09.bmp -> 60x71
// Trike02, 10.bmp -> 71x71
// Trike03, 11.bmp -> 71x60
// Trike04, 12.bmp -> 60x40
// Trike05, 13.bmp -> 71x60
// Trike06, 14.bmp -> 71x71
// Trike07, 15.bmp -> 60x71
//												�ۼ��� : oedalpha
//												Last Update : 2000. 8.
////////////////////////////////////////////////////////////////////////////////
PTTrike::PTTrike(Explorer* lp_Explorer,	 double d_CurrentWeight) {
	dAlpha 			= 0.16;					// ���Կ� �ӵ��� ���õ� ���
	dWeight 		= 400.;					// ����
	dLimitCap 		= 300.;
	dLimitWeight 	= 1000.;
	dCurrentWeight	= d_CurrentWeight;
	RecalcSpeed();							// �ӵ��� �ٽ� ������ش�
	dAngularVelocity= 1.5;
	dHP				= 350;
	dMaxHP			= 350;
	dDesertConst	= 0.5;
	dStopDistance	= 15;

	flagRotateStatus	= 0;
	flagMoveStatus		= 0;
	flagRotateDirection	= 1;
	flagMoveDirection	= 1;

	dCurrentAngle		= 180;
	dCurrentSpeed		= 0;
	dRemainedStopDistance	= 0;

	idType = PI_TRIKE;
	lpExplorer			= lp_Explorer;

	//sprite.update("Resource/Trike/trike08.bmp", 120, 120);
	//sprite.update("Resource/Trike/trike08.bmp", 40, 60);
	//sprite.update("Resource/Ʈ����/Ʈ����00008.bmp", 150, 110);
	nSpriteStatus = 0;

//	fp = fopen("log.txt", "wt");
}

// for debugging
//PTTrike::~PTTrike() {
//	fclose(fp);
//}

////////////////////////////////////////////////////////////////////////////////
//
// virtual void PowerTrain::Rotate(double _Angle, int _RotateDirection);
//
// int flagRotateStatus : ���� rotate �ؾ��ϴ��� ����
// double dRotateAimAngle : ��ǥ ����
// int flagRotateDirection : rotate �� ���� �ð������ 1, ���������� -1
//
// Trike �� ���ο� Rotate �� ����� ����.
//												�ۼ��� : oedalpha
//												Last Update : 2000. 8.
////////////////////////////////////////////////////////////////////////////////
void 
PTTrike::Rotate(double Angle, int RotateDirection) {
	if (flagMoveStatus != 0) {
		flagRotateStatus = 1;
		//Angle �� ���̳ʽ� ������ �ָ� RotateDirection �� �ٲ��ش�.    
		if (Angle < 0) {
			Angle *= -1;
			RotateDirection *= -1;
		}
	
		dRotateAimAngle = dCurrentAngle + Angle * (double)RotateDirection;
		while (dRotateAimAngle < 0) {
			dRotateAimAngle += 360;
		}
		while (dRotateAimAngle >= 360) {
			dRotateAimAngle -= 360;
		}
		if (RotateDirection >= 0) {
			flagRotateDirection = 1;
		}
		else {
			flagRotateDirection = -1;
		}
	
	}
	else {
		return;
	}

}
///////////////////////////////////////////////////////////////////////////////
// 
// void PTTrike::RecalcSpeed();
//
// ������ Speed �� �ٽ� ����Ѵ�. Weight ���� ����Ǿ��� �� ���
// ���� RotateSpeed �� �ٽ� ����Ѵ�
//												�ۼ��� : oedalpha
//												Last Update : 2000. 8.
////////////////////////////////////////////////////////////////////////////////
void
PTTrike::RecalcSpeed() {
	dSpeed = 16 - dAlpha * ((dWeight+dCurrentWeight)/100) 
		* ((dWeight+dCurrentWeight)/100);
	dRotateSpeed = dSpeed * 0.6;
}


///////////////////////////////////////////////////////////////////////////////
//
// void PTTrike::Draw();
//
// ������ ���� �ٸ� �׸��� �ﵵ�� �Ѵ�.
//												�ۼ��� : oedalpha
//												Last Update : 2000. 9.
////////////////////////////////////////////////////////////////////////////////

void
PTTrike::Draw() {

	int nCurrentX, nCurrentY;
	lpExplorer->QueryPosition(&nCurrentX, &nCurrentY);

	if (dHP <= 0) {
		sprite.update("Resource/cater/cater.bmp", 60,80);
		sprite.setCurrent(nCurrentX-30, nCurrentY-40);
		sprite.redraw();
		return;
	}

	if (flagMoveStatus == 0) {
		sprite.update("Resource/Ʈ����/Ʈ����00000.bmp", 150, 110);
		sprite.setCurrent(nCurrentX-75, nCurrentY-55);
		sprite.redraw();
		return;
	}

	int nSpriteNumber = (int)(dCurrentAngle / 22.5);
	char szSpriteName[80];
	int nSpriteStatusTemp = 0;
	
	if ((0 <= nSpriteStatus && nSpriteStatus <= 4) ||
		(10 <= nSpriteStatus && nSpriteStatus <= 14) ) {
		nSpriteStatusTemp = 0;
	}
	else if (5 <= nSpriteStatus && nSpriteStatus <= 9) {
		nSpriteStatusTemp = 1;
	}
	else if (15 <= nSpriteStatus && nSpriteStatus <= 19) {
		nSpriteStatusTemp = 2;
	}
	else {
		nSpriteStatusTemp = 0;
	}

	sprintf(szSpriteName, "Resource/Ʈ����/Ʈ����%d%04d.bmp", nSpriteStatusTemp, nSpriteNumber);
	
	sprite.update(szSpriteName, 150, 110);
	sprite.setCurrent(nCurrentX - 75, nCurrentY - 55);
	sprite.redraw();

	nSpriteStatus++;

	if (nSpriteStatus >= 20) nSpriteStatus = 0;

}