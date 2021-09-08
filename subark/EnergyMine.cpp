////////////////////////////////////////////////////////////////////////////////
//
// "EnergyMine.cpp"
//		EnergyMine
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
// EnergyMine::EnergyMine();
//		EnergyMine �� ������
//													�ۼ��� : searer
//													Last Update : 2000. 8. 20
//
////////////////////////////////////////////////////////////////////////////////

EnergyMine::EnergyMine(Explorer *lpexExp) {
	lpexExplorer = lpexExp;
	bFire = false;
	bLoad = false;

	nDamage = 0;
	nSplash = 120;
	nDetectRange = 5;								// źȯ ũ�� (����)
	nReloadTime = 25;
	nRemainTime = 25;
	nRemainAmmo = 50;
	nShotNum = 1;

	nEnemyStopTime = 100;
}

////////////////////////////////////////////////////////////////////////////////
//
// EnergyMine::Turn();
//		EnergyMine �� turn
//													�ۼ��� : searer
//													Last Update : 2000. 8. 21
//
////////////////////////////////////////////////////////////////////////////////

void EnergyMine::Turn() {
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
// EnergyMine::Draw();
//		EnergyMine �� draw
//													�ۼ��� : searer
//													Last Update : 2000. 8. 24
//
////////////////////////////////////////////////////////////////////////////////

void EnergyMine::Draw() {
}
