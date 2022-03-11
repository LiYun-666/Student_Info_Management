/******************************************************************************
  * @file    Database.cpp
  * @author  作者
  * @brief   数据库类操作的cpp文件
  *          包含各种函数的具体实现
  *          数据库的CRUD
*/

#include "Database.h"
#include "Student.h"

/**
  * @brief  构造函数
  * @param
  * @retval 无返回值
  */
Database::Database()
{
	host = "127.0.0.1";
	user = "root";
	passWord = "00000000";
	databaseName = "test";
	port = 3306;
	mysql_init(&mysql);
}

/**
  * @brief  析构函数
  * @param
  * @retval 无返回值
  */
Database::~Database()
{
	if (&mysql)
	{
		mysql_close(&mysql); // 关闭数据库连接
	}
}

/**
  * @brief  连接数据库
  * @param
  * @retval 返回布尔值
  */
bool Database::connect()
{
	try
	{
		if (!mysql_real_connect(&mysql, host.c_str(), user.c_str(), passWord.c_str(), databaseName.c_str(), port, NULL, 0))
		{
			throw Myexception("数据库连接失败！");
		}
	}
	catch (Myexception& e)
	{
		cout << e.what() << endl;
		return false;
	}
	return true;
}

/**
  * @brief  查询所有信息
  * @param
  * @retval 返回StudentInfo容器
  */
vector<StudentInfo> Database::select_all()
{
	vector<StudentInfo> student;          // 保存从数据库查询出来的数据，用于返回
	mysql_query(&mysql, "set names gbk"); // 改一下编码，不然中文会乱码

	// 1.执行查询
	string sql = "select * from student";
	try
	{
		if (mysql_real_query(&mysql, sql.c_str(), unsigned long(sql.size())))
		{
			// 查询失败，则直接返回
			throw Myexception("数据库查询失败！");
		}
	}
	catch (Myexception& e)
	{
		cout << e.what() << endl;
		return student;
	}

	// 2.查询成功，取出 SQL 语句执行的结果集
	MYSQL_RES* mysql_res = mysql_store_result(&mysql);

	// 3.提取数据，用于返回
	MYSQL_ROW tmp;
	while (tmp = mysql_fetch_row(mysql_res))
	{
		StudentInfo tmp_student;
		tmp_student.id = atoi(tmp[0]);
		tmp_student.name = tmp[1];
		tmp_student.sex = tmp[2];
		tmp_student.score = atof(tmp[3]);
		student.push_back(tmp_student);
	}

	// 4.释放结果集
	mysql_free_result(mysql_res);

	return student;
}

/**
  * @brief  查询学生信息
  * @param  id：学生学号
  * @retval 返回StudentInfo结构体
  */
StudentInfo Database::select_info(uint32_t id)
{
	StudentInfo student;          // 保存从数据库查询出来的数据，用于返回
	mysql_query(&mysql, "set names gbk"); // 改一下编码，不然中文会乱码

	// 1.执行查询
	string sql = "select * from student where id=" + to_string(id);
	try
	{
		if (mysql_real_query(&mysql, sql.c_str(), unsigned long(sql.size())))
		{
			// 查询失败，则直接返回
			throw Myexception("数据库查询失败！");
		}
	}
	catch (Myexception& e)
	{
		cout << e.what() << endl;
		return student;
	}

	// 2.查询成功，取出 SQL 语句执行的结果集
	MYSQL_RES* mysql_res = mysql_store_result(&mysql);

	// 3.提取数据，用于返回
	MYSQL_ROW tmp = mysql_fetch_row(mysql_res);
	if (tmp) // tmp不为空
	{
		student.id = atoi(tmp[0]);
		student.name = tmp[1];
		student.sex = tmp[2];
		student.score = atof(tmp[3]);
	}

	// 4.释放结果集
	mysql_free_result(mysql_res);

	return student;
}

/**
  * @brief  添加学生信息
  * @param  student：StudentInfo结构体
  * @retval 返回布尔值
  */
bool Database::insert_info(StudentInfo student)
{
	mysql_query(&mysql, "set names gbk"); // 改一下编码，不然中文会乱码
	
	// 执行sql
	string sql = "insert into student (id, name, sex, score) values (" + to_string(student.id) + ", \"" + student.name + "\", \"" + student.sex + "\", " + to_string(student.score) + ")";
	try
	{
		if (mysql_real_query(&mysql, sql.c_str(), unsigned long(sql.size())) || !mysql_affected_rows(&mysql))
		{
			// 插入失败，则直接返回
			throw Myexception("数据库添加数据失败！");
		}
	}
	catch (Myexception& e)
	{
		cout << e.what() << endl;
		return false;
	}
	return true;
}

/**
  * @brief  从txt添加多条学生信息
  * @param  student：StudentInfo结构体容器
  * @retval 返回布尔值
  */
bool Database::insert_txt(vector<StudentInfo> student)
{
	mysql_query(&mysql, "set names gbk"); // 改一下编码，不然中文会乱码

	// 执行sql
	string sql = "insert into student (id, name, sex, score) values ";
	for (size_t i = 0; i < student.size(); i++)
	{
		sql += "(" + to_string(student[i].id) + ", \"" + student[i].name + "\", \"" + student[i].sex + "\", " + to_string(student[i].score) + ")";
		if (i + 1 < student.size())
		{
			sql += ",";
		}
	}
	try
	{
		if (mysql_real_query(&mysql, sql.c_str(), unsigned long(sql.size())) || !mysql_affected_rows(&mysql))
		{
			// 插入失败，则直接返回
			throw Myexception("数据库添加数据失败！");
		}
	}
	catch (Myexception& e)
	{
		cout << e.what() << endl;
		return false;
	}
	return true;
}

/**
  * @brief  删除学生信息
  * @param  id：学生学号
  * @retval 返回布尔值
  */
bool Database::delete_info(uint32_t id)
{
	mysql_query(&mysql, "set names gbk"); // 改一下编码，不然中文会乱码

	// 执行sql
	string sql = "delete from student where id=" + to_string(id);
	try
	{
		if (mysql_real_query(&mysql, sql.c_str(), unsigned long(sql.size())) || !mysql_affected_rows(&mysql))
		{
			// 删除失败，则直接返回
			throw Myexception("数据库删除数据失败！");
		}
	}
	catch (Myexception& e)
	{
		cout << e.what() << endl;
		return false;
	}
	return true;
}