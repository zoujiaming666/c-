#include"workerManager.h"

using namespace std;
WorkerManager::WorkerManager()
{
	//文件不存在
	
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//1,判断文件是否存在   
	if (!ifs.is_open())
	{
		cout << "文件不存在" << "\n";
		//初始化属性
		//初始化记录人数
		this->m_EmpNum = 0;
		//初始化指针数组
		this->m_EmpArray = NULL;
        //初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//2,判断文件是否为空
	char ch;
	ifs >> ch;
	if (ifs.eof())//用来判断文件是否为空
	{
		//文件为空
		cout << "文件为空" << "\n";
		//初始化属性
	//初始化记录人数
		this->m_EmpNum = 0;
		//初始化指针数组
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//3,文件存在  并且记录数据
	int num = this->get_EmpNum();
	cout << "职工人数为：" << num << "\n";
	this->m_EmpNum = num;
	
	//开辟空间
	this->m_EmpArray = new Worker * [this->m_EmpNum];
    //将文件中的数据 ，存到数组中
	this->intit_Emp();
}
void WorkerManager::Show_Menu()
{
	cout << "*****************************************" << "\n";
	cout << "**********欢迎使用职工管理系统***********" << "\n";
	cout << "***********0.退出管理系统****************" << "\n";
	cout << "***********1.增加职工信息****************" << "\n";
	cout << "***********2.显示职工信息****************" << "\n";
	cout << "***********3.删除职工信息****************" << "\n";
	cout << "***********4.修改职工信息****************" << "\n";
	cout << "***********5.查找职工信息****************" << "\n";
	cout << "***********6.按照编号排序****************" << "\n";
	cout << "***********7.清空所有文档****************" << "\n";
	cout << "*****************************************" << "\n";
	cout << "\n";
}
void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用" << "\n";
	system("pause");
	exit(0);//退出程序
}

//添加职工
void WorkerManager::Add_Emp()
{
	cout << "请输入添加职工数量" << "\n";

	int addNum = 0;
	cin >> addNum;

	if (addNum > 0)
	{
		//添加
		//计算添加新空间大小
		int newSize = this->m_EmpNum + addNum;

		//开辟新空间
		Worker** newSpace = new Worker * [newSize];

		//将原来空间下数据，拷贝到新空间下
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		for (int i = 0; i < addNum; i++)
		{
			int id;//职工编号
			string name;//职工姓名
			int dSelect;//部门选择
		s1:
			cout << "请输入第" << i + 1 << "个新职工编号：" << "\n";
			
			cin >> id;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Id == id)
				{
					cout << "职工编号有重复，请重新输入" << "\n";
					goto s1;
				}	
			}

			cout << "请输入第" << i + 1 << "个新职工姓名：" << "\n";
			cin >> name;

			cout << "请选择该职工岗位" << "\n";
			cout << "1,普通职工" << "\n";
			cout << "2,经理" << "\n";
			cout << "3,老板" << "\n";
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			//将创建职工指针，保存到数组中
			newSpace[this->m_EmpNum + i] = worker;
		}
		//释放原有的空间
		delete[] this->m_EmpArray;

		//更改新空间的指向
		this->m_EmpArray = newSpace;

		//更新新的职工人数
		this->m_EmpNum = newSize;

		//更新职工不为空标志
		this->m_FileIsEmpty = false;
		//提示添加成功
		cout << "成功添加" << addNum << "名新职工" << "\n";
		//保存数据
		this->save();
	}
	else
	{
		cout << "输入有误" << "\n";
	}
	//按任意键  清屏回到上级目录
	system("pause");
	system("cls");

}

//保存文件
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << "\n";
	}
	ofs.close();
}

//统计文件中人数
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//打开文件  读
	int id;
	string name;
	int dId;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//统计人数变量
		num++;
	}
	return num;
}
//初始化员工
void WorkerManager::intit_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)//读到头会返回一个假的返回值
	{
		Worker* worker = NULL;
		if (dId == 1)//普通职工
		{
			worker = new Employee(id,  name, dId);
		}
		else if(dId == 2)     //经理
		{
			worker = new Manager(id, name, dId);
		}
		else//老板
		{
		worker = new Boss(id, name, dId);
        }
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}

//显示职工
void WorkerManager::Show_Emp()
{
	//判断文件是否为空
	if (this->m_FileIsEmpty)
	{
		cout << "没有数据，显示失败" << "\n";
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			//利用多态调用程序接口
			this->m_EmpArray[i]->showInfo();
		}
	} 
	system("pause");
	system("cls");
}

//删除职工
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << "\n";
	}
	else
	{
		cout << "请输入想要删除职工编号" << "\n";
		int id = 0; 
		cin >> id;

		int index = this->IsExist(id);

		if (index != -1)//说明职工存在，并且删除该职工
		{
			//数组删除  本质是数组前移
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//更新数组中记录人员个数
			//数据同步更新到文件
			this->save();
			cout << "删除成功" << "\n";
		}
		else
		{
			cout << "删除失败，未找到该职工" << "\n";
		}
		system("pause");
		system("cls");
	}
}
//判断职工是否存在
int WorkerManager::IsExist(int id)
{
	int index = -1;

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			//找到职工
			index = i;

			break;
		}
	}
	return index;
}
//修改职工
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在" << "\n";
	}
	else
	{
		cout << "请输入修改职工的编号" << "\n";
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//查找到编号的职工
			delete this->m_EmpArray[ret];

			int newid = 0;
			string newName = "";
			int dSelect = 0;

			cout << "查到：" << id << "号职工，请输入新职工号：" << "\n";
			cin >> newid;
			cout << "请输入新姓名" << "\n";
			cin >> newName;
			cout << "请输入新的岗位" << "\n";
			cout << "1,普通岗位" << "\n";
			cout << "2，经理" << "\n";
			cout << "3.老板" << "\n";

			cin >> dSelect;
			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newid, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newid, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newid, newName, dSelect);
				break;
			default:
				cout << "输入岗位错误，修改失败" << "\n";
				break;
			}
			//更新数据  到数组中
			this->m_EmpArray[ret] = worker;
			cout << "修改成功" << "\n";
			//保存到文件中
			this->save();

		}
		else
		{
			cout << "修改失败，查无此人" << "\n";
		}

	}
	system("pause");
	system("cls");
}
//查找职工
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << "\n";
	}
	else
	{
		cout << "请输入查找的方式" << "\n";
		cout << "1,按照职工编号查找" << "\n";
		cout << "2,按照职工姓名查找" << "\n";

		int select = 0;
		cin >> select;
		if (select == 1)
		{
			//按照编号查
			int id;
			cout << "请输入查找的职工编号" << "\n";
			cin >> id;

			int ret = IsExist(id);
			if (ret != -1)
			{
				cout << "查找成功!该职工信息如下" << "\n";
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "查无此人" << "\n";
			}
			
		}
		else if (select == 2)
		{
			//按照姓名查
			string name;
			cout << "请输入查找的姓名" << "\n";
			cin >> name;
			//加入判断是否查到的标志

			bool flag = false;
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "查找成功，职工编号为：" << this->m_EmpArray[i]->m_Id << "信息如下" << "\n";
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "查无此人" << "\n";
			}
		}
		else
		{
			//输入错误
			cout << "输入有误" << "\n";

		}
		
	}
	system("pause");
	system("cls");
}
//排序
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空!" << "\n";
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式" << "\n";
		cout << "1,按照职工工号进行升序" << "\n";
		cout << "2,按照职工工号进行降序" << "\n";

		int select = 0;
		cin >> select;
		for (int i = 0; i < m_EmpNum; i++)
		{
			int minOrMax = i;//声明最小值  或最大值下标
			for(int j = i+1;j<this->m_EmpNum;j++)
			{
				if (select == 1)//升序
				{
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;      
					}
				}
				else if(select == 2)//降序
				{
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else
				{
					cout << "输入错误" << "\n";
					return;
				}
			}
			if (i != minOrMax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}
		cout << "排序成功！排序后的结果为" << "\n";
		this->save();
		this->Show_Emp();
	}
}
//清空文件
void WorkerManager::Clean_File()
{
	cout << "确定清空？" << "\n";
	cout << "1,确定" << "\n";
	cout << "2,返回" << "\n";
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//清空文件
		ofstream ofs(FILENAME, ios::trunc);//删除文件后重新创建
	    ofs.close();
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];
					this->m_EmpArray[i] = NULL;
				}

			}
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功" << "\n";
		system("pause");
		system("cls");
	}
	else if (select == 2)
	{
		system("cls");
	}
	else
	{
		cout << "输入有误" << "\n";
		system("pause");
		system("cls");
	}
}
WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpNum = NULL;
	}
}
