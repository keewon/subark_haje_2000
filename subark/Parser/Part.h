////////////////////////////////////////////////////////////////////////////////
//
// "Part.h"
//		Part의 슈퍼클래스 선언
//												작성자 : asura
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
//		Part의 슈퍼 클래스
//												작성자 : asura
//												Last Update : 2000. 7. 18.
//
////////////////////////////////////////////////////////////////////////////////

class Part : public Object {
	public:
		virtual Value *Operation(char *lpszOp, VoidList *lpveArgs) = 0;
			// Operations을 실행
		virtual Value *Attribute(char *lpszAttr) = 0;
			// Attribute의 값을 읽어옴
		virtual void Turn(void) = 0;
			// Part가 각 턴에 해야 할 일
		~Part();							// 소멸자

	protected:
		int nPartId;							// 파트
		int nPartTypeId;						// 파트 종류
		int nWeight;							// 무게
};

#endif // _PART_H_ASURA_BECD_
