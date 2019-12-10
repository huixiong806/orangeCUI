#pragma once
#include <windows.h>
#include <cstdio>
#include"ColorString.h"
class Console
{
public:
	//获得实例
	static Console *getInstance();
	//初始化，程序开始时调用一次
	void init(void);
	//刷新显示
	void refresh(void);
	//清楚所有字符
	void clear(void);
	//设置标题框背景颜色
	void setTitleColor(BackColor color_);
	//设置信息框背景颜色
	void setInformationColor(BackColor color_);
	//设置输入框背景颜色
	void setInputBoxColor(BackColor color_);
	//从第row行开始打印彩色字符串，返回值为总共占了多少行
	short printAt(short row, const ColorString& colorString);
	//隐藏控制台光标
	void hideTheCursor(void);
	//显示控制台光标
	void showTheCursor(void);
	//定位控制台光标
	void setCursorPosition(short x, short y);
	// 重置窗口大小
	void resize(short sizeW, short sizeH);
private:
	Console(){}
	~Console() {}
	static Console* instance;
	//行数
	short row{ 30 };
	//列数
	short col{ 100 };
	//标题的行数
	short titleRow{ 1 };
	BackColor titleColor{ Color::BACK_MAGENTA };
	BackColor informationColor{ Color::BACK_BLACK };
	BackColor inputBoxColor{ Color::BACK_WHITE };
	//输出缓冲
	HANDLE outputBuffer;
	void printCharAt(short x, short y, char ch, Color color);
};