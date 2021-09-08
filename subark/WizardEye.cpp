////////////////////////////////////////////////////////////////////////////////
//
// "WizardEye.cpp"
//		WizartdEye
//													�ۼ��� : searer
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
//		class WizardEye �� ������
//		IN:
//			lpexExp	- Ž�缱�� ������
//													�ۼ��� : searer
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
//		WizardEye �� turn
//													�ۼ��� : searer
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
		// Map �ޱ�
		for (i=0; i<lpmapMap->xSize(); i++)
			for (j=0; j<lpmapMap->ySize(); j++)
				if ((nSensorX-i)*(nSensorX-i) + (nSensorY-j)*(nSensorY-j)
					<= nSensingRange*nSensingRange)
					nMapData[i][j] = lpmapMap->QueryGeometry(i, j);
				else
					nMapData[i][j] = UNKNOWN;

		// ��, źȯ, ���� ���� �ޱ�
		allEnemy = lpmapMap->getObject();
		nEnemy = 0;

		for (i=0; i<100; i++) {
			if (allEnemy[i] != NULL) {
				allEnemy[i]->QueryPosition(&nX, &nY);
				// �浹 üũ
//				if ((nX == nSensorX) && (nY == nSensorY))
//					bCrash = true;
				if ((nSensorX-nX)*(nSensorX-nX) + (nSensorY-nY)*(nSensorY-nY)
					<= nSensingRange*nSensingRange) {
					detectedEnemy[nEnemy] = allEnemy[i];
					nEnemy++;
				}
			}
		}

		// random �ϰ� �̵�
		int nMove = rand() % 16;
		nSensorX = nSensorX + int(2*sin(nMove*22.5));
		nSensorY = nSensorY + int(2*cos(nMove*22.5));
		
		// �浹 üũ
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
//		WizardEye �� draw
//													�ۼ��� : searer
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
//		��ġ�� �Ѱ��ִ� �Լ�
//													�ۼ��� : searer
//													Last Update : 2000. 8. 23
//
////////////////////////////////////////////////////////////////////////////////

void WizardEye::QueryPosition(int *x, int *y) {
	*x = nSensorX;
	*y = nSensorY;
}
