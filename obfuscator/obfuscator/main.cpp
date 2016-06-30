// obfuscator.cpp: определяет точку входа для консольного приложения.
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

