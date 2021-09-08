////////////////////////////////////////////////////////////////////////////////
//
// "Sensor.cpp"
//		Sensor
//													�ۼ��� : searer
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
//		class Sensor �� �Ҹ���
//													�ۼ��� : searer
//													Last Update : 2000. 8. 4
//
////////////////////////////////////////////////////////////////////////////////

Sensor::~Sensor() {
}

////////////////////////////////////////////////////////////////////////////////
//
// Value* Sensor::Operation(char *lpszOpName, VoidList *lpvlArgument);
//		Operation �� �����ϴ� �Լ�
//		IN:
//			lpszOpName - Operation �̸�
//			lpvlArgument - �Ķ���� ����Ʈ
//		RETURN:
//			NULL
//													�ۼ��� : searer
//													Last Update : 2000. 8. 4
//
////////////////////////////////////////////////////////////////////////////////

Value* Sensor::Operation(char *lpszOpName, VoidList *lpvlArgument) {
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// Value* Sensor::Attribute(char *lpszName);
//		Attribute �� �о���� �Լ�
//		IN:
//			lpszName - Attribute �̸�
//		RETURN:
//			"nMapData" �� �ʿ� ���� ����
//			"nEnemy" �� ��, ����, ������ ���� ����
//			�ƴϸ� NULL
//													�ۼ��� : searer
//													Last Update : 2000. 8. 4
//
////////////////////////////////////////////////////////////////////////////////

Value* Sensor::Attribute(char *lpszName) {
	// nMapData
	if (!strcmp(lpszName, "nMapData")) {
		// 2�� �迭 Ÿ�� ����
		ArrayType *lpatAt1 = new ArrayType;
		ArrayType *lpatAt2 = new ArrayType;
		DataType *lpdtDt = new DataType;
		lpdtDt->tcType = TC_INT;
		lpatAt1->nLength = lpmapMap->xSize();
		lpatAt2->nLength = lpmapMap->ySize();
		lpatAt1->lpdtElementType = lpatAt2;
		lpatAt2->lpdtElementType = lpdtDt;

		// ArrayValue ����
		ArrayValue *lpavAv = new ArrayValue(lpatAt1);

		// ArrayValue �� ���� ���� �� assign
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
		// �迭 Ÿ�� ����
		ArrayType *lpatAt = new ArrayType;
		DataType *lpdtDt = new ObjectType;
		lpdtDt->tcType = TC_OBJECT;
		lpatAt->nLength = nEnemy;
		lpatAt->lpdtElementType = lpdtDt;

		// ArrayValue ����
		ArrayValue *lpavAv = new ArrayValue(lpatAt);

		// ArrayValue �� ���̵� �� ���� �� assign
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
