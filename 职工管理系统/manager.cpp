#include"manager.h"

Manager::Manager(int id, string name, int dId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = dId;
}
//显示个人信息
void Manager::showInfo()
{
	cout << "职工编号：" << this->m_Id << "\t职工姓名：" << this->m_Name << "\t岗位:" << this->m_DeptId << this->getDeptName() <<
		"\t岗位职责：完成老板交给的任务，并且下发任务给普通员工" << "\n";
}
//获取部门名称
string Manager::getDeptName()
 {
	return "经理";
 }