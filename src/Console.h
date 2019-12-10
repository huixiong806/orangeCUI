#pragma once
#include <windows.h>
#include <cstdio>
#include"ColorString.h"
class Console
{
public:
	//���ʵ��
	static Console *getInstance();
	//��ʼ��������ʼʱ����һ��
	void init(void);
	//ˢ����ʾ
	void refresh(void);
	//��������ַ�
	void clear(void);
	//���ñ���򱳾���ɫ
	void setTitleColor(BackColor color_);
	//������Ϣ�򱳾���ɫ
	void setInformationColor(BackColor color_);
	//��������򱳾���ɫ
	void setInputBoxColor(BackColor color_);
	//�ӵ�row�п�ʼ��ӡ��ɫ�ַ���������ֵΪ�ܹ�ռ�˶�����
	short printAt(short row, const ColorString& colorString);
	//���ؿ���̨���
	void hideTheCursor(void);
	//��ʾ����̨���
	void showTheCursor(void);
	//��λ����̨���
	void setCursorPosition(short x, short y);
	// ���ô��ڴ�С
	void resize(short sizeW, short sizeH);
private:
	Console(){}
	~Console() {}
	static Console* instance;
	//����
	short row{ 30 };
	//����
	short col{ 100 };
	//���������
	short titleRow{ 1 };
	BackColor titleColor{ Color::BACK_MAGENTA };
	BackColor informationColor{ Color::BACK_BLACK };
	BackColor inputBoxColor{ Color::BACK_WHITE };
	//�������
	HANDLE outputBuffer;
	void printCharAt(short x, short y, char ch, Color color);
};