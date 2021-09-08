////////////////////////////////////////////////////////////////////////////////
//
// "Weapon.h"
//		Weapon
//													�ۼ��� : searer
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
//		Weapon Part �� Ŭ����
//
//													�ۼ��� : searer
//													Last Update : 2000. 7. 26
//
////////////////////////////////////////////////////////////////////////////////

class Weapon : public Part {
	public:
		~Weapon();							// �Ҹ���
		Value* Operation(char *lpszOpName, VoidList *lpvlArgument);
		Value* Attribute(char *lpszName);
		void Rotate(double);				// ���� ȸ��
		void Fire();						// �߻�
		void Target(int);					// ���ư� �Ÿ�
	
	protected:
		Explorer *lpexExplorer;				// Ž�缱�� ������
		bool bFire;							// �߻� flag
		bool bRotate;						// ȸ�� flag
		bool bLoad;							// ���� flag
		bool bGeoEnable;					// ���� ���� ����

		double dCannonDirect;				// ���� ����
		double dAimAngle;					// ��ǥ ����
		double dRotatingAngle;				// ���밡 ȸ���� ����
		int nRange;							// ���� �Ÿ�
		int nFlyDistance;					// źȯ�� ���ư� �Ÿ�
		int nDamage;						// �������� ũ��
		int nSplash;						// ���÷��� ����
		int nDetectRange;					// ���� ����
		int nReloadTime;					// ������ �ð�
		int nRemainTime;					// ���� ���� �ð�
		int nRemainAmmo;					// ���� źȯ ��
		int nLoadedAmmo;					// ������ źȯ ��
		int nShotNum;						// ���緮
};

////////////////////////////////////////////////////////////////////////////////
//
// class StraightWeapon
//		StraightWeapon �� Ŭ����
//													�ۼ��� : searer
//													Last Update : 2000. 8. 20
//
////////////////////////////////////////////////////////////////////////////////

class StraightWeapon : public Weapon {
	protected:
		bool bRotateEnable;					// �߻� �� ���� ȸ�� ����
		bool bArmorPass;					// �尩 ���� ����

		double dRotateSp;					// ���� ȸ�� �ӵ�
		int nAccuracy;						// ��Ȯ��
		int nFireSp;						// �߻� �ӵ�
		int nEnemyStopTime;					// �� ���� �ð�
};

class StraightCannon : public StraightWeapon {
	public:
		StraightCannon(Explorer *lpexExp);	// ������
		void Turn();						// turn
		void Draw();						// draw
};

class Vulcan : public StraightWeapon {
	public:
		Vulcan(Explorer *lpexExp);			// ������
		void Turn();						// turn
		void Draw();						// draw
};

class RailCannon : public StraightWeapon {
	public:
		RailCannon(Explorer *lpexExp);		// ������
		void Turn();						// turn
		void Draw();						// draw
};

class StraightEnergyField : public StraightWeapon {
	public:
		StraightEnergyField(Explorer *lpexExp);
											// ������
		void Turn();						// turn
		void Draw();						// draw
};

////////////////////////////////////////////////////////////////////////////////
//
// class ArtileryWeapon
//		ArtileryWeapon �� Ŭ����
//													�ۼ��� : searer
//													Last Update : 2000. 8. 20
//
////////////////////////////////////////////////////////////////////////////////

class ArtileryWeapon : public Weapon {
	protected:
		double dRotateSp;					// ���� ȸ�� �ӵ�
		int nAccuracy;						// ��Ȯ��
		int nFireSp;						// �߻� �ӵ�
		int nEnemyStopTime;					// �� ���� �ð�
		int nDamageTime;					// ������ ���� �ð�
};

class ArtileryCannon : public ArtileryWeapon {
	public:
		ArtileryCannon(Explorer *lpexExp);	// ������
		void Turn();						// turn
		void Draw();						// draw
};

class ShotCannon : public ArtileryWeapon {
	public:
		ShotCannon(Explorer *lpexExp);		// ������
		void Turn();						// turn
		void Draw();						// draw
};

class NetroCannon : public ArtileryWeapon {
	public:
		NetroCannon(Explorer *lpexExp);		// ������
		void Turn();						// turn
		void Draw();						// draw
};

class EnergyCannon : public ArtileryWeapon {
	public:
		EnergyCannon(Explorer *lpexExp);	// ������
		void Turn();						// turn
		void Draw();						// draw
};

////////////////////////////////////////////////////////////////////////////////
//
// class Mine
//		Mine �� Ŭ����
//													�ۼ��� : searer
//													Last Update : 2000. 8. 31
//
////////////////////////////////////////////////////////////////////////////////

class Mine : public Weapon {
	protected:
		int nEnemyStopTime;					// �� ���� �ð�
};

class NormalMine : public Mine {
	public:
		NormalMine(Explorer *lpexExp);		// ������
		void Turn();						// turn
		void Draw();						// draw
};

class NetroMine : public Mine {
	public:
		NetroMine(Explorer *lpexExp);		// ������
		void Turn();						// turn
		void Draw();						// draw
};

class EnergyMine : public Mine {
	public:
		EnergyMine(Explorer *lpexExp);		// ������
		void Turn();						// turn
		void Draw();						// draw
};

////////////////////////////////////////////////////////////////////////////////
//
// class HomingMissile
//		HomingMissile �� Ŭ����
//													�ۼ��� : searer
//													Last Update : 2000. 8. 31
//
////////////////////////////////////////////////////////////////////////////////

class HomingMissile : public Weapon {
	public:
		HomingMissile(Explorer *lpexExp);	// ������
		void Turn();						// turn
		void Draw();						// draw

	protected:
		double dRotateSp;					// ���� ȸ�� �ӵ�
		int nHomingRange;					// ���� �Ÿ�
		int nMisRotSp;						// �̻��� ȸ�� �ӵ�
};

////////////////////////////////////////////////////////////////////////////////
//
// class Nuke
//		Nuke �� Ŭ����
//													�ۼ��� : searer
//													Last Update : 2000. 8. 31
//
////////////////////////////////////////////////////////////////////////////////

class Nuke : public Weapon {
	public:
		Nuke(Explorer *lpexExp);			// ������
		void Turn();						// turn
		void Draw();						// draw

	protected:
		int nFallingTime;					// ���Ͻð�
		int nFireGeo;						// �߻� ����
		int nNowGeo;						// ���� ����
};

#endif	// _WEAPON_H_SEARER_BECD_
