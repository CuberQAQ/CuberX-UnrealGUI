#pragma once
#include<iostream>
#include<Windows.h>
using namespace std;

//键位宏


//版本
string $CU_VERSION = "dev";
using namespace std;
namespace cuberx {
	class Base;

	//窗口信息
	class WindowInfo {
	public:
		//获取显示句柄
		HANDLE GetDisplayHandle()
		{
			return GetStdHandle(STD_OUTPUT_HANDLE);
		}
		char NowFontsColor;
		char NowWindowColor;
	} WI;
	//窗口设置
	class WindowSetting {
	private:
		short w;
		short h;
	public:
		WindowSetting() {
			w = 0;
			h = 0;
		}
		//窗口大小
		int WindowArea(short w, short h, bool ifcls = 0) {
			HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD size = { w, h };
			SetConsoleScreenBufferSize(hOut, size);
			SMALL_RECT rc = { 1,1, w, h };
			SetConsoleWindowInfo(hOut, true, &rc);
			if (ifcls == 1) system("cls");
			return 0;
		}
		//锁定窗口大小
		int LockWindow() {
			HWND hWnd = GetConsoleWindow(); //获得cmd窗口句柄
			RECT rc;
			GetWindowRect(hWnd, &rc); //获得cmd窗口对应矩形
			//改变cmd窗口风格
			SetWindowLongPtr(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
			//因为风格涉及到边框改变，必须调用SetWindowPos，否则无效果
			SetWindowPos(hWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, NULL);
			return 0;
		}
		//设置全局显示颜色
		int ColorSetting(char FontsColor = '7', char WindowColor = '0') {
			char SendStr[] = "color xx";
			char* p_ch = SendStr + 6;
			*p_ch = WindowColor;
			*(++p_ch) = FontsColor;
			system(SendStr);
			return 0;
		}
		//光标跳转
		void PointJump(int pawnH, int pawnW, HANDLE handle = WI.GetDisplayHandle())
		{
			COORD PointPawn;
			PointPawn.X = pawnW;             //宽坐标
			PointPawn.Y = pawnH;             //高坐标
			SetConsoleCursorPosition(handle, PointPawn);
		}

		/*彩色输出
		0 = 黑色 8 = 灰色
		1 = 蓝色 9 = 淡蓝色
		2 = 绿色 10 = 淡绿色
		3 = 浅绿色 11 = 淡浅绿色
		4 = 红色 12 = 淡红色
		5 = 紫色 13 = 淡紫色
		6 = 黄色 14 = 淡黄色
		7 = 白色 15 = 亮白色
		https://blog.csdn.net/qq_42885747/article/details/103835671?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.control&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.control
		*/
		void colorOut(string str, int FontsColorInt, int WindowColorInt) {
			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | (FontsColorInt + WindowColorInt * 16));
			cout << str;
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
		}

		
	} winS;
	template<class T>
	class SuperArray
	{
	private:
		T** mem;
		int HEIGHT;
		int WIDTH;
		bool ifON;
	public:
		SuperArray() 
		{
			HEIGHT = 0;
			WIDTH = 0;
			ifON = 0;
		}
		SuperArray(int height, int width) 
		{
			HEIGHT = height;
			WIDTH = width;
			ifON = 1;
			mem = new T * [HEIGHT];
			//数组mem[HEIDHT][WIDTH];
			for (int i = 0; i < HEIGHT; i++)
			{
				mem[i] = new T[WIDTH];
			}
		}
		void reset(int newHeight, int newWidth)
		{
			if (ifON == 1)
			{
				for (int i = 0; i < HEIGHT; i++)
				{
					delete[] mem[i];
					mem[i] = 0;
				}
				delete[] mem;
				mem = 0;
			}
			HEIGHT = newHeight;
			WIDTH = newWidth;
			ifON = 1;
			mem = new T * [HEIGHT];
			//数组mem[HEIDHT][WIDTH];
			for (int i = 0; i < HEIGHT; i++)
			{
				mem[i] = new T[WIDTH];
			}
		}
		~SuperArray()
		{
			for (int i = 0; i < HEIGHT; i++)
			{
				delete[] mem[i];
				mem[i] = 0;
			}
			delete[] mem;
			mem = 0;
		}

		T* operator[](int a)
		{
			if (a < HEIGHT)
			{
				return mem[a];
			}
			else
			{
				return 0;
			}
		}
	};
	//位置信息
	struct Coordinate
	{
		int width = 0;
		int height = 0;
		int& x = width;
		int& y = height;
	};
	//色彩信息
	struct ColorInfo
	{
		int backGround = 0;
		int font = 7;
	};
	//一个纯虚函数的包装
	class CUFunction
	{
	public:
		//注意:表示Base对象的指针是this_base而不是this
		virtual void func(Base* this_base) = 0;
	};
	//键位信息
	class Key
	{
	public:
		static const int $UP = 72;
		static const int $DOWN = 80;
		static const int $LEFT = 75;
		static const int $RIGHT = 77;
		static const int $SPACE = 32;
		static const int $BACK_SPACE = 8;
		static const int $ESC = 27;
		static const int $ENTER = 13;
		static const int $DELETE = 83;
		static const int $INSERT = 82;
	} KEY;

	//基本类
	class Base
	{
	protected:
		cuberx::Coordinate location;
		cuberx::Coordinate size;
		string text;
		bool beChosed;
		bool canBeChosed;
		bool visible;
	public:
		Base()
		{
			text = " ";
			canBeChosed = 0;
			beChosed = 0;
			visible = 1;
		}
		Base(string newText)
		{
			text = newText;
			canBeChosed = 0;
			beChosed = 0;
			visible = 1;
		}
		Base(int width, int height, int x, int y)
		{
			location.x = x;
			location.y = y;
			size.width = width;
			size.height = height;
			canBeChosed = 0;
			beChosed = 0;
			visible = 1;
		}
		Base(int width, int height)
		{
			size.width = width;
			size.height = height;
			canBeChosed = 0;
			beChosed = 0;
			visible = 1;
		}
		Base(string newText, int width, int height, int x, int y)
		{
			text = newText;
			location.x = x;
			location.y = y;
			size.width = width;
			size.height = height;
			canBeChosed = 0;
			beChosed = 0;
			visible = 1;
		}
		Base(string newText, int width, int height)
		{
			text = newText;
			size.width = width;
			size.height = height;
			canBeChosed = 0;
			beChosed = 0;
			visible = 1;
		}
		virtual void RUN_WHEN_BE_CREATED()
		{
			return;
		}
		virtual void draw()
		{
			return;
		}
		virtual void whenBeChosed()
		{
			return;
		}
		virtual void whenStopChosed()
		{
			return;
		}
		//一般规定：1表示读取成功，0表示失败
		virtual int keyAction(int newKey)
		{
			return 1;
		}
		virtual void setText(string newText)
		{
			text = newText;
		}
		virtual bool getVisible()
		{
			return visible;
		}
		virtual void setVisible(bool ifVisible)
		{
			visible = ifVisible;
		}
		virtual void setCanBeChosed(bool ifCanBeChosed)
		{
			canBeChosed = ifCanBeChosed;
		}
		virtual bool getCanBeChosed()
		{
			return canBeChosed;
		}
	};

	//容器类
	class Container : public cuberx::Base
	{


	public:
		Container()
		{
			text = " ";
			canBeChosed = 0;
			beChosed = 0;
		}
		Container(string newText)
		{
			text = newText;
			canBeChosed = 0;
			beChosed = 0;
		}
		Container(int width, int height, int x, int y)
		{
			location.x = x;
			location.y = y;
			size.width = width;
			size.height = height;
			canBeChosed = 0;
			beChosed = 0;
		}
		Container(int width, int height)
		{
			size.width = width;
			size.height = height;
			canBeChosed = 0;
			beChosed = 0;
		}
		Container(string newText, int width, int height, int x, int y)
		{
			text = newText;
			location.x = x;
			location.y = y;
			size.width = width;
			size.height = height;
			canBeChosed = 0;
			beChosed = 0;
		}
		Container(string newText, int width, int height)
		{
			text = newText;
			size.width = width;
			size.height = height;
			canBeChosed = 0;
			beChosed = 0;
		}
		virtual int add(cuberx::Base* newObject)
		{
			return 0;
		}
		virtual int add(cuberx::Base& newObject)
		{
			return 0;
		}
		virtual void remove(cuberx::Base* newObject)
		{

		}
		virtual void remove(cuberx::Base& newObject)
		{

		}
	};

	//组件类
	class Module : public cuberx::Base
	{
	public:
		Module()
		{

		}
		
	};

}