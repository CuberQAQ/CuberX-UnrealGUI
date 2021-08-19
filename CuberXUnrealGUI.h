#ifndef $CU_STANDARD
#define $CU_STANDARD
#include<iostream>
#include<Windows.h>
#include <thread>
#include <conio.h>
#include <cmath>
#include <mmsystem.h> //导入声音头文件库
#pragma comment(lib,"winmm.lib")//导入声音的链接库
#pragma message("Creating CuberX UnrealGUI")
//关闭开始动画
#define $CU_TURN_OFF_OPENING_ACTION
using namespace std;

//版本
static const string $CU_VERSION = "Beta 0.1.2";

//预声明
namespace cuberx
{
    class MainWindow;
    class Container;
    class FPSText;
}// namespace cuberx

//Basic
namespace cuberx
{
    class Base;

    //窗口信息
    class WindowInfo {
    public:
        //获取显示句柄
        static HANDLE GetDisplayHandle()
        {
            return GetStdHandle(STD_OUTPUT_HANDLE);
        }
    };
    //窗口设置
    class WindowSetting {
    private:
    public:
        WindowSetting()
        {
            //启动信息显示
#ifndef $CU_TURN_OFF_OPENING_ACTION
            HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
            ColorSetting('F', 'C');
            SetConsoleTextAttribute(handle, (unsigned)FOREGROUND_INTENSITY | (15u + 12u * 16u));
            //设置窗口大小
            WindowArea(120, 32);
            Sleep(5);
            //隐藏光标
            setCursorVisition(false);

            PointJump(10, 0);
            cout
                << "                                                                            ========     ========   " << endl
                << "                         ======              ==                                ====       ====      " << endl
                << "                       ===    ==             ==          =====     == =====      ====   ====        " << endl
                << "                      ===         ==    ==  ========   ==    ===  =====   ==       =======          " << endl
                << "                      ===         ==    ==  ===   ===  ========    ==              =======          " << endl
                << "                       ===    ==  ==    ==  ===   ===  ==      =   ==            ====   ====        " << endl
                << "                         ======    ======    =======     ======     =          ====       ====      " << endl
                << "                                                                            ========     ========   " << endl
                << "                                                                                                    " << endl
                << "                                                                                                    " << endl
                << "                                                                                                    " << endl
                << "                                                                                                    " << endl
                << "                                                                                                    " << endl
                << "                                                                                                    " << endl
                << "                                                                                                    " << endl
                << "                                                                                                    ";
            PointJump(18, 35);
            cout << "========= CuberX UnrealGUI (dev) =========";
            PointJump(31, 0);
            colorOut("VERSION= ", 7, 12);
            colorOut($CU_VERSION, 7, 12);
            PointJump(31, 127);
            Sleep(800);
            system("cls");
            PointJump(0, 0);
            ColorSetting('7', '0');
            SetConsoleTextAttribute(handle, (unsigned)FOREGROUND_INTENSITY | 7u);
            //显示光标
            setCursorVisition(true);
#endif
            //设置窗口大小
            WindowArea(128, 32);
            Sleep(5);
        }
        //窗口大小
        static int WindowArea(short w, short h, bool ifcls = false)
        {
            HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
            COORD size  = {w, h};
            SetConsoleScreenBufferSize(hOut, size);
            SMALL_RECT rc = {0, 0, static_cast<SHORT>(w - 1), static_cast<SHORT>(h - 1)};
            SetConsoleWindowInfo(hOut, 1, &rc);
            if(ifcls == 1)
            {
                system("cls");
            }
            return 0;
        }
        //锁定窗口大小
        static int LockWindow()
        {
            HWND hWnd = GetConsoleWindow();//获得cmd窗口句柄
            RECT rc;
            GetWindowRect(hWnd, &rc);//获得cmd窗口对应矩形
            //改变cmd窗口风格
            SetWindowLongPtr(hWnd, GWL_STYLE, (unsigned)GetWindowLong(hWnd, GWL_STYLE) & ~(unsigned)WS_THICKFRAME & ~(unsigned)WS_MAXIMIZEBOX & ~(unsigned)WS_MINIMIZEBOX);
            //因为风格涉及到边框改变，必须调用SetWindowPos，否则无效果
            SetWindowPos(hWnd, nullptr, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, 0);
            return 0;
        }
        //设置全局显示颜色
        static int ColorSetting(char FontsColor = '7', char WindowColor = '0')
        {
            char SendStr[] = "color xx";
            char *p_ch     = SendStr + 6;
            *p_ch          = WindowColor;
            *(++p_ch)      = FontsColor;
            system(SendStr);
            return 0;
        }
        //光标跳转
        static void PointJump(SHORT pawnH, SHORT pawnW, HANDLE handle = WindowInfo::GetDisplayHandle())
        {
            COORD PointPawn;
            PointPawn.X = pawnW;//宽坐标
            PointPawn.Y = pawnH;//高坐标
            SetConsoleCursorPosition(handle, {static_cast<SHORT>(pawnW), static_cast<SHORT>(pawnH)});
        }

        /*彩色输出
        0 = 黑色 8 = 灰色
        1 = 蓝色 9 = 淡蓝色
        2 = 绿色 10 = 淡绿色
        3 = 浅蓝色 11 = 淡浅绿色
        4 = 红色 12 = 淡红色
        5 = 紫色 13 = 淡紫色
        6 = 黄色 14 = 淡黄色
        7 = 白色 15 = 亮白色
        https://blog.csdn.net/qq_42885747/article/details/103835671?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.control&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.control
        */
        static void colorOut(const string &str, int FontsColorInt, int WindowColorInt)
        {
            HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(handle, (unsigned)FOREGROUND_INTENSITY | ((unsigned)FontsColorInt + (unsigned)WindowColorInt * 16u));
            cout << str;
            SetConsoleTextAttribute(handle, (unsigned)FOREGROUND_INTENSITY | 7u);
        }

        //显示/隐藏光标
        static void SetCursorVisible(bool visible)
        {
            HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_CURSOR_INFO CursorInfo;
            GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
            CursorInfo.bVisible = visible;            //隐藏控制台光标
            SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
        }
    };
    static WindowSetting winS;

    //可以变量设置大小的数组（内存安全需注意）
    template<class T>
    class SuperArray {
    private:
        T **mem;
        int HEIGHT;
        int WIDTH;
        bool ifON;

    public:
        SuperArray()
        {
            HEIGHT = 0;
            WIDTH  = 0;
            ifON   = false;
        }
        SuperArray(int height, int width)
        {
            HEIGHT = height;
            WIDTH  = width;
            ifON   = true;
            mem    = new T *[HEIGHT];
            //数组mem[HEIGHT][WIDTH];
            for(int i = 0; i < HEIGHT; i++)
            {
                mem[i] = new T[WIDTH];
            }
        }
        void reset(int newHeight, int newWidth)
        {
            if(ifON == 1)
            {
                for(int i = 0; i < HEIGHT; i++)
                {
                    delete[] mem[i];
                    mem[i] = 0;
                }
                delete[] mem;
                mem = 0;
            }
            HEIGHT = newHeight;
            WIDTH  = newWidth;
            ifON   = true;
            mem    = new T *[HEIGHT];
            //数组mem[HEIGHT][WIDTH];
            for(int i = 0; i < HEIGHT; i++)
            {
                mem[i] = new T[WIDTH];
            }
        }
        ~SuperArray()
        {
            for(int i = 0; i < HEIGHT; i++)
            {
                delete[] mem[i];
                mem[i] = nullptr;
            }
            delete[] mem;
            mem = nullptr;
        }

        T *operator[](int a)
        {
            if(a < HEIGHT)
            {
                return mem[a];
            }
            else
            {
                return 0;
            }
        }
    };
    template<class T>
        class SuperArray1 {
        private:
            T *mem;
            int LENGTH;
            bool ifON;

        public:
            SuperArray1()
            {
                LENGTH = 0;
                ifON   = false;
            }
            SuperArray1(int length)
            {
                LENGTH = length;
                ifON   = true;
                mem    = new T[LENGTH];
            }
            void reset(int newLength)
            {
                if(ifON)
                {
                    delete[] mem;
                    mem = nullptr;
                }
                LENGTH = newLength;
                ifON   = true;
                mem    = new T [LENGTH];
            }
            ~SuperArray1()
            {
                delete[] mem;
                mem = nullptr;
            }

            T& operator[](int a)
            {
                return mem[a];
            }
        };
    //指针工具
    class PointerTool {
    public:
        template<class T>
        inline static T P2TA2(T **p, UINT width, UINT y, UINT x)
        {
            return *((T *)p + y * width + x);
        }
        template<class T>
        inline static T P2TA2(SuperArray<T> *p, UINT width, UINT y, UINT x)
        {
            return (*p)[y][x];
        }
        template<class T>
        inline static T P2TA2(SuperArray<T> p, UINT width, UINT y, UINT x)
        {
            return p[y][x];
        }
    };
    //位置信息
    struct Coordinate {
        short width  = 0;
        short height = 0;
        short &x     = width;
        short &y     = height;
        Coordinate(short x, short y)
        {
            width  = x;
            height = y;
        }
        Coordinate() = default;
    };
    /* 色彩信息
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
    struct ColorInfo {
        //此处char是为了节省内存
        char backGround = 0;
        char font       = 7;
    };
    //一个纯虚函数的包装
    class CUFunction {
    public:
        //注意:表示Base对象的指针是this_base而不是this
        virtual void func(Base *this_base) = 0;
    };
    //任务信息
    class CUTask {
    private:
        unsigned short index;           //序号
        unsigned int tag;               //标签
        bool enable;                    //是否启用
        void (*runFunc)(cuberx::Base *);//运行接口函数
        cuberx::Base *RunClass;         //运行接口对象
        DWORD CountDownTick;            //剩余时刻
    public:
        CUTask()
        {
            index         = 0;
            tag           = 0;
            runFunc       = nullptr;
            CountDownTick = 0;
            RunClass      = nullptr;
            enable        = false;
        }


        void setCountDownTick(DWORD newCountDownTick)
        {
            CountDownTick = newCountDownTick;
        }
        DWORD getCountDownTick() const
        {
            return CountDownTick;
        }
        void setIndex(unsigned short newIndex)
        {
            this->index = newIndex;
        }
        unsigned short getIndex() const
        {
            return index;
        }
        void setTag(unsigned int newTag)
        {
            tag = newTag;
        }
        unsigned int getTag() const
        {
            return tag;
        }
        void setRunFunc(void (*newRunFunc)(cuberx::Base *))
        {
            runFunc = newRunFunc;
        }
        bool getEnable() const
        {
            return enable;
        }
        void setEnable(bool ifEnable)
        {
            enable = ifEnable;
        }
        //获取运行函数前者为方法本身，(cuberx::Base*)为返回的函数的参数
        void (*getRunFunc())(cuberx::Base *)
        {
            return runFunc;
        }
        void setRunClass(cuberx::Base *newRunClass)
        {
            RunClass = newRunClass;
        }
        //获取目标对象的指针
        cuberx::Base *getRunClass()
        {
            return RunClass;
        }
        //将剩余时刻减少1
        void countDown()
        {
            CountDownTick -= 1;
        }

        //运行该任务
        void run()
        {
            //运行绑定的函数
            runFunc(RunClass);
        }
        //清空任务
        int reset()
        {
            index         = 0;
            tag           = 0;
            runFunc       = nullptr;
            RunClass      = nullptr;
            CountDownTick = 0;
            setEnable(false);
            return 0;
        }
        //设置任务
        int set(cuberx::Base *NewRunClass, int NewTag, void (*NewRun)(cuberx::Base *) = nullptr, DWORD NewCountDownTick = 0, bool ifEnable = true)
        {
            tag           = NewTag;
            runFunc       = NewRun;
            RunClass      = NewRunClass;
            CountDownTick = NewCountDownTick;
            enable        = ifEnable;
            return 0;
        }
    };
    //键位信息
    class Key {
    public:
        static const int $UP         = 72;
        static const int $DOWN       = 80;
        static const int $LEFT       = 75;
        static const int $RIGHT      = 77;
        static const int $SPACE      = 32;
        static const int $BACK_SPACE = 8;
        static const int $ESC        = 27;
        static const int $ENTER      = 13;
        static const int $DELETE     = 83;
        static const int $INSERT     = 82;
        static const int $TAB        = 3;
    };
    //键位任务
    class KeyTask {
    private:
        int key{};
        cuberx::Base *this_base{};
        int (*run)(cuberx::Base *){};

    public:
        KeyTask() = default;
        KeyTask(int key, cuberx::Base *this_base, int (*run)(cuberx::Base *))
        {
            this->key       = key;
            this->this_base = this_base;
            this->run       = run;
        }
        int Run()
        {
            if(run != nullptr)
            {
                return run(this_base);
            }
        }
        void Reset()
        {
            this->key       = 0;
            this->this_base = nullptr;
            this->run       = nullptr;
        }
        void Set(int key, cuberx::Base *this_base, int (*run)(cuberx::Base *))
        {
            this->key       = key;
            this->this_base = this_base;
            this->run       = run;
        }
        bool Empty()
        {
            if(key == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        int GetKey()
        {
            return key;
        }
        void SetKey(int newKey)
        {
            key = newKey;
        }
        cuberx::Base *GetThisBase()
        {
            return this_base;
        }
        void SetThisBase(cuberx::Base *newThisBase)
        {
            this_base = newThisBase;
        }
        int (*GetRun())(cuberx::Base *)//返回值为函数指针的方法
        {
            return run;
        }
    };
    //字符串工具
    class StringTool {
    public:
        static string WCharToString(wchar_t *firstWChar)
        {
            //表示为单字节时长度
            int charLength  = WideCharToMultiByte(CP_OEMCP, 0, firstWChar, (int)wcslen(firstWChar), nullptr, 0, nullptr, nullptr);
            char *finalChar = new char[(long long)charLength + (long long)1];
            //转换
            WideCharToMultiByte(CP_OEMCP, 0, firstWChar, (int)wcslen(firstWChar), finalChar, charLength, nullptr, nullptr);
            finalChar[charLength] = '\0';
            string result         = finalChar;
            delete[] finalChar;
            return result;
        }
        //注意释放内存
        static wchar_t *StringToWchar(const string &firstString)
        {
            const char *firstChar = firstString.c_str();
            //第一次调用返回转换后的字符串长度，用于确认为wchar_t*开辟多大的内存空间
            int WCharLeng    = MultiByteToWideChar(CP_OEMCP, 0, firstChar, (int)strlen(firstChar) + 1, nullptr, 0);
            auto *finalWChar = new wchar_t[WCharLeng];
            //第二次调用将单字节字符串转换成双字节字符串
            MultiByteToWideChar(CP_OEMCP, 0, firstChar, (int)strlen(firstChar) + 1, finalWChar, WCharLeng);
            return finalWChar;
        }
    };

    //基本类
    class Base {
    protected:
        cuberx::Coordinate location{};
        cuberx::Coordinate size{};
        cuberx::Coordinate offset{};
        cuberx::MainWindow *fatherMainWindow{};
        cuberx::Container *fatherContainer{};
        string text{};
        bool beChosed{};
        bool canBeChosed{};
        bool bVisible{};

    public:
        Base()
        {
            text             = " ";
            canBeChosed      = false;
            beChosed         = false;
            bVisible         = true;
            fatherMainWindow = nullptr;
        }
        explicit Base(const string &newText)
        {
            text             = newText;
            canBeChosed      = false;
            beChosed         = false;
            bVisible         = true;
            fatherMainWindow = nullptr;
        }
        Base(short width, short height, short x, short y)
        {
            location.x       = x;
            location.y       = y;
            size.width       = width;
            size.height      = height;
            canBeChosed      = false;
            beChosed         = false;
            bVisible         = true;
            fatherMainWindow = nullptr;
        }
        Base(short width, short height)
        {
            size.width       = width;
            size.height      = height;
            canBeChosed      = false;
            beChosed         = false;
            bVisible         = true;
            fatherMainWindow = nullptr;
        }
        Base(const string &newText, short width, short height, short x, short y)
        {
            text             = newText;
            location.x       = x;
            location.y       = y;
            size.width       = width;
            size.height      = height;
            canBeChosed      = false;
            beChosed         = false;
            bVisible         = true;
            fatherMainWindow = nullptr;
        }
        Base(const string &newText, short width, short height)
        {
            text             = newText;
            size.width       = width;
            size.height      = height;
            canBeChosed      = false;
            beChosed         = false;
            bVisible         = true;
            fatherMainWindow = nullptr;
        }
        virtual void draw(short offsetX, short offsetY)
        {
        }
        virtual void drawNull(short offsetX, short offsetY)
        {
            string null_str{};
            for(int i = 0; i < size.x; i++)
            {
                null_str += " ";
            }
            for(int i = 0; i < size.y; i++)
            {
                WindowSetting::PointJump(short(location.y + offsetY + i), short(location.x + offsetX));
                cout << null_str;
            }
        }
        virtual void whenBeChosed()
        {
            beChosed = true;
        }
        virtual void whenStopChosed()
        {
            beChosed = false;
        }
        //一般规定：1表示读取成功，0表示失败
        virtual int keyAction(int newKey)
        {
            return 0;
        }
        virtual void setText(const string &newText)
        {
            text = newText;
        }
        virtual string getText()
        {
            return text;
        }
        virtual bool getVisible()
        {
            return bVisible;
        }
        virtual void setVisible(bool ifVisible)
        {
            bVisible = ifVisible;
        }
        virtual void setSize(short width, short height)
        {
            size.width  = width;
            size.height = height;
        }
        virtual Coordinate getSize()
        {
            return size;
        }
        virtual void setLocation(short x, short y)
        {
            location.x = x;
            location.y = y;
        }
        virtual Coordinate getLocation()
        {
            return location;
        }
        virtual void setCanBeChosed(bool ifCanBeChosed)
        {
            canBeChosed = ifCanBeChosed;
        }
        virtual bool getCanBeChosed()
        {
            return canBeChosed;
        }
        virtual void setBeChosed(bool ifBeChosed)
        {
            beChosed = ifBeChosed;
            if(ifBeChosed)
            {
                whenBeChosed();
            }
            else
            {
                whenStopChosed();
            }
        }
        virtual bool getBeChosed()
        {
            return beChosed;
        }
        //设置所属主窗口信息
        virtual void setFatherMainWindow(cuberx::MainWindow *newFatherMainWindow)
        {
            fatherMainWindow = newFatherMainWindow;
        }
        //重置所属主窗口信息
        virtual void resetFatherMainWindow()
        {
            fatherMainWindow = nullptr;
        }
        //获取所属主窗口
        virtual cuberx::MainWindow *getFatherMainWindow()
        {
            return fatherMainWindow;
        }
        //设置所属容器信息
        virtual void setFatherContainer(cuberx::Container *newFatherContainer)
        {
            fatherContainer = newFatherContainer;
        }
        //重置所属容器信息
        virtual void resetFatherContainer()
        {
            fatherContainer = nullptr;
        }
        //获取所属容器
        virtual cuberx::Container *getFatherContainer()
        {
            return fatherContainer;
        }
        //设置绘制偏移量
        virtual void setOffset(short offsetX, short offsetY)
        {
            this->offset.x = offsetX;
            this->offset.y = offsetY;
        }
        //获取绘制偏移量
        virtual cuberx::Coordinate getOffset()
        {
            return offset;
        }
    };

    //容器类
    class Container : public cuberx::Base {
    protected:
        int nowChosingObject;

    public:
        Container()
        {
            text             = " ";
            canBeChosed      = false;
            beChosed         = false;
            nowChosingObject = 0;
        }
        explicit Container(const string &newText)
        {
            text             = newText;
            canBeChosed      = false;
            beChosed         = false;
            nowChosingObject = 0;
        }
        Container(short width, short height, short x, short y)
        {
            location.x       = x;
            location.y       = y;
            size.width       = width;
            size.height      = height;
            canBeChosed      = false;
            beChosed         = false;
            nowChosingObject = 0;
        }
        Container(short width, short height)
        {
            size.width       = width;
            size.height      = height;
            canBeChosed      = false;
            beChosed         = false;
            nowChosingObject = 0;
        }
        Container(const string &newText, short width, short height, short x, short y)
        {
            text             = newText;
            location.x       = x;
            location.y       = y;
            size.width       = width;
            size.height      = height;
            canBeChosed      = false;
            beChosed         = false;
            nowChosingObject = 0;
        }
        Container(const string &newText, short width, short height)
        {
            text             = newText;
            size.width       = width;
            size.height      = height;
            canBeChosed      = false;
            beChosed         = false;
            nowChosingObject = 0;
        }
        virtual int add(cuberx::Base *newObject)
        {
            return 0;
        }
        virtual int add(cuberx::Base &newObject)
        {
            return 0;
        }
        virtual void remove(cuberx::Base *newObject)
        {
        }
        virtual void remove(cuberx::Base &newObject)
        {
        }
        virtual int getNowChosingObject()
        {
            return nowChosingObject;
        }
        //最好重写
        virtual void setNowChosingObject(int newChosingObject)
        {
            nowChosingObject = newChosingObject;
        }
        //最好重写
        virtual void exit()
        {

        }
    };

    //组件类
    class Module : public cuberx::Base {
    public:
        Module() = default;
    };
}// namespace cuberx

//MainWindow
#define $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT 256
#define $CU_MAINWINDOW_TOTAL_TASKS_COUNT 256
#define $CU_MAINWINDOW_TOTAL_G_KEYACTION_BEFORE_COUNT 32
#define $CU_MAINWINDOW_TOTAL_G_KEYACTION_AFTER_COUNT 32
namespace cuberx
{

    class MainWindow : public cuberx::Container {
    protected:
        string title;              //窗口标题(反映在控制台上)
        bool enable;               //是否启用
        bool useTickListener;      //是否使用帧率管理器
        bool checkKey;             //是否检测键位
        ULONGLONG lastTestTickTime;//上一次检测(运行)帧时间
        ULONGLONG timePerTick;     //帧率时间(0为无限制 单位为毫秒)
        int tickListenerMode;      //检测模式(1为不足则补齐,2为不足则补齐 且 超时则多次执行)
        int nowChosingObject;      //目前选择的CU组件(-1表示无)
        cuberx::Base *objects[$CU_MAINWINDOW_TOTAL_OBJECTS_COUNT]{};
        cuberx::CUTask tasks[$CU_MAINWINDOW_TOTAL_TASKS_COUNT];
        cuberx::KeyTask keyTasksBefore[$CU_MAINWINDOW_TOTAL_G_KEYACTION_BEFORE_COUNT]{};
        cuberx::KeyTask keyTasksAfter[$CU_MAINWINDOW_TOTAL_G_KEYACTION_AFTER_COUNT]{};
        thread *tickListenerThread;
        bool threadEnable;

    public:
        int returnInt;
        MainWindow()
        {
            returnInt = 0;
            setSize(0, 0);
            title  = "CuberX UnrealGUI  (" + $CU_VERSION + ")";
            enable = false;
            for(auto &object: objects)
            {
                object = nullptr;
            }
            for(int i = 0; i < $CU_MAINWINDOW_TOTAL_TASKS_COUNT; i++)
            {
                tasks[i].setIndex(i);
            }
            timePerTick        = 0;
            tickListenerMode   = 2;
            nowChosingObject   = 0;
            checkKey           = true;
            tickListenerThread = nullptr;
            threadEnable       = false;
            useTickListener    = true;
            lastTestTickTime   = 0;
        }
        explicit MainWindow(const string &title, short new_size_width = 0, short new_size_height = 0, bool enable = false) :
            Container(new_size_width, new_size_height)
        {
            returnInt = 0;
            setSize(new_size_width, new_size_height);
            this->title  = title;
            this->enable = enable;
            for(auto &object: objects)
            {
                object = nullptr;
            }
            timePerTick      = 0;
            tickListenerMode = 2;
            nowChosingObject = 0;
            for(int i = 0; i < $CU_MAINWINDOW_TOTAL_TASKS_COUNT; i++)
            {
                tasks[i].setIndex(i);
            }
            checkKey           = true;
            tickListenerThread = nullptr;
            threadEnable       = false;
            useTickListener    = true;
            lastTestTickTime   = 0;
        }
        MainWindow(short new_size_width, short new_size_height, bool enable = false) :
            Container(new_size_width, new_size_height)
        {
            returnInt = 0;
            setSize(new_size_width, new_size_height);
            this->title  = "CuberX UnrealGUI  (" + $CU_VERSION + ")";
            this->enable = enable;
            for(auto &object: objects)
            {
                object = nullptr;
            }
            timePerTick      = 0;
            tickListenerMode = 2;
            nowChosingObject = 0;
            for(int i = 0; i < $CU_MAINWINDOW_TOTAL_TASKS_COUNT; i++)
            {
                tasks[i].setIndex(i);
            }
            checkKey           = true;
            tickListenerThread = nullptr;
            threadEnable       = false;
            useTickListener    = true;
            lastTestTickTime   = 0;
        }
        ~MainWindow()
        {
            if(tickListenerThread != nullptr)
            {
                enable = false;
                Sleep(getTimePerTick() + 10);
                // delete tickListenerThread;
                tickListenerThread = nullptr;
            }
        }
        //添加对象
        int add(cuberx::Base *newObject) override
        {
            for(int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
            {
                if(objects[i] == nullptr)
                {
                    objects[i] = newObject;
                    newObject->setFatherMainWindow(this);
                    return i;
                }
            }
            return -1;
        }
        int add(cuberx::Base &newObject) override
        {
            for(int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
            {
                if(objects[i] == nullptr)
                {
                    objects[i] = &newObject;
                    newObject.setFatherMainWindow(this);
                    return i;
                }
            }
            return -1;
        }
        MainWindow &operator<<(cuberx::Base *newObject)
        {
            for(auto &object: objects)
            {
                if(object == nullptr)
                {
                    object = newObject;
                    newObject->setFatherMainWindow(this);
                    return *this;
                }
            }
            cout << "[CuberX UnrealGUI]No Enough Place For The New Object. Please Change #define $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT.";
            return *this;
        }
        MainWindow &operator<<(cuberx::Base &newObject)
        {
            for(auto &object: objects)
            {
                if(object == nullptr)
                {
                    object = &newObject;
                    newObject.setFatherMainWindow(this);
                    return *this;
                }
            }
            cout << "[CuberX UnrealGUI]No Enough Place For The New Object. Please Change #define CU_MAINWINDOW_TOTAL_OBJECTS_COUNT.";
            return *this;
        }
        MainWindow &operator+=(cuberx::Base *newObject)
        {
            for(auto &object: objects)
            {
                if(object == nullptr)
                {
                    object = newObject;
                    newObject->setFatherMainWindow(this);
                    return *this;
                }
            }
            cout << "[CuberX UnrealGUI]No Enough Place For The New Object. Please Change #define $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT.";
            return *this;
        }
        MainWindow &operator+=(cuberx::Base &newObject)
        {
            for(auto &object: objects)
            {
                if(object == nullptr)
                {
                    object = &newObject;
                    newObject.setFatherMainWindow(this);
                    return *this;
                }
            }
            cout << "[CuberX UnrealGUI]No Enough Place For The New Object. Please Change #define CU_MAINWINDOW_TOTAL_OBJECTS_COUNT.";
            return *this;
        }

        //移除对象
        void remove(cuberx::Base *removeObject) override
        {
            if(removeObject != nullptr)
            {
                for(auto &object: objects)
                {
                    if(object == removeObject)
                    {
                        object->resetFatherMainWindow();
                        object = nullptr;
                        draw();
                    }
                }
            }
        }
        void remove(cuberx::Base &removeObject) override
        {
            cuberx::Base *pRemoveObject = &removeObject;
            for(auto &object: objects)
            {
                if(object == pRemoveObject)
                {
                    object->resetFatherMainWindow();
                    object = nullptr;
                    draw();
                }
            }
        }
        MainWindow &operator>>(cuberx::Base *removeObject)
        {
            if(removeObject != nullptr)
            {
                for(auto &object: objects)
                {
                    if(object == removeObject)
                    {
                        object->resetFatherMainWindow();
                        object = nullptr;
                        draw();
                    }
                }
            }
            return *this;
        }
        MainWindow &operator>>(cuberx::Base &removeObject)
        {
            cuberx::Base *pRemoveObject = &removeObject;
            for(auto &object: objects)
            {
                if(object == pRemoveObject)
                {
                    object->resetFatherMainWindow();
                    object = nullptr;
                    draw();
                }
            }

            return *this;
        }
        MainWindow &operator-=(cuberx::Base *removeObject)
        {
            if(removeObject != nullptr)
            {
                for(auto &object: objects)
                {
                    if(object == removeObject)
                    {
                        object->resetFatherMainWindow();
                        object = nullptr;
                        draw();
                    }
                }
            }
            return *this;
        }
        MainWindow &operator-=(cuberx::Base &removeObject)
        {
            cuberx::Base *pRemoveObject = &removeObject;
            for(auto &object: objects)
            {
                if(object == pRemoveObject)
                {
                    object->resetFatherMainWindow();
                    object = nullptr;
                    draw();
                }
            }

            return *this;
        }

        virtual thread *setEnable(bool ifEnable)
        {
            enable = ifEnable;
            if(ifEnable)
            {
                //设置窗口大小
                if(getSize().height == 0 || getSize().width == 0)
                {//某一尺寸为零
                }
                else
                {
                    //正常尺寸(未考虑负数)  设置窗口大小 并 清屏
                    cuberx::WindowSetting::WindowArea(getSize().width, getSize().height, true);
                    //延迟，防止卡顿
                    Sleep(10);
                }

                //标题显示
                char setTitleString[256] = "title ";
                strcat(setTitleString, title.c_str());
                system(setTitleString);

                //隐藏光标
                cuberx::WindowSetting::SetCursorVisible(false);

                //子组件全部绘制
                draw();

                //根据useTickListener 启用帧率管理器线程
                if(useTickListener)
                {
                    if(this->tickListenerThread != nullptr)
                    {
                        enable = false;
                        Sleep(getTimePerTick() + 1000);
                        // delete this->tickListenerThread;
                        enable                   = true;
                        this->tickListenerThread = nullptr;
                    }
                    auto *tickListenerThread = new thread(tickListener, this);
                    this->tickListenerThread = tickListenerThread;
                    return tickListenerThread;
                }
            }
            else
            {
                if(tickListenerThread != nullptr)
                {
                    Sleep(getTimePerTick() + 1000);
                    // delete tickListenerThread;
                    tickListenerThread = nullptr;
                }
                setLastTestTickTime(0);
                //显示光标
                cuberx::WindowSetting::SetCursorVisible(true);
            }
            return nullptr;
        }
        virtual bool getEnable()
        {
            return enable;
        }
        void draw(int drawObjectIndex = -1)
        {
            if(drawObjectIndex <= -1)
            {
                for(auto &object: objects)
                {
                    if(object != nullptr)
                    {
                        if(object->getVisible())
                        {
                            object->draw(object->getOffset().x, object->getOffset().y);
                        }
                    }
                }
            }
            else
            {
                objects[drawObjectIndex]->draw(objects[drawObjectIndex]->getOffset().x, objects[drawObjectIndex]->getOffset().y);
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
            if(enable)
            {
                //刷新状态，即重新启用
                setEnable(true);
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
        int getNowChosingObject() override
        {
            return nowChosingObject;
        }
        void setNowChosingObject(int newChosingObject) override
        {
            if(objects[newChosingObject] == nullptr)
            {
                cout << "[CuberX]Error:The newChosingObject Has Not Be Found!";
            }
            else
            {
                if(objects[nowChosingObject] != nullptr)
                {
                    objects[nowChosingObject]->whenStopChosed();
                }
                objects[newChosingObject]->whenBeChosed();
                nowChosingObject = newChosingObject;
            }
        }

        //添加全局键位任务
        void addGKeyActionBefore(const cuberx::KeyTask &newKeyAction)
        {
            for(auto &i: keyTasksBefore)
            {
                if(i.Empty())
                {
                    i = newKeyAction;
                    return;
                }
            }
        }
        void addGKeyActionBefore(int key, cuberx::Base *this_base, int (*run)(cuberx::Base *))
        {
            for(auto &i: keyTasksBefore)
            {
                if(i.Empty())
                {
                    i.Set(key, this_base, run);
                    return;
                }
            }
        }
        void addGKeyActionAfter(const cuberx::KeyTask &newKeyAction)
        {
            for(auto &i: keyTasksAfter)
            {
                if(i.Empty())
                {
                    i = newKeyAction;
                    return;
                }
            }
        }
        void addGKeyActionAfter(int key, cuberx::Base *this_base, int (*run)(cuberx::Base *))
        {
            for(auto &i: keyTasksAfter)
            {
                if(i.Empty())
                {
                    i.Set(key, this_base, run);
                    return;
                }
            }
        }

        //根据索引获取容器内对象
        virtual cuberx::Base *getObjectFromIndex(int index)
        {
            if(index >= 0 || index < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT)
            {
                return objects[index];
            }
            else
            {
                return nullptr;
            }
        }
        virtual cuberx::Base *operator[](int index)
        {
            if(index >= 0 || index < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT)
            {
                return objects[index];
            }
            else
            {
                return nullptr;
            }
        }

        //根据索引获取任务信息
        virtual cuberx::CUTask &getTaskInfoFromIndex(int index)
        {
            return tasks[index];
        }
        //根据标签获取任务信息
        virtual cuberx::CUTask *getTaskInfoFromTag(int tag)
        {
            for(auto &i: tasks)
            {
                if(i.getTag() == tag)
                {
                    return &i;
                }
            }
            return nullptr;
        }


        //分配空任务
        virtual int getNewTask()
        {

            //遍历寻找
            for(int i = 0; i < $CU_MAINWINDOW_TOTAL_TASKS_COUNT; i++)
            {
                //寻找到空位（未启用的任务）
                if(tasks[i].getEnable() == 0)
                {
                    //重置该任务
                    tasks[i].reset();
                    //返回该任务的索引
                    return i;
                }
            }

            //无新任务
            return -1;
        }
        //设置任务
        virtual void setTask(int taskIndex, cuberx::Base *NewRunClass, int NewTag, void (*NewRun)(cuberx::Base *), DWORD NewCountDownTick, bool ifEnable = true)
        {
            tasks[taskIndex].set(NewRunClass, NewTag, NewRun, NewCountDownTick, ifEnable);
        }

        //帧率管理器（会被作为子线程生成）
        static void
        tickListener(MainWindow *this_MainWindow)
        {
            while(true)
            {
                //检测是否有关闭
                if(this_MainWindow->getUseTickListener() == 0 || this_MainWindow->getEnable() == 0)
                {
                    return;
                }

                //校正帧率时刻(前者不为零说明有限制,后者不为零说明不是第一次执行)
                if(this_MainWindow->getTimePerTick() != 0)
                {
                    if(this_MainWindow->getLastTestTickTime() != 0)
                    {
                        ULONGLONG pastTime = GetTickCount() - this_MainWindow->getLastTestTickTime();
                        //检测模式(1为不足则补齐,2为不足则补齐 且 超时则多次执行(慎用))
                        switch(this_MainWindow->getTickListenerMode())
                        {
                        case 1:
                        {
                            if(pastTime < this_MainWindow->getTimePerTick())
                            {
                                Sleep((DWORD)this_MainWindow->getTimePerTick() - 1 - (DWORD)pastTime);
                            }
                            this_MainWindow->setLastTestTickTime(GetTickCount());
                        }
                        break;
                        case 2:
                        {
                            if(pastTime <= this_MainWindow->getTimePerTick())
                            {
                                //不足(补齐)|恰好(补0)  (并执行)
                                Sleep((DWORD)this_MainWindow->getTimePerTick() - (DWORD)pastTime);
                                this_MainWindow->setLastTestTickTime(GetTickCount());
                            }
                            else
                            {
                                //超时(执行并调后[上次时间])
                                this_MainWindow->setLastTestTickTime(this_MainWindow->getLastTestTickTime() + this_MainWindow->getTimePerTick() - 1);
                            }
                        }
                        break;
                        default:
                            cout << "\n[CuberX]Error:Unknown TickListenerMode";
                            break;
                        }
                    }
                    else
                    {
                        this_MainWindow->setLastTestTickTime(GetTickCount());
                    }
                }


                //检测键位
                if(this_MainWindow->getCheckKey())
                {
                    if(_kbhit())
                    {
                        int nowInputKey = _getch();
                        this_MainWindow->keyListener(nowInputKey);
                    }
                }

                //任务检测(0为无限运行)
                for(int i = 0; i < $CU_MAINWINDOW_TOTAL_TASKS_COUNT; i++)
                {
                    cuberx::CUTask &nowTask = this_MainWindow->getTaskInfoFromIndex(i);
                    //若任务启用
                    if(nowTask.getEnable())
                    {
                        //已到达时间
                        if(nowTask.getCountDownTick() <= 1)
                        {
                            //运行任务
                            nowTask.run();
                            //重置任务
                            if(nowTask.getCountDownTick() == 1)
                            {
                                nowTask.reset();
                            }
                        }
                        //未到达时间(0表示无限执行(每时每刻)！2及以上视为未到达)
                        else if(nowTask.getCountDownTick() > 1)
                        {
                            //将剩余时刻减少1
                            nowTask.countDown();
                        }
                    }
                }
            }
        }
        /* 键盘监听（一帧内）
         * [0为无响应,1为执行成功]
         */
        virtual void keyListener(int newKey)
        {

            int result = 0;

            //全局键位(优先响应)
            for(auto &i: keyTasksBefore)
            {
                if(i.GetKey() == newKey)
                {
                    //寻找完成
                    result = i.Run();
                    if(result == 1)
                    {
                        return;
                    }
                }
            }


            //目前选中成员
            if(getNowChosingObject() >= 0)
            {
                if(objects[getNowChosingObject()] != nullptr)
                {
                    result = objects[getNowChosingObject()]->keyAction(newKey);
                    if(result == 1)
                    {
                        return;
                    }
                }
            }
            //遍历其它成员
            /*
            for(int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
            {
                if(objects[i] != nullptr && i != getNowChosingObject())
                {
                    result = objects[i]->keyAction(newKey);
                    if(result == 1)
                    {
                        return;
                    }
                }
            }
             */
            //全局键位(滞后响应)
            switch(newKey)
            {
            //上(左)翻
            case cuberx::Key::$UP:
            case cuberx::Key::$LEFT:
            {
                //遍历前面部分（倒序）
                if(getNowChosingObject() != 0)
                {
                    for(int i = getNowChosingObject() - 1; i >= 0; i--)
                    {
                        if(objects[i] != nullptr && objects[i]->getCanBeChosed() == 1)
                        {
                            setNowChosingObject(i);
                            return;
                        }
                    }
                }
                //遍历全部（在上面代码块未成功情况下）（倒序）
                for(int i = $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT - 1; i >= 0; i--)
                {
                    if(objects[i] != nullptr && objects[i]->getCanBeChosed() == 1)
                    {
                        setNowChosingObject(i);
                        return;
                    }
                }
            }
            break;

            //下(右)翻
            case cuberx::Key::$DOWN://Jump
            case cuberx::Key::$TAB://Jump
            case cuberx::Key::$RIGHT:
            {
                //遍历剩余部分（正序）
                if(getNowChosingObject() != $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT - 1)
                {
                    for(int i = 1 + getNowChosingObject(); i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
                    {
                        if(objects[i] != nullptr && objects[i]->getCanBeChosed() == 1)
                        {
                            setNowChosingObject(i);
                            return;
                        }
                    }
                }
                //遍历全部（在上面代码块未成功情况下）（正序）
                for(int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
                {
                    if(objects[i] != nullptr && objects[i]->getCanBeChosed() == 1)
                    {
                        setNowChosingObject(i);
                        return;
                    }
                }
            }
            break;
            default:
                for(auto &i: keyTasksAfter)
                {
                    if(i.GetKey() == newKey)
                    {
                        //寻找完成
                        result = i.Run();
                        if(result == 1)
                        {
                            return;
                        }
                    }
                }
                break;
            }
        }
    };

}// namespace cuberx

//ARectFrame
namespace cuberx
{
    // 0.     1.┏━ 2. ┓草 3. ┗━ 4. ┛  5. ━━ 6. ┃  7. ┳━ 8. ┻━ 9. ┣━ 10. ┫  11. ╋
    static string frameChar[] = {"  ", "┏━", "┓ ", "┗━", "┛ ", "━━", "┃ ", "┳━", "┻━", "┣━", "┫ ", "╋"};
    //矩形边框
    class ARectFrame : public cuberx::Module {
    protected:
    public:
        ARectFrame() = default;
        ARectFrame(short width, short height, short x, short y)
        {
            location.x  = x;
            location.y  = y;
            size.width  = width;
            size.height = height;
        }
        ARectFrame(short width, short height)
        {
            size.width  = width;
            size.height = height;
        }


        void draw(short offsetX, short offsetY) override
        {
            cuberx::WindowSetting::PointJump(location.y + offsetY, location.x + offsetX);
            cout << frameChar[1];
            for(int i = 0; i < (int)floor((float)(size.width - 2) / 2.0); i++)
            {
                cuberx::WindowSetting::PointJump(location.y + offsetY, location.x + 2 + i * 2 + offsetX);
                cout << frameChar[5];
            }
            cuberx::WindowSetting::PointJump(location.y + offsetY, location.x + size.width - 1 + offsetX);
            cout << frameChar[2];

            cuberx::WindowSetting::PointJump(location.y + size.height - 1 + offsetY, location.x + offsetX);
            cout << frameChar[3];
            for(int i = 0; i < (int)floor((float)(size.width - 2) / 2.0); i++)
            {
                cuberx::WindowSetting::PointJump(location.y + size.height - 1 + offsetY, location.x + 2 + i * 2 + offsetX);
                cout << frameChar[5];
            }
            cuberx::WindowSetting::PointJump(location.y + size.height - 1 + offsetY, location.x + size.width - 1 + offsetX);
            cout << frameChar[4];

            for(int i = 0; i < size.y - 2; i++)
            {
                cuberx::WindowSetting::PointJump(location.y + 1 + i + offsetY, location.x + offsetX);
                cout << frameChar[6];
                cuberx::WindowSetting::PointJump(location.y + 1 + i + offsetY, location.x + size.width - 1 + offsetX);
                cout << frameChar[6];
            }
            if(getFatherMainWindow() != nullptr)
            {
                WindowSetting::PointJump(getFatherMainWindow()->getSize().height - 1, getFatherMainWindow()->getSize().width - 1);
            }
            else
            {
                WindowSetting::PointJump(0, 0);
            }
        }
    };

}// namespace cuberx

//AText
namespace cuberx
{

    class AText : public cuberx::Module {
    public:
        AText()
        {
            text = " ";
        }
        AText(string newText)
        {
            text = newText;
        }
        AText(int width, int height, int x, int y)
        {
            location.x  = x;
            location.y  = y;
            size.width  = width;
            size.height = height;
        }
        AText(int width, int height)
        {
            size.width  = width;
            size.height = height;
        }
        AText(string newText, int width, int height, int x, int y)
        {
            text        = newText;
            location.x  = x;
            location.y  = y;
            size.width  = width;
            size.height = height;
        }
        AText(string newText, int width, int height)
        {
            text        = newText;
            size.width  = width;
            size.height = height;
        }
        void draw(short offsetX, short offsetY) override
        {
            cuberx::WindowSetting::PointJump(location.y + offsetY, location.x + offsetX);
            cout << text;
            if(getFatherMainWindow() != nullptr)
            {
                WindowSetting::PointJump(getFatherMainWindow()->getSize().height - 1, getFatherMainWindow()->getSize().width - 1);
            }
            else
            {
                WindowSetting::PointJump(0, 0);
            }
        }
    };

}// namespace cuberx

//FrameButton
namespace cuberx
{

    // 0.     1.┏━ 2. ┓草 3. ┗━ 4. ┛  5. ━━ 6. ┃  7. ┳━ 8. ┻━ 9. ┣━ 10. ┫  11. ╋


    class FrameButton : public cuberx::Module {
    private:
        cuberx::ColorInfo textColorInfo;
        cuberx::ColorInfo frameColorInfo;
        cuberx::ColorInfo chosedTextColorInfo;
        cuberx::ColorInfo chosedFrameColorInfo;
        cuberx::ColorInfo normalTextColorInfo;
        cuberx::ColorInfo normalFrameColorInfo;
        cuberx::ColorInfo middleTextColorInfo;
        cuberx::ColorInfo middleFrameColorInfo;
        cuberx::ColorInfo clickTextColorInfo;
        cuberx::ColorInfo clickFrameColorInfo;
        cuberx::ColorInfo clickedTextColorInfo;
        cuberx::ColorInfo clickedFrameColorInfo;
        cuberx::CUFunction *clickAction;
        static void $action(cuberx::Base *bs)
        {
            if(bs->getVisible())
            {
                auto *pButton = dynamic_cast<cuberx::FrameButton *>(bs);
                pButton->setTextColor(
                    pButton->getMiddleTextColorInfo().backGround,
                    pButton->getMiddleTextColorInfo().font);
                pButton->setFrameColor(
                    pButton->getMiddleFrameColorInfo().backGround,
                    pButton->getMiddleFrameColorInfo().font);
                pButton->draw(pButton->getOffset().x, pButton->getOffset().y);
            }
        }
        static void $action2(cuberx::Base *bs)
        {
            if(bs->getVisible())
            {
                auto *pButton = dynamic_cast<cuberx::FrameButton *>(bs);
                if(!pButton->getBeChosed())
                {
                    pButton->setTextColor(
                        pButton->getNormalTextColorInfo().backGround,
                        pButton->getNormalTextColorInfo().font);
                    pButton->setFrameColor(
                        pButton->getNormalFrameColorInfo().backGround,
                        pButton->getNormalFrameColorInfo().font);
                    pButton->draw(pButton->getOffset().x, pButton->getOffset().y);
                }
            }
        }
        static void $action3(cuberx::Base *bs)
        {
            if(bs->getVisible())
            {
                auto *pButton = dynamic_cast<cuberx::FrameButton *>(bs);
                if(pButton->getBeChosed())
                {
                    pButton->setTextColor(
                        pButton->getChosedTextColorInfo().backGround,
                        pButton->getChosedTextColorInfo().font);
                    pButton->setFrameColor(
                        pButton->getChosedFrameColorInfo().backGround,
                        pButton->getChosedFrameColorInfo().font);
                    pButton->draw(pButton->getOffset().x, pButton->getOffset().y);
                }
            }
        }
        static void $action4(cuberx::Base *bs)
        {
            if(bs->getVisible())
            {
                auto *pButton = dynamic_cast<cuberx::FrameButton *>(bs);
                pButton->setTextColor(
                    pButton->getClickTextColorInfo().backGround,
                    pButton->getClickTextColorInfo().font);
                pButton->setFrameColor(
                    pButton->getClickFrameColorInfo().backGround,
                    pButton->getClickFrameColorInfo().font);
                pButton->draw(pButton->getOffset().x, pButton->getOffset().y);
            }
        }
        static void $action5(cuberx::Base *bs)
        {
            if(bs->getVisible())
            {
                auto *pButton = dynamic_cast<cuberx::FrameButton *>(bs);
                if(pButton->getBeChosed())
                {
                    pButton->setTextColor(
                        pButton->getClickedTextColorInfo().backGround,
                        pButton->getClickedTextColorInfo().font);
                    pButton->setFrameColor(
                        pButton->getClickedFrameColorInfo().backGround,
                        pButton->getClickedFrameColorInfo().font);
                    pButton->draw(pButton->getOffset().x, pButton->getOffset().y);
                }
                else
                {
                    pButton->setTextColor(
                        pButton->getNormalTextColorInfo().backGround,
                        pButton->getNormalTextColorInfo().font);
                    pButton->setFrameColor(
                        pButton->getNormalFrameColorInfo().backGround,
                        pButton->getNormalFrameColorInfo().font);
                    pButton->draw(pButton->getOffset().x, pButton->getOffset().y);
                }
            }
        }

    public:
        FrameButton()
        {
            text                            = " ";
            canBeChosed                     = true;
            chosedTextColorInfo.backGround  = 15;
            chosedTextColorInfo.font        = 0;
            chosedFrameColorInfo.backGround = 0;
            chosedFrameColorInfo.font       = 15;
            normalTextColorInfo.backGround  = 0;
            normalTextColorInfo.font        = 7;
            normalFrameColorInfo.backGround = 0;
            normalFrameColorInfo.font       = 7;
            textColorInfo                   = normalTextColorInfo;
            frameColorInfo                  = normalFrameColorInfo;
            middleTextColorInfo.backGround  = 8;
            middleTextColorInfo.font        = 7;
            middleFrameColorInfo            = normalFrameColorInfo;
            clickTextColorInfo.backGround   = 7;
            clickTextColorInfo.font         = 0;
            clickFrameColorInfo             = normalFrameColorInfo;
            clickedTextColorInfo.backGround = 15;
            clickedTextColorInfo.font       = 0;
            clickFrameColorInfo             = normalFrameColorInfo;
            clickAction                     = nullptr;
        }
        explicit FrameButton(string newText)
        {
            text                            = std::move(newText);
            canBeChosed                     = true;
            chosedTextColorInfo.backGround  = 15;
            chosedTextColorInfo.font        = 0;
            chosedFrameColorInfo.backGround = 0;
            chosedFrameColorInfo.font       = 15;
            normalTextColorInfo.backGround  = 0;
            normalTextColorInfo.font        = 7;
            normalFrameColorInfo.backGround = 0;
            normalFrameColorInfo.font       = 7;
            textColorInfo                   = normalTextColorInfo;
            frameColorInfo                  = normalFrameColorInfo;
            middleTextColorInfo.backGround  = 8;
            middleTextColorInfo.font        = 7;
            middleFrameColorInfo            = normalFrameColorInfo;
            clickTextColorInfo.backGround   = 7;
            clickTextColorInfo.font         = 0;
            clickFrameColorInfo             = normalFrameColorInfo;
            clickedTextColorInfo.backGround = 15;
            clickedTextColorInfo.font       = 0;
            clickFrameColorInfo             = normalFrameColorInfo;
            clickAction                     = nullptr;
        }
        FrameButton(short width, short height, short x, short y)
        {
            location.x                      = x;
            location.y                      = y;
            size.width                      = width;
            size.height                     = height;
            canBeChosed                     = true;
            chosedTextColorInfo.backGround  = 15;
            chosedTextColorInfo.font        = 0;
            chosedFrameColorInfo.backGround = 0;
            chosedFrameColorInfo.font       = 15;
            normalTextColorInfo.backGround  = 0;
            normalTextColorInfo.font        = 7;
            normalFrameColorInfo.backGround = 0;
            normalFrameColorInfo.font       = 7;
            textColorInfo                   = normalTextColorInfo;
            frameColorInfo                  = normalFrameColorInfo;
            middleTextColorInfo.backGround  = 8;
            middleTextColorInfo.font        = 7;
            middleFrameColorInfo            = normalFrameColorInfo;
            clickTextColorInfo.backGround   = 7;
            clickTextColorInfo.font         = 0;
            clickFrameColorInfo             = normalFrameColorInfo;
            clickedTextColorInfo.backGround = 15;
            clickedTextColorInfo.font       = 0;
            clickFrameColorInfo             = normalFrameColorInfo;
            clickAction                     = nullptr;
        }
        FrameButton(short width, short height)
        {
            size.width                      = width;
            size.height                     = height;
            canBeChosed                     = true;
            chosedTextColorInfo.backGround  = 15;
            chosedTextColorInfo.font        = 0;
            chosedFrameColorInfo.backGround = 0;
            chosedFrameColorInfo.font       = 15;
            normalTextColorInfo.backGround  = 0;
            normalTextColorInfo.font        = 7;
            normalFrameColorInfo.backGround = 0;
            normalFrameColorInfo.font       = 7;
            textColorInfo                   = normalTextColorInfo;
            frameColorInfo                  = normalFrameColorInfo;
            middleTextColorInfo.backGround  = 8;
            middleTextColorInfo.font        = 7;
            middleFrameColorInfo            = normalFrameColorInfo;
            clickTextColorInfo.backGround   = 7;
            clickTextColorInfo.font         = 0;
            clickFrameColorInfo             = normalFrameColorInfo;
            clickedTextColorInfo.backGround = 15;
            clickedTextColorInfo.font       = 0;
            clickFrameColorInfo             = normalFrameColorInfo;
            clickAction                     = nullptr;
        }
        FrameButton(const string &newText, short width, short height, short x, short y)
        {
            text                            = newText;
            location.x                      = x;
            location.y                      = y;
            size.width                      = width;
            size.height                     = height;
            canBeChosed                     = true;
            chosedTextColorInfo.backGround  = 15;
            chosedTextColorInfo.font        = 0;
            chosedFrameColorInfo.backGround = 0;
            chosedFrameColorInfo.font       = 15;
            normalTextColorInfo.backGround  = 0;
            normalTextColorInfo.font        = 7;
            normalFrameColorInfo.backGround = 0;
            normalFrameColorInfo.font       = 7;
            textColorInfo                   = normalTextColorInfo;
            frameColorInfo                  = normalFrameColorInfo;
            middleTextColorInfo.backGround  = 8;
            middleTextColorInfo.font        = 7;
            middleFrameColorInfo            = normalFrameColorInfo;
            clickTextColorInfo.backGround   = 7;
            clickTextColorInfo.font         = 0;
            clickFrameColorInfo             = normalFrameColorInfo;
            clickedTextColorInfo.backGround = 15;
            clickedTextColorInfo.font       = 0;
            clickFrameColorInfo             = normalFrameColorInfo;
            clickAction                     = nullptr;
        }
        FrameButton(const string &newText, short width, short height)
        {
            text                            = newText;
            size.width                      = width;
            size.height                     = height;
            canBeChosed                     = true;
            chosedTextColorInfo.backGround  = 15;
            chosedTextColorInfo.font        = 0;
            chosedFrameColorInfo.backGround = 0;
            chosedFrameColorInfo.font       = 15;
            normalTextColorInfo.backGround  = 0;
            normalTextColorInfo.font        = 7;
            normalFrameColorInfo.backGround = 0;
            normalFrameColorInfo.font       = 7;
            textColorInfo                   = normalTextColorInfo;
            frameColorInfo                  = normalFrameColorInfo;
            middleTextColorInfo.backGround  = 8;
            middleTextColorInfo.font        = 7;
            middleFrameColorInfo            = normalFrameColorInfo;
            clickTextColorInfo.backGround   = 7;
            clickTextColorInfo.font         = 0;
            clickFrameColorInfo             = normalFrameColorInfo;
            clickedTextColorInfo.backGround = 15;
            clickedTextColorInfo.font       = 0;
            clickFrameColorInfo             = normalFrameColorInfo;
            clickAction                     = nullptr;
        }
        void draw(short offsetX, short offsetY) override
        {
            //绘制边框
            cuberx::WindowSetting::PointJump((short)(location.y + offsetY), (short)(location.x + offsetX));
            WindowSetting::colorOut(frameChar[1], frameColorInfo.font, frameColorInfo.backGround);
            for(int i = 0; i < (int)floor((float)(size.width - 2) / 2.0); i++)
            {
                cuberx::WindowSetting::PointJump((short)(location.y + offsetY), (short)(location.x + offsetX + 2 + i * 2));
                WindowSetting::colorOut(frameChar[5], frameColorInfo.font, frameColorInfo.backGround);
            }
            cuberx::WindowSetting::PointJump((short)(location.y + offsetY), (short)(location.x + offsetX + size.width - 1));
            WindowSetting::colorOut(frameChar[2], frameColorInfo.font, frameColorInfo.backGround);

            cuberx::WindowSetting::PointJump((short)(location.y + offsetY + size.height - 1), (short)(location.x + offsetX));
            WindowSetting::colorOut(frameChar[3], frameColorInfo.font, frameColorInfo.backGround);
            for(int i = 0; i < (int)floor((float)(size.width - 2) / 2.0); i++)
            {
                cuberx::WindowSetting::PointJump((short)(location.y + offsetY + size.height - 1), (short)(location.x + offsetX + 2 + i * 2));
                WindowSetting::colorOut(frameChar[5], frameColorInfo.font, frameColorInfo.backGround);
            }
            cuberx::WindowSetting::PointJump((short)(location.y + offsetY + size.height - 1), (short)(location.x + offsetX + size.width - 1));
            WindowSetting::colorOut(frameChar[4], frameColorInfo.font, frameColorInfo.backGround);

            for(int i = 0; i < size.y - 2; i++)
            {
                cuberx::WindowSetting::PointJump((short)(location.y + offsetY + 1 + i), (short)(location.x + offsetX));
                WindowSetting::colorOut(frameChar[6], frameColorInfo.font, frameColorInfo.backGround);
                cuberx::WindowSetting::PointJump((short)(location.y + offsetY + 1 + i), (short)(location.x + offsetX + size.width - 1));
                WindowSetting::colorOut(frameChar[6], frameColorInfo.font, frameColorInfo.backGround);
            }
            //显示文字
            cuberx::WindowSetting::PointJump((short)(location.y + offsetY + 1), (short)(location.x + offsetX + 2));
            WindowSetting::colorOut(text, textColorInfo.font, textColorInfo.backGround);

            if(getFatherMainWindow() != nullptr)
            {
                WindowSetting::PointJump((short)(getFatherMainWindow()->getSize().height - 1), (short)(getFatherMainWindow()->getSize().width - 1));
            }
            else
            {
                WindowSetting::PointJump(0, 0);
            }
        }
        void whenBeChosed() override
        {
            beChosed = true;
            if(getFatherMainWindow() != nullptr)
            {
                cuberx::MainWindow &fmw = *getFatherMainWindow();
                //运行接口函数
                fmw.setTask(fmw.getNewTask(), this, 1, $action, 2);
                fmw.setTask(fmw.getNewTask(), this, 1, $action3, 5);
            }
            else
            {
                setTextColor(15, 0);
                draw(offset.x, offset.y);
            }
        }
        void whenStopChosed() override
        {
            beChosed = false;
            if(getFatherMainWindow() != nullptr)
            {
                cuberx::MainWindow &fmw = *getFatherMainWindow();
                //运行接口函数
                fmw.setTask(fmw.getNewTask(), this, 1, $action, 5);
                fmw.setTask(fmw.getNewTask(), this, 1, $action2, 10);
            }
            else
            {
                setTextColor(normalTextColorInfo.backGround, normalTextColorInfo.font);
                draw(offset.x, offset.y);
            }
        }

        //设置颜色信息
        void setTextColor(char backGround, char font)
        {
            textColorInfo.backGround = backGround;
            textColorInfo.font       = font;
        }
        void setFrameColor(char backGround, char font)
        {
            frameColorInfo.backGround = backGround;
            frameColorInfo.font       = font;
        }
        void setChosedTextColorInfo(char backGround, char font)
        {
            chosedTextColorInfo.backGround = backGround;
            chosedTextColorInfo.font       = font;
        }
        void setChosedFrameColorInfo(char backGround, char font)
        {
            chosedFrameColorInfo.backGround = backGround;
            chosedFrameColorInfo.font       = font;
        }
        void setNormalTextColorInfo(char backGround, char font)
        {
            normalTextColorInfo.backGround = backGround;
            normalTextColorInfo.font       = font;
        }
        void setNormalFrameColorInfo(char backGround, char font)
        {
            normalFrameColorInfo.backGround = backGround;
            normalFrameColorInfo.font       = font;
        }
        void setMiddleTextColorInfo(char backGround, char font)
        {
            middleTextColorInfo.backGround = backGround;
            middleTextColorInfo.font       = font;
        }
        void setMiddleFrameColorInfo(char backGround, char font)
        {
            middleFrameColorInfo.backGround = backGround;
            middleFrameColorInfo.font       = font;
        }
        void setClickTextColorInfo(char backGround, char font)
        {
            clickTextColorInfo.backGround = backGround;
            clickTextColorInfo.font       = font;
        }
        void setClickFrameColorInfo(char backGround, char font)
        {
            clickFrameColorInfo.backGround = backGround;
            clickFrameColorInfo.font       = font;
        }
        void setClickedTextColorInfo(char backGround, char font)
        {
            clickedTextColorInfo.backGround = backGround;
            clickedTextColorInfo.font       = font;
        }
        void setClickedFrameColorInfo(char backGround, char font)
        {
            clickedFrameColorInfo.backGround = backGround;
            clickedFrameColorInfo.font       = font;
        }

        //获取颜色信息
        ColorInfo getTextColor() const
        {
            return textColorInfo;
        }
        ColorInfo getFrameColor() const
        {
            return frameColorInfo;
        }
        ColorInfo getChosedTextColorInfo() const
        {
            return chosedTextColorInfo;
        }
        ColorInfo getChosedFrameColorInfo() const
        {
            return chosedFrameColorInfo;
        }
        ColorInfo getNormalTextColorInfo() const
        {
            return normalTextColorInfo;
        }
        ColorInfo getNormalFrameColorInfo() const
        {
            return normalFrameColorInfo;
        }
        ColorInfo getMiddleTextColorInfo() const
        {
            return middleTextColorInfo;
        }
        ColorInfo getMiddleFrameColorInfo() const
        {
            return middleFrameColorInfo;
        }
        ColorInfo getClickTextColorInfo() const
        {
            return clickTextColorInfo;
        }
        ColorInfo getClickFrameColorInfo() const
        {
            return clickFrameColorInfo;
        }
        ColorInfo getClickedTextColorInfo() const
        {
            return clickedTextColorInfo;
        }
        ColorInfo getClickedFrameColorInfo() const
        {
            return clickedFrameColorInfo;
        }


        void setBeChosed(bool newCase) override
        {
            beChosed = newCase;
            if(newCase)
            {
                whenBeChosed();
            }
        }
        void setClickAction(cuberx::CUFunction *newFunc)
        {
            clickAction = newFunc;
        }
        void setClickAction(cuberx::CUFunction &newFunc)
        {
            clickAction = &newFunc;
        }
        void setClickAction(void (*func)(cuberx::Base *this_base))
        {
            class NewAction : public cuberx::CUFunction {
                void (*pFunc)(cuberx::Base *this_base);

            public:
                explicit NewAction(void (*newPFunc)(cuberx::Base *this_base))
                {
                    pFunc = newPFunc;
                }
                void func(cuberx::Base *this_base) override
                {
                    pFunc(this_base);
                }
            };
            auto *na    = new NewAction(func);
            clickAction = na;
        }
        CUFunction &getClickAction()
        {
            return *clickAction;
        }
        int keyAction(int newKey) override
        {
            switch(newKey)
            {
            case cuberx::Key::$ENTER:
            {
                cuberx::MainWindow *fmw = getFatherMainWindow();


                //运行接口函数
                if(fmw != nullptr)
                {
                    fmw->setTask(fmw->getNewTask(), this, 1, $action4, 2);
                }
                if(&getClickAction() != nullptr)
                {
                    getClickAction().func(this);
                }
                if(fmw != nullptr)
                {
                    fmw->setTask(fmw->getNewTask(), this, 1, $action5, 35);
                }
                return 1;
            }
            }
            return 0;
        }
    };

}// namespace cuberx

//TextButton 纯文本按钮
namespace cuberx
{

    /// <summary>
    /// 纯文本按钮
    /// </summary>
    class TextButton : public cuberx::Module {
    protected:
        cuberx::ColorInfo textColorInfo;
        cuberx::ColorInfo chosedTextColorInfo; //被选择
        cuberx::ColorInfo normalTextColorInfo; //原色
        cuberx::ColorInfo middleTextColorInfo; //灰色
        cuberx::ColorInfo clickTextColorInfo;  //按下
        cuberx::ColorInfo clickedTextColorInfo;//按下并弹起后
        cuberx::CUFunction *clickAction;
        //灰色
        static void $action(cuberx::Base *bs)
        {
            if(bs->getVisible())
            {
                auto *pButton = dynamic_cast<cuberx::TextButton *>(bs);
                pButton->setTextColor(
                    pButton->getMiddleColorInfo().backGround,
                    pButton->getMiddleColorInfo().font);

                pButton->draw(pButton->getOffset().x, pButton->getOffset().y);
            }
        }
        //原色
        static void $action2(cuberx::Base *bs)
        {
            if(bs->getVisible())
            {
                auto *pButton = dynamic_cast<cuberx::TextButton *>(bs);
                if(!pButton->getBeChosed())
                {
                    pButton->setTextColor(
                        pButton->getNormalColorInfo().backGround,
                        pButton->getNormalColorInfo().font);
                    pButton->draw(pButton->getOffset().x, pButton->getOffset().y);
                }
            }
        }
        //被选择
        static void $action3(cuberx::Base *bs)
        {
            if(bs->getVisible())
            {
                auto *pButton = dynamic_cast<cuberx::TextButton *>(bs);
                if(pButton->getBeChosed())
                {
                    pButton->setTextColor(
                        pButton->getChosedColorInfo().backGround,
                        pButton->getChosedColorInfo().font);
                    pButton->draw(pButton->getOffset().x, pButton->getOffset().y);
                }
            }
        }
        //被按下
        static void $action4(cuberx::Base *bs)
        {
            if(bs->getVisible())
            {
                auto *pButton = dynamic_cast<cuberx::TextButton *>(bs);
                pButton->setTextColor(
                    pButton->getClickColorInfo().backGround,
                    pButton->getClickColorInfo().font);
                pButton->draw(pButton->getOffset().x, pButton->getOffset().y);
            }
        }
        //被按下后弹起
        static void $action5(cuberx::Base *bs)
        {
            if(bs->getVisible())
            {
                auto *pButton = dynamic_cast<cuberx::TextButton *>(bs);
                if(pButton->getBeChosed())
                {
                    pButton->setTextColor(
                        pButton->getClickedColorInfo().backGround,
                        pButton->getClickedColorInfo().font);
                    pButton->draw(pButton->getOffset().x, pButton->getOffset().y);
                }
                else
                {
                    pButton->setTextColor(
                        pButton->getNormalColorInfo().backGround,
                        pButton->getNormalColorInfo().font);
                    pButton->draw(pButton->getOffset().x, pButton->getOffset().y);
                }
            }
        }

    public:
        TextButton()
        {
            text                            = " ";
            canBeChosed                     = true;
            chosedTextColorInfo.backGround  = 15;
            chosedTextColorInfo.font        = 0;
            normalTextColorInfo.backGround  = 0;
            normalTextColorInfo.font        = 15;
            textColorInfo                   = normalTextColorInfo;
            middleTextColorInfo.backGround  = 8;
            middleTextColorInfo.font        = 7;
            clickTextColorInfo.backGround   = 7;
            clickTextColorInfo.font         = 0;
            clickedTextColorInfo.backGround = 15;
            clickedTextColorInfo.font       = 0;
            clickAction                     = nullptr;
        }
        explicit TextButton(string text, short x = 0, short y = 0, short width = 8, short height = 1)
        {
            this->text                      = std::move(text);
            canBeChosed                     = true;
            chosedTextColorInfo.backGround  = 15;
            chosedTextColorInfo.font        = 0;
            normalTextColorInfo.backGround  = 0;
            normalTextColorInfo.font        = 15;
            textColorInfo                   = normalTextColorInfo;
            middleTextColorInfo.backGround  = 8;
            middleTextColorInfo.font        = 7;
            clickTextColorInfo.backGround   = 7;
            clickTextColorInfo.font         = 0;
            clickedTextColorInfo.backGround = 15;
            clickedTextColorInfo.font       = 0;
            clickAction                     = nullptr;
            location.x                      = x;
            location.y                      = y;
            size.width                      = width;
            size.height                     = height;
        }
        explicit TextButton(short x = 0, short y = 0, short width = 8, short height = 1)
        {
            text                            = " ";
            canBeChosed                     = true;
            chosedTextColorInfo.backGround  = 15;
            chosedTextColorInfo.font        = 0;
            normalTextColorInfo.backGround  = 0;
            normalTextColorInfo.font        = 15;
            textColorInfo                   = normalTextColorInfo;
            middleTextColorInfo.backGround  = 8;
            middleTextColorInfo.font        = 7;
            clickTextColorInfo.backGround   = 7;
            clickTextColorInfo.font         = 0;
            clickedTextColorInfo.backGround = 15;
            clickedTextColorInfo.font       = 0;
            clickAction                     = nullptr;
            location.x                      = x;
            location.y                      = y;
            size.width                      = width;
            size.height                     = height;
        }

        /// <summary>
        /// 设置文字颜色
        /// (0:黑   8:灰
        ///  1:蓝   9:淡蓝
        ///  2:绿   10:淡绿色
        ///  3:浅绿色 11:淡浅绿色
        ///  4:红色 12:淡红色
        ///  5:紫色 13:淡紫色
        ///  6:黄色 14:淡黄色
        ///  7:白色 15:亮白色)
        /// </summary>
        /// <param name="backGround">背景色</param>
        /// <param name="font">文字色</param>

        //设置颜色信息
        virtual void setTextColor(char backGround, char font)
        {
            textColorInfo.backGround = backGround;
            textColorInfo.font       = font;
        }
        virtual void setMiddleColorInfo(char backGround, char font)
        {
            middleTextColorInfo.backGround = backGround;
            middleTextColorInfo.font       = font;
        }
        virtual void setNormalColorInfo(char backGround, char font)
        {
            normalTextColorInfo.backGround = backGround;
            normalTextColorInfo.font       = font;
        }
        virtual void setChosedColorInfo(char backGround, char font)
        {
            chosedTextColorInfo.backGround = backGround;
            chosedTextColorInfo.font       = font;
        }
        virtual void setClickColorInfo(char backGround, char font)
        {
            clickTextColorInfo.backGround = backGround;
            clickTextColorInfo.font       = font;
        }
        virtual void setClickedColorInfo(char backGround, char font)
        {
            clickedTextColorInfo.backGround = backGround;
            clickedTextColorInfo.font       = font;
        }

        //获取颜色信息
        virtual cuberx::ColorInfo getTextColor() const
        {
            return textColorInfo;
        }
        virtual cuberx::ColorInfo getMiddleColorInfo() const
        {
            return middleTextColorInfo;
        }
        virtual cuberx::ColorInfo getNormalColorInfo() const
        {
            return normalTextColorInfo;
        }
        virtual cuberx::ColorInfo getChosedColorInfo() const
        {
            return chosedTextColorInfo;
        }
        virtual cuberx::ColorInfo getClickColorInfo() const
        {
            return clickTextColorInfo;
        }
        virtual cuberx::ColorInfo getClickedColorInfo() const
        {
            return clickedTextColorInfo;
        }


        void setBeChosed(bool newCase) override
        {
            beChosed = newCase;
            if(newCase)
            {
                whenBeChosed();
            }
            else
            {
                whenStopChosed();
            }
        }
        virtual void setClickAction(cuberx::CUFunction *newFunc)
        {
            clickAction = newFunc;
        }
        virtual void setClickAction(cuberx::CUFunction &newFunc)
        {
            clickAction = &newFunc;
        }
        virtual void setClickAction(void (*func)(cuberx::Base *this_base))
        {
            class NewAction : public cuberx::CUFunction {
                void (*pFunc)(cuberx::Base *this_base);

            public:
                explicit NewAction(void (*newPFunc)(cuberx::Base *this_base))
                {
                    pFunc = newPFunc;
                }
                void func(cuberx::Base *this_base) override
                {
                    pFunc(this_base);
                }
            };
            auto *na    = new NewAction(func);
            clickAction = na;
        }
        virtual CUFunction &getClickAction()
        {
            return *clickAction;
        }
        int keyAction(int newKey) override
        {
            switch(newKey)
            {
            case cuberx::Key::$ENTER:
            {
                cuberx::MainWindow &fmw = *getFatherMainWindow();


                //运行接口函数
                if(&fmw != nullptr)
                {
                    fmw.setTask(fmw.getNewTask(), this, 1, $action4, 2);
                }
                if(&getClickAction() != nullptr)
                {
                    getClickAction().func(this);
                }
                if(&fmw != nullptr)
                {
                    fmw.setTask(fmw.getNewTask(), this, 1, $action5, 35);
                }
                return 1;
            }
            }
            return 0;
        }

        void draw(short offsetX, short offsetY) override
        {
            WindowSetting::PointJump(location.y + offsetY, location.x + offsetX);
            WindowSetting::colorOut(text, textColorInfo.font, textColorInfo.backGround);
        }
        void whenBeChosed() override
        {
            beChosed = true;
            if(getFatherMainWindow() != nullptr)
            {
                cuberx::MainWindow &fmw = *getFatherMainWindow();
                //运行接口函数
                fmw.setTask(fmw.getNewTask(), this, 1, $action, 2);
                fmw.setTask(fmw.getNewTask(), this, 1, $action3, 5);
            }
            else
            {
                setTextColor(15, 0);
                draw(offset.x, offset.y);
            }
        }
        void whenStopChosed() override
        {
            beChosed = false;
            if(getFatherMainWindow() != nullptr)
            {
                cuberx::MainWindow &fmw = *getFatherMainWindow();
                //运行接口函数
                fmw.setTask(fmw.getNewTask(), this, 1, $action, 4);
                fmw.setTask(fmw.getNewTask(), this, 1, $action2, 8);
            }
            else
            {
                setTextColor(normalTextColorInfo.backGround, normalTextColorInfo.font);
                draw(offset.x, offset.y);
            }
        }
    };

}// namespace cuberx

//ClText 多彩文本
#define $CU_CLTEXT_TEXTCOLORINFO_MAX_LENGTH 128
namespace cuberx
{

    class CLText : public cuberx::Module {
    private:
        cuberx::ColorInfo textColorInfo[$CU_CLTEXT_TEXTCOLORINFO_MAX_LENGTH];

    public:
        CLText()
        {
            for(auto &i: textColorInfo)
            {
                i.backGround = 0;
                i.font       = 7;
            }
        }
        /*
         0 = 黑色	8 = 灰色
         1 = 蓝色	9 = 淡蓝色
         2 = 绿色	A = 淡绿色
         3 = 浅绿色	B = 淡浅绿色
         4 = 红色	C = 淡红色
         5 = 紫色	D = 淡紫色
         6 = 黄色	E = 淡黄色
         7 = 白色	F = 亮白色
        */
        explicit CLText(const string &text)
        {
            this->text = text;
            for(auto &i: textColorInfo)
            {
                i.backGround = 0;
                i.font       = 7;
            }
        }
        CLText(const string &text, string backGroundColorInfoString, string fontColorInfoString, short width = 5, short height = 1, short x = 0, short y = 0)
        {
            this->text = text;

            //重置
            for(auto &i: textColorInfo)
            {
                i.backGround = 0;
                i.font       = 7;
            }
            //读取并写入
            for(int i = 0; i < backGroundColorInfoString.length(); i++)
            {
                switch(backGroundColorInfoString[i])
                {
                case '0':
                    textColorInfo[i].backGround = 0;
                    break;
                case '1':
                    textColorInfo[i].backGround = 1;
                    break;
                case '2':
                    textColorInfo[i].backGround = 2;
                    break;
                case '3':
                    textColorInfo[i].backGround = 3;
                    break;
                case '4':
                    textColorInfo[i].backGround = 4;
                    break;
                case '5':
                    textColorInfo[i].backGround = 5;
                    break;
                case '6':
                    textColorInfo[i].backGround = 6;
                    break;
                case '7':
                    textColorInfo[i].backGround = 7;
                    break;
                case '8':
                    textColorInfo[i].backGround = 8;
                    break;
                case '9':
                    textColorInfo[i].backGround = 9;
                    break;
                case 'A':
                case 'a':
                    textColorInfo[i].backGround = 10;
                    break;
                case 'B':
                case 'b':
                    textColorInfo[i].backGround = 11;
                    break;
                case 'C':
                case 'c':
                    textColorInfo[i].backGround = 12;
                    break;
                case 'D':
                case 'd':
                    textColorInfo[i].backGround = 13;
                    break;
                case 'E':
                case 'e':
                    textColorInfo[i].backGround = 14;
                    break;
                case 'F':
                case 'f':
                    textColorInfo[i].backGround = 15;
                    break;
                default:
                    break;
                }
            }
            for(int i = 0; i < fontColorInfoString.length(); i++)
            {
                switch(fontColorInfoString[i])
                {
                case '0':
                    textColorInfo[i].font = 0;
                    break;
                case '1':
                    textColorInfo[i].font = 1;
                    break;
                case '2':
                    textColorInfo[i].font = 2;
                    break;
                case '3':
                    textColorInfo[i].font = 3;
                    break;
                case '4':
                    textColorInfo[i].font = 4;
                    break;
                case '5':
                    textColorInfo[i].font = 5;
                    break;
                case '6':
                    textColorInfo[i].font = 6;
                    break;
                case '7':
                    textColorInfo[i].font = 7;
                    break;
                case '8':
                    textColorInfo[i].font = 8;
                    break;
                case '9':
                    textColorInfo[i].font = 9;
                    break;
                case 'A':
                case 'a':
                    textColorInfo[i].font = 10;
                    break;
                case 'B':
                case 'b':
                    textColorInfo[i].font = 11;
                    break;
                case 'C':
                case 'c':
                    textColorInfo[i].font = 12;
                    break;
                case 'D':
                case 'd':
                    textColorInfo[i].font = 13;
                    break;
                case 'E':
                case 'e':
                    textColorInfo[i].font = 14;
                    break;
                case 'F':
                case 'f':
                    textColorInfo[i].font = 15;
                    break;
                default:
                    break;
                }
            }

            setSize(width, height);
            setLocation(x, y);
        }
        void draw(short offsetX, short offsetY) override
        {
            ULONGLONG strLength = text.length();
            string temp;
            WindowSetting::PointJump((short)(getLocation().y + offsetY), (short)(getLocation().x + offsetX));
            for(long long i = 0; i < strLength; i++)
            {
                temp = text[i];
                WindowSetting::colorOut(temp, textColorInfo[i].font, textColorInfo[i].backGround);
            }
            if(getFatherMainWindow() != nullptr)
            {
                WindowSetting::PointJump((short)(getFatherMainWindow()->getSize().height - 1), (short)(getFatherMainWindow()->getSize().width - 1));
            }
            else
            {
                WindowSetting::PointJump(0, 0);
            }
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
        virtual void setTextColorInfo(string backGroundColorInfoString, string fontColorInfoString, bool ifResetAll = false, bool ifChangeNow = true)
        {
            //若变量ifResetAll为true(1)则重置
            if(ifResetAll)
            {
                for(auto &i: textColorInfo)
                {
                    i.backGround = 0;
                    i.font       = 7;
                }
            }
            //读取并写入
            for(int i = 0; i < backGroundColorInfoString.length(); i++)
            {
                switch(backGroundColorInfoString[i])
                {
                case '0':
                    textColorInfo[i].backGround = 0;
                    break;
                case '1':
                    textColorInfo[i].backGround = 1;
                    break;
                case '2':
                    textColorInfo[i].backGround = 2;
                    break;
                case '3':
                    textColorInfo[i].backGround = 3;
                    break;
                case '4':
                    textColorInfo[i].backGround = 4;
                    break;
                case '5':
                    textColorInfo[i].backGround = 5;
                    break;
                case '6':
                    textColorInfo[i].backGround = 6;
                    break;
                case '7':
                    textColorInfo[i].backGround = 7;
                    break;
                case '8':
                    textColorInfo[i].backGround = 8;
                    break;
                case '9':
                    textColorInfo[i].backGround = 9;
                    break;
                case 'A':
                case 'a':
                    textColorInfo[i].backGround = 10;
                    break;
                case 'B':
                case 'b':
                    textColorInfo[i].backGround = 11;
                    break;
                case 'C':
                case 'c':
                    textColorInfo[i].backGround = 12;
                    break;
                case 'D':
                case 'd':
                    textColorInfo[i].backGround = 13;
                    break;
                case 'E':
                case 'e':
                    textColorInfo[i].backGround = 14;
                    break;
                case 'F':
                case 'f':
                    textColorInfo[i].backGround = 15;
                    break;
                case 'N':
                case 'n':
                {
                    ColorInfo normalColorInfo;
                    textColorInfo[i].backGround = normalColorInfo.backGround;
                    break;
                }
                default:
                    break;
                }
            }
            for(int i = 0; i < fontColorInfoString.length(); i++)
            {
                switch(fontColorInfoString[i])
                {
                case '0':
                    textColorInfo[i].font = 0;
                    break;
                case '1':
                    textColorInfo[i].font = 1;
                    break;
                case '2':
                    textColorInfo[i].font = 2;
                    break;
                case '3':
                    textColorInfo[i].font = 3;
                    break;
                case '4':
                    textColorInfo[i].font = 4;
                    break;
                case '5':
                    textColorInfo[i].font = 5;
                    break;
                case '6':
                    textColorInfo[i].font = 6;
                    break;
                case '7':
                    textColorInfo[i].font = 7;
                    break;
                case '8':
                    textColorInfo[i].font = 8;
                    break;
                case '9':
                    textColorInfo[i].font = 9;
                    break;
                case 'A':
                case 'a':
                    textColorInfo[i].font = 10;
                    break;
                case 'B':
                case 'b':
                    textColorInfo[i].font = 11;
                    break;
                case 'C':
                case 'c':
                    textColorInfo[i].font = 12;
                    break;
                case 'D':
                case 'd':
                    textColorInfo[i].font = 13;
                    break;
                case 'E':
                case 'e':
                    textColorInfo[i].font = 14;
                    break;
                case 'F':
                case 'f':
                    textColorInfo[i].font = 15;
                    break;
                case 'N':
                case 'n':
                {
                    ColorInfo normalColorInfo;
                    textColorInfo[i].font = normalColorInfo.font;
                    break;
                }
                default:
                    break;
                }
            }
            //立即绘制
            if(ifChangeNow)
            {
                draw(offset.x, offset.y);
            }
        }
    };

}// namespace cuberx

//组件群组
namespace cuberx
{
    //组件群组(建议在堆内分配子组件的内存(即用new关键字),析构函数会自动回收内存)
    template<int objectCount>
    class Group : public cuberx::Container {
    protected:
        cuberx::Base *objects[objectCount]{};

    public:
        Group()
        {
            for(int i = 0; i < objectCount; i++)
            {
                objects[i] = nullptr;
            }
        }
        ~Group()
        {
            for(int i = 0; i < objectCount; i++)
            {
                if(objects[i] != nullptr)
                {
                    delete objects[i];
                    objects[i] = nullptr;
                }
            }
        }
        //绘制子组件，-1表示绘制所有
        virtual void draw(short index, short offsetX, short offsetY)
        {
            if(index == -1)
            {
                for(int i = 0; i < objectCount; i++)
                {
                    objects[i]->drawNull(location.x + offsetX, location.y + offsetY);
                    objects[i]->draw(location.x + offsetX, location.y + offsetY);
                }
            }
            else if(index >= 0)
            {
                objects[index]->drawNull(location.x + offsetX, location.y + offsetY);
                objects[index]->draw(location.x + offsetX, location.y + offsetY);
            }
        }
        void draw(short offsetX, short offsetY) override
        {
            for(int i = 0; i < objectCount; i++)
            {
                if(objects[i] != nullptr)
                {
                    // objects[i]->drawNull(location.x + offsetX, location.y + offsetY);
                    objects[i]->draw(location.x + offsetX, location.y + offsetY);
                }
            }
        }
        void setNowChosingObject(int newChoingObject) override
        {
            if(objects[nowChosingObject] != nullptr)
            {
                objects[nowChosingObject]->whenStopChosed();
            }
            if(objects[newChoingObject] != nullptr)
            {
                objects[newChoingObject]->whenBeChosed();
            }
            nowChosingObject = newChoingObject;
        }
        //键位反应
        int keyAction(int newKey) override
        {
            //
            int result = 0;
            for(int i = 0; i < objectCount; i++)
            {
                if(objects[i] != nullptr)
                {
                    result = objects[i]->keyAction(newKey);
                    if(result == 1)
                    {
                        return result;
                    }
                }
            }
            return result;
        }
        void setLocation(short x, short y) override
        {
            location.x = x;
            location.y = y;
            setOffset(getOffset().x, getOffset().y);
        }
        void setOffset(short offsetX, short offsetY) override
        {
            offset.x = offsetX;
            offset.y = offsetY;
            for(auto *i: objects)
            {
                if(i != nullptr)
                {
                    i->setOffset(offsetX + location.x, offsetY + location.y);
                }
            }
        }

        void setVisible(bool bVisible) override
        {
            this->bVisible = bVisible;
            //todo 尽快完善Container
            //todo add时应考虑父组件bVisible
            for(int i = 0; i < objectCount; ++i)
            {
                if(objects[i] != nullptr)
                {
                    objects[i]->setVisible(bVisible);
                }
            }
        }

        //设置所属主窗口信息(同步到子组件)
        void setFatherMainWindow(cuberx::MainWindow *newFatherMainWindow) override
        {
            fatherMainWindow = newFatherMainWindow;
            for(int i = 0; i < objectCount; i++)
            {
                if(objects[i] != nullptr)
                {
                    objects[i]->setFatherMainWindow(newFatherMainWindow);
                }
            }
        }
        //重置所属主窗口信息(同步到子组件)
        void resetFatherMainWindow() override
        {
            fatherMainWindow = nullptr;
            for(int i = 0; i < objectCount; i++)
            {
                if(objects[i] != nullptr)
                {
                    objects[i]->resetFatherMainWindow();
                }
            }
        }\
        //设置所属容器信息(同步到子组件)
        void setFatherContainer(cuberx::Container *newFatherContainer) override
        {
            fatherContainer = newFatherContainer;
            for(int i = 0; i < objectCount; i++)
            {
                if(objects[i] != nullptr)
                {
                    objects[i]->setFatherContainer(newFatherContainer);
                }
            }
        }
        //重置所属容器信息(同步到子组件)
        void resetFatherContainer() override
        {
            fatherContainer = nullptr;
            for(int i = 0; i < objectCount; i++)
            {
                if(objects[i] != nullptr)
                {
                    objects[i]->resetFatherContainer();
                }
            }
        }
    };

}// namespace cuberx

//测试组件:黑白标题+彩色内容+自动伸缩边框
namespace cuberx
{

    class TipBar : public cuberx::Group<3> {
    protected:
        cuberx::ARectFrame *arf;
        cuberx::AText *at;
        cuberx::CLText *clt;
        bool autoSize;
        bool frameVisible;

    public:
        TipBar()
        {
            autoSize = true;
            arf      = new cuberx::ARectFrame;
            at       = new cuberx::AText("提示: ", 6, 1, 2, 1);
            clt      = new cuberx::CLText("无", "00", "cc", 2, 1, (short)(at->getText().length() + 2), 1);
            runAutoSize();
            objects[0]   = arf;
            objects[1]   = at;
            objects[2]   = clt;
            frameVisible = true;
        }
        TipBar(const string &title, const string &tip, const string &tipBackGroundColorInfo = "", const string &tipFontColorInfo = "", short x = 0, short y = 0, bool frameVisible = true, bool ifUseAutoSize = true, short width = 10, short height = 3)
        {
            autoSize = ifUseAutoSize;
            arf      = new cuberx::ARectFrame(width, height);
            at       = new cuberx::AText(title, (short)(title.length()), 1, 2, 1);
            clt      = new cuberx::CLText(tip, tipBackGroundColorInfo, tipFontColorInfo, tip.length(), 1, at->getText().length() + 2, 1);
            setLocation(x, y);
            setSize(width, height);
            if(ifUseAutoSize)
            {
                runAutoSize();
            }
            objects[0]         = arf;
            objects[1]         = at;
            objects[2]         = clt;
            this->frameVisible = frameVisible;
        }
        ~TipBar()
        {
            delete arf;
            delete at;
            delete clt;
            arf = nullptr;
            at  = nullptr;
            clt = nullptr;
        }
        virtual void runAutoSize()
        {
            arf->setSize(at->getText().length() + clt->getText().length() + 3, 3);
            clt->setLocation(2 + at->getText().length(), 1);
        }
        virtual void setAutoSize(bool ifAutoSize)
        {
            autoSize = ifAutoSize;
            if(ifAutoSize)
            {
                runAutoSize();
                draw();
            }
        }
        virtual void setAText(const string &newText)
        {
            at->setText(newText);
            if(autoSize)
            {
                runAutoSize();
            }
            draw();
        }
        virtual void setCLText(const string &newText, const string &tipBackGroundColorInfo = "", const string &tipFontColorInfo = "")
        {
            clt->setText(newText);
            clt->setTextColorInfo(tipBackGroundColorInfo, tipFontColorInfo, true, false);
            if(autoSize)
            {
                runAutoSize();
            }
            draw();
        }
        virtual void setFrameSize(short width, short height)
        {
            arf->setSize(width, height);
            draw();
        }
        void draw(short offsetX = 0, short offsetY = 0) override
        {
            if(frameVisible)
            {
                objects[0]->draw(short(location.x + offsetX), short(location.y + offsetY));
            }
            for(int i = 1; i < 3; i++)
            {
                objects[i]->draw(short(location.x + offsetX), short(location.y + offsetY));
            }
        }
    };

}// namespace cuberx

//TextFrame 带文字的边框
namespace cuberx
{
    class TextFrame : public Group<2>
    {
    private:
        cuberx::ARectFrame* arf;
        cuberx::AText* at;

    public:
        TextFrame(const string& text, short width, short height, short x, short y)
        {
            arf = new ARectFrame(width, height, 0, 0);
            at  = new AText(text, (short)text.length(), 1, 4, 0);
            objects[0] = arf;
            objects[1] = at;
            location.x = x;
            location.y = y;
            size.width = width;
            size.height = height;
        }
        void setText(const string& newText) override
        {
            at->setText(newText);
            draw(offset.x, offset.y);
        }
    };
}

//CLTextFrame 带彩色文字的边框
namespace cuberx
{
    class CLTextFrame : public cuberx::Group<2>
    {
    private:
        cuberx::ARectFrame* arf;
        cuberx::CLText* clt;

    public:
        CLTextFrame(
            const string& text,
            const string& backGroundColorInfo,
            const string& fontColorInfo,
            short width,
            short height,
            short x,
            short y)
        {
            arf = new ARectFrame(width, height, 0, 0);
            clt = new CLText(text, backGroundColorInfo, fontColorInfo, text.length(), 1, 4, 0);
            objects[0] = arf;
            objects[1] = clt;
            location.x = x;
            location.y = y;
            size.width = width;
            size.height = height;
        }
        void setText(const string& newText) override
        {
            clt->setText(newText);
            draw(offset.x, offset.y);
        }
        void setTextColorInfo(const string& backGroundColorInfo, const string& fontColorInfo)
        {
            clt->setTextColorInfo(backGroundColorInfo, fontColorInfo);
            draw(offset.x, offset.y);
        }
    };
}

//PGBar 进度条
namespace cuberx {
    //进度条字符(9种,从"  "到"█")
    static const string ProgressChar[] = {"  ", "▏", "▎", "▍", "▌", "▋", "▊", "▉", "█"};

    class PGBar : public cuberx::Module {
    protected:
        int ProgressCount;
        int lastFullCount;
        int lastHungryCountLevel;
        long double maxValue;
        long double minValue;
        long double nowValue;
        bool ifDrawPercentage;
        double percentage;
        cuberx::ColorInfo ProgressColor;

    public:
        PGBar() {
            ProgressCount        = 8;
            maxValue             = 100;
            minValue             = 0;
            nowValue             = 0;
            ifDrawPercentage     = true;
            percentage           = (double)(nowValue - minValue) / (maxValue - minValue);
            lastHungryCountLevel = 0;
            lastFullCount        = 0;
        }
        /// <summary>
        /// 进度条
        /// </summary>
        /// <param name="ProgressCount">进度条总格数</param>
        /// <param name="x">坐标X位置</param>
        /// <param name="y">坐标Y位置</param>
        /// <param name="maxValue">最大值</param>
        /// <param name="minValue">最小值</param>
        /// <param name="nowValue">当前值</param>
        /// <param name="ifDrawPercentage">是否在进度条右侧显示百分比</param>
        /// <param name="progressBackgroundColor">进度条的背景色</param>
        /// <param name="progressFontColor">进度条本身的颜色</param>
        PGBar(short ProgressCount, short x, short y, long double maxValue = 100, long double minValue = 0, long double nowValue = 0, bool ifDrawPercentage = true, char progressBackgroundColor = 0, char progressFontColor = 7) {
            location.x               = x;
            location.y               = y;
            size.width               = short(ProgressCount * 2);
            size.height              = 1;
            this->ProgressCount      = ProgressCount;
            this->maxValue           = maxValue;
            this->minValue           = minValue;
            this->nowValue           = nowValue;
            this->ifDrawPercentage   = ifDrawPercentage;
            percentage               = (nowValue - minValue) / (maxValue - minValue);
            ProgressColor.backGround = progressBackgroundColor;
            ProgressColor.font       = progressFontColor;
            lastFullCount            = 0;
            lastHungryCountLevel     = 0;
        }
        /// <summary>
        /// 绘制进度条
        /// </summary>
        /// <param name="offsetX">坐标X偏移量</param>
        /// <param name="offsetY">坐标Y偏移量</param>
        void draw(short offsetX, short offsetY) override {
            //清空当前显示内容并铺上背景色
            WindowSetting::PointJump(short(location.y + offsetY), short(location.x + offsetX + lastFullCount * 2));
            for(int i = lastFullCount * 2; i < size.width; i++) {
                WindowSetting::colorOut(" ", ProgressColor.font, ProgressColor.backGround);
            }

            //正式绘制
            if(nowValue >= minValue && nowValue <= maxValue) {
                double disCount = ProgressCount * percentage;

                //确定fullCount
                int fullCount = floor(disCount);

                // 确定hungryCountLevel
                int hungryCountLevel = 0;
                {
                    double hungryCount = disCount - fullCount;
                    if(hungryCount == 0 || hungryCount <= 0.0625) {
                        hungryCountLevel = 0;
                    } else if(hungryCount <= 0.1875) {
                        hungryCountLevel = 1;
                    } else if(hungryCount <= 0.3125) {
                        hungryCountLevel = 2;
                    } else if(hungryCount <= 0.4375) {
                        hungryCountLevel = 3;
                    } else if(hungryCount <= 0.5625) {
                        hungryCountLevel = 4;
                    } else if(hungryCount <= 0.6875) {
                        hungryCountLevel = 5;
                    } else if(hungryCount <= 0.8125) {
                        hungryCountLevel = 6;
                    } else if(hungryCount <= 0.9375) {
                        hungryCountLevel = 7;
                    } else {
                        hungryCountLevel = 8;
                    }
                }

                //绘制Full部分
                {
                    //与 last 相等(无需绘制)
                    if(fullCount == lastFullCount) {
                    }
                    //比 last 小(清除多余部分[hungry所占部分除外])
                    else if(fullCount < lastFullCount) {
                        for(int i = fullCount + 1; i < lastFullCount; i++) {
                            WindowSetting::PointJump(location.y + offsetY, location.x + offsetX + i * 2);
                            WindowSetting::colorOut("  ", ProgressColor.font, ProgressColor.backGround);
                        }
                    }
                    //比 last 大(显示缺失部分)
                    else {
                        for(int i = lastFullCount; i < fullCount; i++) {
                            WindowSetting::PointJump(location.y + offsetY, location.x + offsetX + i * 2);
                            WindowSetting::colorOut(ProgressChar[8], ProgressColor.font, ProgressColor.backGround);
                        }
                    }
                }

                //绘制Hungry部分
                {
                    //位置不变, 直接覆盖
                    if(fullCount == lastFullCount) {
                        WindowSetting::PointJump(location.y + offsetY, location.x + offsetX + fullCount * 2);
                        WindowSetting::colorOut(ProgressChar[hungryCountLevel], ProgressColor.font, ProgressColor.backGround);
                    }
                    //位置有变, 清除之前的再重新显示
                    else {
                        if(lastFullCount > fullCount) {
                            WindowSetting::PointJump(location.y + offsetY, location.x + offsetX + lastFullCount * 2);
                            WindowSetting::colorOut("  ", ProgressColor.font, ProgressColor.backGround);
                        }
                        WindowSetting::PointJump(location.y + offsetY, location.x + offsetX + fullCount * 2);
                        WindowSetting::colorOut(ProgressChar[hungryCountLevel], ProgressColor.font, ProgressColor.backGround);
                    }
                }

                //刷新last信息
                lastFullCount        = fullCount;
                lastHungryCountLevel = hungryCountLevel;
            }
            //当前值小于最小值
            else if(nowValue <= minValue) {
            }
            //当前值大于最大值
            else {
                for(int i = lastFullCount; i < ProgressCount; i++) {
                    WindowSetting::PointJump(location.y + offsetY, location.x + offsetX + i * 2);
                    WindowSetting::colorOut(ProgressChar[8], ProgressColor.font, ProgressColor.backGround);
                }
                lastFullCount = ProgressCount;
            }

            //显示百分比
            {
                if(ifDrawPercentage) {
                    if(percentage <= 0) {
                        WindowSetting::PointJump(location.y + offsetY, location.x + offsetX + size.width);
                        cout << "0  %";
                    } else if(percentage >= 1) {
                        WindowSetting::PointJump(location.y + offsetY, location.x + offsetX + size.width);
                        cout << "100%";
                    } else {
                        string disMem      = "            ";
                        disMem             = (percentage * 100);
                        string finalDisMem = "             ";
                        if(disMem.length() >= 0)
                            finalDisMem[0] = disMem[0];
                        if(disMem.length() >= 1)
                            finalDisMem[1] = disMem[1];
                        if(disMem.length() >= 2)
                            finalDisMem[2] = disMem[2];
                        if(disMem.length() >= 3)
                            finalDisMem[3] = disMem[3];
                        if(disMem.length() >= 4)
                            finalDisMem[4] = '%';
                        finalDisMem[5] = 0;
                        WindowSetting::PointJump(location.y + offsetY, location.x + offsetX + size.width);
                        cout << "     ";
                        WindowSetting::PointJump(location.y + offsetY, location.x + offsetX + size.width);
                        cout << ceil(percentage * 100);
                        WindowSetting::PointJump(location.y + offsetY, location.x + offsetX + size.width + 3);
                        cout << "%";
                    }
                }
            }
            if(getFatherMainWindow() != nullptr) {
                WindowSetting::PointJump(getFatherMainWindow()->getSize().height - 1, getFatherMainWindow()->getSize().width - 1);
            } else {
                WindowSetting::PointJump(0, 0);
            }
        }
        virtual int getProgressCount() {
            return ProgressCount;
        }
        virtual void setProgressCount(int newProgressCount, bool ifChangeNow = 1) {
            ProgressCount = newProgressCount;
            size.width    = ProgressCount * 2;
            if(ifChangeNow) {
                draw(offset.x, offset.y);
            }
        }
        virtual long double getMaxValue() {
            return maxValue;
        }
        virtual void setMaxValue(long double newMaxValue, bool ifChangeNow = 1) {
            maxValue   = newMaxValue;
            percentage = (nowValue - minValue) / (maxValue - minValue);
            if(ifChangeNow) {
                draw(offset.x, offset.y);
            }
        }
        virtual long double getMinValue() {
            return minValue;
        }
        virtual void setMinValue(long double newMinValue, bool ifChangeNow = 1) {
            minValue   = newMinValue;
            percentage = (nowValue - minValue) / (maxValue - minValue);
            if(ifChangeNow) {
                draw(offset.x, offset.y);
            }
        }
        virtual long double getNowValue() {
            return nowValue;
        }
        virtual void setNowValue(long double newNowValue, bool ifChangeNow = 1) {
            nowValue   = newNowValue;
            percentage = (nowValue - minValue) / (maxValue - minValue);
            if(ifChangeNow) {
                draw(offset.x, offset.y);
            }
        }
        virtual bool getIfDrawPercentage() {
            return ifDrawPercentage;
        }
        virtual void setIfDrawPercentage(bool ifDrawPercentage, bool ifChangeNow = 1) {
            this->ifDrawPercentage = ifDrawPercentage;
            if(ifChangeNow) {
                draw(offset.x, offset.y);
            }
        }
        virtual cuberx::ColorInfo getProgressColor() {
            return ProgressColor;
        }
        virtual void setProgressColor(int backGroundColor, int fontColor, bool ifChangeNow = 1) {
            ProgressColor.backGround = backGroundColor;
            ProgressColor.font       = fontColor;
            if(ifChangeNow) {
                draw(offset.x, offset.y);
            }
        }
    };

}// namespace cuberx

//WAVSoundPlayer WAV音频播放器
namespace cuberx {

    // WAV音频播放器
    class WAVSoundPlayer : public cuberx::Module {
    private:
        string soundFile;
        bool useNewThread;//是否使用多线程播放(可以实现多个声音并行播放)
        thread *newThr;
        static void $playSound(string fileName) {
            //若为局部路径则转换为绝对路径
            if(fileName.length() > 2) {
                if(fileName[1] != ':') {
                    char temp[1024];
                    _fullpath(temp, fileName.c_str(), 1024);
                    fileName = temp;
                }
            }
            //播放
            string strOpenCommand     = "open ";
            strOpenCommand            = strOpenCommand + fileName;
            wchar_t *wcharOpenCommand = cuberx::StringTool::StringToWchar(strOpenCommand);
            string strPlayCommand     = "play ";
            strPlayCommand            = strPlayCommand + fileName;
            wchar_t *wcharPlayCommand = cuberx::StringTool::StringToWchar(strPlayCommand);
            // mciSendString(reinterpret_cast<LPCSTR>(wcharOpenCommand), NULL, 0, 0);
            // mciSendString(reinterpret_cast<LPCSTR>(wcharPlayCommand), NULL, 0, 0);
            delete[] wcharOpenCommand;
            delete[] wcharPlayCommand;
        }

    public:
        WAVSoundPlayer() {
            soundFile    = "";
            useNewThread = 1;
            newThr       = nullptr;
        }
        WAVSoundPlayer(string newSoundFile, bool ifUseNewThread = 1) {
            soundFile    = newSoundFile;
            useNewThread = ifUseNewThread;
            newThr       = nullptr;
        }

        static thread *playSoundTool(string fileName, bool ifUseNewThread = 1) {
            if(ifUseNewThread) {
                thread *thr = new thread($playSound, fileName);
                return thr;
            } else {
                $playSound(fileName);
            }
            return nullptr;
        }

        virtual void playSound() {
            if(newThr != nullptr) {
                // TODO: 此处应删除该线程
                newThr = nullptr;
            }
            thread *tempThr;
            tempThr = playSoundTool(soundFile, useNewThread);
            if(tempThr != nullptr) {
                newThr = tempThr;
            }
        }
        virtual void setSoundFile(string newSoundFile) {
            soundFile = newSoundFile;
        }
        virtual string getSoundFile() {
            return soundFile;
        }
        virtual void setIfUseNewThread(bool ifUseNewThread) {
            useNewThread = ifUseNewThread;
        }
        virtual bool getIfUseNewThread() {
            return useNewThread;
        }
    };

}// namespace cuberx

//ASwitch 开关按钮
namespace cuberx {
    // ASwitch 开关按钮
    class ASwitch : public cuberx::Module {
    protected:
        bool condition;// On(true) | Off(false)
        //中间
        static void $action1(cuberx::Base *this_base) {
            auto *this_aOnOff = dynamic_cast<cuberx::ASwitch *>(this_base);
            WindowSetting::PointJump(
                this_aOnOff->getLocation().y + this_aOnOff->getOffset().y,
                this_aOnOff->getLocation().x + this_aOnOff->getOffset().x);
            WindowSetting::colorOut(" ■ ", 7, 6);
        }
        //开启
        static void $action2(cuberx::Base *this_base) {
            auto *this_aOnOff = dynamic_cast<cuberx::ASwitch *>(this_base);
            WindowSetting::PointJump(
                this_aOnOff->getLocation().y + this_aOnOff->getOffset().y,
                this_aOnOff->getLocation().x + this_aOnOff->getOffset().x);
            if(this_aOnOff->getBeChosed()) {
                WindowSetting::colorOut("  ■", 7, 10);
            } else {
                WindowSetting::colorOut("  ■", 8, 10);
            }
        }
        //关闭
        static void $action3(cuberx::Base *this_base) {
            auto *this_aOnOff = dynamic_cast<cuberx::ASwitch *>(this_base);
            WindowSetting::PointJump(
                this_aOnOff->getLocation().y + this_aOnOff->getOffset().y,
                this_aOnOff->getLocation().x + this_aOnOff->getOffset().x);
            if(this_aOnOff->getBeChosed()) {
                WindowSetting::colorOut("■  ", 7, 12);
            } else {
                WindowSetting::colorOut("■  ", 8, 12);
            }
        }

    public:
        ASwitch() {
            location.x  = 0;
            location.y  = 0;
            condition   = false;
            canBeChosed = true;
        }
        ASwitch(short x, short y, bool defaultCondition = false) {
            location.x  = x;
            location.y  = y;
            condition   = defaultCondition;
            canBeChosed = true;
        }
        void draw(short offsetX, short offsetY) override {
            WindowSetting::PointJump(location.y + offsetY, location.y + offsetY);
            if(condition) {
                // On
                if(beChosed) {
                    WindowSetting::PointJump(location.y + offsetY, location.x + offsetX);
                    WindowSetting::colorOut("  ■", 7, 10);
                } else {
                    WindowSetting::PointJump(location.y + offsetY, location.x + offsetX);
                    WindowSetting::colorOut("  ■", 8, 10);
                }
            } else {
                // Off
                if(beChosed) {
                    WindowSetting::PointJump(location.y + offsetY, location.x + offsetX);
                    WindowSetting::colorOut("■  ", 7, 12);
                } else {
                    WindowSetting::PointJump(location.y + offsetY, location.x + offsetX);
                    WindowSetting::colorOut("■  ", 8, 12);
                }
            }
        }
        int keyAction(int newKey) override {
            int result              = 0;
            cuberx::MainWindow *fmw = getFatherMainWindow();
            switch(newKey) {
            case Key::$LEFT: {
                if(condition) {
                    condition = false;
                    if(fmw != nullptr && fmw->getUseTickListener()) {
                        // Use Action
                        fmw->setTask(fmw->getNewTask(), this, 7, $action1, 5);
                        fmw->setTask(fmw->getNewTask(), this, 7, $action3, 10);
                    } else {
                        // No Action
                        draw(offset.x, offset.y);
                    }
                }
                result = 1;
            }
            break;
            case Key::$RIGHT: {
                if(!condition) {
                    condition = true;
                    if(fmw != nullptr && fmw->getUseTickListener()) {
                        // Use Action
                        fmw->setTask(fmw->getNewTask(), this, 7, $action1, 5);
                        fmw->setTask(fmw->getNewTask(), this, 7, $action2, 10);
                    } else {
                        // No Action
                        draw(offset.x, offset.y);
                    }
                }
                result = 1;
            }
            break;
            case Key::$ENTER: {
                if(condition) {
                    // On => Off
                    condition = false;

                    if(fmw != nullptr && fmw->getUseTickListener()) {
                        // Use Action
                        fmw->setTask(fmw->getNewTask(), this, 7, $action1, 5);
                        fmw->setTask(fmw->getNewTask(), this, 7, $action3, 10);
                    } else {
                        // No Action
                        draw(offset.x, offset.y);
                    }
                } else {
                    // Off => On
                    condition = true;
                    if(fmw != nullptr && fmw->getUseTickListener()) {
                        // Use Action
                        fmw->setTask(fmw->getNewTask(), this, 7, $action1, 5);
                        fmw->setTask(fmw->getNewTask(), this, 7, $action2, 10);
                    } else {
                        // No Action
                        draw(offset.x, offset.y);
                    }
                }
                result = 1;
            }
            break;
            default:
                break;
            }
            return result;
        }
        void whenBeChosed() override {
            beChosed = true;
            draw(offset.x, offset.y);
        }
        void whenStopChosed() override {
            beChosed = false;
            draw(offset.x, offset.y);
        }
    };
}// namespace cuberx

//TextSwitch (组件群组)带文字的开关按钮
namespace cuberx {
    // TextSwitch (组件群组)带文字的开关按钮
    class TextSwitch : public cuberx::Group<2> {
    protected:
        cuberx::CLText *cltText;
        cuberx::ASwitch *aSwitch;

    public:
        TextSwitch(const string &text = "", short width = 4, short height = 1, short x = 0, short y = 0, bool defaultCondition = false) {
            cltText = new cuberx::CLText(
                text,
                "",
                "8888888888888888888888888888888888888888",
                width,
                height,
                x,
                y);
            aSwitch     = new cuberx::ASwitch((short)(x + width - 4), y, defaultCondition);
            objects[0]  = cltText;
            objects[1]  = aSwitch;
            canBeChosed = true;
        }
        void whenBeChosed() override {
            beChosed = true;
            cltText->setTextColorInfo("", "7777777777777777777777777777777777777777", false, true);
            aSwitch->whenBeChosed();
        }
        void whenStopChosed() override {
            beChosed = false;
            cltText->setTextColorInfo("", "8888888888888888888888888888888888888888", false, true);
            aSwitch->whenStopChosed();
        }
    };
}// namespace cuberx

//FreedomFrame 自由边框
namespace cuberx
{
    // FreedomFrame 自由边框
    class FreedomFrame : public cuberx::Module {
    private:
        cuberx::SuperArray<int> frameInfo{};
        bool bTransparent;

    public:
        //自由边框 注意: 此组件的1个width等于2小格
        FreedomFrame(short width, short height, short x, short y, BYTE** frameInfo, bool bTransparent = false)
        {
            this->frameInfo.reset(height, width);
            for(int i = 0; i < height; ++i)
            {
                for(int j = 0; j < width; ++j)
                {
                    this->frameInfo[i][j] = *((int *)frameInfo + i * width + j);
                }
            }
            location.x = x;
            location.y = y;
            size.x     = width;
            size.y     = height;
            this->bTransparent = bTransparent;
        }
        FreedomFrame(short width, short height, short x, short y, SuperArray<BYTE> frameInfo, bool bTransparent = false)
        {
            this->frameInfo.reset(height, width);
            for(int i = 0; i < height; ++i)
            {
                for(int j = 0; j < width; ++j)
                {
                    this->frameInfo[i][j] = frameInfo[i][j];
                }
            }
            location.x = x;
            location.y = y;
            size.x     = width;
            size.y     = height;
            this->bTransparent = bTransparent;
        }
        void draw(short offsetX, short offsetY) override
        {
            for(short i = 0; i < size.height; ++i)
            {
                for(short j = 0; j < size.width; ++j)
                {
                    WindowSetting::PointJump(location.y + offsetY + i, location.x + offsetX + j * 2);
                    switch(frameInfo[i][j])
                    {
                    case 0:
                        // 0000
                        if(bTransparent)//判断是否透明
                        {
                            // Do Nothing
                        }
                        else
                        {
                            cout << cuberx::frameChar[0];
                        }
                        break;
                    case 1:
                        // 0001
                        cout << cuberx::frameChar[5];
                        break;
                    case 2:
                        // 0010
                        cout << cuberx::frameChar[5];
                        break;
                    case 3:
                        // 0011
                        cout << cuberx::frameChar[5];
                        break;
                    case 4:
                        // 0100
                        cout << cuberx::frameChar[6];
                        break;
                    case 5:
                        // 0101
                        cout << cuberx::frameChar[1];
                        break;
                    case 6:
                        // 0110
                        cout << cuberx::frameChar[2];
                        break;
                    case 7:
                        // 0111
                        cout << cuberx::frameChar[7];
                        break;
                    case 8:
                        // 1000
                        cout << cuberx::frameChar[6];
                        break;
                    case 9:
                        // 1001
                        cout << cuberx::frameChar[3];
                        break;
                    case 10:
                        // 1010
                        cout << cuberx::frameChar[4];
                        break;
                    case 11:
                        // 1011
                        cout << cuberx::frameChar[8];
                        break;
                    case 12:
                        // 1100
                        cout << cuberx::frameChar[6];
                        break;
                    case 13:
                        // 1101
                        cout << cuberx::frameChar[9];
                        break;
                    case 14:
                        // 1110
                        cout << cuberx::frameChar[10];
                        break;
                    case 15:
                        // 1111
                        cout << cuberx::frameChar[11];
                        break;
                    }
                }
                WindowSetting::PointJump(location.y + offsetY + i, location.x + offsetX + size.width * 2);
                cout << "  ";
            }
        }
        void drawNull(short offsetX, short offsetY) override
        {
            for(int i = 0; i < size.height; ++i)
            {
                for(int j = 0; j < size.width; ++j)
                {
                    WindowSetting::PointJump(location.y + offsetY + i, location.x + offsetX + j * 2);
                    if(frameInfo[i][j] >= 0 && frameInfo[i][j] <= 15)
                    {
                        cout << "  ";
                    }
                }

            }
        }

        //简易边框信息 转换为 最终边框信息
        static SuperArray<BYTE> EasyToFinal(short width, short height, bool** before)
        {
            SuperArray<BYTE> temp(height, width);
            for(int h = 0; h < height; ++h)
            {
                for(int w = 0; w < width; ++w)
                {
                    //UP
                    if(h != 0)
                    {
                        if(PointerTool::P2TA2(before, width, h - 1, w))
                        {
                            temp[h][w] |= 8;
                        }
                    }
                    //DOWN
                    if(h != height - 1)
                    {
                        if(PointerTool::P2TA2(before, width, h + 1, w))
                        {
                            temp[h][w] |= 4;
                        }
                    }
                    //LEFT
                    if(w != 0)
                    {
                        if(PointerTool::P2TA2(before, width, h, w - 1))
                        {
                            temp[h][w] |= 2;
                        }
                    }
                    //RIGHT
                    if(w != width - 1)
                    {
                        if(PointerTool::P2TA2(before, width, h, w + 1))
                        {
                            temp[h][w] |= 1;
                        }
                    }
                }
            }
            //返回值
            return temp;
        }
        static SuperArray<BYTE>* RectToFinal(short width, short height, short x1, short y1, short x2, short y2)
        {
            cuberx::SuperArray<BYTE>* temp = new cuberx::SuperArray<BYTE>(height,width);
            //初始化
            for(int i = 0; i < height; ++i)
            {
                for(int j = 0; j < width; ++j)
                {
                    (*temp)[i][j] = 0;
                }
            }
            //UP & DOWN
            for(int i = x1 + 1; i <= x2 - 1; ++i)
            {
                //UP
                (*temp)[y1][i] = 3;//0011
                //DOWN
                (*temp)[y2][i] = 3;//0011
            }
            //LEFT & RIGHT
            for(int j = y1 + 1; j <= y2 - 1; ++j)
            {
                //LEFT
                (*temp)[j][x1] = 12;//1100
                //RIGHT
                (*temp)[j][x2] = 12;//1100
            }
            //LEFT UP
            (*temp)[y1][x1] = 5;//0101
            //LEFT DOWN
            (*temp)[y2][x1] = 9;//1001
            //RIGHT UP
            (*temp)[y1][x2] = 6;//0110
            //RIGHT DOWN
            (*temp)[y2][x2] = 10;//1010
            return temp;
        }
        static SuperArray<BYTE>* AddTwoFinal(short width, short height, SuperArray<BYTE>* final1, SuperArray<BYTE>* final2)
        {
            cuberx::SuperArray<BYTE>* temp = new cuberx::SuperArray<BYTE>(height,width);
            for(int i = 0; i < height; ++i)
            {
                for(int j = 0; j < width; ++j)
                {
                    (*temp)[i][j] = PointerTool::P2TA2(final1, width, i, j) | PointerTool::P2TA2(final2, width, i, j);
                }
            }
            return temp;
        }
    };
}// namespace cuberx

//SubWindow 子窗体
#define $CU_SUBWINDOW_OBJECTS_COUNT 32
#define $CU_SUBWINDOW_TOTAL_G_KEYACTION_BEFORE_COUNT 32
#define $CU_SUBWINDOW_TOTAL_G_KEYACTION_AFTER_COUNT 32
namespace cuberx
{
    //SubWindow 子窗体
    class SubWindow : public cuberx::Container
    {
    protected:
        class frame_NOTHING : public cuberx::Group<3>
            {
            };
        class frame_FRAME : public cuberx::Group<3>
            {
            private:
                cuberx::ARectFrame* arf;

            public:
                frame_FRAME(short width, short height)
                {
                    arf = new ARectFrame(width, height);
                    size.width = width;
                    size.height = height;
                    objects[0] = arf;
                }
                ~frame_FRAME()
                {
                    delete arf;
                    arf = nullptr;
                }
            };
        class frame_TEXT_ON_FRAME : public cuberx::Group<3>
            {
            private:
                cuberx::CLTextFrame* cltf;

            public:
                frame_TEXT_ON_FRAME(const string& text, short width, short height)
                {
                    cltf = new cuberx::CLTextFrame(text,"","",width,height,0,0);
                    size.width = width;
                    size.height = height;
                    objects[0] = cltf;
                }
                ~frame_TEXT_ON_FRAME()
                {
                    delete cltf;
                    cltf = nullptr;
                }

            };
        class frame_TEXT_IN_FRAME : public cuberx::Group<3>
            {
            private:
                cuberx::FreedomFrame* ff;
                cuberx::CLText* clt;

            public:
                frame_TEXT_IN_FRAME(const string& text, const short width, const short height)
                {
                    ff = new cuberx::FreedomFrame(width,
                                                  height,
                                                  0,
                                                  0,
                                                  *cuberx::FreedomFrame::AddTwoFinal(
                                                      width,
                                                      height,
                                                      cuberx::FreedomFrame::RectToFinal(width, height, (short)0,(short)0,short(width - 1), short(height - 1)),
                                                      cuberx::FreedomFrame::RectToFinal(width, height, (short)0,(short)0,short(width - 1), (short)2)
                                                      ),
                                                      true
                                                      );
                    clt = new cuberx::CLText(text,"","",(short)text.length(),1,2,1);
                    objects[0] = ff;
                    objects[1] = clt;
                }
                ~frame_TEXT_IN_FRAME()
                {
                    delete ff;
                    delete clt;
                    ff = nullptr;
                    clt = nullptr;
                }

            };
        class frame_CLOSE_BUTTON_FRAME : public cuberx::Group<3>
            {
            private:
                cuberx::FreedomFrame* ff;
                cuberx::TextButton* tb;

            public:
                frame_CLOSE_BUTTON_FRAME(short width, short height)
                {
                    canBeChosed = true;
                    ff          = new cuberx::FreedomFrame(
                        width,
                        height,
                        0,
                        0,
                        *cuberx::FreedomFrame::AddTwoFinal(
                            width,
                            height,
                            cuberx::FreedomFrame::AddTwoFinal(
                                width,
                                height,
                                cuberx::FreedomFrame::RectToFinal(
                                    width,
                                    height,
                                    0,
                                    0,
                                    width - 1,
                                    height - 1
                                    ),
                                    cuberx::FreedomFrame::RectToFinal(
                                        width,
                                        height,
                                        0,
                                        0,
                                        width - 1,
                                        2
                                        )
                                        ),
                                        cuberx::FreedomFrame::RectToFinal(
                                            width,
                                            height,
                                            width - 3,
                                            0,
                                            width - 1,
                                            2
                                            )
                                            ),
                                            true
                                            );
                    tb = new cuberx::TextButton(" X",width * 2 - 4, 1, 2, 1);
                    tb->setChosedColorInfo(12, 15);
                    tb->setMiddleColorInfo(4, 7);
                    tb->setClickAction([](cuberx::Base* this_base)->void{
                        this_base->getFatherContainer()->exit();
                    });
                    objects[0] = ff;
                    objects[1] = tb;
                }
                ~frame_CLOSE_BUTTON_FRAME()
                {
                    delete ff;
                    delete tb;
                    ff = nullptr;
                    tb = nullptr;
                }

                //关闭窗口
                virtual void exit()
                {
                    setVisible(false);
                    drawNull(offset.x, offset.y);
                }

                void whenBeChosed() override
                {
                    beChosed = true;
                    objects[1]->setBeChosed(true);
                }
                void whenStopChosed() override
                {
                    beChosed = false;
                    objects[1]->setBeChosed(false);
                }
                int keyAction(int newKey)
                {
                    return objects[1]->keyAction(newKey);
                }
            };
        class frame_CLOSE_BUTTON_AND_TEXT_IN_FRAME : public cuberx::Group<3> {
            private:
                cuberx::FreedomFrame *ff;
                cuberx::TextButton *tb;
                cuberx::CLText *clt;

            public:
                frame_CLOSE_BUTTON_AND_TEXT_IN_FRAME(const string &text, short width, short height)
                {
                    canBeChosed = true;
                    ff          = new cuberx::FreedomFrame(
                                 width,
                                 height,
                                 0,
                                 0,
                                 *cuberx::FreedomFrame::AddTwoFinal(
                                     width,
                                     height,
                                     cuberx::FreedomFrame::AddTwoFinal(
                                         width,
                                         height,
                                         cuberx::FreedomFrame::RectToFinal(
                                             width,
                                             height,
                                             0,
                                             0,
                                             width - 1,
                                             height - 1
                                             ),
                                         cuberx::FreedomFrame::RectToFinal(
                                             width,
                                             height,
                                             0,
                                             0,
                                             width - 1,
                                             2
                                             )
                                         ),
                                     cuberx::FreedomFrame::RectToFinal(
                                         width,
                                         height,
                                         width - 3,
                                         0,
                                         width - 1,
                                         2
                                         )
                                     ),
                                 true
                                 );
                    tb          = new cuberx::TextButton(" X", width * 2 - 4, 1, 2, 1);
                    tb->setChosedColorInfo(12, 15);
                    tb->setMiddleColorInfo(4, 7);
                    tb->setClickColorInfo(4,7);
                    tb->setClickedColorInfo(12,15);
                    tb->setClickAction([](cuberx::Base* this_base)->void{
                        this_base->getFatherContainer()->exit();
                    });
                    clt         = new cuberx::CLText(text, "", "", (short)text.length(), 1, 2, 1);
                    objects[0]  = ff;
                    objects[1]  = tb;
                    objects[2]  = clt;
                }
                ~frame_CLOSE_BUTTON_AND_TEXT_IN_FRAME()
                {

                    delete ff;
                    delete tb;
                    delete clt;
                    ff  = nullptr;
                    tb  = nullptr;
                    clt = nullptr;
                }
                void whenBeChosed() override
                {
                    beChosed = true;
                    objects[1]->setBeChosed(true);
                }
                void whenStopChosed() override
                {
                    beChosed = false;
                    objects[1]->setBeChosed(false);
                }
                int keyAction(int newKey) override
                {
                    return objects[1]->keyAction(newKey);
                }
            };

    protected:
        cuberx::Group<3>* windowFrame;
        BYTE style; //窗口风格
        cuberx::Base* objects[$CU_SUBWINDOW_OBJECTS_COUNT];
        cuberx::Coordinate subObjOffset;
        cuberx::KeyTask keyTasksBefore[$CU_SUBWINDOW_TOTAL_G_KEYACTION_BEFORE_COUNT]{};
        cuberx::KeyTask keyTasksAfter[$CU_SUBWINDOW_TOTAL_G_KEYACTION_AFTER_COUNT]{};

    public:
        enum StyleType{NOTHING,FRAME,TEXT_ON_FRAME,TEXT_IN_FRAME,CLOSE_BUTTON_FRAME,CLOSE_BUTTON_AND_TEXT_IN_FRAME};

    public:
        SubWindow(const string& title, short width, short height, short x, short y, StyleType style, bool bVisible)
        {
            text = title;
            size.width = width;
            size.height = height;
            location.x = x;
            location.y = y;
            this->bVisible = bVisible;
            this->style = style;
            text = title;
            canBeChosed = true;

            switch(style)
            {
            case NOTHING://无附加显示
                subObjOffset.x = 0;
                subObjOffset.y = 0;
                windowFrame    = new frame_NOTHING();
                break;
            case FRAME://带边框
                subObjOffset.x = 2;
                subObjOffset.y = 1;
                windowFrame    = new frame_FRAME(width, height);
                break;
            case TEXT_ON_FRAME://带文字的边框
                subObjOffset.x = 2;
                subObjOffset.y = 1;
                windowFrame    = new frame_TEXT_ON_FRAME(title, width, height);
                break;
            case TEXT_IN_FRAME://带单独标题的边框
                subObjOffset.x = 2;
                subObjOffset.y = 3;
                windowFrame    = new frame_TEXT_IN_FRAME(text, width, height);
                break;
            case CLOSE_BUTTON_FRAME://带关闭按钮的边框
                subObjOffset.x = 2;
                subObjOffset.y = 3;
                windowFrame    = new frame_CLOSE_BUTTON_FRAME(width, height);
                break;
            case CLOSE_BUTTON_AND_TEXT_IN_FRAME://带单独标题和关闭按钮的边框
                subObjOffset.x = 2;
                subObjOffset.y = 3;
                windowFrame    = new frame_CLOSE_BUTTON_AND_TEXT_IN_FRAME(text, width, height);
                break;
            }

            *this << windowFrame;
            windowFrame->setOffset(x,y);
        }
        ~SubWindow()
        {
            if(windowFrame != nullptr) {
                delete windowFrame;
                windowFrame = nullptr;
            }
        }

        //添加组件
        int add(cuberx::Base* newObject) override
        {
            for(int i = 0; i < $CU_SUBWINDOW_OBJECTS_COUNT; i++)
            {
                if(objects[i] == nullptr)
                {
                    //寻找成功
                    objects[i] = newObject;
                    newObject->setFatherMainWindow(getFatherMainWindow());
                    newObject->setOffset(location.x + subObjOffset.x,location.y + subObjOffset.y);
                    newObject->setFatherContainer(this);
                    return i;
                }
            }
            //寻找失败
            return -1;
        }
        int add(cuberx::Base& newObject) override
        {
            for(int i = 0; i < $CU_SUBWINDOW_OBJECTS_COUNT; i++)
            {
                if(objects[i] == nullptr)
                {
                    //寻找成功
                    objects[i] = &newObject;
                    newObject.setFatherMainWindow(getFatherMainWindow());
                    newObject.setOffset(location.x + subObjOffset.x,location.y + subObjOffset.y);
                    newObject.setFatherContainer(this);
                    return i;
                }
            }
            //寻找失败
            return -1;
        }
        virtual cuberx::SubWindow& operator<<(cuberx::Base* newObject)
        {
            for(auto *& object : objects)
            {
                if(object == nullptr)
                {
                    //寻找成功
                    object = newObject;
                    newObject->setFatherMainWindow(getFatherMainWindow());
                    newObject->setOffset(location.x + subObjOffset.x,location.y + subObjOffset.y);
                    newObject->setFatherContainer(this);
                    return *this;
                }
            }
            //失败
            return *this;
        }
        virtual cuberx::SubWindow& operator<<(cuberx::Base& newObject)
        {
            for(auto *& object : objects)
            {
                if(object == nullptr)
                {
                    //寻找成功
                    object = &newObject;
                    newObject.setFatherMainWindow(getFatherMainWindow());
                    newObject.setOffset(location.x + subObjOffset.x + offset.x,location.y + subObjOffset.y);
                    newObject.setFatherContainer(this);
                    return *this;
                }
            }
            //失败
            return *this;
        }
        virtual cuberx::SubWindow& operator+=(cuberx::Base* newObject)
        {
            for(auto *& object : objects)
            {
                if(object == nullptr)
                {
                    //寻找成功
                    object = newObject;
                    newObject->setFatherMainWindow(getFatherMainWindow());
                    newObject->setOffset(location.x + subObjOffset.x,location.y + subObjOffset.y);
                    newObject->setFatherContainer(this);
                    return *this;
                }
            }
            //失败
            return *this;
        }
        virtual cuberx::SubWindow& operator+=(cuberx::Base& newObject)
        {
            for(auto *& object : objects)
            {
                if(object == nullptr)
                {
                    //寻找成功
                    object = &newObject;
                    newObject.setFatherMainWindow(getFatherMainWindow());
                    newObject.setOffset(location.x + subObjOffset.x,location.y + subObjOffset.y);
                    newObject.setFatherContainer(this);
                    return *this;
                }
            }
            //失败
            return *this;
        }

        //删除组件
        void remove(cuberx::Base* object) override
        {
            for(auto & i : objects)
            {
                if(i == object)
                {
                    i = nullptr;
                    object->setFatherMainWindow(nullptr);
                    object->setOffset(0,0);
                    object->resetFatherMainWindow();
                    return;
                }
            }
        }
        void remove(cuberx::Base& object) override
        {
            for(auto & i : objects)
            {
                if(i == &object)
                {
                    i = nullptr;
                    object.setFatherMainWindow(nullptr);
                    object.setOffset(0,0);
                    object.resetFatherMainWindow();
                    return;
                }
            }
        }
        virtual cuberx::SubWindow& operator>>(cuberx::Base* object)
            {
            for(auto & i : objects)
            {
                if(i == object)
                {
                    i = nullptr;
                    object->setFatherMainWindow(nullptr);
                    object->setOffset(0,0);
                    object->resetFatherMainWindow();
                    return *this;//成功
                }
            }
            return *this;//失败
            }
        virtual cuberx::SubWindow& operator>>(cuberx::Base& object)
                {
            for(auto & i : objects)
            {
                if(i == &object)
                {
                    i = nullptr;
                    object.setFatherMainWindow(nullptr);
                    object.setOffset(0,0);
                    object.resetFatherMainWindow();
                    return *this;//成功
                }
            }
            return *this;//失败
                }
        virtual cuberx::SubWindow& operator-=(cuberx::Base* object)
        {
            for(auto & i : objects)
            {
                if(i == object)
                {
                    i = nullptr;
                    object->setFatherMainWindow(nullptr);
                    object->setOffset(0,0);
                    object->resetFatherMainWindow();
                    return *this;//成功
                }
            }
            return *this;//失败
        }
        virtual cuberx::SubWindow& operator-=(cuberx::Base& object)
            {
            for(auto & i : objects)
            {
                if(i == &object)
                {
                    i = nullptr;
                    object.setFatherMainWindow(nullptr);
                    object.setOffset(0,0);
                    object.resetFatherMainWindow();
                    return *this;//成功
                }
            }
            return *this;//失败
            }

        void setFatherMainWindow(cuberx::MainWindow* newFMW) override
        {
                for(auto *& i : objects)
                {
                    if(i != nullptr)
                    {
                        i->setFatherMainWindow(newFMW);
                    }
                }
                Base::setFatherMainWindow(newFMW);
        }
        void setLocation(short x, short y) override
        {
            drawNull(offset.x, offset.y);
            location.x = x;
            location.y = y;
        }
        void setSize(short width, short height) override
        {
            drawNull(offset.x, offset.y);
            size.width = width;
            size.height = height;
            setStyle((StyleType)style);
        }
        void setOffset(short x, short y) override
        {
            offset.x = x;
            offset.y = y;
            if(windowFrame != nullptr)
            {
                windowFrame->setOffset(location.x + offset.x, location.y + offset.y);
            }
            for(int i = 1; i < $CU_SUBWINDOW_OBJECTS_COUNT; ++i)
            {
                if(objects[i] != nullptr)
                {
                    objects[i]->setOffset(
                        location.x + subObjOffset.x + offset.x,
                        location.y + subObjOffset.y + offset.y
                        );
                }
            }
        }

        //绘制
        void draw(int drawObjectIndex = -1) {
            if (drawObjectIndex <= -1) {
                drawOnlyStyle(offset.x, offset.y);
                for (auto & object : objects) {
                    if (object != nullptr) {
                        if (object->getVisible()) {
                            object->draw(
                                location.x
                                + offset.x
                                + subObjOffset.x,
                                location.y
                                + offset.y
                                + subObjOffset.y);
                        }
                    }
                }
            } else
            {
                drawOnlyStyle(offset.x, offset.y);
                objects[drawObjectIndex]->draw(
                    location.x
                        + offset.x
                        + subObjOffset.x,
                    location.y
                        + offset.y
                        + subObjOffset.y);
            }
        }
        void draw(short offsetX, short offsetY) override
        {
            drawOnlyStyle(offsetX, offsetY);
            for(int i = 1; i < $CU_SUBWINDOW_OBJECTS_COUNT; ++i)
            {
                if(objects[i] != nullptr)
                {
                    objects[i]->draw(location.x + offsetX + subObjOffset.x, location.y + offsetY + subObjOffset.y);
                }
            }
        }
        void drawNull(short offsetX, short offsetY) override
        {
            for(int i = 0; i < size.height; ++i)
            {
                for(int j = 0; j < size.width * 2; ++j)
                {
                    WindowSetting::PointJump(
                        location.y
                        + offsetY
                        + i,
                        location.x
                        + offsetX
                        + j
                        );
                    cout << " ";
                }
            }
        }

        //注意：传参别加上location!这里有
        virtual void drawOnlyStyle(short offsetX, short offsetY)
        {
            windowFrame->draw(location.x + offsetX, location.y + offsetY);
        }

        //根据索引获取容器内对象
        virtual cuberx::Base* getObjectFromIndex(int index) {
            if (index >= 0 || index < $CU_SUBWINDOW_OBJECTS_COUNT) {
                return objects[index];
            } else {
                return nullptr;
            }
        }
        virtual cuberx::Base* operator[](int index) {
            if (index >= 0 || index < $CU_SUBWINDOW_OBJECTS_COUNT) {
                return objects[index];
            } else {
                return nullptr;
            }
        }

        //添加全局键位任务
        void addGKeyActionBefore(const cuberx::KeyTask& newKeyAction)
        {
            for(auto & i : keyTasksBefore)
            {
                if(i.Empty())
                {
                    i = newKeyAction;
                    return;
                }
            }
        }
        void addGKeyActionBefore(int key, cuberx::Base* this_base, int(*run)(cuberx::Base*))
        {
            for(auto & i : keyTasksBefore)
            {
                if(i.Empty())
                {
                    i.Set(key, this_base, run);
                    return;
                }
            }
        }
        void addGKeyActionAfter(const cuberx::KeyTask& newKeyAction)
        {
            for(auto & i : keyTasksAfter)
            {
                if(i.Empty())
                {
                    i = newKeyAction;
                    return;
                }
            }
        }
        void addGKeyActionAfter(int key, cuberx::Base* this_base, int(*run)(cuberx::Base*))
        {
            for(auto & i : keyTasksAfter)
            {
                if(i.Empty())
                {
                    i.Set(key, this_base, run);
                    return;
                }
            }
        }

        //选中切换
        void setNowChosingObject(int newChosingObject) override
        {
            objects[nowChosingObject]->setBeChosed(false);
            nowChosingObject = newChosingObject;
            objects[newChosingObject]->setBeChosed(true);
        }
        void setBeChosed(bool bBeChosed) override
        {
            objects[nowChosingObject]->setBeChosed(bBeChosed);
            beChosed = bBeChosed;
            if(bBeChosed)
            {
                whenBeChosed();
            }
            else
            {
                whenStopChosed();
            }
        }

        // 键盘监听（一帧内）[0为无响应,1为执行成功]
        int keyAction(int newKey) override {

            if(getVisible())
            {
                int result = 0;

                //全局键位(优先响应)
                for(auto &i: keyTasksBefore)
                {
                    if(i.GetKey() == newKey)
                    {
                        //寻找完成
                        result = i.Run();
                        if(result == 1)
                        {
                            return result;
                        }
                    }
                }


                //目前选中成员
                if(getNowChosingObject() >= 0)
                {
                    if(objects[getNowChosingObject()] != nullptr)
                    {
                        result = objects[getNowChosingObject()]->keyAction(newKey);
                        if(result == 1)
                        {
                            return result;
                        }
                    }
                }
                //遍历其它成员
                /*
                for (int i = 0; i < $CU_SUBWINDOW_OBJECTS_COUNT; i++) {
                    if (objects[i] != nullptr && i != getNowChosingObject()) {
                        result = objects[i]->keyAction(newKey);
                        if (result == 1) {
                            return result;
                        }
                    }
                }
                 */

                //全局键位(滞后响应)
                switch(newKey)
                {
                //上(左)翻
                case cuberx::Key::$UP:
                case cuberx::Key::$LEFT:
                {
                    //遍历前面部分（倒序）
                    if(getNowChosingObject() != 0)
                    {
                        for(int i = getNowChosingObject() - 1; i >= 0; i--)
                        {
                            if(objects[i] != nullptr && objects[i]->getCanBeChosed() == 1)
                            {
                                setNowChosingObject(i);
                                result = 1;
                                return result;
                            }
                        }
                    }
                    //遍历全部（在上面代码块未成功情况下）（倒序）
                    for(int i = $CU_SUBWINDOW_OBJECTS_COUNT - 1; i >= 0; i--)
                    {
                        if(objects[i] != nullptr && objects[i]->getCanBeChosed() == 1)
                        {
                            setNowChosingObject(i);
                            result = 1;
                            return result;
                        }
                    }
                }
                break;

                //下(右)翻
                case cuberx::Key::$DOWN:
                case cuberx::Key::$RIGHT:
                {
                    //遍历剩余部分（正序）
                    if(getNowChosingObject() != $CU_SUBWINDOW_OBJECTS_COUNT - 1)
                    {
                        for(int i = 1 + getNowChosingObject(); i < $CU_SUBWINDOW_OBJECTS_COUNT; i++)
                        {
                            if(objects[i] != nullptr && objects[i]->getCanBeChosed() == 1)
                            {
                                setNowChosingObject(i);
                                result = 1;
                                return result;
                            }
                        }
                    }
                    //遍历全部（在上面代码块未成功情况下）（正序）
                    for(int i = 0; i < $CU_SUBWINDOW_OBJECTS_COUNT; i++)
                    {
                        if(objects[i] != nullptr && objects[i]->getCanBeChosed() == 1)
                        {
                            setNowChosingObject(i);
                            result = 1;
                            return result;
                        }
                    }
                }
                break;
                default:
                    for(auto &i: keyTasksAfter)
                    {
                        if(i.GetKey() == newKey)
                        {
                            //寻找完成
                            result = i.Run();
                            if(result == 1)
                            {
                                return result;
                            }
                        }
                    }
                    break;
                }
                return result;
            }
            else
            {
                return 0;
            }
        }//keyAction(...)

        // 风格
        virtual void setStyle(StyleType newStyle)
        {
            if(windowFrame != nullptr)
            {
                delete windowFrame;
                windowFrame = nullptr;
            }
            switch(newStyle)
            {
            case StyleType::NOTHING:
                windowFrame = new frame_NOTHING();
                break;
            case StyleType::FRAME:
                windowFrame = new frame_FRAME(size.width, size.height);
                break;
            case StyleType::TEXT_ON_FRAME:
                windowFrame = new frame_TEXT_ON_FRAME(text, size.width, size.height);
                break;
            case StyleType::TEXT_IN_FRAME:
                windowFrame = new frame_TEXT_IN_FRAME(text, size.width, size.height);
                break;
            case StyleType::CLOSE_BUTTON_FRAME:
                windowFrame = new frame_CLOSE_BUTTON_FRAME(size.width, size.height);
                break;
            case StyleType::CLOSE_BUTTON_AND_TEXT_IN_FRAME:
                windowFrame = new frame_CLOSE_BUTTON_AND_TEXT_IN_FRAME(text, size.width, size.height);
                break;
            }
            draw(offset.x, offset.y);
        }
        virtual StyleType getStyle()
        {
            return (StyleType)style;
        }

        //关闭
        void exit()
        {
            drawNull(offset.x, offset.y);
            setVisible(false);
            setCanBeChosed(false);
            for(int i = 0; i < $CU_SUBWINDOW_OBJECTS_COUNT; ++i)
            {
                if(objects[i] != nullptr)
                {
                    objects[i]->setVisible(false);
                }
            }
        }
    };
}

//FPSText 帧率显示器
namespace cuberx
{
    class FPSText : public cuberx::TipBar
    {
    private:
        UINT testTime;
        DWORD last_check_time{};
        DWORD now_tick_time{};
        UINT tick_per_second_counter{};
        UINT tick_per_second_result{};

    public:
        FPSText(short x, short y, UINT newTestTime = 1, const string& text = "FPS:") : cuberx::TipBar(text, "   ","","CCCCCCC",x,y,false,false,text.length() + 5,3)
        {
            testTime = newTestTime;
        }
        void setFatherMainWindow(cuberx::MainWindow* newFMW) override
        {
            if(getFatherMainWindow() != nullptr)
            {
                getFatherMainWindow()->getTaskInfoFromTag(40)->reset();
            }
            if(newFMW != nullptr)
            {
                if(newFMW->getTaskInfoFromTag(40) == nullptr)
                {
                    newFMW->setTask(
                        newFMW->getNewTask(),
                        this,
                        40,
                        [](cuberx::Base* this_base)->void{
                            auto * this_FPSText = dynamic_cast<cuberx::FPSText*>(this_base);
                            ++this_FPSText->tick_per_second_counter;
                            this_FPSText->now_tick_time = GetTickCount();
                            if(this_FPSText->last_check_time - this_FPSText->last_check_time % 1000 <= this_FPSText->now_tick_time - this_FPSText->now_tick_time % 1000 - 1000 * this_FPSText->testTime)
                            {
                                this_FPSText->tick_per_second_result = (UINT)(this_FPSText->tick_per_second_counter / this_FPSText->testTime);
                                this_FPSText->tick_per_second_counter = 0;
                                this_FPSText->last_check_time = this_FPSText->now_tick_time;
                                this_FPSText->update();
                            }
                        },//lambda
                        0,
                        true
                        );//setTask(...)
                }
            }

            cuberx::Group<3>::setFatherMainWindow(newFMW);
            last_check_time = 0;
            now_tick_time = 0;
            tick_per_second_counter = 0;
        }
        void update()
        {
            setCLText(to_string(tick_per_second_result),"","CcCcCc");
            TipBar::drawNull(offset.x,offset.y);
            TipBar::draw(offset.x,offset.y);
        }
    };
}

//InputBar 输入栏
namespace cuberx
{
    //InputBar 输入栏
    class InputBar : public cuberx::Module
    {
    private:
        BYTE mode;
        BYTE cursorLocation;
        int lastKey;

    private:
        static void $Cursor_On(cuberx::Base* this_base)
        {
            if(this_base->getBeChosed())
            {
                auto *pInputBar = dynamic_cast<cuberx::InputBar *>(this_base);
                WindowSetting::PointJump(
                    pInputBar->getLocation().y
                    + pInputBar->getOffset().y,
                    pInputBar->getLocation().x
                    + pInputBar->getOffset().x
                    + pInputBar->getCursorLocation()
                    );
                cout << "_";
                this_base->getFatherMainWindow()->setTask(
                    this_base->getFatherMainWindow()->getNewTask(),
                    this_base,
                    50,
                    $Cursor_Off,
                    100
                    );
            }
        }
        static void $Cursor_Off(cuberx::Base* this_base)
        {
                auto *pInputBar = dynamic_cast<cuberx::InputBar *>(this_base);
                WindowSetting::PointJump(
                    pInputBar->getLocation().y
                    + pInputBar->getOffset().y,
                    pInputBar->getLocation().x
                    + pInputBar->getOffset().x
                    );
                pInputBar->draw(pInputBar->getCursorLocation());
                if(this_base->getBeChosed())
                {
                    this_base->getFatherMainWindow()->setTask(
                        this_base->getFatherMainWindow()->getNewTask(),
                        this_base,
                        50,
                        $Cursor_On,
                        100
                        );
                }
        }

    public:
        InputBar(short width, short height, short x, short y, const string& defaultText = "",BYTE mode = 0)
        {
            size.width = width;
            size.height = height;
            location.x = x;
            location.y = y;
            text = defaultText;
            this->mode = mode;
            cursorLocation = text.length();
            canBeChosed = true;
            lastKey = 0;
        }
        virtual void input(char newChar)
        {
            if(text.length() < size.width)
            {
                if(cursorLocation < text.length())
                {
                    string temp;
                    temp.push_back(newChar);
                    text.insert(cursorLocation, temp);
                    draw(offset.x, offset.y);
                    ++cursorLocation;
                }
                else
                {
                    text += newChar;
                    draw(offset.x, offset.y);
                    ++cursorLocation;
                }
            }
        }
        virtual void backspace()
        {
            if(text.length() >= 1 && cursorLocation != 0)
            {
                text.erase(cursorLocation - 1, 1);
                --cursorLocation;
                drawNull(offset.x, offset.y);
                draw(offset.x, offset.y);
            }
        }
        virtual BYTE getCursorLocation()
        {
            return cursorLocation;
        }
        virtual void setCursorLocation(BYTE newCursorLocation)
        {
            if(newCursorLocation >= 0 && newCursorLocation <= size.width)
            {
                cursorLocation = newCursorLocation;
                drawNull(offset.x, offset.y);
                draw(offset.x, offset.y);
                WindowSetting::PointJump(
                    location.y + offset.y,
                    location.x + offset.x + cursorLocation
                    );
                cout << "_";
            }
        }
        //Chose选中事件
        void whenBeChosed() override
        {
            beChosed = true;
            getFatherMainWindow()->setTask(
                getFatherMainWindow()->getNewTask(),
                this,
                50,
                $Cursor_On,
                100
                );
        }
        void whenStopChosed() override
        {
            beChosed = false;
        }
        //绘制
        void draw(short offsetX, short offsetY) override
        {
            WindowSetting::PointJump(location.y + offsetY, location.x + offsetX);
            cout << text;
        }
        virtual void draw(UINT index = 0)
        {
            WindowSetting::PointJump(
                location.y + offset.y,
                location.x + offset.x + index
                );
            if(index < text.length())
            {
                cout << text[index];
            }
            else
            {
                cout << " ";
            }
        }
        void drawNull(short offsetX, short offsetY) override
        {
            string null_str{};
            for(int i = 0; i < size.x + 1; i++)
            {
                null_str += " ";
            }
            for(int i = 0; i < size.y; i++)
            {
                WindowSetting::PointJump(short(location.y + offsetY + i), short(location.x + offsetX));
                cout << null_str;
            }
        }

        int keyAction(int newKey) override
        {
            if(getBeChosed())
            {
                if(lastKey == 224)
                {
                    switch(newKey)
                    {
                    case Key::$LEFT:
                        setCursorLocation(getCursorLocation() - 1);
                        lastKey = Key::$LEFT;
                        return 1;
                        break;
                    case Key::$RIGHT:
                        if(cursorLocation < text.length())
                        {
                            setCursorLocation(getCursorLocation() + 1);
                            lastKey = Key::$RIGHT;
                        }
                        return 1;
                        break;
                    default:
                        return 0;
                        break;
                    }
                }
                else if((newKey >= 32 && newKey <= 126))
                {
                    input((char)newKey);
                    lastKey = newKey;
                    return 1;
                }
                else if(newKey == Key::$BACK_SPACE)
                {
                    backspace();
                    lastKey = Key::$BACK_SPACE;
                }
                else
                {
                    lastKey = newKey;
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
    };
}// namespace cuberx

//FrameInput 带边框的输入栏
namespace cuberx
{
    class FrameInput : public cuberx::Group<2>
    {
    private:
        cuberx::ARectFrame* arf;
        cuberx::InputBar* inputBar;

    public:
        FrameInput(short width, short height, short x, short y, const string& defaultText, BYTE mode)
        {
            arf = new ARectFrame(width, height, 0, 0);
            inputBar = new InputBar(width - 4, height - 2, 2, 1, defaultText, mode);
            canBeChosed = true;
            objects[0] = arf;
            objects[1] = inputBar;
            Group<2>::setLocation(x, y);
            size.width = width;
            size.height = height;
        }
        virtual string getText()
        {
            return objects[1]->getText();
        }
        void whenBeChosed() override
        {
            inputBar->whenBeChosed();
        }
        void whenStopChosed() override
        {
            inputBar->whenStopChosed();
        }
        int keyAction(int newKey)
        {
            return objects[1]->keyAction(newKey);
        }
    };
}

//Loading 加载动画
namespace cuberx
{
    // Loading 加载动画
    class Loading : public cuberx::Module
    {
    private:
        static void $action(cuberx::Base* this_base)
        {
            if(this_base->getVisible())
            {

                cuberx::Loading *this_Loading = dynamic_cast<cuberx::Loading *>(this_base);
                //光标跳转
                WindowSetting::PointJump(
                    this_base->getLocation().y
                    + this_base->getOffset().y,
                    this_base->getLocation().x
                    + this_base->getOffset().x
                    );
                //输出动画
                BYTE sleepTick = 0;
                switch(this_Loading->getNowActionIndex())
                {
                case 0:
                    cout << "          ";
                    sleepTick = 100;
                    break;
                case 1:
                    cout << " .        ";
                    sleepTick = 8;
                    break;
                case 2:
                    cout << "     .    ";
                    sleepTick = 8;
                    break;
                case 3:
                    cout << "       .  ";
                    sleepTick = 8;
                    break;
                case 4:
                    cout << ".      .  ";
                    sleepTick = 8;
                    break;
                case 5:
                    cout << "    .  .  ";
                    sleepTick = 8;
                    break;
                case 6:
                    cout << "     . .  ";
                    sleepTick = 8;
                    break;
                case 7:
                    cout << "      ..  ";
                    sleepTick = 8;
                    break;
                case 8:
                    cout << ".     ..  ";
                    sleepTick = 8;
                    break;
                case 9:
                    cout << "   .  ..  ";
                    sleepTick = 8;
                    break;
                case 10:
                    cout << "    . ..  ";
                    sleepTick = 8;
                    break;
                case 11:
                    cout << "     ...  ";
                    sleepTick = 8;
                    break;
                case 12:
                    cout << ".    ...  ";
                    sleepTick = 8;
                    break;
                case 13:
                    cout << "   . ...  ";
                    sleepTick = 8;
                    break;
                case 14:
                    cout << "    ....  ";
                    sleepTick = 8;
                    break;
                case 15:
                    cout << ".   ....  ";
                    sleepTick = 8;
                    break;
                case 16:
                    cout << "  . ....  ";
                    sleepTick = 8;
                    break;
                case 17:
                    cout << "   .....  ";
                    sleepTick = 8;
                    break;
                case 18:
                    cout << ".  .....  ";
                    sleepTick = 8;
                    break;
                case 19:
                    cout << "  ......  ";
                    sleepTick = 80;
                    break;
                case 20:
                    cout << "  .....  .";
                    sleepTick = 8;
                    break;
                case 21:
                    cout << "  .....   ";
                    sleepTick = 8;
                    break;
                case 22:
                    cout << "  .... .  ";
                    sleepTick = 8;
                    break;
                case 23:
                    cout << "  ....   .";
                    sleepTick = 8;
                    break;
                case 24:
                    cout << "  ....    ";
                    sleepTick = 8;
                    break;
                case 25:
                    cout << "  ... .   ";
                    sleepTick = 8;
                    break;
                case 26:
                    cout << "  ...  .  ";
                    sleepTick = 8;
                    break;
                case 27:
                    cout << "  ...    .";
                    sleepTick = 8;
                    break;
                case 28:
                    cout << "  ...     ";
                    sleepTick = 8;
                    break;
                case 29:
                    cout << "  .. .    ";
                    sleepTick = 8;
                    break;
                case 30:
                    cout << "  ..  .   ";
                    sleepTick = 8;
                    break;
                case 31:
                    cout << "  ..    . ";
                    sleepTick = 8;
                    break;
                case 32:
                    cout << "  ..      ";
                    sleepTick = 4;
                    break;
                case 33:
                    cout << "  . .     ";
                    sleepTick = 4;
                    break;
                case 34:
                    cout << "  .  .    ";
                    sleepTick = 4;
                    break;
                case 35:
                    cout << "  .     . ";
                    sleepTick = 4;
                    break;
                case 36:
                    cout << "  .       ";
                    sleepTick = 1;
                    break;
                case 37:
                    cout << "  .       ";
                    sleepTick = 1;
                    break;
                case 38:
                    cout << "  .       ";
                    sleepTick = 1;
                    break;
                case 39:
                    cout << "   .      ";
                    sleepTick = 8;
                    break;
                case 40:
                    cout << "    .     ";
                    sleepTick = 8;
                    break;
                case 41:
                    cout << "       .  ";
                    sleepTick = 8;
                    break;
                case 42:
                    cout << "          ";
                    sleepTick = 50;
                    break;
                }
                //更新nowActionIndex
                if(this_Loading->getNowActionIndex() == 42)
                {
                    this_Loading->setNowActionIndex(0);
                }
                else
                {
                    this_Loading->setNowActionIndex(this_Loading->getNowActionIndex() + 1);
                }
                //创建任务
                this_base->getFatherMainWindow()->setTask(
                    this_base->getFatherMainWindow()->getNewTask(),
                    this_base,
                    55,
                    $action,
                    sleepTick,
                    true
                    );
            }
        }

    public:
        BYTE nowActionIndex;


    public:
        Loading(short x, short y)
        {
            location.x = x;
            location.y = y;
            size.width = 10;
            size.height = 1;
        }

        //nowActionIndex
        virtual BYTE getNowActionIndex()
        {
            return nowActionIndex;
        }
        virtual void setNowActionIndex(BYTE newActionIndex)
        {
            nowActionIndex = newActionIndex;
        }

        //绘制
        void draw(short offsetX, short offsetY) override
        {
            setOffset(offsetX, offsetY);
            if(getFatherMainWindow()->getTaskInfoFromTag(55) == nullptr)
            {
                getFatherMainWindow()->setTask(
                    getFatherMainWindow()->getNewTask(),
                    this,
                    55,
                    $action,
                    2,
                    true);
            }
        }

    };
}// namespace cuberx

//StaticImage 静态图像
namespace cuberx
{
    //StaticImage 静态图像
    class StaticImage : public cuberx::Module
    {
    private:
        SuperArray1<string> image;

    public:
        StaticImage()
        {
            setLocation(0,0);
            size.width = 0;
            size.height = 0;
        }
        StaticImage(short width, short height, short x, short y, SuperArray1<string>& image)
        {
            location.x = x;
            location.y = y;
            size.width = width;
            size.height = height;
            this->image.reset(height);
            for(int i = 0; i < height; ++i)
            {
                this->image[i] = move(image[i]);
            }
        }

        //绘制
        void draw(short offsetX, short offsetY)
        {
            if(bVisible)
            {
                for(int i = 0; i < size.height; ++i)
                {
                    WindowSetting::PointJump(
                        location.y + offsetY + i,
                        location.x + offsetX);
                    cout << image[i];
                }// for i
            }
        }

    };
}// namespace cuberx

#endif
