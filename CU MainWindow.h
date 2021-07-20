#pragma once
#include"CU Basic.h"
#include <iostream>
#include <thread>
#include <conio.h>
#define $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT 256
using namespace std;


namespace cuberx {

	class MainWindow : public cuberx::Container
	{
	protected:
		string title;//窗口标题(反映在控制台上)
		bool enable;//是否启用
		bool useTickListener;//是否使用帧率管理器
		bool checkKey;//是否检测键位
		ULONGLONG lastTestTickTime;//上一次检测(运行)帧时间
		ULONGLONG timePerTick;//帧率时间(0为无限制 单位为毫秒)
		int tickListenerMode;//检测模式(1为不足则补齐,2为不足则补齐 且 超时则多次执行)
		int nowChosingObject;//目前选择的CU组件(-1表示无)
		cuberx::Base* objects[$CU_MAINWINDOW_TOTAL_OBJECTS_COUNT];
	public:
		
		MainWindow()
		{
			title = "CuberX UnrealGUI ( " + $CU_VERSION + " )";
			enable = 0;
			for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
			{
				objects[i] = 0;
			}
			timePerTick = 0;
			tickListenerMode = 2;
			nowChosingObject = 0;
		}
		MainWindow(string title, int new_size_width = 0, int new_size_height = 0, bool enable = 0) : Container(new_size_width, new_size_height)
		{
			this->title = title;
			this->enable = enable;
			for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
			{
				objects[i] = 0;
			}
			timePerTick = 0;
			tickListenerMode = 2;
			nowChosingObject = 0;
		}
		MainWindow(int new_size_width = 0, int new_size_height = 0, bool enable = 0) : Container(new_size_width, new_size_height)
		{
			this->title = "CuberX UnrealGUI ( " + $CU_VERSION + " )";
			this->enable = enable;
			for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
			{
				objects[i] = 0;
			}
			timePerTick = 0;
			tickListenerMode = 2;
			nowChosingObject = 0;
		}
		
		//添加对象
		int add(cuberx::Base* newObject)
		{
			for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
			{
				if (objects[i] == 0)
				{
					objects[i] = newObject;
					return i;
				}
			}
			return -1;
		}
		int add(cuberx::Base& newObject)
		{
			for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
			{
				if (objects[i] == 0)
				{
					objects[i] = &newObject;
					return i;
				}
			}
			return -1;
		}
		MainWindow& operator<<(cuberx::Base* newObject)
		{
			for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
			{
				if (objects[i] == 0)
				{
					objects[i] = newObject;
					return *this;
				}
				
			}
			throw "[CuberX UnrealGUI]No Enough Place For The New Object. Please Change #define $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT.";
			return *this;
		}
		MainWindow& operator<<(cuberx::Base& newObject)
		{
			for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
			{
				if (objects[i] == 0)
				{
					objects[i] = &newObject;
					return *this;
				}
				
			}
			throw "[CuberX UnrealGUI]No Enough Place For The New Object. Please Change #define CU_MAINWINDOW_TOTAL_OBJECTS_COUNT.";
			return *this;
		}
		virtual thread* setEnable(bool ifEnable)
		{
			if (ifEnable)
			{
				enable = ifEnable;
				draw();
				if (useTickListener)
				{
					thread *tickListenerThread = new thread(tickListener, this);
					return tickListenerThread;	
				}
			}
			else
			{
				enable = ifEnable;
				setLastTestTickTime(0);
				return 0;
			}
			
		}
		virtual bool getEnable()
		{
			return enable;
		}
		virtual void draw(int drawObjectIndex = -1)
		{
			if (drawObjectIndex <= -1)
			{
				for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
				{
					if (objects[i] != 0)
					{
						if (objects[i]->getVisible())
						{
							objects[i]->draw();
						}
					}
				}
			}
			else
			{
				objects[drawObjectIndex]->draw();
			}
		}
		virtual void setTimePerTick(ULONGLONG newTimePerTick)
		{
			timePerTick = newTimePerTick;
		}
		virtual ULONGLONG getTimePerTick()
		{
			return timePerTick;
		}
		virtual void setUseTickListener(bool ifUseTickListener)
		{
			useTickListener = ifUseTickListener;
			if (enable)
			{
				//刷新状态，即重新启用
				setEnable(1);
			}
		}
		virtual bool getUseTickListener()
		{
			return useTickListener;
		}
		virtual void setCheckKey(bool ifCheckKey)
		{
			checkKey = ifCheckKey;
		}
		virtual bool getCheckKey()
		{
			return checkKey;
		}
		virtual ULONGLONG getLastTestTickTime()
		{
			return lastTestTickTime;
		}
		virtual void setLastTestTickTime(ULONGLONG newLastTestTickTime)
		{
			lastTestTickTime = newLastTestTickTime;
		}
		virtual void setTickListenerMode(int newMode)
		{
			tickListenerMode = newMode;
		}
		virtual int getTickListenerMode()
		{
			return tickListenerMode;
		}
		virtual int getNowChosingObject()
		{
			return nowChosingObject;
		}
		virtual void setNowChosingObject(int newChosingObject)
		{
			if (objects[newChosingObject] == 0)
			{
				cout << "[CuberX]Error:The newChosingObject Has Not Be Found!";
			}
			else
			{
				if (objects[nowChosingObject] != 0)
				{
					objects[nowChosingObject]->whenStopChosed();
				}
				objects[newChosingObject]->whenBeChosed();
				nowChosingObject = newChosingObject;
			}
		}


		//帧率管理器（会被作为子线程生成）
		static void tickListener(MainWindow* this_MainWindow)
		{
			while(1)
			{
				//检测是否有关闭
				if (this_MainWindow->getUseTickListener() == 0 || this_MainWindow->getEnable() == 0)
				{
					return;
				}

				//校正帧率时刻(前者不为零说明有限制,后者不为零说明不是第一次执行)
				if (this_MainWindow->getTimePerTick() != 0 && this_MainWindow->getLastTestTickTime() != 0)
				{
					ULONGLONG pastTime = GetTickCount64() - this_MainWindow->getLastTestTickTime();
					//检测模式(1为不足则补齐,2为不足则补齐 且 超时则多次执行(慎用))
					switch (this_MainWindow->getTickListenerMode())
					{
					case 1:
					{
						if (pastTime < this_MainWindow->getTimePerTick())
						{
							Sleep(this_MainWindow->getTimePerTick() - pastTime);
						}
						this_MainWindow->setLastTestTickTime(GetTickCount64());
					}
					break;
					case 2:
					{
						if (pastTime <= this_MainWindow->getTimePerTick())
						{
							//不足(补齐)|恰好(补0)  (并执行)
							Sleep(this_MainWindow->getTimePerTick() - pastTime);
							this_MainWindow->setLastTestTickTime(GetTickCount64());
						}
						else
						{
							//超时(执行并调后[上次时间])
							this_MainWindow->setLastTestTickTime(this_MainWindow->getLastTestTickTime() + this_MainWindow->getTimePerTick());
						}
					}
					break;
					default:
						cout << "\n[CuberX]Error:Unknown TickListenerMode";
						break;
					}

				}

				//检测键位
				if (this_MainWindow->getCheckKey())
				{
					if (_kbhit())
					{
						int nowInputKey = _getch();
						this_MainWindow->keyListener(nowInputKey);
					}
				}
				//TODO: 任务检测

				
			}
			return;
		}
		virtual void keyListener(int newKey)
		{
			
			//全局键位(优先响应)
			switch (newKey)
			{
			default:
				break;
			}

			int result = 0;

			//目前选中成员
			if (getNowChosingObject() >= 0)
			{
				if (objects[getNowChosingObject()] != 0)
				{
					result = objects[getNowChosingObject()]->keyAction(newKey);
					if (result == 1)
					{
						return;
					}
				}
			}
			//遍历其它成员
			for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
			{
				if (objects[i] != 0 && i != getNowChosingObject())
				{
					result = objects[i]->keyAction(newKey);
					if (result == 1)
					{
						return;
					}
				}
			}
			//全局键位(滞后响应)
			switch (newKey)
			{
				//上(左)翻
			case KEY.$UP:
			case KEY.$LEFT:
			{
				//遍历剩余部分（正序）
				if (getNowChosingObject() != $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT - 1)
				{
					for (int i = 1 + getNowChosingObject(); i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
					{
						if (objects[i] != 0 && objects[i]->getCanBeChosed() == 1)
						{
							setNowChosingObject(i);
							return;
						}
					}
				}
				//遍历全部（在上面代码块未成功情况下）（正序）
				for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
				{
					if (objects[i] != 0 && objects[i]->getCanBeChosed() == 1)
					{
						setNowChosingObject(i);
						return;
					}
				}
			}
				break;

				//下(右)翻
			case KEY.$DOWN:
			case KEY.$RIGHT:
			{
				//遍历前面部分（倒序）
				if (getNowChosingObject() != 0)
				{
					for (int i = getNowChosingObject() - 1; i >= 0; i--)
					{
						if (objects[i] != 0 && objects[i]->getCanBeChosed() == 1)
						{
							setNowChosingObject(i);
							return;
						}
					}
				}
				//遍历全部（在上面代码块未成功情况下）（倒序）
				for (int i = $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT - 1; i >= 0; i--)
				{
					if (objects[i] != 0 && objects[i]->getCanBeChosed() == 1)
					{
						setNowChosingObject(i);
						return;
					}
				}
			}
				break;
			default:
				break;
			}
		}
	};

}