////////////////////////////////////////////////////////////////////////////////
//
// "EnergyMine.cpp"
//		EnergyMine
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
// EnergyMine::EnergyMine();
//		EnergyMine 의 생성자
//													작성자 : searer
//													Last Update : 2000. 8. 20
//
////////////////////////////////////////////////////////////////////////////////

EnergyMine::EnergyMine(Explorer *lpexExp) {
	lpexExplorer = lpexExp;
	bFire = false;
	bLoad = false;

	nDamage = 0;
	nSplash = 120;
	nDetectRange = 5;								// 탄환 크기 (수정)
	nReloadTime = 25;
	nRemainTime = 25;
	nRemainAmmo = 50;
	nShotNum = 1;

	nEnemyStopTime = 100;
}

////////////////////////////////////////////////////////////////////////////////
//
// EnergyMine::Turn();
//		EnergyMine 의 turn
//													작성자 : searer
//													Last Update : 2000. 8. 21
//
////////////////////////////////////////////////////////////////////////////////

void EnergyMine::Turn() {
	// 탄환 발사
	if (bFire == true) {							// 발사 flag 체크
		if (bLoad == true) {						// 장전 flag 체크
			int nX, nY;
			lpexExplorer->QueryPosition(&nX, &nY);
			lpmapMap->Append(new MineBullet(nX, nY, nDamage, nSplash,
				nDetectRange, nEnemyStopTime));
													// 탄환 생성
			nLoadedAmmo--;
			if (nLoadedAmmo > 0)
				return;
			bLoad = false;
			bFire = false;
		}
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
// EnergyMine::Draw();
//		EnergyMine 의 draw
//													작성자 : searer
//													Last Update : 2000. 8. 24
//
////////////////////////////////////////////////////////////////////////////////

void EnergyMine::Draw() {
}
