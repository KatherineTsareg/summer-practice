#pragma once
#include "stdafx.h"
#include "Delete.h"
#include "CVariables.h"

class CObfuscator
{
public:
	CObfuscator(std::string const& fileName);
	void Start();
	void ShowCode() const;
	~CObfuscator() = default;
private:
	std::vector<std::string> m_inputText;
	std::vector<std::string> m_code;
	void ReadInputData(std::string const& fileName);
};

