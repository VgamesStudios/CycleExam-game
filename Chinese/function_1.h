#ifndef FUNCTION_1_H
#define FUNCTION_1_H

// 导入库
#include <regex>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <variant>
#include <ctime>
#include <thread>
#include <chrono>
#include <iomanip>

// 导入自定义库
#include "set_1.h"

// 导入平台专属库
#ifdef _WIN32
    #include <windows.h>
    #include <mmsystem.h>
    #define CLEAR_SCREEN system("cls")
    #define PAUSE_PROGRAM system("pause")
    // 以MSVC方式链接库
    #ifdef _MSC_VER
        #pragma comment(lib, "winmm.lib")
    #endif
#else
    #define PlaySound(a, b, c) ((void)0)
    #define TEXT(a) a
    #define SND_FILENAME 0
    #define SND_ASYNC 0
    #define SND_LOOP 0
    #define CLEAR_SCREEN system("clear")
    #define PAUSE_PROGRAM do { cin.ignore(numeric_limits<streamsize>::max(), '\n');cout << "按任意键继续..." << endl; cin.get(); } while(0)
#endif

// 声明命名空间
using namespace std;
// 声明函数
int getNum(int min, int max); // 输入校验函数
void autoRestarter();         // 自动重启函数
void page_main();             // 游戏主菜单
void page_exit();             // 退出游戏 
void page_intro();            // 游戏简介
void page_setting();          // 游戏设置
void page_changeLog();        // 版本更新日志
void set_0();                 // 设置_游戏难度
void set_1();                 // 设置_Debug模式
void chapter_1();             // 第一章_家
void chapter_2();             // 第二章_路上
void chapter_3();             // 第三章_学校
void page_1();                // 游戏开始剧情
void page_2();                // 睡过头了
void page_3();                // 继续睡觉1
void page_4();                // 继续睡觉2
void page_5();                // 结局：不醒人室（Bed End 1）
void page_6();                // 前往学校
void page_7();
void page_8();
void page_9();
void page_10();
void page_11();
void page_12();
void page_13();
void page_14();
void page_15();
void page_16();
void page_17();
void page_18();
void page_19();
void page_20();
void page_21();
void page_22();
void page_23();
void page_24();
void page_25();
void page_26();
void page_27();
void page_28();
void page_29();
void page_30();
void page_31();
void page_32();
void page_33();
void page_34();
void page_35();
void page_36();
void page_37();
void page_38();
void page_39();
void page_40();
void page_41();
void page_42();
void page_43();
void page_44();
void page_45();
void page_46();
void page_47();
void page_48();
void page_49();
void page_50();
void page_51();
void page_52();
void page_53();
void page_54();
void page_55();
void page_56();
void page_57();
void page_58();
void page_59();
void page_60();
void page_61();
void page_62();
void page_63();
void page_64();
void page_65();
void page_66();
void page_67();
void page_68();
void page_69();
void page_70();
void page_71();
void page_72();
void page_73();
void page_74();
void page_75();
void page_76();
void page_77();
void page_78();
void page_79();
void page_80();
void page_81();
void page_82();
void page_83();
void page_84();
void page_85();
void page_86();
void page_87();
void page_88();
void page_89();
void page_90();
void page_91();
void page_92();
void page_93();
void page_94();
void page_95();
void page_96();
void page_97();
void page_98();
void page_99();
void page_100();
// 定义全局变量
int switchs = 0;
int sleepSubjects = 0;
bool inPageMain = true;
bool autoRestarted = false;
int setProject = 0;
int setSwitch = 0;
bool debugMode = false; 
ofstream fout; // 全局文件输出流
// 定义函数及结构体
struct PageInformation
{
    std::function<void()> function;
    std::vector<std::string> jump_pages;
};
/// 代理类，同时持有 cout 和 fout 两个输出流，并在每行行首加时间戳和标签
class CFOut
{
private:
    ostream &os1;      // 控制台流 (cout)
    ostream &os2;      // 文件流 (fout)
    std::string tag;   // 日志标签
    bool isDebugMsg;   // 是否为调试类消息（INPUT/STATE/SYS）

    // 全局行首标志：为 true 表示下一个输出需要打时间戳
    static bool &atLineStart()
    {
        static bool flag = true;
        return flag;
    }

    // 生成 [HH:MM:SS.mmm] 形式的时间戳字符串
    static std::string getTimestamp()
    {
        auto now = chrono::system_clock::now();
        auto ms = chrono::duration_cast<chrono::milliseconds>(
                      now.time_since_epoch()) %
                  1000;
        time_t t = chrono::system_clock::to_time_t(now);
        tm *lt = localtime(&t);

        char buf[16];
        strftime(buf, sizeof(buf), "[%H:%M:%S", lt);

        ostringstream oss;
        oss << buf << "." << setfill('0') << setw(3) << ms.count() << "] ";
        return oss.str();
    }

    // 若当前处于行首，先输出时间戳和标签
    void ensureTimestamp()
    {
        if (atLineStart())
        {
            std::string ts = getTimestamp();

            // 调试类消息 且 debugMode 开启 → 控制台显示带标签的时间戳
            if (isDebugMsg && debugMode)
            {
                os1 << ts << tag << " ";
            }
            // 普通游戏输出（cfout）在控制台不加任何前缀（保持干净）

            // 文件流：永远都写 时间戳 + 标签
            os2 << ts << tag << " ";

            atLineStart() = false;
        }
    }

public:
    // 构造函数：t = 标签；dbg = 是否属于调试类消息
    CFOut(ostream &o1, ostream &o2,
          const std::string &t = "[Output/INFO]",
          bool dbg = false)
        : os1(o1), os2(o2), tag(t), isDebugMsg(dbg) {}

    // 泛型 operator<<，处理所有可输出类型
    template <typename T>
    CFOut &operator<<(const T &val)
    {
        ensureTimestamp();

        // 普通消息（cfout）永远写控制台；调试消息仅当 debugMode 开启时写控制台
        if (!isDebugMsg || debugMode)
        {
            os1 << val;
        }
        os2 << val;

        using U = std::decay_t<T>;
        if constexpr (std::is_convertible_v<U, std::string>)
        {
            std::string s = val;
            if (!s.empty() && s.back() == '\n')
                atLineStart() = true;
        }
        else if constexpr (std::is_same_v<U, char>)
        {
            if (val == '\n')
                atLineStart() = true;
        }
        return *this;
    }

    // 专门处理 endl 等操纵符
    CFOut &operator<<(ostream &(*manip)(ostream &))
    {
        ensureTimestamp();

        if (!isDebugMsg || debugMode)
        {
            os1 << manip;
        }
        os2 << manip;

        if (manip == static_cast<ostream &(*)(ostream &)>(std::endl))
            atLineStart() = true;

        return *this;
    }
};
// 基础输出宏
#define cfout    CFOut(cout, fout)
// 调试类宏（仅当 debugMode == true 时输出到控制台，文件始终记录）
#define cfinputI CFOut(cout, fout, "[INPUT/INFO]",  true)
#define cfstateI CFOut(cout, fout, "[STATE/INFO]",  true)
#define cfsysI   CFOut(cout, fout, "[SYS/INFO]  ",  true)
#define cfinputW CFOut(cout, fout, "[INPUT/WARN]",  true)
#define cfstateW CFOut(cout, fout, "[STATE/WARN]",  true)
#define cfsysW   CFOut(cout, fout, "[SYS/WARN]  ",  true)
#define cfinputE CFOut(cout, fout, "[INPUT/ERROR]", true)
#define cfstateE CFOut(cout, fout, "[STATE/ERROR]", true)
#define cfsysE   CFOut(cout, fout, "[SYS/ERROR] ",  true)
int getNum(int min, int max) // 输入校验函数（参数为可输入的最小值和最大值）
{
    int n;
    // 输入不是数字 或 超出范围 → 重新输入
    if (!(cin >> n) || n < min || n > max)
    {
        cin.clear();                                         // 重置输入缓冲区
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 丢弃错误输入
        CLEAR_SCREEN;
        cfout << "只能输入" << min << "-" << max << "的数字！\n\n";
        return 0; // 返回0标记输入错误（执行default）
    }
    return n; // 输入有效则返回选项编号
}
void autoRestarter()
{
    if (!autoRestarted)
    {
        autoRestarted = true;
        thread
        ([](){
            while(true)
            {
                this_thread::sleep_for(chrono::minutes(autoRestarterMinutes));
                if (!inPageMain&&autoRestart)
                {
                    cfout<<"1"<<endl;
                }
            }
        })
            .detach();
        /*thread
        ([](){
            while(true)
            {
                this_thread::sleep_for(chrono::seconds(1));
                cfout<<"Hello World"<<endl;
            } 
        })
            .detach();*/
    }
}
void page_main() // 游戏主菜单
{
    //PlaySound(TEXT("./assets/audio/CycleExam.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    inPageMain = true;
    cfout << "********************\n";
    cfout << "*                  *\n";
    cfout << "*     轮回答卷     *\n";
    cfout << "*                  *\n";
    cfout << "*            26w20a*\n";
    cfout << "********************\n";
    cfout << "[1]开始游戏 [2]游戏简介 [3]游戏设置 [4]更新日志 [5]退出游戏\n";
}
void page_exit()
{
    PlaySound(NULL, NULL, 0);
    if(inPageMain)
    {
        cfout << "存档已保存\n";
        cfout << "游戏已正常退出，退出代码为0x00000000\n";
        PAUSE_PROGRAM;
        exit(0x00000000);
    }
}
void page_intro() // 游戏简介
{
    inPageMain = false;
    cfout << "《轮回答卷》是一款基于文字的选择冒险游戏，\n";
    cfout << "玩家将扮演一名即将面临中考的学生。\n";
    cfout << "从一个普通的早晨开始，你将面对一系列关键决策，\n";
    cfout << "每一个选择都可能影响故事的走向。\n";
    cfout << "游戏以简洁的文字叙述和分支选项为核心，\n";
    cfout << "探索日常生活中的抉择与后果。\n";
    cfout << "适合喜欢“轻松”互动故事的玩家体验，\n";
    cfout << "当前版本为预览版，部分剧情仍在开发中。\n";
    cfout << "[1]回到主菜单\n";
}
void page_setting() // 游戏设置
{
    inPageMain = false;
    cfout << "set_0:游戏难度\n";
    cfout << "set_1:Debug模式\n";
    cfout << "[1]回到主菜单 [设置项编号+2]对应设置项\n";
}
void set_0() // 设置_游戏难度
{
    setProject = 0;
    cfout << "本设置项用于调整游戏难度\n";
    cfout << "当前版本游戏难度仅影响自动循环时间\n";
    cfout << "难度越高，自动循环时间越短\n";
    cfout << "极简单：不自动循环\n";
    cfout << "简单：每30分钟自动循环一次\n";
    cfout << "中等：每20分钟自动循环一次\n";
    cfout << "困难：每10分钟自动循环一次\n";
    cfout << "请选择游戏难度：\n";
    cfout << "当前游戏难度：";
    switch(setProjects[setProject])
    {
        case 0: cfout << "未设置\n"; break;
        case 1: cfout << "极简单\n"; break;
        case 2: cfout << "简单\n"; break;
        case 3: cfout << "中等\n"; break;
        case 4: cfout << "困难\n"; break;
        default: cfout << "未知\n"; break;
    }
    cfout << "[1]选择极简单难度 [2]选择简单难度 [3]选择中等难度 [4]选择困难难度 [5]返回设置菜单\n";
}
void set_1() // 设置_Debug模式
{
    cfout << "本设置项用于开启/关闭 Debug 模式\n";
    cfout << "开启后，控制台会实时显示 INPUT / STATE / SYS 类日志\n";
    cfout << "关闭后，这些日志只记录到 .log 文件，不影响游戏界面\n";
    cfout << "当前状态：" << (debugMode ? "已开启" : "已关闭") << "\n";
    cfout << "[1]开启 [2]关闭 [3]返回设置菜单\n";
}
void page_changeLog() // 版本更新日志
{
    inPageMain = false;
    string relativePath = "changeLog.md";
    char absolutePath[512] = {0}; // 统一用 512 替代 MAX_PATH
    #ifdef _WIN32
        DWORD pathLen = GetFullPathNameA(relativePath.c_str(), sizeof(absolutePath), absolutePath, NULL);
    #else
        // Linux 下获取绝对路径
        char* res = realpath(relativePath.c_str(), absolutePath);
        int pathLen = res ? 1 : 0;
    #endif
    ifstream logFile(relativePath);
    string line;
    if (logFile.is_open()) // 判断日志文件是否成功打开
    {
        cfout << "==================== 版本更新日志 ====================\n";
        while (getline(logFile, line)) // 逐行读取日志内容
        {
            cfout << line << endl;
        }
        logFile.close();
    }
    else // 无法打开日志文件
    {
        cfout << "无法读取更新日志文件！\n";
        if (pathLen > 0)
        {
            cfout << "文件绝对路径：" << absolutePath << "\n";
        }
        else
        {
            cfout << "文件相对路径：" << relativePath << "\n";
        }
        cfout << "请检查更新日志(changeLog.md)是否存在于主程序(main.exe)同目录下或已通过其他途径打开！\n";
    }
    cfout << "==================================================\n";
    cfout << "[1]回到主菜单\n";
}
void chapter_1() // 第一章_家
{
    inPageMain = false;
    cfout << "                        第一章 家                  \n";
    cfout << "--------------------------------------------------\n";
    cfout << "                     周围很安静                    \n";
    cfout << "    你能听到的，只有墙上老旧挂钟那略显沉重的滴答声    \n";
    cfout << "           空气里有一股属于阴雨天的潮湿味道          \n";
    cfout << "        你在这个熟悉又略显压抑的房间里，闭着眼        \n";
    cfout << "                      突然——                       \n";
    cfout << "                      [1]继续                      \n";
}
void page_1() // 游戏开始剧情
{
    inPageMain = false;
    autoRestarter();
    cfout << "叮铃铃铃！\n";
    cfout << "闹钟响了，你从睡梦中醒来\n";
    cfout << "你伸了个懒腰，睁开了眼\n";
    cfout << "一个美丽的早晨，但天阴阴沉沉的，像是要下雨一样\n";
    cfout << "你突然想起来今天要中考了，但还有半小时就要开考第一科了，你决定\n";
    cfout << "[1]再睡一会 [2]立刻前往学校\n";
}
void page_2() // 睡过头了
{
    sleepSubjects++;
    cfout << "你已经睡过一个科目了\n";
    cfout << "趁现在起床去考试也许还能拿一些分数\n";
    cfout << "但你又想着这床如此舒服，而且就算起床也不会有好的成绩，你决定\n";
    cfout << "[1]继续睡觉 [2]立刻前往学校\n";
}
void page_3() // 继续睡觉1
{
    sleepSubjects++;
    cfout << "你真是个睡神\n";
    cfout << "吉尼斯世界纪录都应该给你颁个奖\n";
    cfout << "但现在说这些又有什么用呢\n";
    cfout << "你又睡过了一个科目\n";
    cfout << "现在已经没有什么去考试的意义了，你决定\n";
    cfout << "[1]继续睡觉 [2]立刻前往学校\n";
}
void page_4() // 继续睡觉2
{
    sleepSubjects++;
    cfout << "睡神，你赢了\n";
    cfout << "三场考试都已经结束了\n";
    cfout << "而你却还在床上舒服的躺着\n";
    cfout << "现在绝对没有再去考试的必要性了，你决定\n";
    cfout << "[1]继续睡觉 [2]立刻前往学校\n";
}
void page_5() // 结局：不醒人室（Bed End 1）
{
    cfout << "你不禁对自己发问\n";
    cfout << "这样做有什么意义吗\n";
    cfout << "与其浪费时间，不如去考场随便蒙两道题\n";
    cfout << "但现在说什么也没用了\n";
    cfout << "考试已经结束了，你完全没有做哪怕一题\n";
    cfout << "你突然想起你之前玩的某个六字游戏的一句话...\n";
    cfout << "--------------------------------------------------\n";
    cfout << "----------达成结局Bed End 1 【不醒人室】----------\n";
    cfout << "--------愿此行，终抵群星，且容我，再睡一会--------\n";
    cfout << "--------------------------------------------------\n";
    cfout << "[1]回到主菜单\n";
}
/*void page_6() // 前往学校
{
    cfout<<"\n";
}*/
map<string, PageInformation> pageMap =
    {
        {"page_main", {page_main, {"page_main", "chapter_1", "page_intro", "page_setting", "page_changeLog", "page_exit"}}},
        {"page_exit", {page_exit, {"page_exit"}}},
        {"page_intro", {page_intro, {"page_intro", "page_main"}}},
        {"page_setting", {page_setting, {"page_setting", "page_main", "set_0","set_1"}}},
        {"set_0", {set_0, {"set_0", "page_setting", "page_setting", "page_setting", "page_setting", "page_setting"}}},
        {"set_1", {set_1, {"set_1", "page_setting", "page_setting", "page_setting"}}},
        {"page_changeLog", {page_changeLog, {"page_changeLog", "page_main"}}},
        {"chapter_1", {chapter_1, {"chapter_1", "page_1"}}},
        {"page_1", {page_1, {"page_1", "page_2" /*, "page_6"*/}}},
        {"page_2", {page_2, {"page_2", "page_3" /*, "page_6"*/}}},
        {"page_3", {page_3, {"page_3", "page_4" /*, "page_6"*/}}},
        {"page_4", {page_4, {"page_4", "page_5" /*, "page_6"*/}}},
        {"page_5", {page_5, {"page_5", "page_main"}}},
};
#endif
