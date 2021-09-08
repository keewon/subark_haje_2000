////////////////////////////////////////////////////////////////////////////////
//
// "WizardEye.cpp"
//		WizartdEye
//													작성자 : searer
//													Last Update : 2000. 8. 17
//
////////////////////////////////////////////////////////////////////////////////

/// Includes ///////////////////////////////////////////////////////////////////

#include "Sensor.h"
#include "Map.h"
#include <stdlib.h>
#include <math.h>

/// Public macros & Constants //////////////////////////////////////////////////

/// Implementations ////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// WizardEye::WizardEye(Explorer *lpexExp);
//		class WizardEye 의 생성자
//		IN:
//			lpexExp	- 탐사선의 포인터
//													작성자 : searer
//													Last Update : 2000. 8. 17
//
////////////////////////////////////////////////////////////////////////////////

WizardEye::WizardEye(Explorer *lpexExp) {
	lpexExplorer = lpexExp;
	nSensingRange = 10;
	nTurnType = 1;
	bTrigger = true;
	bCrash = false;
	sprite.update("Resource/WizardEye.bmp", 20, 20);
}

////////////////////////////////////////////////////////////////////////////////
//
// WizardEye::Turn();
//		WizardEye 의 turn
//													작성자 : searer
//													Last Update : 2000. 8. 17
//
////////////////////////////////////////////////////////////////////////////////

void WizardEye::Turn() {
	int i, j;
	int nX, nY;

	switch (nTurnType) {
	// nTurnType 1
	case 1:
		// Sensor initialize
		for (i=0; i<lpmapMap->xSize(); i++)
			for (j=0; j<lpmapMap->ySize(); j++)
				nMapData[i][j] = UNKNOWN;

		if (bTrigger == false)
			return;
		nTurnType = 2;
		lpexExplorer->QueryPosition(&nX, &nY);
		nSensorX = nX/20;
		nSensorY = nY/20;
		lpmapMap->Append(this);
	// nTurnType 2
	case 2:
		// Map 받기
		for (i=0; i<lpmapMap->xSize(); i++)
			for (j=0; j<lpmapMap->ySize(); j++)
				if ((nSensorX-i)*(nSensorX-i) + (nSensorY-j)*(nSensorY-j)
					<= nSensingRange*nSensingRange)
					nMapData[i][j] = lpmapMap->QueryGeometry(i, j);
				else
					nMapData[i][j] = UNKNOWN;

		// 적, 탄환, 센서 정보 받기
		allEnemy = lpmapMap->getObject();
		nEnemy = 0;

		for (i=0; i<100; i++) {
			if (allEnemy[i] != NULL) {
				allEnemy[i]->QueryPosition(&nX, &nY);
				// 충돌 체크
//				if ((nX == nSensorX) && (nY == nSensorY))
//					bCrash = true;
				if ((nSensorX-nX)*(nSensorX-nX) + (nSensorY-nY)*(nSensorY-nY)
					<= nSensingRange*nSensingRange) {
					detectedEnemy[nEnemy] = allEnemy[i];
					nEnemy++;
				}
			}
		}

		// random 하게 이동
		int nMove = rand() % 16;
		nSensorX = nSensorX + int(2*sin(nMove*22.5));
		nSensorY = nSensorY + int(2*cos(nMove*22.5));
		
		// 충돌 체크
		if (bCrash == false)
			return;
		nTurnType = 3;
		bTrigger = false;
		bCrash = false;
		lpmapMap->Delete(this);
		for (i=0; i<lpmapMap->xSize(); i++)
			for (j=0; j<lpmapMap->ySize(); j++)
				nMapData[i][j] = UNKNOWN;
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// WizardEye::Draw();
//		WizardEye 의 draw
//													작성자 : searer
//													Last Update : 2000. 8. 23
//
////////////////////////////////////////////////////////////////////////////////

void WizardEye::Draw() {
	if (bTrigger == true) {
		sprite.setCurrent(20*nSensorX, 20*nSensorY);
		sprite.redraw();
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// WizardEye::QueryPosition();
//		위치를 넘겨주는 함수
//													작성자 : searer
//													Last Update : 2000. 8. 23
//
////////////////////////////////////////////////////////////////////////////////

void WizardEye::QueryPosition(int *x, int *y) {
	*x = nSensorX;
	*y = nSensorY;
}
