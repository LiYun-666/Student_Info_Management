/******************************************************************************
  * @file    Student.h
  * @author  作者
  * @brief   Student类的头文件
  *          最主要的类
  *          用于管理学生信息
*/

#pragma once

#include "Configure.h"
#include "Database.h"


class Student
{
public:
	/**
	  * @brief  构造函数
	  * @param  
	  * @retval 无返回值
	  */
	Student(uint32_t _maxStudent);

	/**
	  * @brief  析构函数
	  * @param
	  * @retval 无返回值
	  */
	~Student();

	/**
	  * @brief  运行函数
	  * @param
	  * @retval 布尔值
	  */
	bool run();

	/**
	  * @brief  菜单选择函数
	  * @param
	  * @retval 布尔值
	  */
	bool menu();

	/**
	  * @brief  菜单选择1：展示所有学生信息
	  * @param
	  * @retval 布尔值
	  */
	bool display_all_student();

	/**
	  * @brief  菜单选择2：查询学生信息
	  * @param
	  * @retval 布尔值
	  */
	bool inquire_student();

	/**
	  * @brief  菜单选择3：添加学生信息
	  * @param
	  * @retval 布尔值
	  */
	bool add_student();

	/**
	  * @brief  菜单选择4：删除学生信息
	  * @param
	  * @retval 布尔值
	  */
	bool delete_student();

	/**
	  * @brief  菜单选择5：展示其他信息
	  * @param
	  * @retval 布尔值
	  */
	bool show_other();

	/**
	  * @brief  菜单选择6：读取txt文件信息
	  * @param
	  * @retval 无返回值
	  */
	bool read_txt();

	/**
	  * @brief  菜单选择7：保存信息至二进制文件
	  * @param
	  * @retval 无返回值
	  */
	bool save_file();

	/**
	  * @brief  打印第一行信息
	  * @param
	  * @retval 无返回值
	  */
	void print_firstline();

	/**
	  * @brief  友元重载运算符函数
	  * @param  流对象和类
	  * @retval 流对象
	  */
	friend ostream& operator<<(ostream& output, Student& S);

private:
	uint32_t maxStudent;    // 最大学生数量
	StudentInfo* student;   // StudentInfo结构指针(没有用到，单纯完成new delete的任务)
};