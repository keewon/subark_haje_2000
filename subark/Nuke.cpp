////////////////////////////////////////////////////////////////////////////////
//
// "Nuke.cpp"
//		Nuke
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
// Nuke::Nuke();
//		Nuke �� ������
//													�ۼ��� : searer
//													Last Update : 2000. 8. 20
//
////////////////////////////////////////////////////////////////////////////////

Nuke::Nuke(Explorer *lpexExp) {
	lpexExplorer = lpexExp;
	bFire = true;
	bLoad = false;

	nDamage = 650;
	nSplash = 50;
	nReloadTime = 10;
	nRemainTime = 10;
	nRemainAmmo = 7;
	nShotNum = 1;

	nRange = 400;
}

////////////////////////////////////////////////////////////////////////////////
//
// Nuke::Turn();
//		Nuke �� turn
//													�ۼ��� : searer
//													Last Update : 2000. 8. 21
//
////////////////////////////////////////////////////////////////////////////////

void Nuke::Turn() {
	// źȯ �߻�
	if (bFire == true) {							// �߻� flag üũ
		if (bLoad == true) {						// ���� flag üũ
//			new NukeBullet(nShotNum);
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
// Nuke::Draw();
//		Nuke �� draw
//													�ۼ��� : searer
//													Last Update : 2000. 8. 24
//
////////////////////////////////////////////////////////////////////////////////

void Nuke::Draw() {
}