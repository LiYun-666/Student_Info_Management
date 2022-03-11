/******************************************************************************
  * @file    Student.cpp
  * @author  作者
  * @brief   Student类的cpp文件
  *          最主要的类
  *          各种学生信息管理功能的具体实现
*/

#include "Student.h"

/**
  * @brief  构造函数
  * @param
  * @retval 没有返回值
  */
Student::Student(uint32_t _maxStudent)
{
	maxStudent = _maxStudent;
	student = new StudentInfo[maxStudent];
}

/**
  * @brief  析构函数
  * @param
  * @retval 没有返回值
  */
Student::~Student()
{
	delete[] student;
	student = nullptr;
}

/**
  * @brief  运行函数
  * @param
  * @retval 返回布尔值
  */
bool Student::run()
{
	menu();
	return true;
}

/**
  * @brief  菜单选择函数
  * @param
  * @retval 返回布尔值
  */
bool Student::menu()
{
	// 能计算学生的优良等级，统计总人数，及格率及各分数段人数。
	while (1)
	{
		// 1.画界面
		system("cls"); //清屏
		cout << endl << endl;
		cout << "                    **        *        ** ****** *       ****    ****       *         *      ******" << endl;
		cout << "                     **      ***      **  *      *      *       *    *     * *       * *     *     " << endl;
		cout << "                      **    ** **    **   *****  *      *       *    *    *   *     *   *    ******" << endl;
		cout << "                       **  **   **  **    *      *      *       *    *   *     *   *     *   *     " << endl;
		cout << "                        ***      ***      *      *      *       *    *  *       * *       *  *     " << endl;
		cout << "                         *        *       ****** ******  ****    ****  *         *         * ******" << endl;
		cout << endl << endl << endl;
		cout << "                                ☆☆☆☆☆☆☆☆☆☆ Student Information Manage System ☆☆☆☆☆☆☆☆☆☆" << endl;
		cout << endl;
		cout << "                                         ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
		cout << "                                         ┃      欢迎使用学生信息管理系统      ┃" << endl;
		cout << "                                         ┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃" << endl;
		cout << "                                         ┃ 1.查看所有学生信息   2.查找学生信息┃" << endl;
		cout << "                                         ┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃" << endl;
		cout << "                                         ┃ 3.添加学生信息       4.删除学生信息┃" << endl;
		cout << "                                         ┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃" << endl;
		cout << "                                         ┃ 5.查看其它信息       6.读取txt文件 ┃" << endl;
		cout << "                                         ┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃" << endl;
		cout << "                                         ┃ 7.保存学生信息       8.退出        ┃" << endl;
		cout << "                                         ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
		
		// 2.输入选择
		uint32_t choice = 0;
		while (1)
		{
			try
			{
				cout << "                                                       请输入：";
				cin >> choice;
				if (cin.fail() || choice <= 0 || choice >= 9) 
				{
					cin.clear(); // 更改cin标志
					cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');  // 清除输入缓冲区中的当前行内容
					throw Myexception("                                             输入错误！( 请输入数字1-8 )");
				}
				cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');  // 清除输入缓冲区中的当前行内容
				break;
			}
			catch (Myexception& e)
			{
				cout << e.what() << endl;
			}
		}
		// 3.根据不同输入调用不同函数
		switch (choice)
		{
		case 1:
			display_all_student();
			system("pause");
			break;
		case 2:
			inquire_student();
			system("pause");
			break;
		case 3:
			add_student();
			system("pause");
			break;
		case 4:
			delete_student();
			system("pause");
			break;
		case 5:
			show_other();
			system("pause");
			break;
		case 6:
			read_txt();
			system("pause");
			break;
		case 7:
			save_file();
			system("pause");
			break;
		default:
			return true;
		}
	}
	return true;
}

/**
  * @brief  菜单选择1：展示所有学生信息
  * @param
  * @retval 返回布尔值
  */
bool Student::display_all_student()
{
	// 1.连接数据库
	Database db;
	if (!db.connect())
	{
		return false; // 若连接失败直接返回布尔值false退出
	}
	
	// 2.连接成功，进行查询
	vector<StudentInfo> tmp_student = db.select_all();

	// 3.格式化输出查询结果
	print_firstline();
	for (size_t i = 0; i < tmp_student.size(); i++)
	{
		cout << "                      ┃"
			<< setw(9 + to_string(tmp_student[i].id).size() / 2) << tmp_student[i].id << setw(9 - to_string(tmp_student[i].id).size() / 2) << " " << "┃"
			<< setw(9 + tmp_student[i].name.size() / 2) << tmp_student[i].name << setw(9 - tmp_student[i].name.size() / 2) << " " << "┃"
			<< setw(9 + tmp_student[i].sex.size() / 2) << tmp_student[i].sex << setw(9 - tmp_student[i].sex.size() / 2) << " " << "┃"
			<< setw(8 + int(ceil((to_string(tmp_student[i].score).size() - 4) / 2.0))) << fixed << setprecision(1) << tmp_student[i].score << setw(9 - int(ceil((to_string(tmp_student[i].score).size() - 4) / 2.0))) << " " << "┃"
			<< endl;
		if (i == tmp_student.size() - 1)
		{
			cout << "                      ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
		}
		else
		{
			cout << "                      ┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃" << endl;
		}
	}

	// 4.成功执行完毕，返回布尔值true
	return true;
}

/**
  * @brief  查询学生信息
  * @param
  * @retval 返回布尔值
  */
bool Student::inquire_student()
{
	// 只做了由id查询，所以如果查询成功只有一条记录；由姓名性别成绩啥的查询没有做，原理都一样
	// 1.输入学号，下面是确保输入正确的代码
	uint32_t id = 0;
	while (1)
	{
		try
		{
			cout << "                                               请输入学生的学号进行查询：";
			cin >> id;
			if (cin.fail() || id <= 0)
			{
				cin.clear();
				cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');  // 清除输入缓冲区中的当前行内容
				throw Myexception("                                               输入错误！( 请输入正整数 )");
			}
			cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');  // 清除输入缓冲区中的当前行内容
			break;
		}
		catch (Myexception& e)
		{
			cout << e.what() << endl;
		}
	}
	
	// 2.连接数据库
	Database db;
	if (!db.connect())
	{
		return false; // 若连接失败直接返回布尔值false退出
	}

	// 3.连接成功，传入id参数进行查询
	StudentInfo tmp_student = db.select_info(id);

	// 4.格式化输出查询结果
	if (tmp_student.id) // 不为空(不为0)
	{
		print_firstline();
		cout << "                      ┃"
			<< setw(9 + to_string(tmp_student.id).size() / 2) << tmp_student.id << setw(9 - to_string(tmp_student.id).size() / 2) << " " << "┃"
			<< setw(9 + tmp_student.name.size() / 2) << tmp_student.name << setw(9 - tmp_student.name.size() / 2) << " " << "┃"
			<< setw(9 + tmp_student.sex.size() / 2) << tmp_student.sex << setw(9 - tmp_student.sex.size() / 2) << " " << "┃"
			<< setw(8 + int(ceil((to_string(tmp_student.score).size() - 4) / 2.0))) << fixed << setprecision(1) << tmp_student.score << setw(9 - int(ceil((to_string(tmp_student.score).size() - 4) / 2.0))) << " " << "┃"
			<< endl;
		cout << "                      ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
	}
	
	// 5.成功执行完毕，返回布尔值true
	return true;
}

/**
  * @brief  添加学生信息
  * @param
  * @retval 返回布尔值
  */
bool Student::add_student()
{
	// 1.创建要插入的数据
	StudentInfo tmp_student;

	// 2.输入学号
	while (1)
	{
		try
		{
			cout << "                                         请输入学生的学号(正整数且不能重复)：";
			cin >> tmp_student.id;
			if (cin.fail() || tmp_student.id <= 0)
			{
				cin.clear();
				cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');  // 清除输入缓冲区中的当前行内容
				throw Myexception("                                               输入错误！( 请输入正整数 )");
			}
			cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');  // 清除输入缓冲区中的当前行内容
			break;
		}
		catch (Myexception& e)
		{
			cout << e.what() << endl;
		}
	}

	// 3.输入姓名
	cout << "                                             请输入学生的姓名：";
	cin >> tmp_student.name;

	// 4.输入性别
	cout << "                                             请输入学生的性别：";
	cin >> tmp_student.sex;

	// 5.输入score
	while (1)
	{
		try
		{
			cout << "                                         请输入学生的score(0-100,一位小数)：";
			cin >> tmp_student.score;
			if (cin.fail() || tmp_student.score < 0 || tmp_student.score > 100)
			{
				cin.clear();
				cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');  // 清除输入缓冲区中的当前行内容
				throw Myexception("                                             输入错误！( 请输入0-100,一位小数 )");
			}
			cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');  // 清除输入缓冲区中的当前行内容
			break;
		}
		catch (Myexception& e)
		{
			cout << e.what() << endl;
		}
	}

	// 6.连接数据库
	Database db;
	if (!db.connect())
	{
		return false; // 若连接失败直接返回布尔值false退出
	}

	// 7.连接成功，传入tmp_student参数进行添加
	if (db.insert_info(tmp_student))
	{
		cout << "                                                       添加成功！" << endl;
	}
	else
	{
		return false;
	}

	// 8.成功执行完毕，返回布尔值true
	return true;
}

/**
  * @brief  删除学生信息
  * @param
  * @retval 返回布尔值
  */
bool Student::delete_student()
{
	// 只做了由id删除
	// 1.输入学号
	uint32_t id = 0;
	while (1)
	{
		try
		{
			cout << "                                               请输入学生的学号进行删除：";
			cin >> id;
			if (cin.fail() || id <= 0)
			{
				cin.clear();
				cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');  // 清除输入缓冲区中的当前行内容
				throw Myexception("                                             输入错误！( 请输入正整数 )");
			}
			cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');  // 清除输入缓冲区中的当前行内容
			break;
		}
		catch (Myexception& e)
		{
			cout << e.what() << endl;
		}
	}

	// 2.连接数据库
	Database db;
	if (!db.connect())
	{
		return false; // 若连接失败直接返回布尔值false退出
	}

	// 3.连接成功，传入id参数进行删除
	if (db.delete_info(id))
	{
		cout << "                                                       删除成功！" << endl;
	}
	else
	{
		return false;
	}

	// 5.成功执行完毕，返回布尔值true
	return true;
}

/**
  * @brief  展示其他信息，计算学生的优良等级，统计总人数，及格率及各分数段人数。
  * @param
  * @retval 返回布尔值
  */
bool Student::show_other()
{
	// 1.展示学生的优良等级
	// 1).连接数据库
	Database db;
	if (!db.connect())
	{
		return false; // 若连接失败直接返回布尔值false退出
	}

	// 2).连接成功，进行查询
	vector<StudentInfo> tmp_student = db.select_all();

	// 3).格式化输出查询结果
	print_firstline();
	for (size_t i = 0; i < tmp_student.size(); i++)
	{
		string rate;
		if (tmp_student[i].score >= 85)
		{
			rate = "优秀";
		}
		else if (tmp_student[i].score >= 75)
		{
			rate = "良好";
		}
		else if (tmp_student[i].score >= 60)
		{
			rate = "及格";
		}
		else
		{
			rate = "不及格";
		}
		cout << "                      ┃"
			<< setw(9 + to_string(tmp_student[i].id).size() / 2) << tmp_student[i].id << setw(9 - to_string(tmp_student[i].id).size() / 2) << " " << "┃"
			<< setw(9 + tmp_student[i].name.size() / 2) << tmp_student[i].name << setw(9 - tmp_student[i].name.size() / 2) << " " << "┃"
			<< setw(9 + tmp_student[i].sex.size() / 2) << tmp_student[i].sex << setw(9 - tmp_student[i].sex.size() / 2) << " " << "┃"
			<< setw(8 + rate.size() / 2) << rate << setw(9 - rate.size() / 2) << " " << "┃"
			<< endl;
		if (i == tmp_student.size() - 1)
		{
			cout << "                      ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
		}
		else
		{
			cout << "                      ┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃" << endl;
		}
	}

	// 2.输出总人数
	cout << "                                                 总人数为：" << tmp_student.size() << endl;

	// 3.输出及格率
	uint32_t passed = 0;
	for (size_t i = 0; i < tmp_student.size(); i++)
	{
		if (tmp_student[i].score >= 60)
		{
			passed++;
		}
	}
	cout << "                                                 及格率为：" <<fixed<<setprecision(2) << double(passed) * 100 / tmp_student.size() <<"%" << endl;

	// 4.输出各分数段人数
	vector<int> student_num(11, 0);
	for (size_t i = 0; i < tmp_student.size(); i++)
	{
		student_num[int(tmp_student[i].score / 10)]++;
	}
	for (size_t i = 0; i < student_num.size(); i++)
	{
		if (i + 1 < student_num.size())
		{
			cout << "                                            " << i * 10 << "分---" << i * 10 + 9 << "分的人数为：" << student_num[i] << endl;
		}
		else
		{
			cout << "                                            100分的人数为：" << student_num[i] << endl;
		}
	}
	
	return true;
}

/**
  * @brief  读取txt文件信息
  * @param
  * @retval 无返回值
  */
bool Student::read_txt()
{
	// 1.创建各个变量
	fstream file("D:\\student_txt.txt", ios::in);
	vector<StudentInfo> all_student;
	StudentInfo tmp_student;
	string buffer[4];
	file >> buffer[0]>> buffer[1]>>buffer[2]>> buffer[3]; // 清除第一行标题行

	// 2.从文件将信息读取至变量中，关闭文件
	while (file >> tmp_student.id >> tmp_student.name >> tmp_student.sex >> tmp_student.score)
	{
		if (tmp_student.id <= 0 || tmp_student.score < 0 || tmp_student.score > 100)
		{
			cout << "                                                       读取失败！" << endl;
			return false;
		}
		all_student.push_back(tmp_student);
	}
	file.close();

	// 3.连接数据库
	Database db;
	if (!db.connect())
	{
		return false; // 若连接失败直接返回布尔值false退出
	}

	// 4.连接成功，传入all_student参数进行添加
	if (db.insert_txt(all_student))
	{
		cout << "                                                       添加成功！" << endl;
	}
	else
	{
		return false;
	}

	// 8.成功执行完毕，返回布尔值true
	return true;
}

/**
  * @brief  保存信息至二进制文件
  * @param
  * @retval 无返回值
  */
bool Student::save_file()
{
	// 1.连接数据库
	Database db;
	if (!db.connect())
	{
		return false; // 若连接失败直接返回布尔值false退出
	}

	// 2.连接成功，进行查询
	vector<StudentInfo> tmp_student = db.select_all();

	// 3.将信息保存至二进制文件中
	fstream file("D:\\student_dat.dat", ios::out | ios::binary);
	for (size_t i = 0; i < tmp_student.size(); i++)
	{
		file.write((char*)&tmp_student[i], sizeof(StudentInfo));
	}
	StudentInfo empty_record(0, "noName\0", "noSex\0", 0); // 创建空记录
	file.write((char*)&empty_record, sizeof(StudentInfo)); // 写入空记录，代表文件结束标志

	// 4.关闭文件，返回结果
	cout << "                                                       保存成功！" << endl;
	file.close();
	return true;
}

/**
  * @brief  打印第一行信息
  * @param
  * @retval 无返回值
  */
void Student::print_firstline()
{
	cout << "                      ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
	cout << "                      ┃       学号       ┃       姓名       ┃       性别       ┃      score      ┃" << endl;
	cout << "                      ┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃" << endl;
}

/**
  * @brief  友元重载运算符函数
  * @param  流对象和类
  * @retval 流对象
  */
ostream& operator<<(ostream& output, Student& S)
{
	output << "                                                     感谢您的使用！";
	return output;
}
