#pragma once
#include "CU Basic.h"
#include <iostream>
using namespace std;

namespace cuberx {

	//0.     1.©³©¥ 2. ©·²Ý 3. ©»©¥ 4. ©¿  5. ©¥©¥ 6. ©§  7. ©×©¥ 8. ©ß©¥ 9. ©Ç©¥ 10. ©Ï  11. ©ï


	class FrameButton : public cuberx::Module
	{
	private:
		cuberx::ColorInfo textColorInfo;
		cuberx::ColorInfo frameColorInfo;
		cuberx::ColorInfo chosedTextColorInfo;
		cuberx::ColorInfo chosedFrameColorInfo;
		cuberx::ColorInfo normalTextColorInfo;
		cuberx::ColorInfo normalFrameColorInfo;
		cuberx::CUFunction* clickAction;
	public:
		FrameButton()
		{
			text = " ";
			canBeChosed = 1;
			chosedTextColorInfo = { 7,0 };
			chosedFrameColorInfo = { 0,7 };
			normalTextColorInfo = { 0,7 };
			normalFrameColorInfo = { 0,7 };
			textColorInfo = normalTextColorInfo;
			frameColorInfo = normalFrameColorInfo;
			clickAction = 0;
		}
		FrameButton(string newText)
		{
			text = newText;
			canBeChosed = 1;
			chosedTextColorInfo = { 7,0 };
			chosedFrameColorInfo = { 0,7 };
			normalTextColorInfo = { 0,7 };
			normalFrameColorInfo = { 0,7 };
			textColorInfo = normalTextColorInfo;
			frameColorInfo = normalFrameColorInfo;
			clickAction = 0;
		}
		FrameButton(int width, int height, int x, int y)
		{
			location.x = x;
			location.y = y;
			size.width = width;
			size.height = height;
			canBeChosed = 1;
			chosedTextColorInfo = { 7,0 };
			chosedFrameColorInfo = { 0,7 };
			normalTextColorInfo = { 0,7 };
			normalFrameColorInfo = { 0,7 };
			textColorInfo = normalTextColorInfo;
			frameColorInfo = normalFrameColorInfo;
			clickAction = 0;
		}
		FrameButton(int width, int height)
		{
			size.width = width;
			size.height = height;
			canBeChosed = 1;
			chosedTextColorInfo = { 7,0 };
			chosedFrameColorInfo = { 0,7 };
			normalTextColorInfo = { 0,7 };
			normalFrameColorInfo = { 0,7 };
			textColorInfo = normalTextColorInfo;
			frameColorInfo = normalFrameColorInfo;
			clickAction = 0;
		}
		FrameButton(string newText, int width, int height, int x, int y)
		{
			text = newText;
			location.x = x;
			location.y = y;
			size.width = width;
			size.height = height;
			canBeChosed = 1;
			chosedTextColorInfo = { 7,0 };
			chosedFrameColorInfo = { 0,7 };
			normalTextColorInfo = { 0,7 };
			normalFrameColorInfo = { 0,7 };
			textColorInfo = normalTextColorInfo;
			frameColorInfo = normalFrameColorInfo;
			clickAction = 0;
		}
		FrameButton(string newText, int width, int height)
		{
			text = newText;
			size.width = width;
			size.height = height;
			canBeChosed = 1;
			chosedTextColorInfo = { 7,0 };
			chosedFrameColorInfo = { 0,7 };
			normalTextColorInfo = { 0,7 };
			normalFrameColorInfo = { 0,7 };
			textColorInfo = normalTextColorInfo;
			frameColorInfo = normalFrameColorInfo;
			clickAction = 0;
		}
		void draw()
		{
			cuberx::winS.PointJump(location.y, location.x);
			winS.colorOut(frameChar[1], frameColorInfo.font, frameColorInfo.backGround);
			for (int i = 0; i < size.width - 2; i++)
			{
				cuberx::winS.PointJump(location.y, location.x + 1 + i);
				winS.colorOut(frameChar[5], frameColorInfo.font, frameColorInfo.backGround);
			}
			cuberx::winS.PointJump(location.y, location.x + size.width - 1);
			winS.colorOut(frameChar[2], frameColorInfo.font, frameColorInfo.backGround);

			cuberx::winS.PointJump(location.y + size.height - 1, location.x);
			winS.colorOut(frameChar[3], frameColorInfo.font, frameColorInfo.backGround);
			for (int i = 0; i < size.width - 2; i++)
			{
				cuberx::winS.PointJump(location.y + size.height - 1, location.x + 1 + i);
				winS.colorOut(frameChar[5], frameColorInfo.font, frameColorInfo.backGround);
			}
			cuberx::winS.PointJump(location.y + size.height - 1, location.x + size.width - 1);
			winS.colorOut(frameChar[4], frameColorInfo.font, frameColorInfo.backGround);

			for (int i = 0; i < size.y - 2; i++)
			{
				cuberx::winS.PointJump(location.y + 1 + i, location.x);
				winS.colorOut(frameChar[6], frameColorInfo.font, frameColorInfo.backGround);
				cuberx::winS.PointJump(location.y + 1 + i, location.x + size.width - 1);
				winS.colorOut(frameChar[6], frameColorInfo.font, frameColorInfo.backGround);
			}
			cuberx::winS.PointJump(location.y + 1, location.x + 2);
			winS.colorOut(text, textColorInfo.font, textColorInfo.backGround);

		}
		void whenBeChosed()
		{
			setTextColor(chosedTextColorInfo.backGround, chosedTextColorInfo.font);
			draw();
		}
		void whenStopChosed()
		{
			setTextColor(normalTextColorInfo.backGround, normalTextColorInfo.font);
			draw();
		}
		void setTextColor(int backGround, int font)
		{
			textColorInfo.backGround = backGround;
			textColorInfo.font = font;
		}
		void setFrameColor(int backGround, int font)
		{
			frameColorInfo.backGround = backGround;
			frameColorInfo.font = font;
		}
		void setBeChosed(bool newCase)
		{
			beChosed = newCase;
			if (newCase)
			{
				whenBeChosed();
			}
		}
		void setClickAction(cuberx::CUFunction* newFunc)
		{
			clickAction = newFunc;
		}
		void setClickAction(cuberx::CUFunction& newFunc)
		{
			clickAction = &newFunc;
		}
		CUFunction& getClickAction()
		{
			return *clickAction;
		}
		int keyAction(int newKey)
		{
			switch (newKey)
			{
			case KEY.$ENTER:
				draw();
				if (&getClickAction() != 0)
				{
					getClickAction().func(this);
				}
				return 1;
			}
			return 0;
		}
	};
	
}