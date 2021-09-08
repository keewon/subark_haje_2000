////////////////////////////////////////////////////////////////////////////////
//
// "PowerTrain.cpp"
//	파워트레인	
//												작성자 : oedalpha
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
// Operation 을 실행하는 함수. 
//
// 처리하는 오퍼레이션 rotate(double, int), stop(), move(double)
// 처리못하는 오퍼레이션에서는 NULL 처리한 오퍼레이션은 VOID 를 리턴
//
// 좌표계는 맵의 왼쪽 위가 0,0 오른쪽 아래가 MAX, MAX
// 
// 초기 파워트레인의 방향은 12시 방향, 전진하라고 시키면 y가 감소될 것이다
// 각도는 시계방향으로 360도를 사용한다.
//
// rotate 에서 double 은 각도, int 는 1:시계, -1 : 반시계이다.
//
//												작성자 : oedalpha
//												Last Update : 2000. 8.
////////////////////////////////////////////////////////////////////////////////
Value* PowerTrain::Operation(char *lpszOpName, VoidList *lpvlArgument) {
	if (!strcmp(lpszOpName, "Rotate")) {
		// 인자 분리해내기
		double dParam1; int nParam2;
        if (((Value*)lpvlArgument->lpveHead->lpElement)->lpdt->tcType == TC_INT)
            dParam1 = ((IntValue*)lpvlArgument->lpveHead->lpElement)->n;
        else
		    dParam1 = ((RealValue*)lpvlArgument->lpveHead->lpElement)->r;
		nParam2 = ((IntValue*)lpvlArgument->lpveHead->lpveNext->lpElement)->n;

		Rotate(dParam1, nParam2);				 // 실행

		// 리턴값 (VOID) 만들기 아따 복잡하구만
		Value *lpvReturn = new Value();
		lpvReturn->lpdt = new DataType();
		lpvReturn->lpdt->tcType = TC_VOID;
		return lpvReturn;
	}
	else if (!strcmp(lpszOpName, "Stop")) {
		//얘는 인자가 없다 아싸 신난다
		Stop();

		// 리턴값 (VOID) 만들기 아따 복잡하구만
		Value *lpvReturn = new Value();
		lpvReturn->lpdt = new DataType();
		lpvReturn->lpdt->tcType = TC_VOID;
		return lpvReturn;
	}
	else if (!strcmp(lpszOpName, "Move")) {

		//인자 분리해내기
		double dParam1;
        if (((Value*)lpvlArgument->lpveHead->lpElement)->lpdt->tcType == TC_INT)
            dParam1 = ((IntValue*)lpvlArgument->lpveHead->lpElement)->n;
        else
		    dParam1 = ((RealValue*)lpvlArgument->lpveHead->lpElement)->r;
		Move(dParam1);

		// 리턴값 (VOID) 만들기 아따 복잡하구만
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
// Attribute 를 읽어오는 함수
//												작성자 : oedalpha
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
// int flagRotateStatus : 현재 rotate 해야하는지 여부
// double dRotateAimAngle : 목표 각도
// int flagRotateDirection : rotate 할 방향 시계방향은 1, 고도리방향은 -1
//
// Trike 만 새로운 Rotate 를 만들어 쓴다.
// Trike 는 움직이지 않으면 회전하지 못하기 떄문이다.
// Dragoon 은 회전을 하지 않기 때문에 새로운 Rotate 를 만들어서 쓴다.
//												작성자 : oedalpha
//												Last Update : 2000. 8.
////////////////////////////////////////////////////////////////////////////////
void 
PowerTrain::Rotate(double Angle, int RotateDirection) {
	flagRotateStatus = 1;
	lpExplorer->SetMoveStatus(1);

	//Angle 을 마이너스 값으로 주면 RotateDirection 을 바꿔준다.    
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
// 움직이는 중이었으면 flagMoveStatus 를 -1(미끄러지는 상태)로 
// 바꿔준다. 다른 경우에는 아무일도 안해도 된다.
//
// Dragoon 은 자기만의 Stop 을 쓴다. 바로 멈추기 때문이다
//
//												작성자 : oedalpha
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
// _Direction 이 1 이면 전진 /  -1 이면 후진
// 이 플래그만은 double 을 쓰기로 했다..
// 4족보행 유닛만 Move 를 새로 만들어서 쓴다.
// 다른 파워트레인들은 이  Move 를 사용한다.
//												작성자 : oedalpha
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
// Damage 를 주면
// 리턴값은 현재 HP
//												작성자 : oedalpha
//												Last Update : 2000. 8. 18.
///////////////////////////////////////////////////////////////////////////////
double
PowerTrain::Damage(int bulletType, double dDamage) {
	// 아직은 Bullet 의 성질을 고려하지 않았다.
	// 앞으로도 고려할 필요는 없을 지도 모른다
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
// dHpPlus 만큼 아머 치료
// 리턴값 현재 HP
//												작성자 : oedalpha
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
// double 만큼 CurrentWeight 감소시키기
//												작성자 : oedalpha
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
//												작성자 : oedalpha
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
// PowerTrain 을 상속받은 Trike 의 Turn
//
// Explorer 에 접근하는 방법
// void QueryPosition(int *, int *);
// void SetPosition(int, int);		// pixel 단위
//
// CMap 에 접근하는 방법
// int QueryGeometry(&int, &int);	// grid 단위
//
// ###### 주의 #######
// nCurrentX, nCurrentY, nNextX, nNextY 는 픽셀단위 수치이다.
// map 은  grid 단위를 사용하고 
// Explorer 는 pixel 단위를 사용한다
//												작성자 : oedalpha
////////////////////////////////////////////////////////////////////////////////
void 
PowerTrain::
Turn() {
	int nCurrentX, nCurrentY, nNextX0, nNextY0;
	int nCurrentTerrain;
	int nNextTerrain[8], nNextX[8], nNextY[8];

	// 지도 크기를 구해 놓는다.
	int nMapXsize = TILE_SIZE * lpmapMap->xSize();	// pixel 단위
	int nMapYsize = TILE_SIZE * lpmapMap->ySize();

	///////////////////////////////////////////////////////////////
	// 현재 위치와 지형을 구한다.
	lpExplorer->QueryPosition(&nCurrentX, &nCurrentY);
	nCurrentTerrain = 
		lpmapMap->QueryGeometry(nCurrentX/TILE_SIZE, nCurrentY/TILE_SIZE);

	///////////////////////////////////////////////////////////////
	// 먼저 돌아보자. 돌아야 한다면
	// 단 트라이크는 앞으로 가는 경우에만 돌 수 있다.
	
	if ((flagRotateStatus == 1 && idType != PI_TRIKE) ||
		(flagRotateStatus == 1 && 
		(flagMoveStatus == 1 || flagMoveStatus == -1) && idType == PI_TRIKE)) {

		dCurrentAngle += (dAngularVelocity * (double)flagRotateDirection);

		// 360도를 0도로 보정하기
		while (dCurrentAngle >= 360)    dCurrentAngle -= 360;
        while (dCurrentAngle < 0)       dCurrentAngle += 360;

		// 오차 없이 돌게 하기
		double dMinAimAngle, dMaxAimAngle;
        dMinAimAngle = dRotateAimAngle - dAngularVelocity;
        dMaxAimAngle = dRotateAimAngle + dAngularVelocity;
        while (dMinAimAngle < 0)        dMinAimAngle += 360;
        while (dMaxAimAngle >= 360)     dMaxAimAngle -= 360;

		// 목표치만큼 다 회전했으면 목표치대로 조정하기
		// MinAimAngle이 MaxAimAngle보다 큰 경우도 고려하여야 한다.

		if (dMinAimAngle <= dMaxAimAngle) {
			if (dMinAimAngle <= dCurrentAngle && dCurrentAngle < dMaxAimAngle) {
				dCurrentAngle = dRotateAimAngle;
				flagRotateStatus = 0;   // 다 돌았다
			}
		}
		else {
			if ((dMinAimAngle <= dCurrentAngle && dCurrentAngle < 360) ||
				(0 <= dCurrentAngle && dCurrentAngle < dMaxAimAngle) ) {
				dCurrentAngle = dRotateAimAngle;
				flagRotateStatus = 0;   // 다 돌았다
			}
		}
	}

	//////////////////////////////////////////////////////////////
	// 앞으로 가야 한다면 앞으로 앞으로 (미끄러지는 것도 가능) 
	
	if (flagMoveStatus == 1 || flagMoveStatus == -1) { 
		
		// 달릴 속도를 정한다 
		// 도는 경우와 아닌 경우를 구분해야죠
		if (flagRotateStatus == 1) dCurrentSpeed = dRotateSpeed;
		else dCurrentSpeed = dSpeed;
		
		// 브레이크가 걸린 상태의 경우 처리
		//		브레이크를 건 상태에서 미끄러질 거리가 움직일 거리보다
		//		짧으면 그 만큼만 움직인다.
		//		드라군은 미끄러지지 않는다. (flagMoveStatus가 -1일 경우가 없다)
		if (flagMoveStatus == -1 && dCurrentSpeed > dRemainedStopDistance) {
			dCurrentSpeed = dRemainedStopDistance;
		}
		
		// 속도가 0이하인 경우 처리 : 당장 멈춰야 한다.
		if (dCurrentSpeed <= 0) {
			flagMoveStatus = 0;
			flagRotateStatus = 0;
			lpExplorer->SetMoveStatus(0);
			return;
		}

		// NextX와 NextY 의 원점을 구한다.
		nNextX0 = nCurrentX + int((dCurrentSpeed * flagMoveDirection) * 
			sin(dCurrentAngle/360.*2.*PI));
		nNextY0 = nCurrentY - int((dCurrentSpeed * flagMoveDirection) *
			cos(dCurrentAngle/360.*2.*PI));

		// 다음 갈 곳이 지금과 같은 경우 : 당장 멈춰야 한다.
		if ((nNextX0 == nCurrentX) && (nNextY0 == nCurrentY)) {
			flagMoveStatus = 0;
			flagRotateStatus = 0;
			lpExplorer->SetMoveStatus(0);
			return;
		}

		// 다른 파워트레인과의 충돌 체크 (2000.11.2.)
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
		

		// NextX와 NextY의 주변을 구한다. : 8개씩만 하기로 했다.
		// 파워트레인을 중심으로 반지름은 25 pixel로..
		// 다음 갈 곳의 지형정보도 같이 읽는다.
		for (int i=0; i <= 7; i++) {
			nNextX[i] = nNextX0 
				+ int(25.* sin(((double)i*45.+dCurrentAngle)/360*2*PI));
			nNextY[i] = nNextY0 
				+ int(25.* sin(((double)i*45.+dCurrentAngle)/360*2*PI));
			nNextTerrain[i] = lpmapMap->QueryGeometry
				(nNextX[i]/TILE_SIZE, nNextY[i]/TILE_SIZE);
		}

		// 현재지형과 다음지형이 다른 경우를 체크한다.
		// Hover의 경우 제외
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

		// 지도 밖으로 못나가게 체크한다.
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

		// Explorer 를 움직이자
		lpExplorer->SetPosition(nNextX0, nNextY0);

		//미끄러지는 중이었으면 앞으로 남은 미끄러질 거리를 줄인다.
		if (flagMoveStatus == -1) {
			dRemainedStopDistance -= dCurrentSpeed;
			if (dRemainedStopDistance <= 0) { // 다 미끄러졌으면
				flagMoveStatus = 0;
				dRemainedStopDistance = 0;
				lpExplorer->SetMoveStatus(0);
			}
		}
		return;

	} // flagMoveStatus 가 1이나 -1 인 경우 끝

	// flagMoveStatus 가 0인 경우
	else {
		return;
	}

}