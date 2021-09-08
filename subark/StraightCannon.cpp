////////////////////////////////////////////////////////////////////////////////
//
// "StraightCannon.cpp"
//		StraightCannon
//													�ۼ��� : searer
//													Last Update : 2000. 8. 20
//
////////////////////////////////////////////////////////////////////////////////

/// Includes ///////////////////////////////////////////////////////////////////

#include "Weapon.h"

/// Public macros & Constants //////////////////////////////////////////////////

/// Implementations ////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// StraightCannon::StraightCannon();
//		StraightCannon �� ������
//													�ۼ��� : searer
//													Last Update : 2000. 8. 20
//
////////////////////////////////////////////////////////////////////////////////

StraightCannon::StraightCannon(Explorer *lpexExp) {
	lpexExplorer = lpexExp;
	bFire = false;
	nFlyDistance = 200;
	bRotate = false;
	bLoad = false;
	bGeoEnable = false;
	bRotateEnable = false;
	bArmorPass = false;

	dCannonDirect = 180;							// ���� ���� (����)
	nDamage = 150;
	nSplash = 30;
	nDetectRange = 5;								// źȯ ũ�� (����)
	nReloadTime = 5;
	nRemainTime = 1;
	nRemainAmmo = 10000;
	nShotNum = 2;

	dRotateSp = 20;
	nRange = 360;
	nAccuracy = 100;
	nFireSp = 15;									// �ʱ� �ӵ� (����)
	nEnemyStopTime = 0;
}

////////////////////////////////////////////////////////////////////////////////
//
// StraightCannon::Turn();
//		StraightCannon �� turn
//													�ۼ��� : searer
//													Last Update : 2000. 8. 20
//
////////////////////////////////////////////////////////////////////////////////

void StraightCannon::Turn() {
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
			if (bRotateEnable == false)
				return;
		}
	}
	// źȯ �߻�
	if (bFire == true) {							// �߻� flag üũ
		if (bLoad == true) {						// ���� flag üũ
			int nX, nY;
			int nGeo;
			lpexExplorer->QueryPosition(&nX, &nY);
			nGeo = lpmapMap->QueryGeometry(nX, nY);
			// ��ǥ���� (40 <== ���� ����)
			nX += int(40*sin(dCannonDirect*3.141592/180));
			nY -= int(40*cos(dCannonDirect*3.141592/180));
			lpmapMap->Append(new StraightBullet(dCannonDirect, nX, nY, nDamage,
				nSplash, nDetectRange, bGeoEnable, bArmorPass, nFlyDistance,
				nFireSp, nAccuracy, nEnemyStopTime, nGeo));
													// źȯ ����
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
// StraightCannon::Draw();
//		StraightCannon �� draw
//													�ۼ��� : searer
//													Last Update : 2000. 8. 24
//
////////////////////////////////////////////////////////////////////////////////

void StraightCannon::Draw() {
	int nCurrentX, nCurrentY;
	char szSpriteName[30];
	double temp = dCannonDirect;

	// ���� ����
	while (temp < 0)
		temp += 360;
	while (temp >= 360)
		temp -= 360;

	// ���� ������ ���� �׸� ��ȣ
	int nSpriteNumber = (int)(temp/22.5);

	lpexExplorer->QueryPosition(&nCurrentX, &nCurrentY);
	sprintf(szSpriteName, "Resource/����/����%04d.bmp", nSpriteNumber);
	sprite.update(szSpriteName, 150, 110);
	sprite.setCurrent(nCurrentX-75, nCurrentY-55);
	sprite.redraw();
}
