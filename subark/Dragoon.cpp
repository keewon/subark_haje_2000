////////////////////////////////////////////////////////////////////////////////
//
// "Dragoon.cpp"
// 사족보행유닛 드라군
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
// PTDragoon::PTDragoon(Explorer* _lpExplorer);
//
// PowerTrain 을 상속받은 Dragoon 의 생성자
// 아직은 trike 만 만들었다
//												작성자 : oedalpha
//												Last Update : 2000. 8.
////////////////////////////////////////////////////////////////////////////////
PTDragoon::PTDragoon(Explorer* lp_Explorer,	 double d_CurrentWeight) {
	dAlpha 			= 0.3;					// 무게와 속도에 관련된 상수
	dWeight 		= 550.;					// 무게
	dLimitCap 		= 450.;
	dLimitWeight 	= 1000.;
	dCurrentWeight	= d_CurrentWeight;
	RecalcSpeed();							// 속도를 다시 계산해준다
	dAngularVelocity= 0;					// 사용하지 않는다.
	dHP				= 560;
	dMaxHP			= 560;
	dDesertConst	= 0.2;
	dStopDistance	= 0;

	flagRotateStatus	= 0;
	flagMoveStatus		= 0;
	flagRotateDirection	= 1;
	flagMoveDirection	= 1;

	dCurrentAngle		= 180;
	dCurrentSpeed		= 0;
	dRemainedStopDistance	= 0;

	idType	=  PI_DRAGOON;
	lpExplorer			= lp_Explorer;

	sprite.update("Resource/Dragoon/dragoon.bmp", 60, 60);
}

////////////////////////////////////////////////////////////////////////////////
//
// virtual void PTDragoon::Move(double _Direction);
//
// 여기서의 _Direction 은 0에서 360까지의 값이다.
// 이 플래그만은 double 을 쓰기로 했다.. 
// 4족보행 유닛만 Move 를 새로 만들어서 쓴다.
//												작성자 : oedalpha
//												Last Update : 2000. 8.
////////////////////////////////////////////////////////////////////////////////
void 
PTDragoon::Move(double Direction) {
	flagMoveStatus = 1;
	lpExplorer->SetMoveStatus(1);
	dCurrentAngle = Direction;
	while (dCurrentAngle < 0) dCurrentAngle += 360;
	while (dCurrentAngle >= 360) dCurrentAngle -= 360;
}

////////////////////////////////////////////////////////////////////////////////
//
// virtual void PTDragoon::Rotate(double Angle, int Direction);
//
// 사족보행 유닛도 새로운 Rotate 를 만들어서 쓴다.
// 즉시 회전이 가능하기 때문이다.
// Move 에서는 절대각도로 움직이고 Rotate 에서는 상대각도로 움직이도록 한다
//
//												작성자 : oedalpha
//												Last Update : 2000. 8.
////////////////////////////////////////////////////////////////////////////////
void 
PTDragoon::Rotate(double Angle, int RotateDirection) {
	// 순간적으로 돌기 때문에 flag 를 바꿀 필요가 없다.

	//Angle 을 마이너스 값으로 주면 RotateDirection 을 바꿔준다.    
	if (Angle < 0) {
		Angle *= -1;
		RotateDirection *= -1;
	}

	dCurrentAngle = dCurrentAngle + Angle * (double)RotateDirection;
	while (dCurrentAngle < 0)	dCurrentAngle += 360;
	while (dCurrentAngle >= 360)	dCurrentAngle -= 360;

}

////////////////////////////////////////////////////////////////////////////////
//
// virtual void PTDragoon::Stop();
//
// Dragoon 은 자기만의 Stop 을 쓴다. 바로 멈추기 때문이다
//
//												작성자 : oedalpha
//												Last Update : 2000. 8.
///////////////////////////////////////////////////////////////////////////////
void 
PTDragoon::Stop() {
	flagMoveStatus = 0;
	lpExplorer->SetMoveStatus(0);
}

///////////////////////////////////////////////////////////////////////////////
// 
// void PTDragoon::RecalcSpeed();
//
// 강제로 Speed 를 다시 계산한다. Weight 등이 변경되었을 때 사용
// 물론 RotateSpeed 도 다시 계산한다
//												작성자 : oedalpha
//												Last Update : 2000. 8.
////////////////////////////////////////////////////////////////////////////////
void
PTDragoon::RecalcSpeed() {
	dSpeed = 9 - dAlpha * (dWeight+dCurrentWeight)/100;
	dRotateSpeed = dSpeed;
}


///////////////////////////////////////////////////////////////////////////////
//
// void PTTrike::Draw();
//
// 각도에 따라 다른 그림을 찍도록 한다.
//												작성자 : oedalpha
//												Last Update : 2000. 8. 25. 아침
////////////////////////////////////////////////////////////////////////////////

void
PTDragoon::Draw() {

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