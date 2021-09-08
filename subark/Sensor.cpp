////////////////////////////////////////////////////////////////////////////////
//
// "Sensor.cpp"
//		Sensor
//													작성자 : searer
//													Last Update : 2000. 8. 4
//
////////////////////////////////////////////////////////////////////////////////

/// Includes ///////////////////////////////////////////////////////////////////

#include "Sensor.h"
#include "Map.h"

/// Public macros & Constants //////////////////////////////////////////////////

/// Implementations ////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Sensor::~Sensor();
//		class Sensor 의 소멸자
//													작성자 : searer
//													Last Update : 2000. 8. 4
//
////////////////////////////////////////////////////////////////////////////////

Sensor::~Sensor() {
}

////////////////////////////////////////////////////////////////////////////////
//
// Value* Sensor::Operation(char *lpszOpName, VoidList *lpvlArgument);
//		Operation 을 실행하는 함수
//		IN:
//			lpszOpName - Operation 이름
//			lpvlArgument - 파라미터 리스트
//		RETURN:
//			NULL
//													작성자 : searer
//													Last Update : 2000. 8. 4
//
////////////////////////////////////////////////////////////////////////////////

Value* Sensor::Operation(char *lpszOpName, VoidList *lpvlArgument) {
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// Value* Sensor::Attribute(char *lpszName);
//		Attribute 를 읽어오는 함수
//		IN:
//			lpszName - Attribute 이름
//		RETURN:
//			"nMapData" 면 맵에 대한 정보
//			"nEnemy" 면 적, 지뢰, 센서에 대한 정보
//			아니면 NULL
//													작성자 : searer
//													Last Update : 2000. 8. 4
//
////////////////////////////////////////////////////////////////////////////////

Value* Sensor::Attribute(char *lpszName) {
	// nMapData
	if (!strcmp(lpszName, "nMapData")) {
		// 2중 배열 타입 설정
		ArrayType *lpatAt1 = new ArrayType;
		ArrayType *lpatAt2 = new ArrayType;
		DataType *lpdtDt = new DataType;
		lpdtDt->tcType = TC_INT;
		lpatAt1->nLength = lpmapMap->xSize();
		lpatAt2->nLength = lpmapMap->ySize();
		lpatAt1->lpdtElementType = lpatAt2;
		lpatAt2->lpdtElementType = lpdtDt;

		// ArrayValue 생성
		ArrayValue *lpavAv = new ArrayValue(lpatAt1);

		// ArrayValue 에 지형 정보 값 assign
		int i, j;
		int nTab;

		for (i=0; i<lpmapMap->xSize(); i++) {
			for (j=0; j<lpmapMap->ySize(); j++) {
				nTab = sizeof(int)*(i*(lpmapMap->xSize()) + j);
				*((int*)lpavAv->value + nTab) = nMapData[i][j];
			}
		}

		return lpavAv;
	}
	// detectedEnemy
	else if (!strcmp(lpszName, "detectedEnemy")) {
		// 배열 타입 설정
		ArrayType *lpatAt = new ArrayType;
		DataType *lpdtDt = new ObjectType;
		lpdtDt->tcType = TC_OBJECT;
		lpatAt->nLength = nEnemy;
		lpatAt->lpdtElementType = lpdtDt;

		// ArrayValue 생성
		ArrayValue *lpavAv = new ArrayValue(lpatAt);

		// ArrayValue 에 센싱된 적 정보 값 assign
		int i;
		int nTab;

		for (i=0; i<nEnemy; i++) {
			nTab = i*sizeof(Object);
			*((Object*)lpavAv->value + nTab) = *detectedEnemy[i];
		}

		return lpavAv;
	}
	else
		return NULL;
}
