////////////////////////////////////////////////////////////////////////////////
//
// "Bullet.h"
//		źȯ
//												�ۼ��� : searer
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
//		Bullet �� Ŭ����
//												�ۼ��� : searer
//												Last Update : 2000. 8. 15
//
////////////////////////////////////////////////////////////////////////////////

class Bullet : public Object {
	public:
		~Bullet();							// �Ҹ���

		virtual void Turn() = 0;			// turn
		virtual void Draw() = 0;			// draw
		virtual void Damage(int) = 0;

	protected:
		double dFireDirection;				// �߻� ����
		int nBulletX, nBulletY;				// źȯ ��ġ
		int nDamage;						// ������ ũ��
		int nSplash;						// ���÷��� �������� ����
		int nDetectRange;					// źȯ ũ��
};

////////////////////////////////////////////////////////////////////////////////
//
// class StraightBullet
//		StraightBullet �� Ŭ����
//												�ۼ��� : searer
//												Last Update : 2000. 8. 23
//
////////////////////////////////////////////////////////////////////////////////

class StraightBullet : public Bullet {
	public:
		StraightBullet(double dFD, int nX, int nY, int nDmg, int nSplsh,
			int nDRange, bool bGeoE, bool bAPass, int nFlyD,
			int nFSp, int nAcc, int nEStop, int nFGeo);
											// ������
		void Turn();						// turn
		void Draw();						// draw
		void Damage(int);

	protected:
		bool bGeoEnable;					// ���� ���� ����
		bool bArmorPass;					// �尩 ���� ����
		bool bBang;							// ���� ����
		int nFlyDistance;					// ���ư� �Ÿ�
		int nFireSp;						// �߻� �ӵ�
		int nAccuracy;						// ��Ȯ��
		int nEnemyStopTime;					// �� ���� �ð�
		int nFireGeo;						// �߻�����
		int nCurrentGeo;					// ���� ����
		int nBangNumber;					// ���� �� ��������Ʈ ��ȣ
};

////////////////////////////////////////////////////////////////////////////////
//
// class ArtileryBullet
//		ArtileryBullet �� Ŭ����
//												�ۼ��� : searer
//												Last Update : 2000. 8. 23
//
////////////////////////////////////////////////////////////////////////////////

class ArtileryBullet : public Bullet {
	public:
		ArtileryBullet(double dFD, int nX, int nY, int nDmg, int nSplsh,
			int nDRange, bool bGeoE, int nFlyD,	int nFSp,
			int nAcc, int nEStop, int nDTime);
											// ������
		void Turn();						// turn
		void Draw();						// draw
		void Damage(int);

	protected:
		bool bGeoEnable;					// ���� ���� ����
		bool bBang;							// ���� ����
		int nFlyDistance;					// ���ư� �Ÿ�
		int nFireSp;						// �߻� �ӵ�
		int nAccuracy;						// ��Ȯ��
		int nEnemyStopTime;					// �� ���� �ð�
		int nDamageTime;					// ������ ���� �ð�
		int nBangNumber;					// ���� �� ��������Ʈ ��ȣ
};

////////////////////////////////////////////////////////////////////////////////
//
// class MineBullet
//		MineBullet �� Ŭ����
//												�ۼ��� : searer
//												Last Update : 2000. 8. 23
//
////////////////////////////////////////////////////////////////////////////////

class MineBullet : public Bullet {
	public:
		MineBullet(int nX, int nY, int nDmg, int nSplsh, int nDRange,
			int nEStop);					// ������
		void Turn();						// turn
		void Draw();						// draw
		void Damage(int);

	protected:
		bool bBang;							// ���� ����
		int nEnemyStopTime;					// �� ���� �ð�
		int nDamageTime;					// ������ ���� �ð�
};

////////////////////////////////////////////////////////////////////////////////
//
// class HomingBullet
//		HomingBullet �� Ŭ����
//												�ۼ��� : searer
//												Last Update : 2000. 8. 23
//
////////////////////////////////////////////////////////////////////////////////

class HomingBullet : public Bullet {
	public:
		void Turn();						// turn
		void Draw();						// draw
		void Damage(int);

	protected:
		bool bGeoEnable;					// ���� ���� ����
		bool bHoming;						// ���� flag
		bool bBang;							// ���� ����
		double dAimAngle;					// ��ǥ ����
		double dRotatingSp;					// �̻��� ȸ�� �ӵ�
		int nFlyDistance;					// ���ư� �Ÿ�
		int nFireSp;						// �߻� �ӵ�
		int nAccuracy;						// ��Ȯ��
		int nHomingRange;					// ������ ������ �Ÿ�
		int nFireGeo;						// �߻�����
		int nCurrentGeo;					// ���� ����
};

////////////////////////////////////////////////////////////////////////////////
//
// class NukeBullet
//		NukeBullet �� Ŭ����
//												�ۼ��� : searer
//												Last Update : 2000. 8. 23
//
////////////////////////////////////////////////////////////////////////////////

class NukeBullet : public Bullet {
	public:
		NukeBullet(int nX, int nY, int nDmg, int nSplsh);
											// ������
		void Turn();						// turn
		void Draw();						// draw
		void Damage(int);

	protected:
		bool bFalling;						// ���� flag
		int nAccuracy;						// ��Ȯ��
		int nRemainTime;					// ���� ���� �ð�
};

#endif	// _BULLET_H_SEARER_BECD_
