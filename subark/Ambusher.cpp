////////////////////////////////////////////////////////////////////////////////
//
// "Ambusher.cpp"
//		Ambusher
//													�ۼ��� : searer
//													Last Update : 2000. 8. 19
//
////////////////////////////////////////////////////////////////////////////////

/// Includes ///////////////////////////////////////////////////////////////////

#include "Sensor.h"
#include "Map.h"

/// Public macros & Constants //////////////////////////////////////////////////

/// Implementations ////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Ambusher::Ambusher(Explorer *lpexExp);
//		class Ambusher �� ������
//		IN:
//			lpexExp - Ž�缱�� ������
//													�ۼ��� : searer
//													Last Update : 2000. 8. 19
//
////////////////////////////////////////////////////////////////////////////////

Ambusher::Ambusher(Explorer *lpexExp) {
	lpexExplorer = lpexExp;
	nSensingRange = 20;
	nTurnType = 1;
	bTrigger = true;
	bCrash = false;
}

////////////////////////////////////////////////////////////////////////////////
//
// Ambusher::Turn();
//		Ambusher �� turn
//													�ۼ��� : searer
//													Last Update : 2000. 8. 19
//
////////////////////////////////////////////////////////////////////////////////

void Ambusher::Turn() {
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
				if ((nX == nSensorX) && (nY == nSensorY))
					bCrash = true;
				if ((nSensorX-nX)*(nSensorX-nX) + (nSensorY-nY)*(nSensorY-nY)
					<= nSensingRange*nSensingRange) {
					detectedEnemy[nEnemy] = allEnemy[i];
					nEnemy++;
				}
			}
		}

		// �浹 üũ
		if (bCrash == false)
			return;
		nTurnType = 3;
		bTrigger = false;
		bCrash = false;
		for (i=0; i<lpmapMap->xSize(); i++)
			for (j=0; j<lpmapMap->ySize(); j++)
				nMapData[i][j] = UNKNOWN;
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// Ambusher::Draw();
//		Ambusher �� draw
//													�ۼ��� : searer
//													Last Update : 2000. 8. 23
//
////////////////////////////////////////////////////////////////////////////////

void Ambusher::Draw() {
	int nCurrentX = 100, nCurrentY = 100;

//	lpexExplorer->QueryPosition(&nCurrentX, &nCurrentY);
//	sprite.setCurrent(nCurrentX, nCurrentY);
//	sprite.redraw();
}

////////////////////////////////////////////////////////////////////////////////
//
// Ambusher::QueryPosition();
//		��ġ�� �Ѱ��ִ� �Լ�
//													�ۼ��� : searer
//													Last Update : 2000. 8. 23
//
////////////////////////////////////////////////////////////////////////////////

void Ambusher::QueryPosition(int *x, int *y) {
	*x = nSensorX;
	*y = nSensorY;
}
