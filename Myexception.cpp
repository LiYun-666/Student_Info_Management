/******************************************************************************
  * @file    Myexception.cpp
  * @author  作者
  * @brief   异常处理类的cpp文件
  *          包含异常处理函数
  *          继承了std::exception类，重写了虚函数const char* what() const throw()
*/

#include "myException.h"

/**
  * @brief  Myexception的构造函数
  * @param  一个string类型参数_e
  * @retval 无返回值
  */
Myexception::Myexception(string _e)
{
	e = _e;
}

/**
  * @brief  Myexception的析构函数
  * @param
  * @retval 无返回值
  */
Myexception::~Myexception()
{
	// 析构函数
}

/**
  * @brief  重写what()虚函数
  * @param
  * @retval 返回字符串
  */
const char* Myexception::what() const throw()
{
	return e.c_str();
}
