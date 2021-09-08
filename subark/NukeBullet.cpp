////////////////////////////////////////////////////////////////////////////////
//
// "NukeBullet.cpp"
//		NukeBullet
//												�ۼ��� : searer
//												Last Update : 2000. 11. 2
//
////////////////////////////////////////////////////////////////////////////////

/// Includes ///////////////////////////////////////////////////////////////////

#include "Bullet.h"
#include "Map.h"

/// Class or functions /////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// NukeBullet::NukeBullet();
//		NukeBullet �� Ŭ����
//												�ۼ��� : searer
//												Last Update : 2000. 11. 2
//
////////////////////////////////////////////////////////////////////////////////

NukeBullet::NukeBullet(int nX, int nY, int nDmg, int nSplsh) {
	nBulletX = nX;
	nBulletY = nY;
	nDamage = nDmg;
	nSplash = nSplsh;

	bFalling = false;
	nRemainTime = 120;
	sprite.update("Resource/NukeBullet.bmp", 20, 20);
}

////////////////////////////////////////////////////////////////////////////////
//
// NukeBullet::Turn();
//		NukeBullet �� turn
//												�ۼ��� : searer
//												Last Update : 2000. 11. 2
//
////////////////////////////////////////////////////////////////////////////////

void NukeBullet::Turn() {
	// ���� �ð� ����
	if (nRemainTime <= 0)
		bFalling = true;
	else
		nRemainTime--;

	// ���� ��
	if (bFalling == true) {
		// ������ �ֱ�
		int i = 0;
		int nX, nY;
		Object **enemyList = lpmapMap->getObject();

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
		lpmapMap->Delete(this);
		delete this;
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// NukeBullet::Draw();
//		NukeBullet �� draw
//												�ۼ��� : searer
//												Last Update : 2000. 11. 2
//
////////////////////////////////////////////////////////////////////////////////

void NukeBullet::Draw() {
	sprite.setCurrent(nBulletX, nBulletY);
	sprite.redraw();
}

////////////////////////////////////////////////////////////////////////////////
//
// NukeBullet::Damage(int);
//												�ۼ��� : searer
//												Last Update : 2000. 11. 2
//
////////////////////////////////////////////////////////////////////////////////

void NukeBullet::Damage(int) {
	bFalling = true;
}
