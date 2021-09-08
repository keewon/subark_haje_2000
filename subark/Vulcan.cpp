////////////////////////////////////////////////////////////////////////////////
//
// "Vulcan.cpp"
//		Vulcan
//													작성자 : searer
//													Last Update : 2000. 8. 21
//
////////////////////////////////////////////////////////////////////////////////

/// Includes ///////////////////////////////////////////////////////////////////

#include "Weapon.h"

/// Public macros & Constants //////////////////////////////////////////////////

/// Implementations ////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Vulcan::Vulcan();
//		Vulcan 의 생성자
//													작성자 : searer
//													Last Update : 2000. 8. 21
//
////////////////////////////////////////////////////////////////////////////////

Vulcan::Vulcan(Explorer *lpexExp) {
	lpexExplorer = lpexExp;
	bFire = false;
	bRotate = false;
	bLoad = false;
	bGeoEnable = false;
	bRotateEnable = false;
	bArmorPass = false;

	dCannonDirect = 180;							// 포대 각도 (수정)
	nDamage = 10;
	nSplash = 30;
	nDetectRange = 5;								// 탄환 크기 (수정)
	nReloadTime = 10;
	nRemainTime = 10;
	nRemainAmmo = 2000;
	nShotNum = 20;

	dRotateSp = 2;
	nRange = 200;
	nAccuracy = 100;
	nFireSp = 5;									// 초기 속도 (수정)
	nEnemyStopTime = 0;
}

////////////////////////////////////////////////////////////////////////////////
//
// Vulcan::Turn();
//		Vulcan 의 turn
//													작성자 : searer
//													Last Update : 2000. 8. 21
//
////////////////////////////////////////////////////////////////////////////////

void Vulcan::Turn() {
	// 포대 회전
	if (bRotate == true) {							// 회전 flag 체크
		if (dCannonDirect == dAimAngle)				// 회전 각도 체크
			bRotate = false;
		else {
			if (dAimAngle > 0) {					// 회전 속도만큼 회전
				if (dAimAngle-dCannonDirect > dRotateSp)
					dCannonDirect += dRotateSp;
				else
					dCannonDirect = dAimAngle;
			}
			else {
				if (dCannonDirect-dAimAngle > dRotateSp)
					dCannonDirect -= dRotateSp;
				else
					dCannonDirect = dAimAngle;
			}
			if (bRotateEnable == false)
				return;
		}
	}
	// 탄환 발사
	if (bFire == true) {							// 발사 flag 체크
		if (bLoad == true) {						// 장전 flag 체크
			int nX, nY;
			int nGeo;
			lpexExplorer->QueryPosition(&nX, &nY);
			nGeo = lpmapMap->QueryGeometry(nX, nY);
			// 좌표보정 (40 <== 포대 길이)
			nX += int(40*sin(dCannonDirect*3.141592/180));
			nY -= int(40*cos(dCannonDirect*3.141592/180));
			lpmapMap->Append(new StraightBullet(dCannonDirect, nX, nY, nDamage,
				nSplash, nDetectRange, bGeoEnable, bArmorPass, nFlyDistance,
				nFireSp, nAccuracy, nEnemyStopTime, nGeo));
													// 탄환 생성
			nLoadedAmmo--;
			if (nLoadedAmmo > 0)
				return;
			bLoad = false;
			bFire = false;
		}
//		else
//			bFire = false;
	}
	else {
		if (bLoad == true)
			return;
		else if (nRemainAmmo <= 0)
			return;
	}
	// 탄환 장전
	nRemainTime--;									// 장전 시간 감소
	if (nRemainTime <= 0 && nRemainAmmo > 0) {
		bLoad = true;
		nLoadedAmmo = nShotNum;						// 연사량 만큼 장전
		nRemainAmmo -= nShotNum;
		nRemainTime = nReloadTime;
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// Vulcan::Draw();
//		Vulcan 의 draw
//													작성자 : searer
//													Last Update : 2000. 8. 24
//
////////////////////////////////////////////////////////////////////////////////

void Vulcan::Draw() {
	int nCurrentX, nCurrentY;
	char szSpriteName[30];
	double temp = dCannonDirect;

	// 각도 보정
	while (temp < 0)
		temp += 360;
	while (temp >= 360)
		temp -= 360;

	// 포대 각도에 따른 그림 번호
	int nSpriteNumber = (int)(temp/45);

	lpexExplorer->QueryPosition(&nCurrentX, &nCurrentY);
	sprintf(szSpriteName, "Resource/Vulcan%d.bmp", nSpriteNumber);
	sprite.update(szSpriteName, 40, 40);
	sprite.setCurrent(nCurrentX-20, nCurrentY-20);
	sprite.redraw();
}
