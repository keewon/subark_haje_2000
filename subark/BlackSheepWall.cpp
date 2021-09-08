////////////////////////////////////////////////////////////////////////////////
//
// "BlackSheepWall.cpp"
//		BalckSheepWall
//													�ۼ��� : searer
//													Last Update : 2000. 8. 17
//
////////////////////////////////////////////////////////////////////////////////

/// Includes ///////////////////////////////////////////////////////////////////

#include "Sensor.h"
#include "Map.h"

/// Public macros & Constants //////////////////////////////////////////////////

/// Implementations ////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// BlackSheepWall::BlackSheepWall();
//		class BlackSheepWall �� ������
//													�ۼ��� : searer
//													Last Update : 2000. 8. 17
//
////////////////////////////////////////////////////////////////////////////////

BlackSheepWall::BlackSheepWall() {
	nContinueTime = 120;
	nTurnType = 1;
}

////////////////////////////////////////////////////////////////////////////////
//
// BlackSheepWall::Turn();
//		BlackSheepWall �� turn
//													�ۼ��� : searer
//													Last Update : 2000. 8. 17
//
////////////////////////////////////////////////////////////////////////////////

void BlackSheepWall::Turn() {
	int i, j;

	switch (nTurnType) {
	// nTurnType 1
	case 1:
		// Sensor initialize
		for (i=0; i<lpmapMap->xSize(); i++)
			for (j=0; j<lpmapMap->ySize(); j++)
				nMapData[i][j] = UNKNOWN;

		if (bTrigger == false)
			return;
		nRemainingTime = nContinueTime;
		nTurnType = 2;
	// nTurnType 2
	case 2:
		// Map �ޱ�
		for (i=0; i<lpmapMap->xSize(); i++)
			for (j=0; j<lpmapMap->ySize(); j++)
				nMapData[i][j] = lpmapMap->QueryGeometry(i, j);

		// ��, źȯ, ���� ���� �ޱ�
		allEnemy = lpmapMap->getObject();
		nEnemy = 0;

		for (i=0; i<100; i++) {
			if (allEnemy[i] != NULL) {
				detectedEnemy[nEnemy] = allEnemy[i];
				nEnemy++;
			}
		}
		
		nRemainingTime--;
		if (nRemainingTime > 0)
			return;
		nTurnType = 3;
		bTrigger = false;

		// Sensor �� �� ���̴� ���·� �ٲٱ�
		for (i=0; i<lpmapMap->xSize(); i++)
			for (j=0; j<lpmapMap->ySize(); j++)
				nMapData[i][j] = UNKNOWN;
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// BlackSheepWall::Draw();
//		BlackSheepWall �� draw
//													�ۼ��� : searer
//													Last Update : 2000. 8. 23
//
////////////////////////////////////////////////////////////////////////////////

void BlackSheepWall::Draw() {
	int nCurrentX = 100, nCurrentY = 100;

//	lpexExplorer->QueryPosition(&nCurrentX, &nCurrentY);
//	sprite.setCurrent(nCurrentX, nCurrentY);
//	sprite.redraw();
}
