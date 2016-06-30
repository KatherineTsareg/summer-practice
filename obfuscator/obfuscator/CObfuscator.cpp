#include "stdafx.h"
#include "CObfuscator.h"

using namespace std;

void CObfuscator::ReadInputData(std::string const & fileName)
{
	ifstream fin(fileName);
	if (fin.is_open())
	{
		string newStr;
		while (getline(fin, newStr))
		{
			m_inputText.push_back(newStr);
		}
	}
	else
	{
		throw invalid_argument("Invalid file name");
	}
}

CObfuscator::CObfuscator(std::string const & fileName)
{
	ReadInputData(fileName);
}

void CObfuscator::Start()
{
	CDelete deleted(m_inputText);
	deleted.CodeChange();
	m_code = deleted.GetResult();

	CVariables variables(m_code);
	variables.Renaming();
}

void CObfuscator::ShowCode() const
{
	for (auto str : m_code)
	{
		cout << str << endl;
	}
}

