////////////////////////////////////////////////////////////////////////////////
//
// "Hover.cpp"
// 공중부양 파워트레인 호버
// 안만들었다
//												작성자 : oedalpha
//												Last Update : 2000. 8. 
//
////////////////////////////////////////////////////////////////////////////////

/// Includes ///////////////////////////////////////////////////////////////////
#include "PowerTrain.h"

/// Public macros & Constants //////////////////////////////////////////////////

/// Global variables ///////////////////////////////////////////////////////////

/// Local functinos ////////////////////////////////////////////////////////////

/// Implementations ////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// PTHover::PTHover(CMap* _lpMap, Explorer* _lpExplorer);
//
// PowerTrain 을 상속받은 Hover 의 생성자
//												작성자 : oedalpha
//												Last Update : 2000. 8.
////////////////////////////////////////////////////////////////////////////////
PTHover::PTHover(Explorer* lp_Explorer, double d_CurrentWeight) {
	dWeight 		= 380.;					// 무게
	dLimitCap 		= 350.;
	dLimitWeight 	= 900.;
	dCurrentWeight	= d_CurrentWeight;
	RecalcSpeed();							// 속도를 다시 계산해준다
	dAngularVelocity= 1.5;
	dHP				= 330;
	dMaxHP			= 330;
	dStopDistance	= 7;

	flagRotateStatus	= 0;
	flagMoveStatus		= 0;
	flagRotateDirection	= 1;
	flagMoveDirection	= 1;

	dCurrentAngle		= 180;
	dCurrentSpeed		= 0;
	dRemainedStopDistance	= 0;

	idType = PI_HOVER;
	lpExplorer			= lp_Explorer;

	sprite.update("Resource/Hover/Hover.bmp", 60, 60);
}

///////////////////////////////////////////////////////////////////////////////
// 
// void PTHover::RecalcSpeed();
//
// 강제로 Speed 를 다시 계산한다. Weight 등이 변경되었을 때 사용
// 물론 RotateSpeed 도 다시 계산한다
//												작성자 : oedalpha
//												Last Update : 2000. 8.
////////////////////////////////////////////////////////////////////////////////
void
PTHover::RecalcSpeed() {
	dSpeed = 6.;
	dRotateSpeed = 4.2;
}

///////////////////////////////////////////////////////////////////////////////
//
// void PTHover::Draw();
//
// 각도에 따라 다른 그림을 찍도록 한다.
//												작성자 : oedalpha
//												Last Update : 2000. 8. 25. 아침
////////////////////////////////////////////////////////////////////////////////

void
PTHover::Draw() {
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