// obfuscator.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "CObfuscator.h"

int main()
{
	CObfuscator obfuscator("input.txt");
	obfuscator.Start();
	//obfuscator.ShowCode();
    return 0;
}

