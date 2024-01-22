#include"workerManager.h"

using namespace std;
WorkerManager::WorkerManager()
{
	//�ļ�������
	
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//1,�ж��ļ��Ƿ����   
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << "\n";
		//��ʼ������
		//��ʼ����¼����
		this->m_EmpNum = 0;
		//��ʼ��ָ������
		this->m_EmpArray = NULL;
        //��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//2,�ж��ļ��Ƿ�Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())//�����ж��ļ��Ƿ�Ϊ��
	{
		//�ļ�Ϊ��
		cout << "�ļ�Ϊ��" << "\n";
		//��ʼ������
	//��ʼ����¼����
		this->m_EmpNum = 0;
		//��ʼ��ָ������
		this->m_EmpArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//3,�ļ�����  ���Ҽ�¼����
	int num = this->get_EmpNum();
	cout << "ְ������Ϊ��" << num << "\n";
	this->m_EmpNum = num;
	
	//���ٿռ�
	this->m_EmpArray = new Worker * [this->m_EmpNum];
    //���ļ��е����� ���浽������
	this->intit_Emp();
}
void WorkerManager::Show_Menu()
{
	cout << "*****************************************" << "\n";
	cout << "**********��ӭʹ��ְ������ϵͳ***********" << "\n";
	cout << "***********0.�˳�����ϵͳ****************" << "\n";
	cout << "***********1.����ְ����Ϣ****************" << "\n";
	cout << "***********2.��ʾְ����Ϣ****************" << "\n";
	cout << "***********3.ɾ��ְ����Ϣ****************" << "\n";
	cout << "***********4.�޸�ְ����Ϣ****************" << "\n";
	cout << "***********5.����ְ����Ϣ****************" << "\n";
	cout << "***********6.���ձ������****************" << "\n";
	cout << "***********7.��������ĵ�****************" << "\n";
	cout << "*****************************************" << "\n";
	cout << "\n";
}
void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << "\n";
	system("pause");
	exit(0);//�˳�����
}

//���ְ��
void WorkerManager::Add_Emp()
{
	cout << "���������ְ������" << "\n";

	int addNum = 0;
	cin >> addNum;

	if (addNum > 0)
	{
		//���
		//��������¿ռ��С
		int newSize = this->m_EmpNum + addNum;

		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize];

		//��ԭ���ռ������ݣ��������¿ռ���
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		for (int i = 0; i < addNum; i++)
		{
			int id;//ְ�����
			string name;//ְ������
			int dSelect;//����ѡ��
		s1:
			cout << "�������" << i + 1 << "����ְ����ţ�" << "\n";
			
			cin >> id;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Id == id)
				{
					cout << "ְ��������ظ�������������" << "\n";
					goto s1;
				}	
			}

			cout << "�������" << i + 1 << "����ְ��������" << "\n";
			cin >> name;

			cout << "��ѡ���ְ����λ" << "\n";
			cout << "1,��ְͨ��" << "\n";
			cout << "2,����" << "\n";
			cout << "3,�ϰ�" << "\n";
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
			//������ְ��ָ�룬���浽������
			newSpace[this->m_EmpNum + i] = worker;
		}
		//�ͷ�ԭ�еĿռ�
		delete[] this->m_EmpArray;

		//�����¿ռ��ָ��
		this->m_EmpArray = newSpace;

		//�����µ�ְ������
		this->m_EmpNum = newSize;

		//����ְ����Ϊ�ձ�־
		this->m_FileIsEmpty = false;
		//��ʾ��ӳɹ�
		cout << "�ɹ����" << addNum << "����ְ��" << "\n";
		//��������
		this->save();
	}
	else
	{
		cout << "��������" << "\n";
	}
	//�������  �����ص��ϼ�Ŀ¼
	system("pause");
	system("cls");

}

//�����ļ�
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

//ͳ���ļ�������
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ�  ��
	int id;
	string name;
	int dId;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//ͳ����������
		num++;
	}
	return num;
}
//��ʼ��Ա��
void WorkerManager::intit_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)//����ͷ�᷵��һ���ٵķ���ֵ
	{
		Worker* worker = NULL;
		if (dId == 1)//��ְͨ��
		{
			worker = new Employee(id,  name, dId);
		}
		else if(dId == 2)     //����
		{
			worker = new Manager(id, name, dId);
		}
		else//�ϰ�
		{
		worker = new Boss(id, name, dId);
        }
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}

//��ʾְ��
void WorkerManager::Show_Emp()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty)
	{
		cout << "û�����ݣ���ʾʧ��" << "\n";
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			//���ö�̬���ó���ӿ�
			this->m_EmpArray[i]->showInfo();
		}
	} 
	system("pause");
	system("cls");
}

//ɾ��ְ��
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << "\n";
	}
	else
	{
		cout << "��������Ҫɾ��ְ�����" << "\n";
		int id = 0; 
		cin >> id;

		int index = this->IsExist(id);

		if (index != -1)//˵��ְ�����ڣ�����ɾ����ְ��
		{
			//����ɾ��  ����������ǰ��
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//���������м�¼��Ա����
			//����ͬ�����µ��ļ�
			this->save();
			cout << "ɾ���ɹ�" << "\n";
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << "\n";
		}
		system("pause");
		system("cls");
	}
}
//�ж�ְ���Ƿ����
int WorkerManager::IsExist(int id)
{
	int index = -1;

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			//�ҵ�ְ��
			index = i;

			break;
		}
	}
	return index;
}
//�޸�ְ��
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�������" << "\n";
	}
	else
	{
		cout << "�������޸�ְ���ı��" << "\n";
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//���ҵ���ŵ�ְ��
			delete this->m_EmpArray[ret];

			int newid = 0;
			string newName = "";
			int dSelect = 0;

			cout << "�鵽��" << id << "��ְ������������ְ���ţ�" << "\n";
			cin >> newid;
			cout << "������������" << "\n";
			cin >> newName;
			cout << "�������µĸ�λ" << "\n";
			cout << "1,��ͨ��λ" << "\n";
			cout << "2������" << "\n";
			cout << "3.�ϰ�" << "\n";

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
				cout << "�����λ�����޸�ʧ��" << "\n";
				break;
			}
			//��������  ��������
			this->m_EmpArray[ret] = worker;
			cout << "�޸ĳɹ�" << "\n";
			//���浽�ļ���
			this->save();

		}
		else
		{
			cout << "�޸�ʧ�ܣ����޴���" << "\n";
		}

	}
	system("pause");
	system("cls");
}
//����ְ��
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << "\n";
	}
	else
	{
		cout << "��������ҵķ�ʽ" << "\n";
		cout << "1,����ְ����Ų���" << "\n";
		cout << "2,����ְ����������" << "\n";

		int select = 0;
		cin >> select;
		if (select == 1)
		{
			//���ձ�Ų�
			int id;
			cout << "��������ҵ�ְ�����" << "\n";
			cin >> id;

			int ret = IsExist(id);
			if (ret != -1)
			{
				cout << "���ҳɹ�!��ְ����Ϣ����" << "\n";
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "���޴���" << "\n";
			}
			
		}
		else if (select == 2)
		{
			//����������
			string name;
			cout << "��������ҵ�����" << "\n";
			cin >> name;
			//�����ж��Ƿ�鵽�ı�־

			bool flag = false;
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "���ҳɹ���ְ�����Ϊ��" << this->m_EmpArray[i]->m_Id << "��Ϣ����" << "\n";
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "���޴���" << "\n";
			}
		}
		else
		{
			//�������
			cout << "��������" << "\n";

		}
		
	}
	system("pause");
	system("cls");
}
//����
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��!" << "\n";
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ" << "\n";
		cout << "1,����ְ�����Ž�������" << "\n";
		cout << "2,����ְ�����Ž��н���" << "\n";

		int select = 0;
		cin >> select;
		for (int i = 0; i < m_EmpNum; i++)
		{
			int minOrMax = i;//������Сֵ  �����ֵ�±�
			for(int j = i+1;j<this->m_EmpNum;j++)
			{
				if (select == 1)//����
				{
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;      
					}
				}
				else if(select == 2)//����
				{
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else
				{
					cout << "�������" << "\n";
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
		cout << "����ɹ��������Ľ��Ϊ" << "\n";
		this->save();
		this->Show_Emp();
	}
}
//����ļ�
void WorkerManager::Clean_File()
{
	cout << "ȷ����գ�" << "\n";
	cout << "1,ȷ��" << "\n";
	cout << "2,����" << "\n";
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//����ļ�
		ofstream ofs(FILENAME, ios::trunc);//ɾ���ļ������´���
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
		cout << "��ճɹ�" << "\n";
		system("pause");
		system("cls");
	}
	else if (select == 2)
	{
		system("cls");
	}
	else
	{
		cout << "��������" << "\n";
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
