////////////////////////////////////////////////////////////////////////////////
//
// "Weapon.h"
//		Weapon
//													작성자 : searer
//													Last Update : 2000. 8. 4
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _WEAPON_H_SEARER_BECD_
#define _WEAPON_H_SEARER_BECD_

/// Includes ///////////////////////////////////////////////////////////////////

#include "Part.h"
#include "Value.h"
#include "Bullet.h"
#include "Explorer.h"
#include "Map.h"
#include <stdio.h>
#include <string.h>

/// Class or functions /////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class Weapon
//		Weapon Part 의 클래스
//
//													작성자 : searer
//													Last Update : 2000. 7. 26
//
////////////////////////////////////////////////////////////////////////////////

class Weapon : public Part {
	public:
		~Weapon();							// 소멸자
		Value* Operation(char *lpszOpName, VoidList *lpvlArgument);
		Value* Attribute(char *lpszName);
		void Rotate(double);				// 포대 회전
		void Fire();						// 발사
		void Target(int);					// 날아갈 거리
	
	protected:
		Explorer *lpexExplorer;				// 탐사선의 포인터
		bool bFire;							// 발사 flag
		bool bRotate;						// 회전 flag
		bool bLoad;							// 장전 flag
		bool bGeoEnable;					// 지형 영향 여부

		double dCannonDirect;				// 포대 방향
		double dAimAngle;					// 목표 각도
		double dRotatingAngle;				// 포대가 회전한 각도
		int nRange;							// 사정 거리
		int nFlyDistance;					// 탄환이 날아갈 거리
		int nDamage;						// 데미지의 크기
		int nSplash;						// 스플래쉬 범위
		int nDetectRange;					// 감지 범위
		int nReloadTime;					// 재장전 시간
		int nRemainTime;					// 남은 장전 시간
		int nRemainAmmo;					// 남은 탄환 수
		int nLoadedAmmo;					// 장전된 탄환 수
		int nShotNum;						// 연사량
};

////////////////////////////////////////////////////////////////////////////////
//
// class StraightWeapon
//		StraightWeapon 의 클래스
//													작성자 : searer
//													Last Update : 2000. 8. 20
//
////////////////////////////////////////////////////////////////////////////////

class StraightWeapon : public Weapon {
	protected:
		bool bRotateEnable;					// 발사 중 포대 회전 여부
		bool bArmorPass;					// 장갑 무시 여부

		double dRotateSp;					// 포대 회전 속도
		int nAccuracy;						// 정확도
		int nFireSp;						// 발사 속도
		int nEnemyStopTime;					// 적 멈춤 시간
};

class StraightCannon : public StraightWeapon {
	public:
		StraightCannon(Explorer *lpexExp);	// 생성자
		void Turn();						// turn
		void Draw();						// draw
};

class Vulcan : public StraightWeapon {
	public:
		Vulcan(Explorer *lpexExp);			// 생성자
		void Turn();						// turn
		void Draw();						// draw
};

class RailCannon : public StraightWeapon {
	public:
		RailCannon(Explorer *lpexExp);		// 생성자
		void Turn();						// turn
		void Draw();						// draw
};

class StraightEnergyField : public StraightWeapon {
	public:
		StraightEnergyField(Explorer *lpexExp);
											// 생성자
		void Turn();						// turn
		void Draw();						// draw
};

////////////////////////////////////////////////////////////////////////////////
//
// class ArtileryWeapon
//		ArtileryWeapon 의 클래스
//													작성자 : searer
//													Last Update : 2000. 8. 20
//
////////////////////////////////////////////////////////////////////////////////

class ArtileryWeapon : public Weapon {
	protected:
		double dRotateSp;					// 포대 회전 속도
		int nAccuracy;						// 정확도
		int nFireSp;						// 발사 속도
		int nEnemyStopTime;					// 적 멈춤 시간
		int nDamageTime;					// 데미지 지속 시간
};

class ArtileryCannon : public ArtileryWeapon {
	public:
		ArtileryCannon(Explorer *lpexExp);	// 생성자
		void Turn();						// turn
		void Draw();						// draw
};

class ShotCannon : public ArtileryWeapon {
	public:
		ShotCannon(Explorer *lpexExp);		// 생성자
		void Turn();						// turn
		void Draw();						// draw
};

class NetroCannon : public ArtileryWeapon {
	public:
		NetroCannon(Explorer *lpexExp);		// 생성자
		void Turn();						// turn
		void Draw();						// draw
};

class EnergyCannon : public ArtileryWeapon {
	public:
		EnergyCannon(Explorer *lpexExp);	// 생성자
		void Turn();						// turn
		void Draw();						// draw
};

////////////////////////////////////////////////////////////////////////////////
//
// class Mine
//		Mine 의 클래스
//													작성자 : searer
//													Last Update : 2000. 8. 31
//
////////////////////////////////////////////////////////////////////////////////

class Mine : public Weapon {
	protected:
		int nEnemyStopTime;					// 적 멈춤 시간
};

class NormalMine : public Mine {
	public:
		NormalMine(Explorer *lpexExp);		// 생성자
		void Turn();						// turn
		void Draw();						// draw
};

class NetroMine : public Mine {
	public:
		NetroMine(Explorer *lpexExp);		// 생성자
		void Turn();						// turn
		void Draw();						// draw
};

class EnergyMine : public Mine {
	public:
		EnergyMine(Explorer *lpexExp);		// 생성자
		void Turn();						// turn
		void Draw();						// draw
};

////////////////////////////////////////////////////////////////////////////////
//
// class HomingMissile
//		HomingMissile 의 클래스
//													작성자 : searer
//													Last Update : 2000. 8. 31
//
////////////////////////////////////////////////////////////////////////////////

class HomingMissile : public Weapon {
	public:
		HomingMissile(Explorer *lpexExp);	// 생성자
		void Turn();						// turn
		void Draw();						// draw

	protected:
		double dRotateSp;					// 포대 회전 속도
		int nHomingRange;					// 유도 거리
		int nMisRotSp;						// 미사일 회전 속도
};

////////////////////////////////////////////////////////////////////////////////
//
// class Nuke
//		Nuke 의 클래스
//													작성자 : searer
//													Last Update : 2000. 8. 31
//
////////////////////////////////////////////////////////////////////////////////

class Nuke : public Weapon {
	public:
		Nuke(Explorer *lpexExp);			// 생성자
		void Turn();						// turn
		void Draw();						// draw

	protected:
		int nFallingTime;					// 투하시간
		int nFireGeo;						// 발사 지형
		int nNowGeo;						// 현재 지형
};

#endif	// _WEAPON_H_SEARER_BECD_
