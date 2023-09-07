#pragma once
#ifndef TITLE_H
#define TITLE_H

#include "UI.h"
#include "myString.h"


class Title
{
public:
	Title();
	~Title() {}

	void Update();

	void Draw();

private:
	Button*		m_Button;
	MyString*	m_String;
	MyString*	m_Title;

	TEXTURE_DATA m_BG;
};


#endif // !TITLE_H