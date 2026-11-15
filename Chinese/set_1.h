#ifndef SET_1_H
#define SET_1_H
// 导入库
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
// 声明命名空间
using namespace std;
// 声明函数
void setApply(int sP,int sS);// 应用设置
// 定义全局变量
int setProjects[10] = {0};   // 存储设置项的数组，初始值为0
int autoRestarterMinutes = 30;
bool autoRestart = true;
extern bool debugMode;
void setApply(int sP,int sS) // 应用设置
{
    switch(sP)
    {
        case 0:
            switch(sS)
            {
                case 1:
                    autoRestart=false;
                    break;
                case 2:
                    autoRestart=true;
                    autoRestarterMinutes=30;
                    break;
                case 3:
                    autoRestart=true;
                    autoRestarterMinutes=20;
                    break;
                case 4:
                    autoRestart=true;
                    autoRestarterMinutes=10;
                    break;
                default:
                    break;
            }
            break;
        case 1:
            switch(sS)
            {
                case 1:
                    debugMode=true;
                    break;
                case 2:
                    debugMode=false;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    setProjects[sP]=sS;
}
#endif