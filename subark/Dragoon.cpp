////////////////////////////////////////////////////////////////////////////////
//
// "Dragoon.cpp"
// ������������ ���
//												�ۼ��� : oedalpha
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
// PowerTrain �� ��ӹ��� Dragoon �� ������
// ������ trike �� �������
//												�ۼ��� : oedalpha
//												Last Update : 2000. 8.
////////////////////////////////////////////////////////////////////////////////
PTDragoon::PTDragoon(Explorer* lp_Explorer,	 double d_CurrentWeight) {
	dAlpha 			= 0.3;					// ���Կ� �ӵ��� ���õ� ���
	dWeight 		= 550.;					// ����
	dLimitCap 		= 450.;
	dLimitWeight 	= 1000.;
	dCurrentWeight	= d_CurrentWeight;
	RecalcSpeed();							// �ӵ��� �ٽ� ������ش�
	dAngularVelocity= 0;					// ������� �ʴ´�.
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
// ���⼭�� _Direction �� 0���� 360������ ���̴�.
// �� �÷��׸��� double �� ����� �ߴ�.. 
// 4������ ���ָ� Move �� ���� ���� ����.
//												�ۼ��� : oedalpha
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
// �������� ���ֵ� ���ο� Rotate �� ���� ����.
// ��� ȸ���� �����ϱ� �����̴�.
// Move ������ ���밢���� �����̰� Rotate ������ ��밢���� �����̵��� �Ѵ�
//
//												�ۼ��� : oedalpha
//												Last Update : 2000. 8.
////////////////////////////////////////////////////////////////////////////////
void 
PTDragoon::Rotate(double Angle, int RotateDirection) {
	// ���������� ���� ������ flag �� �ٲ� �ʿ䰡 ����.

	//Angle �� ���̳ʽ� ������ �ָ� RotateDirection �� �ٲ��ش�.    
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
// Dragoon �� �ڱ⸸�� Stop �� ����. �ٷ� ���߱� �����̴�
//
//												�ۼ��� : oedalpha
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
// ������ Speed �� �ٽ� ����Ѵ�. Weight ���� ����Ǿ��� �� ���
// ���� RotateSpeed �� �ٽ� ����Ѵ�
//												�ۼ��� : oedalpha
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
// ������ ���� �ٸ� �׸��� �ﵵ�� �Ѵ�.
//												�ۼ��� : oedalpha
//												Last Update : 2000. 8. 25. ��ħ
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