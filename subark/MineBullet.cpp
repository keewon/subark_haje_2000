////////////////////////////////////////////////////////////////////////////////
//
// "MineBullet.cpp"
//		MineBullet
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
// MineBullet::MineBullet();
//		MineBullet �� Ŭ����
//												�ۼ��� : searer
//												Last Update : 2000. 8. 29
//
////////////////////////////////////////////////////////////////////////////////

MineBullet::MineBullet(int nX, int nY, int nDmg, int nSplsh, int nDRange,
					   int nEStop) {
	nBulletX = nX;
	nBulletY = nY;
	nDamage = nDmg;
	nSplash = nSplsh;
	nDetectRange = nDRange;
	nEnemyStopTime = nEStop;
	bBang = false;
	sprite.update("Resource/MineBullet.bmp", 20, 20);
}

////////////////////////////////////////////////////////////////////////////////
//
// MineBullet::Turn();
//		MineBullet �� turn
//												�ۼ��� : searer
//												Last Update : 2000. 8. 29
//
////////////////////////////////////////////////////////////////////////////////

void MineBullet::Turn() {
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
	else {
		// źȯ�� ������ �¾��� �� ����
		while (i<100) {
			enemyList[i]->QueryPosition(&nX, &nY);
			if ((nBulletX-nX)*(nBulletX-nX) + (nBulletY-nY)*(nBulletY-nY)
				<= nDetectRange*nDetectRange) {
				bBang = true;
				break;
			}	
			i++;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// MineBullet::Draw();
//		MineBullet �� draw
//												�ۼ��� : searer
//												Last Update : 2000. 8. 29
//
////////////////////////////////////////////////////////////////////////////////

void MineBullet::Draw() {
	sprite.setCurrent(nBulletX, nBulletY);
	sprite.redraw();
}

////////////////////////////////////////////////////////////////////////////////
//
// MineBullet::Damage(int);
//												�ۼ��� : searer
//												Last Update : 2000. 11. 1
//
////////////////////////////////////////////////////////////////////////////////

void MineBullet::Damage(int) {
	bBang = true;
}
