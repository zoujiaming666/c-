#include"boss.h"

Boss::Boss(int id, string name, int dId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = dId;
}
//显示个人信息
void Boss::showInfo()
{
	cout << "职工编号：" << this->m_Id << "\t职工姓名：" << this->m_Name << "\t岗位:" << this->m_DeptId << this->getDeptName() <<
		"\t岗位职责：管理公司使用事务" << "\n";
}
//获取部门名称
string Boss::getDeptName()
{
	return "老板";
}