#pragma once
#include "stdafx.h"

const size_t LENGTH_VARIABLE_NAME = 8;
class CVariables
{
public:
	CVariables(std::vector<std::string> const& inputVector);
	~CVariables() = default;
	void Renaming();
private:
	std::vector<std::string> m_code;
	std::vector<std::string> m_newNames;
	std::vector<std::string> m_variables;

	char GetRandomSymbol() const;
	std::string GetNewVariableName();
	void FindAllVarNames();
	void ReplacementNames();
	const enum STATE { NOTHING, VARIABLES };
	STATE m_varState = STATE::NOTHING;
};

