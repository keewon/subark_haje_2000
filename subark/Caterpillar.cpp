////////////////////////////////////////////////////////////////////////////////
//
// "Caterpillar.cpp"
// ���ѱ˵� �Ŀ�Ʈ����
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
// PTCaterpillar::PTCaterpillar(CMap* _lpMap, Explorer* _lpExplorer);
//
// PowerTrain �� ��ӹ��� Caterpillar�� ������
// ������ trike �� �������
//												�ۼ��� : oedalpha
//												Last Update : 2000. 8.
////////////////////////////////////////////////////////////////////////////////
PTCaterpillar::PTCaterpillar(Explorer* lp_Explorer, double d_CurrentWeight) {
	dAlpha 			= 0.1;					// ���Կ� �ӵ��� ���õ� ���
	dWeight 		= 1000.;					// ����
	dLimitCap 		= 600.;
	dLimitWeight 	= 2600.;
	dCurrentWeight	= d_CurrentWeight;
	RecalcSpeed();							// �ӵ��� �ٽ� ������ش�
	dAngularVelocity= 10.;
	dHP				= 200;
	dMaxHP			= 200;
	dDesertConst	= 0.9;
	dStopDistance	= 2;

	flagRotateStatus	= 0;
	flagMoveStatus		= 0;
	flagRotateDirection	= 1;
	flagMoveDirection	= 1;

	dCurrentAngle		= 180;
	dCurrentSpeed		= 0;
	dRemainedStopDistance	= 0;
	nSpriteStatus = 0;

	idType = PI_CATAPULT;

	lpExplorer			= lp_Explorer;
}

///////////////////////////////////////////////////////////////////////////////
// 
// void PTCaterpillar::RecalcSpeed();
//
// ������ Speed �� �ٽ� ����Ѵ�. Weight ���� ����Ǿ��� �� ���
// ���� RotateSpeed �� �ٽ� ����Ѵ�
//												�ۼ��� : oedalpha
//												Last Update : 2000. 8.
////////////////////////////////////////////////////////////////////////////////
void
PTCaterpillar::RecalcSpeed() {
	dSpeed = 8 - dAlpha * (dWeight+dCurrentWeight)/100;
	dRotateSpeed = dSpeed * 0.8;
}


///////////////////////////////////////////////////////////////////////////////
//
// void PTCaterpillar::Draw();
//
// ������ ���� �ٸ� �׸��� �ﵵ�� �Ѵ�.
//												�ۼ��� : oedalpha
//												Last Update : 2000. 8. 25. ��ħ
////////////////////////////////////////////////////////////////////////////////

void
PTCaterpillar::Draw() {
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
	
	
	if ((0 <= nSpriteStatus && nSpriteStatus <= 5) ||
		(11 <= nSpriteStatus && nSpriteStatus <= 15) ) {
		nSpriteStatusTemp = 0;
	}
	else if (6 <= nSpriteStatus && nSpriteStatus <= 10) {
		nSpriteStatusTemp = 1;
	}
	else if (16 <= nSpriteStatus && nSpriteStatus <= 20) {
		nSpriteStatusTemp = 2;
	}
	else {
		nSpriteStatusTemp = 0;
	}
	

	/*
	if ((0 <= nSpriteStatus && nSpriteStatus <= 20) ||
		(41 <= nSpriteStatus && nSpriteStatus <= 60) ) {
		nSpriteStatusTemp = 0;
	}
	else if (21 <= nSpriteStatus && nSpriteStatus <= 40) {
		nSpriteStatusTemp = 1;
	}
	else if (61 <= nSpriteStatus && nSpriteStatus <= 80) {
		nSpriteStatusTemp = 2;
	}
	else {
		nSpriteStatusTemp = 0;
	}
	*/
	sprintf(szSpriteName, "Resource/Ʈ����/Ʈ����%d%04d.bmp", nSpriteStatusTemp, nSpriteNumber);
	
	sprite.update(szSpriteName, 150, 110);
	sprite.setCurrent(nCurrentX - 75, nCurrentY - 55);
	sprite.redraw();

	nSpriteStatus++;

	if (nSpriteStatus >= 20) nSpriteStatus = 0;
	/*
	int nCurrentX, nCurrentY;
	lpExplorer->QueryPosition(&nCurrentX, &nCurrentY);
	sprite.update("Resource/Cater/Cater.bmp", 150, 110);
	sprite.setCurrent(nCurrentX - 75, nCurrentY - 55);
	sprite.redraw();
	*/

}
