#pragma once
#include "stdafx.h"

class CDelete
{
public:
	CDelete(std::vector<std::string> const& vector1);
	~CDelete() = default;
	void CodeChange();	
	std::vector<std::string> GetResult() const;
private:
	std::vector<std::string> m_inputText;
	const enum STATE { NOTHING, MILTILINE };
	int m_commentState = STATE::NOTHING;

	void DeleteTabAndHyph();
	void DeleteSpaces();
	void DeleteComments();
};

	


