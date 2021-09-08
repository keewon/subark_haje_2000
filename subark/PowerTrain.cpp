////////////////////////////////////////////////////////////////////////////////
//
// "PowerTrain.cpp"
//	�Ŀ�Ʈ����	
//												�ۼ��� : oedalpha
//												Last Update : 2000. 8. 18.  
//
////////////////////////////////////////////////////////////////////////////////

/// Includes ///////////////////////////////////////////////////////////////////
#include <string.h>
#include "PowerTrain.h"

/// Public macros & Constants //////////////////////////////////////////////////

/// Global variables ///////////////////////////////////////////////////////////

/// Local functinos ////////////////////////////////////////////////////////////

/// Implementations ////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
// Value* PowerTrain::Operation(char *lpszOpName, VoidList *lpvlArgument);
//
// Operation �� �����ϴ� �Լ�. 
//
// ó���ϴ� ���۷��̼� rotate(double, int), stop(), move(double)
// ó�����ϴ� ���۷��̼ǿ����� NULL ó���� ���۷��̼��� VOID �� ����
//
// ��ǥ��� ���� ���� ���� 0,0 ������ �Ʒ��� MAX, MAX
// 
// �ʱ� �Ŀ�Ʈ������ ������ 12�� ����, �����϶�� ��Ű�� y�� ���ҵ� ���̴�
// ������ �ð�������� 360���� ����Ѵ�.
//
// rotate ���� double �� ����, int �� 1:�ð�, -1 : �ݽð��̴�.
//
//												�ۼ��� : oedalpha
//												Last Update : 2000. 8.
////////////////////////////////////////////////////////////////////////////////
Value* PowerTrain::Operation(char *lpszOpName, VoidList *lpvlArgument) {
	if (!strcmp(lpszOpName, "Rotate")) {
		// ���� �и��س���
		double dParam1; int nParam2;
        if (((Value*)lpvlArgument->lpveHead->lpElement)->lpdt->tcType == TC_INT)
            dParam1 = ((IntValue*)lpvlArgument->lpveHead->lpElement)->n;
        else
		    dParam1 = ((RealValue*)lpvlArgument->lpveHead->lpElement)->r;
		nParam2 = ((IntValue*)lpvlArgument->lpveHead->lpveNext->lpElement)->n;

		Rotate(dParam1, nParam2);				 // ����

		// ���ϰ� (VOID) ����� �Ƶ� �����ϱ���
		Value *lpvReturn = new Value();
		lpvReturn->lpdt = new DataType();
		lpvReturn->lpdt->tcType = TC_VOID;
		return lpvReturn;
	}
	else if (!strcmp(lpszOpName, "Stop")) {
		//��� ���ڰ� ���� �ƽ� �ų���
		Stop();

		// ���ϰ� (VOID) ����� �Ƶ� �����ϱ���
		Value *lpvReturn = new Value();
		lpvReturn->lpdt = new DataType();
		lpvReturn->lpdt->tcType = TC_VOID;
		return lpvReturn;
	}
	else if (!strcmp(lpszOpName, "Move")) {

		//���� �и��س���
		double dParam1;
        if (((Value*)lpvlArgument->lpveHead->lpElement)->lpdt->tcType == TC_INT)
            dParam1 = ((IntValue*)lpvlArgument->lpveHead->lpElement)->n;
        else
		    dParam1 = ((RealValue*)lpvlArgument->lpveHead->lpElement)->r;
		Move(dParam1);

		// ���ϰ� (VOID) ����� �Ƶ� �����ϱ���
		Value *lpvReturn = new Value();
		lpvReturn->lpdt = new DataType();
		lpvReturn->lpdt->tcType = TC_VOID;
		return lpvReturn;
	}
	else return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// Value* PowerTrain::Attribute(char *lpszName);
//
// Attribute �� �о���� �Լ�
//												�ۼ��� : oedalpha
//												Last Update : 2000. 8. 13.
////////////////////////////////////////////////////////////////////////////////
Value* PowerTrain::Attribute(char *lpszName) {
	if (!strcmp(lpszName, "speed")) {
		RealValue *lprvReturn = new RealValue();
		lprvReturn->r = dSpeed;
		return lprvReturn;
	}
	else if (!strcmp(lpszName, "rotateSpeed")) {
		RealValue *lprvReturn = new RealValue();
		lprvReturn->r = dRotateSpeed;
		return lprvReturn;
	}
	else if (!strcmp(lpszName, "currentSpeed")) {
		RealValue *lprvReturn = new RealValue();
		lprvReturn->r = dCurrentSpeed;
		return lprvReturn;
	}
	else if (!strcmp(lpszName, "hp")) {
		IntValue *lpivReturn = new IntValue();
		lpivReturn->n = (int)dHP;
		return lpivReturn;
	}
	else if (!strcmp(lpszName, "maxHP")) {
		IntValue *lpivReturn = new IntValue();
		lpivReturn->n = (int)dMaxHP;
		return lpivReturn;
	}
	else if (!strcmp(lpszName, "currentAngle")) {
		RealValue *lprvReturn = new RealValue();
		lprvReturn->r = dCurrentAngle;
		return lprvReturn;
	}
	else if (!strcmp(lpszName, "weight")) {
		RealValue *lprvReturn = new RealValue();
		lprvReturn->r = dWeight;
		return lprvReturn;
	}
	else if (!strcmp(lpszName, "currentWeight")) {
		RealValue *lprvReturn = new RealValue();
		lprvReturn->r = dCurrentWeight;
		return lprvReturn;
	}
	else if (!strcmp(lpszName, "rotateStatus")) {
		IntValue *lpivReturn = new IntValue();
		lpivReturn->n = flagRotateStatus;
		return lpivReturn;
	}
	else if (!strcmp(lpszName, "moveStatus")) {
		IntValue *lpivReturn = new IntValue();
		lpivReturn->n = flagMoveStatus;
		return lpivReturn;
	}
	else if (!strcmp(lpszName, "rotateDirection")) {
		IntValue *lpivReturn = new IntValue();
		lpivReturn->n = flagRotateDirection;
		return lpivReturn;
	}
	else if (!strcmp(lpszName, "moveDirection")) {
		IntValue *lpivReturn = new IntValue();
		lpivReturn->n = flagMoveDirection;
		return lpivReturn;
	}
	else if (!strcmp(lpszName, "rotateAimAngle")) {
		RealValue *lprvReturn = new RealValue();
		lprvReturn->r = dRotateAimAngle;
		return lprvReturn;
	}
	else if (!strcmp(lpszName, "x")) {
		IntValue *lpivReturn = new IntValue();
		int nTempX, nTempY;
		lpExplorer->QueryPosition(&nTempX, &nTempY);
		lpivReturn->n  = nTempX;
		return lpivReturn;
	}
	else if (!strcmp(lpszName, "y")) {
		IntValue *lpivReturn = new IntValue();
		int nTempX, nTempY;
		lpExplorer->QueryPosition(&nTempX, &nTempY);
		lpivReturn->n = nTempY;
		return lpivReturn;
	}
	else if (!strcmp(lpszName, "currentTerrain")) {
		IntValue *lpivReturn = new IntValue();
		int nTempX, nTempY;
		lpExplorer->QueryPosition(&nTempX, &nTempY);
		lpivReturn->n  = lpmapMap->QueryGeometry(nTempX, nTempY);
		return lpivReturn;
	}
	else return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// virtual void PowerTrain::Rotate(double _Angle, int _RotateDirection);
//
// int flagRotateStatus : ���� rotate �ؾ��ϴ��� ����
// double dRotateAimAngle : ��ǥ ����
// int flagRotateDirection : rotate �� ���� �ð������ 1, ���������� -1
//
// Trike �� ���ο� Rotate �� ����� ����.
// Trike �� �������� ������ ȸ������ ���ϱ� �����̴�.
// Dragoon �� ȸ���� ���� �ʱ� ������ ���ο� Rotate �� ���� ����.
//												�ۼ��� : oedalpha
//												Last Update : 2000. 8.
////////////////////////////////////////////////////////////////////////////////
void 
PowerTrain::Rotate(double Angle, int RotateDirection) {
	flagRotateStatus = 1;
	lpExplorer->SetMoveStatus(1);

	//Angle �� ���̳ʽ� ������ �ָ� RotateDirection �� �ٲ��ش�.    
	if (Angle < 0) {
		Angle *= -1;
		RotateDirection *= -1;
	}

	dRotateAimAngle = dCurrentAngle + Angle * (double)RotateDirection;
	while (dRotateAimAngle < 0) {
		dRotateAimAngle += 360;
	}
	while (dRotateAimAngle >= 360) {
		dRotateAimAngle -= 360;
	}
	if (RotateDirection >= 0) {
		flagRotateDirection = 1;
	}
	else {
		flagRotateDirection = -1;
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// void PowerTrain::Stop();
//
// �����̴� ���̾����� flagMoveStatus �� -1(�̲������� ����)�� 
// �ٲ��ش�. �ٸ� ��쿡�� �ƹ��ϵ� ���ص� �ȴ�.
//
// Dragoon �� �ڱ⸸�� Stop �� ����. �ٷ� ���߱� �����̴�
//
//												�ۼ��� : oedalpha
//												Last Update : 2000. 8.
///////////////////////////////////////////////////////////////////////////////
void 
PowerTrain::Stop() {
	if (flagMoveStatus == 1) {
		flagMoveStatus = -1;
		lpExplorer->SetMoveStatus(1);
		dRemainedStopDistance = dStopDistance;
	}
	else {
	}
}


////////////////////////////////////////////////////////////////////////////////
//
// virtual void PowerTrain::Move(double _Direction);
//
// _Direction �� 1 �̸� ���� /  -1 �̸� ����
// �� �÷��׸��� double �� ����� �ߴ�..
// 4������ ���ָ� Move �� ���� ���� ����.
// �ٸ� �Ŀ�Ʈ���ε��� ��  Move �� ����Ѵ�.
//												�ۼ��� : oedalpha
//												Last Update : 2000. 8.
////////////////////////////////////////////////////////////////////////////////
void 
PowerTrain::Move(double Direction) {
	flagMoveStatus = 1;
	lpExplorer->SetMoveStatus(1);
	if (Direction >= 0)
		flagMoveDirection = 1;
	else
		flagMoveDirection = -1;
}

////////////////////////////////////////////////////////////////////////////////
//
//
// Damage �� �ָ�
// ���ϰ��� ���� HP
//												�ۼ��� : oedalpha
//												Last Update : 2000. 8. 18.
///////////////////////////////////////////////////////////////////////////////
double
PowerTrain::Damage(int bulletType, double dDamage) {
	// ������ Bullet �� ������ ������� �ʾҴ�.
	// �����ε� ����� �ʿ�� ���� ���� �𸥴�
	dHP -= dDamage;
	if (dHP <=0 ) {
		dHP = 0;
	}
	else if (dHP >= dMaxHP) {
		dHP = dMaxHP;
	}
	return dHP;
}

////////////////////////////////////////////////////////////////////////////////
//
// dHpPlus ��ŭ �Ƹ� ġ��
// ���ϰ� ���� HP
//												�ۼ��� : oedalpha
//												Last Update : 2000. 8.
////////////////////////////////////////////////////////////////////////////////
double
PowerTrain::Repair(double dHpPlus) {
	dHP += dHpPlus;
	if (dHP >= dMaxHP) dHP = dMaxHP;
	return dHP;
}

////////////////////////////////////////////////////////////////////////////////
//
// void PowerTrain::ReduceCurrentWeight(double);
//
// double ��ŭ CurrentWeight ���ҽ�Ű��
//												�ۼ��� : oedalpha
//												Last Update : 2000. 8.
////////////////////////////////////////////////////////////////////////////////
void
PowerTrain::ReduceCurrentWeight(double d_ReducedWeight) {
	dCurrentWeight -= d_ReducedWeight;
	if (dCurrentWeight <0) {
		dCurrentWeight = 0;
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// bool PowerTrain::IsHpFull()
//
//												�ۼ��� : oedalpha
//												Last Update : 2000. 11.
////////////////////////////////////////////////////////////////////////////////
bool
PowerTrain::IsHpFull() {
	if (dHP == dMaxHP) return true;
	else return false;
}

///////////////////////////////////////////////////////////////////////////////
//
// void PowerTrain::Turn();
//
// PowerTrain �� ��ӹ��� Trike �� Turn
//
// Explorer �� �����ϴ� ���
// void QueryPosition(int *, int *);
// void SetPosition(int, int);		// pixel ����
//
// CMap �� �����ϴ� ���
// int QueryGeometry(&int, &int);	// grid ����
//
// ###### ���� #######
// nCurrentX, nCurrentY, nNextX, nNextY �� �ȼ����� ��ġ�̴�.
// map ��  grid ������ ����ϰ� 
// Explorer �� pixel ������ ����Ѵ�
//												�ۼ��� : oedalpha
////////////////////////////////////////////////////////////////////////////////
void 
PowerTrain::
Turn() {
	int nCurrentX, nCurrentY, nNextX0, nNextY0;
	int nCurrentTerrain;
	int nNextTerrain[8], nNextX[8], nNextY[8];

	// ���� ũ�⸦ ���� ���´�.
	int nMapXsize = TILE_SIZE * lpmapMap->xSize();	// pixel ����
	int nMapYsize = TILE_SIZE * lpmapMap->ySize();

	///////////////////////////////////////////////////////////////
	// ���� ��ġ�� ������ ���Ѵ�.
	lpExplorer->QueryPosition(&nCurrentX, &nCurrentY);
	nCurrentTerrain = 
		lpmapMap->QueryGeometry(nCurrentX/TILE_SIZE, nCurrentY/TILE_SIZE);

	///////////////////////////////////////////////////////////////
	// ���� ���ƺ���. ���ƾ� �Ѵٸ�
	// �� Ʈ����ũ�� ������ ���� ��쿡�� �� �� �ִ�.
	
	if ((flagRotateStatus == 1 && idType != PI_TRIKE) ||
		(flagRotateStatus == 1 && 
		(flagMoveStatus == 1 || flagMoveStatus == -1) && idType == PI_TRIKE)) {

		dCurrentAngle += (dAngularVelocity * (double)flagRotateDirection);

		// 360���� 0���� �����ϱ�
		while (dCurrentAngle >= 360)    dCurrentAngle -= 360;
        while (dCurrentAngle < 0)       dCurrentAngle += 360;

		// ���� ���� ���� �ϱ�
		double dMinAimAngle, dMaxAimAngle;
        dMinAimAngle = dRotateAimAngle - dAngularVelocity;
        dMaxAimAngle = dRotateAimAngle + dAngularVelocity;
        while (dMinAimAngle < 0)        dMinAimAngle += 360;
        while (dMaxAimAngle >= 360)     dMaxAimAngle -= 360;

		// ��ǥġ��ŭ �� ȸ�������� ��ǥġ��� �����ϱ�
		// MinAimAngle�� MaxAimAngle���� ū ��쵵 ����Ͽ��� �Ѵ�.

		if (dMinAimAngle <= dMaxAimAngle) {
			if (dMinAimAngle <= dCurrentAngle && dCurrentAngle < dMaxAimAngle) {
				dCurrentAngle = dRotateAimAngle;
				flagRotateStatus = 0;   // �� ���Ҵ�
			}
		}
		else {
			if ((dMinAimAngle <= dCurrentAngle && dCurrentAngle < 360) ||
				(0 <= dCurrentAngle && dCurrentAngle < dMaxAimAngle) ) {
				dCurrentAngle = dRotateAimAngle;
				flagRotateStatus = 0;   // �� ���Ҵ�
			}
		}
	}

	//////////////////////////////////////////////////////////////
	// ������ ���� �Ѵٸ� ������ ������ (�̲������� �͵� ����) 
	
	if (flagMoveStatus == 1 || flagMoveStatus == -1) { 
		
		// �޸� �ӵ��� ���Ѵ� 
		// ���� ���� �ƴ� ��츦 �����ؾ���
		if (flagRotateStatus == 1) dCurrentSpeed = dRotateSpeed;
		else dCurrentSpeed = dSpeed;
		
		// �극��ũ�� �ɸ� ������ ��� ó��
		//		�극��ũ�� �� ���¿��� �̲����� �Ÿ��� ������ �Ÿ�����
		//		ª���� �� ��ŭ�� �����δ�.
		//		����� �̲������� �ʴ´�. (flagMoveStatus�� -1�� ��찡 ����)
		if (flagMoveStatus == -1 && dCurrentSpeed > dRemainedStopDistance) {
			dCurrentSpeed = dRemainedStopDistance;
		}
		
		// �ӵ��� 0������ ��� ó�� : ���� ����� �Ѵ�.
		if (dCurrentSpeed <= 0) {
			flagMoveStatus = 0;
			flagRotateStatus = 0;
			lpExplorer->SetMoveStatus(0);
			return;
		}

		// NextX�� NextY �� ������ ���Ѵ�.
		nNextX0 = nCurrentX + int((dCurrentSpeed * flagMoveDirection) * 
			sin(dCurrentAngle/360.*2.*PI));
		nNextY0 = nCurrentY - int((dCurrentSpeed * flagMoveDirection) *
			cos(dCurrentAngle/360.*2.*PI));

		// ���� �� ���� ���ݰ� ���� ��� : ���� ����� �Ѵ�.
		if ((nNextX0 == nCurrentX) && (nNextY0 == nCurrentY)) {
			flagMoveStatus = 0;
			flagRotateStatus = 0;
			lpExplorer->SetMoveStatus(0);
			return;
		}

		// �ٸ� �Ŀ�Ʈ���ΰ��� �浹 üũ (2000.11.2.)
		Object **enemyList;
		enemyList= lpmapMap->getObject();

		int nX, nY;
		for (int i=0; i<100; i++) {
			if (enemyList[i] != NULL) {
				enemyList[i]->QueryPosition(&nX, &nY);
				if (((nX != nCurrentX) || (nY != nCurrentY)) &&
					(nNextX0-nX)*(nNextX0-nX) + (nNextY0-nY)*(nNextY0-nY) <= 6400) {
	
					enemyList[i]->Damage((int)(dWeight+dCurrentWeight));
					lpExplorer->Damage((int)(dWeight+dCurrentWeight));
					flagMoveStatus = 0;
					flagRotateStatus = 0;
					lpExplorer->SetMoveStatus(0);
					return;
				}
			}
		}
		

		// NextX�� NextY�� �ֺ��� ���Ѵ�. : 8������ �ϱ�� �ߴ�.
		// �Ŀ�Ʈ������ �߽����� �������� 25 pixel��..
		// ���� �� ���� ���������� ���� �д´�.
		for (int i=0; i <= 7; i++) {
			nNextX[i] = nNextX0 
				+ int(25.* sin(((double)i*45.+dCurrentAngle)/360*2*PI));
			nNextY[i] = nNextY0 
				+ int(25.* sin(((double)i*45.+dCurrentAngle)/360*2*PI));
			nNextTerrain[i] = lpmapMap->QueryGeometry
				(nNextX[i]/TILE_SIZE, nNextY[i]/TILE_SIZE);
		}

		// ���������� ���������� �ٸ� ��츦 üũ�Ѵ�.
		// Hover�� ��� ����
		if (idType != PI_HOVER) {
			for (int i=0; i<=7; i++) {
				if (nNextTerrain[i] != nCurrentTerrain) {
					flagMoveStatus = 0;
					flagRotateStatus = 0;
					lpExplorer->SetMoveStatus(0);
					return;
				}
			}
		}

		// ���� ������ �������� üũ�Ѵ�.
		for (int i=0; i<=7; i++) {
			if ( (nNextX[i] < 0) || (nNextX[i] >= nMapXsize) ||
					(nNextY[i] < 0) || (nNextY[i] >= nMapYsize) ) 
			{
				flagMoveStatus = 0;
				flagRotateStatus = 0;
				lpExplorer->SetMoveStatus(0);
				return;
			}
		}

		// Explorer �� ��������
		lpExplorer->SetPosition(nNextX0, nNextY0);

		//�̲������� ���̾����� ������ ���� �̲����� �Ÿ��� ���δ�.
		if (flagMoveStatus == -1) {
			dRemainedStopDistance -= dCurrentSpeed;
			if (dRemainedStopDistance <= 0) { // �� �̲���������
				flagMoveStatus = 0;
				dRemainedStopDistance = 0;
				lpExplorer->SetMoveStatus(0);
			}
		}
		return;

	} // flagMoveStatus �� 1�̳� -1 �� ��� ��

	// flagMoveStatus �� 0�� ���
	else {
		return;
	}

}