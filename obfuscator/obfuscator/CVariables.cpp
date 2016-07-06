#include "stdafx.h"
#include "CVariables.h"

using namespace std;

const vector<string> delimeters = {",", ":", ";", "-", "+",  "*",  "/", "=",  "(", ")", "[", "]" };

std::vector<std::pair<std::string, std::string>>::iterator FindVal(std::string & val, std::vector<std::pair<std::string, std::string>> & vec)
{
	for (std::vector<std::pair<std::string, std::string>>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		if ((*it).first == val)
		{
			return it;
		}
	}
	return vec.end();
}

CVariables::CVariables(std::vector<std::string> const& inputVector)
	:m_code(inputVector)
{
}

void CVariables::Renaming()
{
	srand(time(NULL));

	ReplacementNames();
}

std::vector<std::string> CVariables::GetResult() const
{
	return m_code;
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
	if (find(begin(m_newNames), end(m_newNames), newName) == end(m_newNames) && newName.length() == LENGTH_VARIABLE_NAME)
	{
		m_newNames.push_back(newName);
		return newName;
	}
	return "";
}

void CVariables::AddNewNameToOldName(std::string & var)
{
	string newName = GetNewVariableName();
	while (newName == "" && newName.length() != LENGTH_VARIABLE_NAME)
	{
		newName = GetNewVariableName();
	}
	if (FindVal(var, m_variablesMap) == m_variablesMap.end())
	{
		m_variablesMap.push_back({ var, newName });
	}
}

void CVariables::FindAndcreateVariablesNames(std::string const& str)
{
	stringstream ss;
	ss << str;
	string var;
	while (ss >> var)
	{
		if (var != "," && var != ":" && var != ";" && var != "VAR" && m_typeState == STATE::VARIABLES)
		{
			AddNewNameToOldName(var);
		}
		else if (var == ":")
		{
			m_typeState = STATE::NOTHING;
		}
		else if (var == ";")
		{
			m_varState = STATE::VARIABLES;
			m_typeState = STATE::VARIABLES;
		}
	}
}

void CVariables::FindAllVarNames()
{
	for (auto str : m_code)
	{
		m_typeState = STATE::VARIABLES;

		size_t functionPos = str.find("FUNCTION");
		if (functionPos == 0)
		{
			string functionId = str.substr(9, str.find('(') - 9);
			AddNewNameToOldName(functionId);
			str.erase(str.begin(), str.begin() + str.find("(") + 1);
		}
		size_t programPos = str.find("PROGRAM");
		if (programPos == 0)
		{
			string programName = str.substr(8, str.find(';') - 8);
			AddNewNameToOldName(programName);
		}
		size_t varPos = str.find("VAR");
		size_t beginPos = str.find("BEGIN");
		
		if (varPos >= 0 && varPos < str.length() && m_varState == STATE::NOTHING)
		{
			FindAndcreateVariablesNames(str);
			m_varState = STATE::VARIABLES;
		}
		else if (m_varState == STATE::VARIABLES && (beginPos < 0 || beginPos >= str.length()))
		{
			FindAndcreateVariablesNames(str);
		}
		else if (m_varState == STATE::VARIABLES && (beginPos >= 0 || beginPos < str.length()))
		{
			m_varState == STATE::NOTHING;
			break;
		}
	}
}

void CVariables::ReplacementNames()
{
	for (auto & str : m_code)
	{
		for (auto del : delimeters)
		{
			boost::replace_all(str, del, " " + del + " ");
		}
	}
	FindAllVarNames();
	sort(begin(m_variablesMap), end(m_variablesMap), [](pair<string, string> last, auto next) 
	{
		return (last.first.length() > next.first.length()); 
	});

	for (auto & str : m_code)
	{
		for (auto name : m_variablesMap)
		{
			boost::replace_all(str, " " + name.first, " " + name.second);
		}
		for (auto del : delimeters)
		{
			boost::replace_all(str, " " + del + " ", del);
		}
	}
}



