// obfuscator.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "CObfuscator.h"

int main()
{
	CObfuscator obfuscator("input.txt");
	obfuscator.DeleteComments();
	obfuscator.ShowCode();
    return 0;
}

