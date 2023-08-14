#include "Error.h"

namespace Error
{
	ER error[ERROR_MAX_ENTRY] =	// ������� ������
	{
		ERROR_ENTRY(0, "������������ ��� ������\n"),
		ERROR_ENTRY(1, "��������� ����\n"),
		ERROR_ENTRY(2, "�������� ������ �����\n"),  
		ERROR_ENTRY(3, "��������� ��� �� ������������ ��������\n"),
		ERROR_ENTRY(4, "��� ������� ��������� ����� ��, ��� � � ������� ���������\n"),
		ERROR_ENTRY(5, "������������ ������ ���������\n"),
		ERROR_ENTRY(6, "������� ����������� � ���������\n"),
		ERROR_ENTRY(7, "������������ ����\n"),
		ERROR_ENTRY(8, "������ ����� ���\n"),
		ERROR_ENTRY(9, "����� �������� �� ����������\n"),
		ERROR_ENTRY(10, "������� Boolean �� ������ ��������� ��� ���������\n"),
	};

	ER geterror(int id){
		ER e;								// ��������� ���������� � ��������� ERROR
		if (id < 0 || id > ERROR_MAX_ENTRY)		// ��������� ��������
			e = error[0];						// ���� ������ ������� �� ��������
		else
			e = error[id];	// ���� ������ � ��������
		return e;
	}

	ER geterrorin(int id, int line = -1, int col = -1){
		ER e;								// ��������� ���������� � ��������� ERROR
		if (id < 0 || id > ERROR_MAX_ENTRY)		// ����� ��������� ��������
			e = error[0];						// �� ������
		else									// ������
		{
			e = error[id];						// ���������� ������
			e.inext.line = line;				// ���������� ������
			e.inext.col = col;					// ���������� �������
		}
		return e;
	}

};
