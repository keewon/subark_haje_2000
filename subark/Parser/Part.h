////////////////////////////////////////////////////////////////////////////////
//
// "Part.h"
//		Part�� ����Ŭ���� ����
//												�ۼ��� : asura
//												Last Update : 2000. 7. 27.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _PART_H_ASURA_BECD_
#define _PART_H_ASURA_BECD_

/// Includes ///////////////////////////////////////////////////////////////////

#include "Object.h"
#include "Types.h"
#include "Value.h"

/// Public macros & Constants //////////////////////////////////////////////////

/// Class or functions /////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class Part
//		Part�� ���� Ŭ����
//												�ۼ��� : asura
//												Last Update : 2000. 7. 18.
//
////////////////////////////////////////////////////////////////////////////////

class Part : public Object {
	public:
		virtual Value *Operation(char *lpszOp, VoidList *lpveArgs) = 0;
			// Operations�� ����
		virtual Value *Attribute(char *lpszAttr) = 0;
			// Attribute�� ���� �о��
		virtual void Turn(void) = 0;
			// Part�� �� �Ͽ� �ؾ� �� ��
		~Part();							// �Ҹ���

	protected:
		int nPartId;							// ��Ʈ
		int nPartTypeId;						// ��Ʈ ����
		int nWeight;							// ����
};

#endif // _PART_H_ASURA_BECD_
