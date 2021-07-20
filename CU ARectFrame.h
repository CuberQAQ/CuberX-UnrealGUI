#pragma once
#include "CU Basic.h"
#include <iostream>
using namespace std;

namespace cuberx {
	//0.     1.©³©¥ 2. ©·²Ý 3. ©»©¥ 4. ©¿  5. ©¥©¥ 6. ©§  7. ©×©¥ 8. ©ß©¥ 9. ©Ç©¥ 10. ©Ï  11. ©ï
	string frameChar[] = { "  ","©³©¥","©·²Ý","©»©¥","©¿ " ,"©¥©¥","©§ ","©×©¥","©ß©¥","©Ç©¥","©Ï ", "©ï" };
	//¾ØÐÎ±ß¿ò
	class ARectFrame : protected cuberx::Module
	{
	protected:
		
	public:
		
		ARectFrame()
		{
			text = " ";
		}
		ARectFrame(string newText)
		{
			text = newText;
		}
		ARectFrame(int width, int height, int x, int y)
		{
			location.x = x;
			location.y = y;
			size.width = width;
			size.height = height;
		}
		ARectFrame(int width, int height)
		{
			size.width = width;
			size.height = height;
		}
		
		ARectFrame(string newText, int width, int height, int x, int y)
		{
			text = newText;
			location.x = x;
			location.y = y;
			size.width = width;
			size.height = height;
		}
		ARectFrame(string newText, int width, int height)
		{
			text = newText;
			size.width = width;
			size.height = height;
		}
		
		void draw()
		{
			cuberx::winS.PointJump(location.y, location.x);
			cout << frameChar[1];
			for (int i = 0; i < size.width - 2; i++)
			{
				cuberx::winS.PointJump(location.y, location.x + 1 + i);
				cout << frameChar[5];
			}
			cuberx::winS.PointJump(location.y, location.x + size.width - 1);
			cout << frameChar[2];

			cuberx::winS.PointJump(location.y + size.height - 1, location.x);
			cout << frameChar[3];
			for (int i = 0; i < size.width - 2; i++)
			{
				cuberx::winS.PointJump(location.y + size.height - 1, location.x + 1 + i);
				cout << frameChar[5];
			}
			cuberx::winS.PointJump(location.y + size.height - 1, location.x + size.width - 1);
			cout << frameChar[4];

			for (int i = 0; i < size.y - 2; i++)
			{
				cuberx::winS.PointJump(location.y + 1 + i, location.x);
				cout << frameChar[6];
				cuberx::winS.PointJump(location.y + 1 + i, location.x + size.width - 1);
				cout << frameChar[6];
			}
		}

	};

}