#include "stdafx.h"
#include "CVariables.h"

using namespace std;


CVariables::CVariables(std::vector<std::string> const& inputVector)
	:m_code(inputVector)
{
}

void CVariables::Renaming()
{
	srand(time(NULL));
	FindAllVarNames();
	ReplacementNames();
}

char CVariables::GetRandomSymbol() const
{
	int	ascii = rand() % 75 + 48;
	while ((ascii >= 58 && ascii <= 64) || (ascii >= 91 && ascii <= 96))
	{
		ascii = rand() % 75 + 48;
	}
	return (char)ascii;
}

std::string CVariables::GetNewVariableName()
{
	string newName, letter;
	char symb;
	newName.reserve(LENGTH_VARIABLE_NAME);
	
	for (size_t i = 0; i < LENGTH_VARIABLE_NAME; )
	{
		stringstream ss;
		symb = GetRandomSymbol();
		if (!((int)symb >= 48 && (int)symb <= 57 && newName.length() == 0))
		{
			ss << symb;
			ss >> letter;
			newName.append(letter);
			++i;
		}
	}
	if (find(begin(m_newNames), end(m_newNames), newName) != end(m_newNames))
	{
		m_newNames.push_back(newName);
		return newName;
	}
	throw invalid_argument("Name can not exist");
}

void CVariables::FindAllVarNames()
{
	for (auto str : m_code)
	{
		size_t varPos = str.find("VAR");
		size_t beginPos = str.find("BEGIN");
		if (varPos >= 0 && varPos < str.length() && m_varState == STATE::NOTHING)
		{
			m_varState = STATE::VARIABLES;
			//найти все переменные послк слова VAR
		}
		else if (m_varState == STATE::VARIABLES && (beginPos < 0 || beginPos >= str.length()))
		{
			//найти все переменные
		}
		else if (m_varState == STATE::VARIABLES && (beginPos >= 0 || beginPos < str.length()))
		{
			//найти все переменные перед словом BEGIN
			m_varState == STATE::NOTHING;
		}
	}
}

void CVariables::ReplacementNames()
{
}



