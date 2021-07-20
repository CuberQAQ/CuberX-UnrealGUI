#pragma once
#include"CU Standard.h"
#include<iostream>
using namespace std;

//组件群组
namespace cuberx {
	//组件群组(建议在堆内分配子组件的内存(即用new关键字),析构函数会自动回收内存)
	template<int objectCount>
	class Group : public cuberx::Container
	{
	protected:
		cuberx::Base* objects[objectCount];
	public:
		Group()
		{
			for (int i = 0; i < objectCount; i++)
			{
				objects[i] = nullptr;
			}
		}
		~Group()
		{
			for (int i = 0; i < objectCount; i++)
			{
				if (objects[i] != nullptr)
				{
					delete objects[i];
					objects[i] = nullptr;
				}
			}
		}
		//绘制子组件，-1表示绘制所有
		virtual void draw(int index, int offsetX = 0, int offsetY = 0)
		{
			if (index == -1)
			{
				for (int i = 0; i < objectCount; i++)
				{
					objects[i]->draw(location.x + offsetX, location.y + offsetY);
				}
			}
			else if (index >= 0)
			{
				objects[index]->draw(location.x + offsetX, location.y + offsetY);
			}
		}
		virtual void draw(int offsetX = 0, int offsetY = 0)
		{
			for (int i = 0; i < objectCount; i++)
			{
				objects[i]->draw(location.x + offsetX, location.y + offsetY);
			}
		}
		virtual void setNowChosingObject(int newChoingObject)
		{
			if (objects[nowChosingObject] != nullptr)
			{
				objects[nowChosingObject]->whenStopChosed();
			}
			if (objects[newChoingObject] != nullptr)
			{
				objects[newChoingObject]->whenBeChosed();
			}
			nowChosingObject = newChoingObject;
		}
		//键位反应
		int keyAction(int newKey)
		{
			//
			int result = 0;
			for (int i = 0; i < objectCount; i++)
			{
				result = objects[i]->keyAction(newKey);
				if (result == 1)
				{
					return result;
				}
			}
			return result;
		}
		//设置所属主窗口信息(同步到子组件)
		virtual void setFatherMainWindow(cuberx::MainWindow* newFatherMainWindow)
		{
			fatherMainWindow = newFatherMainWindow;
			for (int i = 0; i < objectCount; i++)
			{
				if (objects[i] != nullptr)
				{
					objects[i]->setFatherMainWindow(newFatherMainWindow);
				}
			}
		}
		//重置所属主窗口信息(同步到子组件)
		virtual void resetFatherMainWindow()
		{
			fatherMainWindow = nullptr;
			for (int i = 0; i < objectCount; i++)
			{
				if (objects[i] != nullptr)
				{
					objects[i]->resetFatherMainWindow();
				}
			}
		}
	};

}

//测试组件:边框+白色"提示:"+彩色"鸡你太美"
namespace cuberx {

	class TestGroup : public cuberx::Group<3>
	{
	protected:
		cuberx::ARectFrame* arf;
		cuberx::AText* at;
		cuberx::CLText* clt;
	public:
		TestGroup()
		{
			arf = new cuberx::ARectFrame(17, 3, 0, 0);
			at = new cuberx::AText("提示:", 5, 1, 2, 1);
			clt = new cuberx::CLText("鸡你太美", "00000000", "44444444", 8, 1, 8, 1);
			objects[0] = arf;
			objects[1] = at;
			objects[2] = clt;
		}
	};

}

//测试组件:黑白标题+彩色内容+自动伸缩边框
namespace cuberx {

	class TipBar : public cuberx::Group<3>
	{
	protected:
		cuberx::ARectFrame* arf;
		cuberx::AText* at;
		cuberx::CLText* clt;
		bool autoSize;
		bool frameVisible;
	public:
		TipBar()
		{
			autoSize = 1;
			arf = new cuberx::ARectFrame;
			at = new cuberx::AText("提示: ", 6, 1, 2, 1);
			clt = new cuberx::CLText("无", "00", "cc", 2, 1, at->getText().length() + 2, 1);
			runAutoSize();
			objects[0] = arf;
			objects[1] = at;
			objects[2] = clt;
			frameVisible = 1;
		}
		TipBar(string title, string tip, string tipBackGroundColorInfo = "", string tipFontColorInfo = "", int x = 0, int y = 0, bool frameVisible = 1, bool ifUseAutoSize = 1, int width = 10, int height = 3)
		{
			autoSize = ifUseAutoSize;
			arf = new cuberx::ARectFrame(width, height);
			at = new cuberx::AText(title, title.length(), 1, 2, 1);
			clt = new cuberx::CLText(tip, tipBackGroundColorInfo, tipFontColorInfo, tip.length(), 1, at->getText().length() + 2, 1);
			setLocation(x, y);
			setSize(width, height);
			if (ifUseAutoSize)
			{
				runAutoSize();
			}
			objects[0] = arf;
			objects[1] = at;
			objects[2] = clt;
			this->frameVisible = frameVisible;
		}
		virtual void runAutoSize()
		{
			arf->setSize(at->getText().length() + clt->getText().length() + 3, 3);
			clt->setLocation(2 + at->getText().length(), 1);
		}
		virtual void setAutoSize(bool ifAutoSize)
		{
			autoSize = ifAutoSize;
			if (ifAutoSize)
			{
				runAutoSize();
				draw();
			}
		}
		virtual void setAText(string newText)
		{
			at->setText(newText);
			if (autoSize)
			{
				runAutoSize();
			}
			draw();
		}
		virtual void setCLText(string newText, string tipBackGroundColorInfo = "", string tipFontColorInfo = "")
		{
			clt->setText(newText);
			clt->setTextColorInfo(tipBackGroundColorInfo, tipFontColorInfo, true, false);
			if (autoSize)
			{
				runAutoSize();
			}
			draw();
		}
		virtual void setFrameSize(int width, int height)
		{
			arf->setSize(width, height);
			draw();
		}
		virtual void draw(int offsetX = 0, int offsetY = 0)
		{
			if (frameVisible)
			{
				objects[0]->draw(location.x + offsetX, location.y + offsetY);
			}
			for (int i = 1; i < 3; i++)
			{
				objects[i]->draw(location.x + offsetX, location.y + offsetY);
			}
		}
	};
	
}