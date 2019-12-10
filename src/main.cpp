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
	con = make_unique<Console>();
	con->init();
	while (true)
	{
		update();
		Sleep(1000.0/60.0);//��֤FPSΪ60
	}
	return 0;
}