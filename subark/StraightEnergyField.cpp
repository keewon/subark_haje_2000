////////////////////////////////////////////////////////////////////////////////
//
// "StraightEnergyField.cpp"
//		StraightEnergyField
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
// StraightEnergyField::StraightEnergyField();
//		StraightEnergyField �� ������
//													�ۼ��� : searer
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

	dCannonDirect = 180;							// ���� ���� (����)
	nDamage = 0;
	nSplash = 90;
	nDetectRange = 5;								// źȯ ũ�� (����)
	nReloadTime = 14;
	nRemainTime = 14;
	nRemainAmmo = 30;
	nShotNum = 1;

	dRotateSp = 2;
	nRange = 200;
	nAccuracy = 100;
	nFireSp = 5;									// �ʱ� �ӵ� (����)
	nEnemyStopTime = 100;
}

////////////////////////////////////////////////////////////////////////////////
//
// StraightEnergyField::Turn();
//		StraightEnergyField �� turn
//													�ۼ��� : searer
//													Last Update : 2000. 8. 21
//
////////////////////////////////////////////////////////////////////////////////

void StraightEnergyField::Turn() {
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
// StraightEnergyField::Draw();
//		StraightEnergyField �� draw
//													�ۼ��� : searer
//													Last Update : 2000. 8. 24
//
////////////////////////////////////////////////////////////////////////////////

void StraightEnergyField::Draw() {
	int nCurrentX = 100, nCurrentY = 100;

//	lpexExplorer->QueryPosition(&nCurrentX, &nCurrentY);
	sprite.setCurrent(nCurrentX, nCurrentY);
	sprite.redraw();
}
