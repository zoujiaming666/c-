#pragma once   //��ֹͷ�ļ��ظ�����
#include<iostream>
using namespace std;
#include"worker.h"
#include"employer.h"
#include"manager.h"
#include"boss.h"
#include<fstream>
#define FILENAME "empFile.txt"
class WorkerManager
{
public:
	WorkerManager();

	//չʾ�˵�
	void Show_Menu();

	
	//�˳�ϵͳ
	void ExitSystem();
		//��¼ְ������
		int m_EmpNum;
		//ְ������ָ��
		Worker** m_EmpArray;

		//���ְ��
		void Add_Emp();

		//�����ļ�
		void save();

		//�ж��ļ��Ƿ�Ϊ��
		bool m_FileIsEmpty;

		//ͳ���ļ�������
		int get_EmpNum();

		//��ʼ��Ա��
		void intit_Emp();
		//��ʾְ��
		void Show_Emp();

		//ɾ��ְ��
		void Del_Emp();
		//�ж�ְ���Ƿ����
		int IsExist(int id);
		//�޸�ְ��
		void Mod_Emp();
		//����ְ��
		void Find_Emp();
		//���ձ������
		void Sort_Emp();
		//�������
		void Clean_File();
	~WorkerManager();
};

