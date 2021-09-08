////////////////////////////////////////////////////////////////////////////////
//
// "NormalSensor.cpp"
//		NormalSensor
//													작성자 : searer
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
// NormalSensor::NormalSensor(Explorer *lpexExp);
//		class NormalSensor 의 생성자
//		IN:
//			lpexExp	- 탐사선의 포인터
//													작성자 : searer
//													Last Update : 2000. 8. 15
//
////////////////////////////////////////////////////////////////////////////////

NormalSensor::NormalSensor(Explorer *lpexExp) {
	lpexExplorer = lpexExp;
	nSensingRange = 60;
}

////////////////////////////////////////////////////////////////////////////////
//
// NormalSensor::Turn();
//		NormalSensor 의 turn
//													작성자 : searer
//													Last Update : 2000. 8. 15
//
////////////////////////////////////////////////////////////////////////////////

void NormalSensor::Turn() {
	int i, j;
	int nX, nY;								// 센서의 위치

	lpexExplorer->QueryPosition(&nX, &nY);
	nX = nX/20;
	nY = nY/20;

	int nMinX, nMaxX;
	int nMinY, nMaxY;

	nMinX = nX-nSensingRange;
	nMaxX = nX+nSensingRange;
	nMinY = nY-nSensingRange;
	nMaxY = nY+nSensingRange;

	if (nX-nSensingRange < 0)
		nMinX = 0;
	if (nX+nSensingRange >= lpmapMap->xSize())
		nMaxX = lpmapMap->xSize() -1;
	if (nY-nSensingRange < 0)
		nMinY = 0;
	if (nY-nSensingRange >= lpmapMap->ySize())
		nMaxY = lpmapMap->ySize() -1;

	// Map 받기
	for (i=nMinX; i<nMaxX; i++)
		for (j=nMinY; j<nMaxY; j++)
			if ((nX-i)*(nX-i) + (nY-j)*(nY-j) <= nSensingRange*nSensingRange) {
				nMapData[i][j] = lpmapMap->QueryGeometry(i, j);
				// update 하기 예정
			}
			else
				nMapData[i][j] = UNKNOWN;

	// 적, 탄환, 센서 정보 받기
	int nX1, nY1;
	allEnemy = lpmapMap->getObject();
	nEnemy = 0;

	for (i=0; i<100; i++) {
		if (allEnemy[i] != NULL) {
			allEnemy[i]->QueryPosition(&nX1, &nY1);
			if ((nX-nX1)*(nX-nX1) + (nY-nY1)*(nY-nY1)
				<= nSensingRange*nSensingRange) {
				detectedEnemy[nEnemy] = allEnemy[i];
				nEnemy++;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// NormalSensor::Draw();
//		NormalSensor 의 draw
//													작성자 : searer
//													Last Update : 2000. 8. 22
//
////////////////////////////////////////////////////////////////////////////////

void NormalSensor::Draw() {
//	int nCurrentX = 100, nCurrentY = 100;

//	lpexExplorer->QueryPosition(&nCurrentX, &nCurrentY);
//	sprite.setCurrent(nCurrentX, nCurrentY);
//	sprite.redraw();
}
