////////////////////////////////////////////////////////////////////////////////
//
// "NormalMine.cpp"
//		NormalMine
//													�ۼ��� : searer
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
//		NormalMine �� ������
//													�ۼ��� : searer
//													Last Update : 2000. 8. 20
//
////////////////////////////////////////////////////////////////////////////////

NormalMine::NormalMine(Explorer *lpexExp) {
	lpexExplorer = lpexExp;
	bFire = false;
	bLoad = false;

	nDamage = 70;
	nSplash = 40;
	nDetectRange = 5;								// źȯ ũ�� (����)
	nReloadTime = 23;
	nRemainTime = 23;
	nRemainAmmo = 60;
	nShotNum = 1;

	nEnemyStopTime = 0;
}

////////////////////////////////////////////////////////////////////////////////
//
// NormalMine::Turn();
//		NormalMine �� turn
//													�ۼ��� : searer
//													Last Update : 2000. 8. 21
//
////////////////////////////////////////////////////////////////////////////////

void NormalMine::Turn() {
	// źȯ �߻�
	if (bFire == true) {							// �߻� flag üũ
		if (bLoad == true) {						// ���� flag üũ
			int nX, nY;
			lpexExplorer->QueryPosition(&nX, &nY);
			lpmapMap->Append(new MineBullet(nX, nY, nDamage, nSplash,
				nDetectRange, nEnemyStopTime));
													// źȯ ����
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
	// źȯ ����
	nRemainTime--;									// ���� �ð� ����
	if (nRemainTime <= 0 && nRemainAmmo > 0) {
		bLoad = true;
		nLoadedAmmo = nShotNum;						// ���緮 ��ŭ ����
		nRemainAmmo -= nShotNum;
		nRemainTime = nReloadTime;
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// NormalMine::Draw();
//		NormalMine �� draw
//													�ۼ��� : searer
//													Last Update : 2000. 8. 24
//
////////////////////////////////////////////////////////////////////////////////

void NormalMine::Draw() {
}
