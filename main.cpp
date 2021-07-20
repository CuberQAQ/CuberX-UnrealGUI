#include <iostream>
#include "CuberX UnrealGUI.h"
using namespace std;
//TODO: 1.添加多彩text功能 2.FrameButton的延迟响应(有问题，刻度不对) 3.FrameButton的渐变有bug（快速切换时）

int main()
{

	cuberx::FrameButton fb1("开始游戏", 11, 3, 56, 17);
	cuberx::FrameButton fb2("游戏教程", 11, 3, 56, 21);
	cuberx::AText at1("测试界面(假装是个游戏)", 22, 1, 51, 7);
	cuberx::ARectFrame arf(127, 32, 0, 0);
	cuberx::MainWindow mw("测试界面", 128, 32);
	cuberx::CLText clt(" MUSIC ", "CCCCCCC", "7777777", 7, 1, 119, 1);
	cuberx::TestGroup tg;
	cuberx::TipBar tb("提示: ", "按上下键翻页!", "000000000000", "88AAAA888888", 0, 0, false, 0, 23, 3);
	tg.setLocation(53, 9);
	class gb_AC : public cuberx::CUFunction
	{
	public:
		void func(cuberx::Base* this_button)
		{
			/*
				this_button->getFatherMainWindow()->setEnable(0);
				system("cls");
				cout << "新界面";
				*/
		}
	}gb_ac1, gb_ac2;
	fb1.setClickAction(gb_ac1);
	fb2.setClickAction(gb_ac2);


	mw << fb1 << fb2 << at1 << arf << clt << tb;
	mw.setUseTickListener(1);
	mw.setTimePerTick(5);
	thread* thr = mw.setEnable(1);
	Sleep(5000);
	tb.setCLText("按 Enter 键确认", "nnnnnnnnnnnnnnnnnnnnn", "880AAAAA0887777");
	cuberx::SoundPlayer sp;
	wchar_t wc1[] = L"open D:\\7q412-dqfzq.wav";
	wchar_t wc2[] = L"play D:\\7q412-dqfzq.wav";
	sp.playSoundTool(wc1, wc2);
	clt.setTextColorInfo("AAAAAAA", "FFFFFFF");
	thr->join();






	cuberx::winS.PointJump(12, 1);

	return 0;
}