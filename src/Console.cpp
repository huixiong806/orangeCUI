#include "Console.h"
using namespace std;
Console *Console::instance = nullptr;
Console* Console::getInstance()
{
	if (instance == nullptr)
		instance = new Console();
	return instance;
}
void Console::init()
{
	outputBuffer= CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);
	resize(col, row);
	hideTheCursor();
	clear();
	refresh();
}
void Console::refresh(void)
{
	//À´ª∫≥Â¥¶¿Ìœ‘ æ
	COORD coord = { 0,0 };
	DWORD bytes = 0;
	char* data = new char[row * col];
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ReadConsoleOutputCharacterA(outputBuffer, data, row * col, coord, &bytes);
	WriteConsoleOutputCharacterA(hStdOut, data, row* col, coord, &bytes);
	delete data;
	WORD* data2 = new WORD[row * col];
	bytes = 0;
	ReadConsoleOutputAttribute(outputBuffer, data2, row * col, coord, &bytes);
	WriteConsoleOutputAttribute(hStdOut, data2, row * col, coord, &bytes);
	delete data2;
}
void Console::clear(void)
{
	for (size_t j = 0; j < col; ++j)
		for (size_t i = 0; i < row; ++i)
			printCharAt(j, i, ' ', Color::BLACK);
}
//Hides the console cursor
void Console::hideTheCursor()
{
	CONSOLE_CURSOR_INFO cciCursor;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (GetConsoleCursorInfo(hStdOut, &cciCursor))
	{
		cciCursor.bVisible = FALSE;
		SetConsoleCursorInfo(hStdOut, &cciCursor);
	}
}
//Show the console cursor
void Console::showTheCursor()
{
	CONSOLE_CURSOR_INFO cciCursor;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (GetConsoleCursorInfo(hStdOut, &cciCursor))
	{
		cciCursor.bVisible = TRUE;
		SetConsoleCursorInfo(hStdOut, &cciCursor);
	}
}
void Console::setCursorPosition(short x, short y)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hStdOut, { x,y });
}
void Console::resize(short sizeW= 80-1, short sizeH=25-1)
{
	row = sizeH;
	col = sizeW;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT rc = { 0,0,(short)sizeW-1,(short)sizeH-1};
	char* temp = new char[30];
	sprintf(temp, "mode con:cols=%d lines=%d", sizeW, sizeH);
	system(temp);
	delete temp;
	SetConsoleWindowInfo(hStdOut, true, &rc);
	rc = { 0,0,(short)sizeW-1,(short)sizeH-1};
	SetConsoleWindowInfo(outputBuffer, true, &rc);
	SetConsoleScreenBufferSize(hStdOut, { (short)sizeW,(short)sizeH });
	SetConsoleScreenBufferSize(outputBuffer, { (short)sizeW,(short)sizeH });
}
void Console::printCharAt(short x, short y, char ch, Color color)
{
	DWORD count;
	COORD coord = { x, y };
	SetConsoleCursorPosition(outputBuffer, coord);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	//We use csbi for the wAttributes word.
	if (GetConsoleScreenBufferInfo(outputBuffer, &csbi))
	{
		WORD temp = color & 0x0F;
		if (y < titleRow)temp |= titleColor & 0xF0;
		else if(y<row-1)temp |= informationColor & 0xF0;
		else temp |= inputBoxColor & 0xF0;
		SetConsoleTextAttribute(outputBuffer, temp);
		WriteConsole(outputBuffer, &ch, 1, &count, NULL);
	}
}
short Console::printAt(short row, const ColorString& colorString)
{
	int r, c;
	for (int i = 0; i < colorString.size(); ++i)
	{
		r = row+i / col;
		c = i % col;
		printCharAt(c, r, colorString.str()[i],colorString.getColor(i));
	}
	return r - row+1;
}

void Console::setTitleColor(BackColor color_)
{
	titleColor = color_; 
	WORD* data = new WORD[col];
	for (int i = 0; i < col; ++i)
		data[i] = color_;
	DWORD bytes=0;
	WriteConsoleOutputAttribute(outputBuffer, data, col, { 0,0 }, &bytes);
	delete data;
}
void Console::setInformationColor(BackColor color_)
{
	informationColor = color_; 
	WORD* data = new WORD[(row - 2) * col];
	for (int i = 0; i < col; ++i)
		data[i] = color_;
	DWORD bytes=0;
	WriteConsoleOutputAttribute(outputBuffer, data, (row-2)*col, { 0,1 }, &bytes);
	delete data;
}
void Console::setInputBoxColor(BackColor color_)
{ 
	inputBoxColor = color_; 
	WORD* data = new WORD[col];
	for (int i = 0; i < col; ++i)
		data[i] = color_;
	DWORD bytes=0;
	WriteConsoleOutputAttribute(outputBuffer, data, col, { 0,(short)row-1 }, &bytes);
	delete data;
}