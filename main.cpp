#include <iostream>
#include "Cuber UnrealGUI.h"
using namespace std;
//TODO: FrameButton中的彩色显示及被选择后的显示模式切换  没！有！弄！玩！
int main()
{
	cuberx::AText aText("*#|test|#*", 10, 1, 5, 5);
	aText.draw();
	cuberx::FrameButton fb("测试按钮",11,3,10,4);
	fb.setTextColor(15,0);
	fb.draw();
	
	cuberx::ARectFrame art(8, 4, 7, 7);
	art.draw();
	cuberx::winS.PointJump(12, 1);

	return 0;
}