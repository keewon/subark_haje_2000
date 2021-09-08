////////////////////////////////////////////////////////////////////////////////
//
// "StraightBullet.cpp"
//		StraightBullet
//												작성자 : searer
//												Last Update : 2000. 8. 29
//
////////////////////////////////////////////////////////////////////////////////

/// Includes ///////////////////////////////////////////////////////////////////

#include "Bullet.h"
#include "Map.h"
#include <stdio.h>		// to debug

/// Class or functions /////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// StraightBullet::StraightBullet();
//		StraightBullet 의 클래스
//												작성자 : searer
//												Last Update : 2000. 8. 29
//
////////////////////////////////////////////////////////////////////////////////

StraightBullet::StraightBullet(double dFD, int nX, int nY, int nDmg, int nSplsh,
							   int nDRange, bool bGeoE, bool bAPass, int nFlyD,
							   int nFSp, int nAcc, int nEStop, int nFGeo) {
	dFireDirection = dFD;
	nBulletX = nX;
	nBulletY = nY;
	nDamage = nDmg;
	nSplash = nSplsh;
	nDetectRange = nDRange;
	bGeoEnable = bGeoE;
	bArmorPass = bAPass;
	nFlyDistance = nFlyD;
	nFireSp = nFSp;
	nAccuracy = nAcc;
	nEnemyStopTime = nEStop;
	nFireGeo = nFGeo;
	nCurrentGeo = nFGeo;
	bBang = false;
	// oedalpha changed
	nBangNumber = 0;
	//sprite.update("Resource/StraightBullet.bmp", 20, 20);
}

////////////////////////////////////////////////////////////////////////////////
//
// StraightBullet::Turn();
//		StraightBullet 의 turn
//												작성자 : searer
//												Last Update : 2000. 8. 29
//
////////////////////////////////////////////////////////////////////////////////

void StraightBullet::Turn() {
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
		lpmapMap->Delete(this);
		delete this;
	}
	// 날아갈 때
	else {
		// 탄환 이동
		nFlyDistance -= nFireSp;
		nBulletX += int(nFireSp*sin(dFireDirection*3.141592/180));
		nBulletY -= int(nFireSp*cos(dFireDirection*3.141592/180));

		// 지형이 틀려졌을 때 터짐
		nCurrentGeo = lpmapMap->QueryGeometry(nBulletX, nBulletY);
		if (nCurrentGeo != nFireGeo)
			bBang = true;
		// 탄환이 적에게 맞았을 때 터짐
		i = 0;
		while (i<100) {
			if (enemyList[i] != NULL) {
				enemyList[i]->QueryPosition(&nX, &nY);
				if ((nBulletX-nX)*(nBulletX-nX) + (nBulletY-nY)*(nBulletY-nY)
					<= nDetectRange*nDetectRange) {
					bBang = true;
					break;
				}
			}
			i++;
		}
		// 날아갈 거리를 다 날았을 때 터짐
		if (nFlyDistance <= 0)
			bBang = true;
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// StraightBullet::Draw();
//		StraightBullet 의 draw
//												작성자 : searer
//												Last Update : 2000. 8. 29
//
////////////////////////////////////////////////////////////////////////////////

void StraightBullet::Draw() {
	// oedalpha changed this function a lot.
	int nSpriteNumber;
	char szSpriteName[80];
	if (bBang == false) {
		nSpriteNumber = (int)(dFireDirection / 22.5);
		sprintf(szSpriteName, "Resource/탄환/탄환%04d.bmp", nSpriteNumber);
		sprite.update(szSpriteName, 25, 20);
		sprite.setCurrent(nBulletX-12, nBulletY-10);
		sprite.redraw();
	}
	else {
		if (0 <= nBangNumber && nBangNumber < 8) {
			sprintf(szSpriteName, "Resource/달걀/달걀%d.bmp", (int)(nBangNumber / 2));
			sprite.update(szSpriteName, 70, 70);
			sprite.setCurrent(nBulletX-35, nBulletY-35);
			sprite.redraw();
			nBangNumber++;
		}
		else if ( 8 <= nBangNumber && nBangNumber < 24) {
			sprintf(szSpriteName, "Resource/달걀/달걀%d.bmp", 3-(int)((nBangNumber-8) / 4));
			sprite.update(szSpriteName, 70, 70);
			sprite.setCurrent(nBulletX-35, nBulletY-35);
			sprite.redraw();
			nBangNumber++;
		}
		else {
			nBangNumber = 1000;
		}
	}

	/* changed by oedalpha
	HDC hDC;
	char msg[30];

	Sprite::Surface()->GetDC(&hDC);
	sprintf(msg, "%f %d", nFireSp*sin(dFireDirection)*3.141592/180, dFireDirection);
	TextOut(hDC, 0, 0, msg, strlen(msg));
	Sprite::Surface()->ReleaseDC(hDC);
	changed by oedalpha */
}

////////////////////////////////////////////////////////////////////////////////
//
// StraightBullet::Damage(int);
//												작성자 : searer
//												Last Update : 2000. 11. 1
//
////////////////////////////////////////////////////////////////////////////////

void StraightBullet::Damage(int) {
	bBang = true;
}
