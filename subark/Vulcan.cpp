////////////////////////////////////////////////////////////////////////////////
//
// "Vulcan.cpp"
//		Vulcan
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
// Vulcan::Vulcan();
//		Vulcan �� ������
//													�ۼ��� : searer
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

	dCannonDirect = 180;							// ���� ���� (����)
	nDamage = 10;
	nSplash = 30;
	nDetectRange = 5;								// źȯ ũ�� (����)
	nReloadTime = 10;
	nRemainTime = 10;
	nRemainAmmo = 2000;
	nShotNum = 20;

	dRotateSp = 2;
	nRange = 200;
	nAccuracy = 100;
	nFireSp = 5;									// �ʱ� �ӵ� (����)
	nEnemyStopTime = 0;
}

////////////////////////////////////////////////////////////////////////////////
//
// Vulcan::Turn();
//		Vulcan �� turn
//													�ۼ��� : searer
//													Last Update : 2000. 8. 21
//
////////////////////////////////////////////////////////////////////////////////

void Vulcan::Turn() {
	// ���� ȸ��
	if (bRotate == true) {							// ȸ�� flag üũ
		if (dCannonDirect == dAimAngle)				// ȸ�� ���� üũ
			bRotate = false;
		else {
			if (dAimAngle > 0) {					// ȸ�� �ӵ���ŭ ȸ��
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
// Vulcan::Draw();
//		Vulcan �� draw
//													�ۼ��� : searer
//													Last Update : 2000. 8. 24
//
////////////////////////////////////////////////////////////////////////////////

void Vulcan::Draw() {
	int nCurrentX, nCurrentY;
	char szSpriteName[30];
	double temp = dCannonDirect;

	// ���� ����
	while (temp < 0)
		temp += 360;
	while (temp >= 360)
		temp -= 360;

	// ���� ������ ���� �׸� ��ȣ
	int nSpriteNumber = (int)(temp/45);

	lpexExplorer->QueryPosition(&nCurrentX, &nCurrentY);
	sprintf(szSpriteName, "Resource/Vulcan%d.bmp", nSpriteNumber);
	sprite.update(szSpriteName, 40, 40);
	sprite.setCurrent(nCurrentX-20, nCurrentY-20);
	sprite.redraw();
}
