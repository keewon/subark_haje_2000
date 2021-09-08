////////////////////////////////////////////////////////////////////////////////
//
// "MineBullet.cpp"
//		MineBullet
//												작성자 : searer
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
//		MineBullet 의 클래스
//												작성자 : searer
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
//		MineBullet 의 turn
//												작성자 : searer
//												Last Update : 2000. 8. 29
//
////////////////////////////////////////////////////////////////////////////////

void MineBullet::Turn() {
	int i = 0;
	int nX, nY;
	Object **enemyList = lpmapMap->getObject();

	// 터질 때
	if (bBang == true) {
		// 데미지 주기
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

		// 탄환 없애기
		if (nDamageTime <= 0) {
			lpmapMap->Delete(this);
			delete this;
		}
		nDamageTime--;
	}
	else {
		// 탄환이 적에게 맞았을 때 터짐
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
//		MineBullet 의 draw
//												작성자 : searer
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
//												작성자 : searer
//												Last Update : 2000. 11. 1
//
////////////////////////////////////////////////////////////////////////////////

void MineBullet::Damage(int) {
	bBang = true;
}
