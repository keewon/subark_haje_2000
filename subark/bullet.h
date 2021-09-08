////////////////////////////////////////////////////////////////////////////////
//
// "Bullet.h"
//		탄환
//												작성자 : searer
//												Last Update : 2000. 8. 15
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _BULLET_H_SEARER_BECD_
#define _BULLET_H_SEARER_BECD_

/// Includes ///////////////////////////////////////////////////////////////////

#include "Object.h"
#include "Map.h"
#include <math.h>

/// Class or functions /////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class Bullet
//		Bullet 의 클래스
//												작성자 : searer
//												Last Update : 2000. 8. 15
//
////////////////////////////////////////////////////////////////////////////////

class Bullet : public Object {
	public:
		~Bullet();							// 소멸자

		virtual void Turn() = 0;			// turn
		virtual void Draw() = 0;			// draw
		virtual void Damage(int) = 0;

	protected:
		double dFireDirection;				// 발사 방향
		int nBulletX, nBulletY;				// 탄환 위치
		int nDamage;						// 데미지 크기
		int nSplash;						// 스플래쉬 데미지의 범위
		int nDetectRange;					// 탄환 크기
};

////////////////////////////////////////////////////////////////////////////////
//
// class StraightBullet
//		StraightBullet 의 클래스
//												작성자 : searer
//												Last Update : 2000. 8. 23
//
////////////////////////////////////////////////////////////////////////////////

class StraightBullet : public Bullet {
	public:
		StraightBullet(double dFD, int nX, int nY, int nDmg, int nSplsh,
			int nDRange, bool bGeoE, bool bAPass, int nFlyD,
			int nFSp, int nAcc, int nEStop, int nFGeo);
											// 생성자
		void Turn();						// turn
		void Draw();						// draw
		void Damage(int);

	protected:
		bool bGeoEnable;					// 지형 영향 여부
		bool bArmorPass;					// 장갑 무시 여부
		bool bBang;							// 폭발 여부
		int nFlyDistance;					// 날아갈 거리
		int nFireSp;						// 발사 속도
		int nAccuracy;						// 정확도
		int nEnemyStopTime;					// 적 멈춤 시간
		int nFireGeo;						// 발사지형
		int nCurrentGeo;					// 현재 지형
		int nBangNumber;					// 터질 때 스프라이트 번호
};

////////////////////////////////////////////////////////////////////////////////
//
// class ArtileryBullet
//		ArtileryBullet 의 클래스
//												작성자 : searer
//												Last Update : 2000. 8. 23
//
////////////////////////////////////////////////////////////////////////////////

class ArtileryBullet : public Bullet {
	public:
		ArtileryBullet(double dFD, int nX, int nY, int nDmg, int nSplsh,
			int nDRange, bool bGeoE, int nFlyD,	int nFSp,
			int nAcc, int nEStop, int nDTime);
											// 생성자
		void Turn();						// turn
		void Draw();						// draw
		void Damage(int);

	protected:
		bool bGeoEnable;					// 지형 영향 여부
		bool bBang;							// 폭발 여부
		int nFlyDistance;					// 날아갈 거리
		int nFireSp;						// 발사 속도
		int nAccuracy;						// 정확도
		int nEnemyStopTime;					// 적 멈춤 시간
		int nDamageTime;					// 데미지 지속 시간
		int nBangNumber;					// 터질 때 스프라이트 번호
};

////////////////////////////////////////////////////////////////////////////////
//
// class MineBullet
//		MineBullet 의 클래스
//												작성자 : searer
//												Last Update : 2000. 8. 23
//
////////////////////////////////////////////////////////////////////////////////

class MineBullet : public Bullet {
	public:
		MineBullet(int nX, int nY, int nDmg, int nSplsh, int nDRange,
			int nEStop);					// 생성자
		void Turn();						// turn
		void Draw();						// draw
		void Damage(int);

	protected:
		bool bBang;							// 폭발 여부
		int nEnemyStopTime;					// 적 멈춤 시간
		int nDamageTime;					// 데미지 지속 시간
};

////////////////////////////////////////////////////////////////////////////////
//
// class HomingBullet
//		HomingBullet 의 클래스
//												작성자 : searer
//												Last Update : 2000. 8. 23
//
////////////////////////////////////////////////////////////////////////////////

class HomingBullet : public Bullet {
	public:
		void Turn();						// turn
		void Draw();						// draw
		void Damage(int);

	protected:
		bool bGeoEnable;					// 지형 영향 여부
		bool bHoming;						// 유도 flag
		bool bBang;							// 폭발 여부
		double dAimAngle;					// 목표 각도
		double dRotatingSp;					// 미사일 회전 속도
		int nFlyDistance;					// 날아갈 거리
		int nFireSp;						// 발사 속도
		int nAccuracy;						// 정확도
		int nHomingRange;					// 유도가 가능한 거리
		int nFireGeo;						// 발사지형
		int nCurrentGeo;					// 현재 지형
};

////////////////////////////////////////////////////////////////////////////////
//
// class NukeBullet
//		NukeBullet 의 클래스
//												작성자 : searer
//												Last Update : 2000. 8. 23
//
////////////////////////////////////////////////////////////////////////////////

class NukeBullet : public Bullet {
	public:
		NukeBullet(int nX, int nY, int nDmg, int nSplsh);
											// 생성자
		void Turn();						// turn
		void Draw();						// draw
		void Damage(int);

	protected:
		bool bFalling;						// 투하 flag
		int nAccuracy;						// 정확도
		int nRemainTime;					// 남은 투하 시간
};

#endif	// _BULLET_H_SEARER_BECD_
