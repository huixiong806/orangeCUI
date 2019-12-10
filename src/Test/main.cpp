#include"Console.h"
#include<iostream>
#include<algorithm>
#include<memory>
#include<ctime>
#include<Windows.h>
using namespace std;
void update()
{
	Console* con = Console::getInstance();
	static int screenUpdateCounter = 0;
	//һ��ˢ��һ����ʾ
	if (screenUpdateCounter == 0)
		con->refresh();
	/*�����Ǵ��뿪ʼ*/
	time_t now = time(0);
	char* dt = ctime(&now);
	con->printAt(0, ColorString(dt,Color::BRIGHTYELLOW));
	/*�����Ǵ������*/
	screenUpdateCounter++;
	screenUpdateCounter %= 60;
}
int main()
{
	Console* con = Console::getInstance();
	con->init();
	while (true)
	{
		update();
		Sleep(1000.0/60.0);//��֤FPSΪ60
	}
	return 0;
}