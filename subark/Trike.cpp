////////////////////////////////////////////////////////////////////////////////
//
// "Trike.cpp"
// 파워트레인을 상속받은 트라이크(타이어형 자동차)
//
//												작성자 : oedalpha
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
// PowerTrain 을 상속받은 Trike 의 생성자
// 소비자원이나 등은 아직 고려하지 않기로함.
// Sprite 관련도 아직 아는 바 없음.
//
// dCurrentWeight 는 파워트레인 자체무게를 제외한 무게
//
// 그림 크기 관련
// Trike00, 08.bmp -> 40x60
// Trike01, 09.bmp -> 60x71
// Trike02, 10.bmp -> 71x71
// Trike03, 11.bmp -> 71x60
// Trike04, 12.bmp -> 60x40
// Trike05, 13.bmp -> 71x60
// Trike06, 14.bmp -> 71x71
// Trike07, 15.bmp -> 60x71
//												작성자 : oedalpha
//												Last Update : 2000. 8.
////////////////////////////////////////////////////////////////////////////////
PTTrike::PTTrike(Explorer* lp_Explorer,	 double d_CurrentWeight) {
	dAlpha 			= 0.16;					// 무게와 속도에 관련된 상수
	dWeight 		= 400.;					// 무게
	dLimitCap 		= 300.;
	dLimitWeight 	= 1000.;
	dCurrentWeight	= d_CurrentWeight;
	RecalcSpeed();							// 속도를 다시 계산해준다
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
	//sprite.update("Resource/트레인/트레인00008.bmp", 150, 110);
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
// int flagRotateStatus : 현재 rotate 해야하는지 여부
// double dRotateAimAngle : 목표 각도
// int flagRotateDirection : rotate 할 방향 시계방향은 1, 고도리방향은 -1
//
// Trike 만 새로운 Rotate 를 만들어 쓴다.
//												작성자 : oedalpha
//												Last Update : 2000. 8.
////////////////////////////////////////////////////////////////////////////////
void 
PTTrike::Rotate(double Angle, int RotateDirection) {
	if (flagMoveStatus != 0) {
		flagRotateStatus = 1;
		//Angle 을 마이너스 값으로 주면 RotateDirection 을 바꿔준다.    
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
// 강제로 Speed 를 다시 계산한다. Weight 등이 변경되었을 때 사용
// 물론 RotateSpeed 도 다시 계산한다
//												작성자 : oedalpha
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
// 각도에 따라 다른 그림을 찍도록 한다.
//												작성자 : oedalpha
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
		sprite.update("Resource/트레인/트레인00000.bmp", 150, 110);
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

	sprintf(szSpriteName, "Resource/트레인/트레인%d%04d.bmp", nSpriteStatusTemp, nSpriteNumber);
	
	sprite.update(szSpriteName, 150, 110);
	sprite.setCurrent(nCurrentX - 75, nCurrentY - 55);
	sprite.redraw();

	nSpriteStatus++;

	if (nSpriteStatus >= 20) nSpriteStatus = 0;

}