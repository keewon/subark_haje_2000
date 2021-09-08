////////////////////////////////////////////////////////////////////////////////
//
// "ArtileryBullet.cpp"
//		ArtileryBullet
//												�ۼ��� : searer
//												Last Update : 2000. 8. 29
//
////////////////////////////////////////////////////////////////////////////////

/// Includes ///////////////////////////////////////////////////////////////////

#include "Bullet.h"
#include "Map.h"

/// Class or functions /////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// ArtileryBullet::ArtileryBullet();
//		ArtileryBullet �� Ŭ����
//												�ۼ��� : searer
//												Last Update : 2000. 8. 29
//
////////////////////////////////////////////////////////////////////////////////

ArtileryBullet::ArtileryBullet(double dFD, int nX, int nY, int nDmg, int nSplsh,
							   int nDRange, bool bGeoE,  int nFlyD, int nFSp,
							   int nAcc, int nEStop, int nDTime) {
	dFireDirection = dFD;
	nBulletX = nX;
	nBulletY = nY;
	nDamage = nDmg;
	nSplash = nSplsh;
	nDetectRange = nDRange;
	bGeoEnable = bGeoE;
	nFlyDistance = nFlyD;
	nFireSp = nFSp;
	nAccuracy = nAcc;
	nEnemyStopTime = nEStop;
	nDamageTime = nDTime;
	bBang = false;
	nBangNumber = 0;
	//sprite.update("Resource/ArtileryBullet.bmp", 20, 20);
}

////////////////////////////////////////////////////////////////////////////////
//
// ArtileryBullet::Turn();
//		ArtileryBullet �� turn
//												�ۼ��� : searer
//												Last Update : 2000. 8. 29
//
////////////////////////////////////////////////////////////////////////////////

void ArtileryBullet::Turn() {
	int i = 0;
	int nX, nY;
	Object **enemyList = lpmapMap->getObject();

	// ���� ��
	if (bBang == true) {
		// ������ �ֱ�
		while (i<100) {
			if (enemyList[i] != NULL) {
				enemyList[i]->QueryPosition(&nX, &nY);
				if ((nBulletX-nX)*(nBulletX-nX) + (nBulletY-nY)*(nBulletY-nY)
					<= nSplash*nSplash) {
					enemyList[i]->Damage(nDamage);
				}
			}
			i++;
		}

		// źȯ ���ֱ�
		if (nDamageTime <= 0) {
			lpmapMap->Delete(this);
			delete this;
		}
		nDamageTime--;
	}
	// ���ư� ��
	else {
		// źȯ �̵�
		nFlyDistance -= nFireSp;
		nBulletX += int(nFireSp*sin(dFireDirection*3.141592/180));
		nBulletY -= int(nFireSp*cos(dFireDirection*3.141592/180));

		// ���ư� �Ÿ��� �� ������ �� ����
		if (nFlyDistance <= 0)
			bBang = true;
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// ArtileryBullet::Draw();
//		ArtileryBullet �� draw
//												�ۼ��� : searer
//												Last Update : 2000. 8. 29
//
////////////////////////////////////////////////////////////////////////////////

void ArtileryBullet::Draw() {
	int nSpriteNumber;
	char szSpriteName[80];
	if (bBang == false) {
		nSpriteNumber = (int)(dFireDirection / 22.5);
		sprintf(szSpriteName, "Resource/źȯ/źȯ%04d.bmp", nSpriteNumber);
		sprite.update(szSpriteName, 25, 20);
		sprite.setCurrent(nBulletX-12, nBulletY-10);
		sprite.redraw();
	}
	else {
		if (0 <= nBangNumber && nBangNumber < 8) {
			sprintf(szSpriteName, "Resource/�ް�/�ް�%d.bmp", (int)(nBangNumber / 2));
			sprite.update(szSpriteName, 70, 70);
			sprite.setCurrent(nBulletX-35, nBulletY-35);
			sprite.redraw();
			nBangNumber++;
		}
		else if ( 8 <= nBangNumber && nBangNumber < 24) {
			sprintf(szSpriteName, "Resource/�ް�/�ް�%d.bmp", 3-(int)((nBangNumber-8) / 4));
			sprite.update(szSpriteName, 70, 70);
			sprite.setCurrent(nBulletX-35, nBulletY-35);
			sprite.redraw();
			nBangNumber++;
		}
		else {
			nBangNumber = 1000;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// ArtileryBullet::Damage(int);
//												�ۼ��� : searer
//												Last Update : 2000. 11. 1
//
////////////////////////////////////////////////////////////////////////////////

void ArtileryBullet::Damage(int) {
	bBang = true;
}
