////////////////////////////////////////////////////////////////////////////////
//
// "NetroCannon.cpp"
//		NetroCannon
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
// NetroCannon::NetroCannon();
//		NetroCannon �� ������
//													�ۼ��� : searer
//													Last Update : 2000. 8. 20
//
////////////////////////////////////////////////////////////////////////////////

NetroCannon::NetroCannon(Explorer *lpexExp) {
	lpexExplorer = lpexExp;
	bFire = false;
	bRotate = false;
	bLoad = false;
	bGeoEnable = false;

	dCannonDirect = 180;							// ���� ���� (����)
	nDamage = 5;
	nSplash = 90;
	nDetectRange = 5;								// źȯ ũ�� (����)
	nReloadTime = 23;
	nRemainTime = 23;
	nRemainAmmo = 60;
	nShotNum = 1;

	dRotateSp = 1;
	nRange = 900;
	nAccuracy = 85;
	nFireSp = 5;									// �ʱ� �ӵ� (����)
	nEnemyStopTime = 0;
}

////////////////////////////////////////////////////////////////////////////////
//
// NetroCannon::Turn();
//		NetroCannon �� turn
//													�ۼ��� : searer
//													Last Update : 2000. 8. 21
//
////////////////////////////////////////////////////////////////////////////////

void NetroCannon::Turn() {
	// ���� ȸ��
	if (bRotate == true) {							// ȸ�� flag üũ
		if (dCannonDirect == dAimAngle)				// ȸ�� ���� üũ
			bRotate = false;
		else {
			if (dAimAngle > dCannonDirect) {		// ȸ�� �ӵ���ŭ ȸ��
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
		}
	}
	// źȯ �߻�
	if (bFire == true) {							// �߻� flag üũ
		if (bLoad == true) {						// ���� flag üũ
			int nX, nY;
			lpexExplorer->QueryPosition(&nX, &nY);
			// ��ǥ���� (40 <== ���� ����)
			nX += int(40*sin(dCannonDirect*3.141592/180));
			nY -= int(40*cos(dCannonDirect*3.141592/180));
			lpmapMap->Append(new ArtileryBullet(dCannonDirect, nX, nY, nDamage,
				nSplash, nDetectRange, bGeoEnable, nFlyDistance, nFireSp,
				nAccuracy, nEnemyStopTime, nDamageTime));
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
// NetroCannon::Draw();
//		NetroCannon �� draw
//													�ۼ��� : searer
//													Last Update : 2000. 8. 24
//
////////////////////////////////////////////////////////////////////////////////

void NetroCannon::Draw() {
	int nCurrentX = 100, nCurrentY = 100;

//	lpexExplorer->QueryPosition(&nCurrentX, &nCurrentY);
	sprite.setCurrent(nCurrentX, nCurrentY);
	sprite.redraw();
}
