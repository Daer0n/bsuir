#pragma once

#define ERROR_THROW(id) Error::geterror(id);				 		// throw ERRPR_THROW(id)
#define ERROR_THROW_IN(id, l, c) Error::geterrorin(id, l, c);		// throw ERRPR_THROW_IN(id, ������, �������)
#define ERROR_ENTRY(id, m) {id, m, {-1,-1}}							// ������� ������� ������
#define ERROR_MAXSIZE_MESSAGE 200									// ������������ ����� ��������� �� ������
#define ERROR_ENTRY_NODEF(id)		ERROR_ENTRY(-id, "������������ ������")	// 1 �������������� ������� ������� ������

#define ERROR_MAX_ENTRY 1000	// ���������� ��������� � ������� ������

namespace Error
{
	struct ER	// ��� ���������� ��� throw ERROR_THROW | ERROR_THROW_IN � catch(ERROR)
	{
		int id;									// ��� ������
		char message[ERROR_MAXSIZE_MESSAGE];	// ��������� �� ������
		struct IN								// ���������� ��� ������ ��� ��������� ������� ������
		{
			short line;							// ����� ������ (0, 1, 2, ...)
			short col;							// ����� ������� � ������ (0, 1, 2, ...)
		} inext;
	};

	ER geterror(int id);							// ������������ ERROR ��� ERROR_THROW
	ER geterrorin(int id, int line, int col);	// ������������ ERROR ��� ERROR_THROW_IN
}