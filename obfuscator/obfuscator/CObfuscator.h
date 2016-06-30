#pragma once
#include "stdafx.h"

class CObfuscator
{
public:
	CObfuscator(std::string const& fileName);
	void DeleteComments();
	void ShowCode() const;
	~CObfuscator() = default;
private:
	std::vector<std::string> m_inputText;
	const enum STATE { NOTHING, ONELINE, MILTILINE };
	int m_commentState = STATE::NOTHING;

	void ReadInputData(std::string const& fileName);
};

