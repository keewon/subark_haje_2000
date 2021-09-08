////////////////////////////////////////////////////////////////////////////////
//
// "DataType.h"
//		Jacqueline���� ����ϴ� �������� ������ ����
//												�ۼ��� : asura
//												Last Update : 2000. 8. 20.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _DATATYPE_H_ASURA_BECD_
#define _DATATYPE_H_ASURA_BECD_

/// Includes ///////////////////////////////////////////////////////////////////

/// Public macros & Constants //////////////////////////////////////////////////

#ifndef NULL
#define NULL (0)
#endif

/// Class or functions /////////////////////////////////////////////////////////

typedef enum { 
	TC_VOID, TC_INT, TC_REAL, TC_BOOL, TC_ARRAY, TC_OBJECT 
} TypeCode;
	// Type = VOID | INT | REAL | BOOL | ARRAY of Type | OBJECT

////////////////////////////////////////////////////////////////////////////////
//
// class DataType
//		Jacqueline���� ���Ǵ� ������ ������ ��Ÿ���� Ŭ����. ArrayType�� 
//		ObjectType�� �θ� Ŭ������ ��κ��� ��쿡 ������ ������ DataType *�� ��
//		������ ���Ǹ�, �Ҹ��ڿ��� ������ArrayType���� ObjectType���� �Ǵ��Ͽ� 
//		��� ������ delete �� �ش�.
//												�ۼ��� : asura
//												Last Update : 2000. 7. 18.
//
////////////////////////////////////////////////////////////////////////////////

class DataType {
	public:
		~DataType();								// �Ҹ���

		TypeCode tcType;							// ������ Ÿ�� ����
		bool operator==(const DataType &dt);		// == operator
};

////////////////////////////////////////////////////////////////////////////////
//
// class ArrayType
//		ARRAY of Type�� ��Ÿ���� Ŭ����
//												�ۼ��� : asura
//												Last Update : 2000. 7. 18.
//
////////////////////////////////////////////////////////////////////////////////

class ArrayType : public DataType {
	public:
		int GetElementSize(void);					// ���� �ϳ��� ũ�⸦ ���
		ArrayType *CopyType(void);

		int nLength;								// �迭�� ũ��
		DataType *lpdtElementType;					// ������ ��������
};

////////////////////////////////////////////////////////////////////////////////
//
// class ObjectType
//		������ �� Part���� ��Ÿ���� Ŭ����
//												�ۼ��� : asura
//												Last Update : 2000. 7. 18.
//
////////////////////////////////////////////////////////////////////////////////

class ObjectType : public DataType {
	public:
		ObjectType(char *lpszType = NULL);			// ������
	
		char *lpszObject;							// Part ID
};

#endif // _DATATYPE_H_ASURA_BECD_
