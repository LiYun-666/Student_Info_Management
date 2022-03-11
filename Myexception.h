/******************************************************************************
  * @file    Myexception.h
  * @author  作者
  * @brief   异常处理类的头文件
  *          包含异常处理的函数
  *          继承了std::exception类，重写了虚函数const char* what() const throw()
*/

#pragma once

#include "Configure.h"

class Myexception : public exception
{
public:
	/**
	  * @brief  Myexception的构造函数
	  * @param  一个string类型参数_e
	  * @retval 无返回值
	  */
	Myexception(string _e);

	/**
	  * @brief  Myexception的析构函数
	  * @param  
	  * @retval 无返回值
	  */
	~Myexception();

	/**
	  * @brief  重写what()虚函数
	  * @param
	  * @retval 返回字符串
	  */
	const char* what() const throw ();

private:
	string e;
};
