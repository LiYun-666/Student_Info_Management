/******************************************************************************
  * @file    main.cpp
  * @author  作者
  * @brief   main函数文件
  *          程序入口
  *          学生信息管理系统的入口点
*/

#include "Student.h"

/**
  * @brief  main函数
  * @param
  * @retval return 0
  */
int main()
{
	SetConsoleTitle(L"学生信息管理系统"); // 设置窗口标题
	Student s(1000);
	s.run();
	cout << s << endl;
	return 0;
}