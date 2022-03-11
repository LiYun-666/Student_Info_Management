/******************************************************************************
  * @file    Database.h
  * @author  作者
  * @brief   数据库类操作的头文件
  *          包含构造函数、析构函数
  *          以及CURD之类的操作函数
*/

#pragma once

#include "Configure.h"
#include "Myexception.h"


class Database
{
public:
	/**
	  * @brief  构造函数
	  * @param
	  * @retval 无返回值
	  */
	Database();

	/**
	  * @brief  析构函数
	  * @param
	  * @retval 无返回值
	  */
	~Database();

	/**
	  * @brief  连接数据库
	  * @param
	  * @retval 返回布尔值
	  */
	bool connect();

	/**
	  * @brief  查询所有信息
	  * @param
	  * @retval 返回StudentInfo容器
	  */
	vector<StudentInfo> select_all();

	/**
	  * @brief  查询学生信息
	  * @param  id：学生学号
	  * @retval 返回StudentInfo结构体
	  */
	StudentInfo select_info(uint32_t id);

	/**
	  * @brief  添加学生信息
	  * @param  student：StudentInfo结构体
	  * @retval 返回布尔值
	  */
	bool insert_info(StudentInfo student);

	/**
	  * @brief  从txt添加多条学生信息
	  * @param  student：StudentInfo结构体容器
	  * @retval 返回布尔值
	  */
	bool insert_txt(vector<StudentInfo> student);

	/**
	  * @brief  删除学生信息
	  * @param  id：学生学号
	  * @retval 返回布尔值
	  */
	bool delete_info(uint32_t id);

private:
	string host;         // 主机
	string user;         // 用户
	string passWord;     // 密码
	string databaseName; // 数据库名
	int port;            // 端口
	MYSQL mysql;
};