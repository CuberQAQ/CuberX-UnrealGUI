#include <iostream>
#include "Cuber UnrealGUI.h"
using namespace std;
//TODO: 添加MainWindow的任务功能
int main()
{
	cuberx::FrameButton fb1("测试按钮1",12,3,0,0);
	cuberx::FrameButton fb2("测试按钮2",12,3,0,5);
	cuberx::MainWindow mw("Test Window",50,50);
	class gb_AC : public cuberx::CUFunction
	{
	public:
		void func(cuberx::Base* this_button)
		{
			this_button->setText("我被点击!");
			this_button->draw();
		}
	}gb_ac1,gb_ac2;
	fb1.setClickAction(gb_ac1);
	fb2.setClickAction(gb_ac2);

	mw << fb1 << fb2;
	mw.setUseTickListener(1);
	mw.setTimePerTick(0);
	mw.setEnable(1)->join();


	

	

	cuberx::winS.PointJump(12, 1);

	return 0;
}