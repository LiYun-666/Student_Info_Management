/******************************************************************************
  * @file    Configure.h
  * @author  作者
  * @brief   配置文件
  *          包含一些include目录、std命名空间
  *          以及StudentInfo结构体
*/

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include <iomanip>
#include <mysql.h>
#include <exception>
#include <fstream>

using namespace std;

struct StudentInfo
{
	StudentInfo() : id(0), score(0) {}
	StudentInfo(uint32_t _id, string _name, string _sex, double _score) : id(_id), name(_name), sex(_sex), score(_score) {}
	uint32_t id;       // 学号(保证唯一，且是正整数，大于0)
	string name;       // 姓名
	string sex;        // 性别
	double score;        // 成绩(一位小数)
};