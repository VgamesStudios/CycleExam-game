/***********************************************
 *This is a game                               * 
 *But I'm too lazy to write the opening comment*
 *So I don't really have anything to say       *
 *May the force be with you                    *
 ***********************************************/

#include "function_1.h"
int main()
{
        CLEAR_SCREEN;
    // 生成日志文件名：YYYYMMDD_HHMMSS.log（以程序启动时间为准）
    time_t now = time(nullptr);                                            // 获取当前时间戳
    tm* local_time = localtime(&now);                                      // 转换为本地时间结构
    char filename[64];
    strftime(filename, sizeof(filename), "%Y%m%d_%H%M%S.log", local_time); // 格式化

    fout.open(filename);                                                   // 打开文件
    if (!fout.is_open()) 
    {
        cerr << "警告：无法创建日志文件 " << filename << endl;
    }
    string current_page = "page_main";
    while (true)
    {
        auto &inf = pageMap[current_page];
        inf.function();
        int switchs = getNum(1, inf.jump_pages.size() - 1); // 获取选项
        if (switchs)
        {
            CLEAR_SCREEN;
        }

        // 判断当前页面是否为设置项页面（set_0、set_1、set_2...）
        static const std::regex setPagePattern(R"(^set_(\d+)$)");
        std::smatch match;
        if (std::regex_match(current_page, match, setPagePattern))
        {
            // 从页面名中提取设置项索引
            int setIndex = std::stoi(match[1].str());
            // 最后一个选项永远是“返回”，其余有效选项都视为“应用设置”
            if (switchs >= 1 && switchs < static_cast<int>(inf.jump_pages.size()) - 1)
            {
                setApply(setIndex, switchs);
            }
        }

        current_page = inf.jump_pages[switchs];
        if (current_page.empty())
        {
            current_page = inf.jump_pages[0];
        }
    }
    PAUSE_PROGRAM;
    return 0;
}
