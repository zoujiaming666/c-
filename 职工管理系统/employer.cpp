#include"employer.h"

Employee::Employee(int id, string name, int dId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = dId;
}
void Employee::showInfo()
{
	cout << "ְ����ţ�" << this->m_Id << "\tְ��������" << this->m_Name << "\t��λ:" << this->m_DeptId << this->getDeptName() << "\t��λְ����ɾ�����������" << "\n";
		
}
 string Employee::getDeptName()
{
	 return "Ա��"; 
}