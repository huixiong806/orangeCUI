#include"Console.h"
#include<iostream>
#include<algorithm>
#include<string>
#include<memory>
#include<ctime>
#include<Windows.h>
using namespace std;
void update()
{
	Console* con = Console::getInstance();
	static int screenUpdateCounter = 0;
	//一秒刷新一次显示
	if (screenUpdateCounter == 0)
		con->refresh();
	/*这里是代码开始*/
	time_t now = time(0);
	char* dt = ctime(&now);
	con->printAt(0, ColorString(dt,Color::BRIGHTYELLOW));
	for (int i = 1; i <= 16; ++i)
	{
		con->printAt(i, ColorString("color test",(Color)(i-1)));
	}
	/*这里是代码结束*/
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
		Sleep(1000.0/60.0);//保证FPS为60
	}
	return 0;
}