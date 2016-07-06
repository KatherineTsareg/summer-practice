#include "stdafx.h"
#include "Delete.h"

using namespace std;

const set<char> DELIMITER{ '.', ',', ':', ';', '-', '+',  '*',  '/', '=',  '(', ')' };

CDelete::CDelete(std::vector<std::string> const& vector1)
	:m_inputText(vector1)
{
}

void CDelete::DeleteTab()
{
	for (auto &str : m_inputText)
	{ 
		boost::replace_all(str, "\t", "");
	}
}

void CDelete::DeleteSpaces()
{
	{
		//удалить лиишние пробелы
		for (auto &str : m_inputText)
		{
			for (int i = 0; i < str.length(); i++)
				if (str[i] == ' ' && str[i + 1] == ' ')
				{
					str.erase(i, 1);
					i = (i - 1);
				}
		}
		//удалить пробелы между разделителями
	}
}

void CDelete::DeleteComments()
{
	for (string & str : m_inputText)
	{
		size_t posOpen = str.find("{");
		size_t posEnd = str.find("}");
		size_t onelinePos = str.find("//");
		if ((posOpen >= 0 && posOpen < str.length()) && (posEnd >= 0 && posEnd < str.length()) && (m_commentState != STATE::MILTILINE)) //нашли многострочный закрытый комментарий
		{
			str.erase(begin(str) + posOpen, begin(str) + posEnd + 1);
		}
		else if ((posOpen >= 0 && posOpen <= str.length()) && (posEnd < 0 || posEnd >= str.length()) && (m_commentState != STATE::MILTILINE)) //нашли многострочный не закрытый комментарий
		{
			str.erase(begin(str) + posOpen, end(str));
			m_commentState = STATE::MILTILINE;
		}
		else if (m_commentState == STATE::MILTILINE && (posEnd >= 0 && posEnd <= str.length()))
		{
			str.erase(begin(str), begin(str) + posEnd + 1);
			m_commentState = STATE::NOTHING;
		}
		else if ((onelinePos >= 0 && onelinePos < str.length()) && (m_commentState != STATE::MILTILINE))
		{
			str.erase(begin(str) + onelinePos, end(str));
		}
	}
}

void CDelete::CodeChange()
{
	DeleteTab();
	DeleteComments();
	//DeleteSpaces();
}

std::vector<std::string> CDelete::GetResult() const
{
	return m_inputText;
}
