#include<iostream>
using namespace std;
#include"workerManager.h"

#include"worker.h"
#include"employer.h"
#include"manager.h"
#include"boss.h"

int main()
{
	//实例化管理者对象
	WorkerManager wm;
	int choice = 0;
	//调用成员函数
	while (true)
	{


		wm.Show_Menu();
		cout << "请输入你的选择" << "\n";
		cin >> choice;
		switch (choice)
		{
		case 0:
			wm.ExitSystem();
			break;
		case 1:
			wm.Add_Emp();
			break;
		case 2:
			wm.Show_Emp();
			break;
		case 3:
			wm.Del_Emp();
			break;
		case 4:
			wm.Mod_Emp();
			
			break;
		case 5:
			wm.Find_Emp();
			break;
		case 6:
			wm.Sort_Emp();
			break;
		case 7:
			wm.Clean_File();
			break;
		default:
			system("cls");
			break;
		}
		
	}
	system("pause");
	return 0;
}
