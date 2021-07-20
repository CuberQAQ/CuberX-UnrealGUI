#include <iostream>
#include "CuberX UnrealGUI.h"
using namespace std;
//TODO: 1.FrameButton的延迟响应(有问题，刻度不对) 2.窗口大小设置会出问题
int main()
{
	cuberx::FrameButton fb1("开始游戏",11,3,56,17);
	cuberx::FrameButton fb2("游戏教程",11,3,56,21);
	cuberx::AText at1("测试界面(假装是个游戏)", 22, 1, 51, 7);
	cuberx::ARectFrame arf(127, 32, 0, 0);
	cuberx::MainWindow mw(128,32);

	class gb_AC : public cuberx::CUFunction
	{
	public:
		void func(cuberx::Base* this_button)
		{
			/*
			this_button->setText("我被点击!");
			this_button->draw();
			this_button->getFatherMainWindow()->setEnable(0);
			system("cls");
			cout << "新界面";
			*/
		}
	}gb_ac1,gb_ac2;
	fb1.setClickAction(gb_ac1);
	fb2.setClickAction(gb_ac2);


	mw << fb1 << fb2 << at1 << arf;
	mw.setUseTickListener(1);
	mw.setTimePerTick(5);
	mw.setEnable(1)->join();


	

	

	cuberx::winS.PointJump(12, 1);

	return 0;
}