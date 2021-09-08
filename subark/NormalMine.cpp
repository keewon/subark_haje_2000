////////////////////////////////////////////////////////////////////////////////
//
// "NormalMine.cpp"
//		NormalMine
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
// NormalMine::NormalMine();
//		NormalMine 의 생성자
//													작성자 : searer
//													Last Update : 2000. 8. 20
//
////////////////////////////////////////////////////////////////////////////////

NormalMine::NormalMine(Explorer *lpexExp) {
	lpexExplorer = lpexExp;
	bFire = false;
	bLoad = false;

	nDamage = 70;
	nSplash = 40;
	nDetectRange = 5;								// 탄환 크기 (수정)
	nReloadTime = 23;
	nRemainTime = 23;
	nRemainAmmo = 60;
	nShotNum = 1;

	nEnemyStopTime = 0;
}

////////////////////////////////////////////////////////////////////////////////
//
// NormalMine::Turn();
//		NormalMine 의 turn
//													작성자 : searer
//													Last Update : 2000. 8. 21
//
////////////////////////////////////////////////////////////////////////////////

void NormalMine::Turn() {
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
// NormalMine::Draw();
//		NormalMine 의 draw
//													작성자 : searer
//													Last Update : 2000. 8. 24
//
////////////////////////////////////////////////////////////////////////////////

void NormalMine::Draw() {
}
