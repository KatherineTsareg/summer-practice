#pragma once
#include "stdafx.h"

const size_t LENGTH_VARIABLE_NAME = 8;

class CVariables
{
public:
	CVariables(std::vector<std::string> const& inputVector);
	~CVariables() = default;
	void Renaming();
	std::vector<std::string> GetResult() const;
private:
	std::vector<std::string> m_code;
	std::vector<std::string> m_newNames;
	std::vector<std::pair<std::string, std::string>> m_variablesMap;

	char GetRandomSymbol() const;
	std::string GetNewVariableName();
	void FindAllVarNames();
	void ReplacementNames();
	void FindAndcreateVariablesNames(std::string const& str);
	void AddNewNameToOldName(std::string & var);
	const enum STATE { NOTHING, VARIABLES };
	STATE m_varState = STATE::NOTHING;
	STATE m_typeState = STATE::VARIABLES;
};