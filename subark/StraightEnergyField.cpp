////////////////////////////////////////////////////////////////////////////////
//
// "StraightEnergyField.cpp"
//		StraightEnergyField
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
// StraightEnergyField::StraightEnergyField();
//		StraightEnergyField 의 생성자
//													작성자 : searer
//													Last Update : 2000. 8. 20
//
////////////////////////////////////////////////////////////////////////////////

StraightEnergyField::StraightEnergyField(Explorer *lpexExp) {
	lpexExplorer = lpexExp;
	bFire = false;
	bRotate = false;
	bLoad = false;
	bGeoEnable = false;
	bRotateEnable = false;
	bArmorPass = false;

	dCannonDirect = 180;							// 포대 각도 (수정)
	nDamage = 0;
	nSplash = 90;
	nDetectRange = 5;								// 탄환 크기 (수정)
	nReloadTime = 14;
	nRemainTime = 14;
	nRemainAmmo = 30;
	nShotNum = 1;

	dRotateSp = 2;
	nRange = 200;
	nAccuracy = 100;
	nFireSp = 5;									// 초기 속도 (수정)
	nEnemyStopTime = 100;
}

////////////////////////////////////////////////////////////////////////////////
//
// StraightEnergyField::Turn();
//		StraightEnergyField 의 turn
//													작성자 : searer
//													Last Update : 2000. 8. 21
//
////////////////////////////////////////////////////////////////////////////////

void StraightEnergyField::Turn() {
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
// StraightEnergyField::Draw();
//		StraightEnergyField 의 draw
//													작성자 : searer
//													Last Update : 2000. 8. 24
//
////////////////////////////////////////////////////////////////////////////////

void StraightEnergyField::Draw() {
	int nCurrentX = 100, nCurrentY = 100;

//	lpexExplorer->QueryPosition(&nCurrentX, &nCurrentY);
	sprite.setCurrent(nCurrentX, nCurrentY);
	sprite.redraw();
}
