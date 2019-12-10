#include"Console.h"
#include<iostream>
#include<algorithm>
#include<memory>
#include<ctime>
#include<Windows.h>
using namespace std;
unique_ptr<Console> con;
void update()
{
	static int screenUpdateCounter = 0;
	//一秒刷新一次显示
	if (screenUpdateCounter == 0)
		con->refresh();
	/*这里是代码开始*/
	time_t now = time(0);
	char* dt = ctime(&now);
	con->printAt(0, ColorString(dt,Color::BRIGHTYELLOW));
	/*这里是代码结束*/
	screenUpdateCounter++;
	screenUpdateCounter %= 60;
}
int main()
{
	con = make_unique<Console>();
	con->init();
	while (true)
	{
		update();
		Sleep(1000.0/60.0);//保证FPS为60
	}
	return 0;
}