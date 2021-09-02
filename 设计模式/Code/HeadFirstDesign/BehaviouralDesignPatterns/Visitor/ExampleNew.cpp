/*
* @Description:	采用“访问者模式”设计的的员工薪资及工作时间系统
*/

#include <iostream>
#include <list>

using namespace std;

class Department;

//员工-抽象元素
class Employee
{
public:
	virtual void Accept(Department *department) = 0;	
};

//正式员工-具体元素
class FulltimeEmployee : public Employee
{
public:
	FulltimeEmployee(string name,double weekly_wage,int work_time);

	void Accept(Department *department);

	void SetName(string name);
	string GetName();

	void SetWeeklyWage(double weekly_wage);
	double GetWeeklyWage();

	void SetWorkTime(string name);
	int GetWorkTime();

private:
	string name;			//员工名称
	double weekly_wage;		//周薪
	int work_time;			//周工作时间
};

//临时工-具体元素
class ParttimeEmployee : public Employee
{
public:
	ParttimeEmployee(string name,double weekly_wage,int work_time);

	void Accept(Department *department);

	void SetName(string name);

	string GetName();

	void SetWeeklyWage(double weekly_wage);
	double GetWeeklyWage();

	void SetWorkTime(string name);
	int GetWorkTime();
private:
	string name;			//员工名称
	double weekly_wage;		//周薪
	int work_time;			//周工作时间	
};

//部分-抽象访问者
class Department
{
public: 
	virtual void Visit(FulltimeEmployee *employee) = 0;	
	virtual void Visit(ParttimeEmployee *employee) = 0;	
};


//财务部-具体访问者(统计工资)
class FADepartment : public Department
{
public:
	void Visit(FulltimeEmployee *employee)
	{
		int work_time = employee->GetWorkTime();
		double weekly_wage = employee->GetWeeklyWage();
		if (40 < work_time)
		{
			weekly_wage = weekly_wage + (work_time - 40) * 100;
		}	
		else 
		{
			weekly_wage = weekly_wage - (40 - work_time) * 80;
			if (0 > weekly_wage)
			{
				weekly_wage = 0;
			}	
		}

		cout << "正式员工" << employee->GetName() << "实际工资为" << weekly_wage << endl;

	}

	void Visit(ParttimeEmployee *employee)
	{
		int work_time = employee->GetWorkTime();
		double weekly_wage = employee->GetWeeklyWage();

		cout << "临时工" << employee->GetName() << "实际工资为" << work_time * weekly_wage << endl;
	}
};

//人事部-具体访问者(统计工时)
class HRDepartment : public Department
{
public:
	void Visit(FulltimeEmployee *employee)
	{
		int work_time = employee->GetWorkTime();
		cout << "正式员工" << employee->GetName() << "实际工时为" << work_time;

		if (40 < work_time)
		{
			cout << "正式员工" << employee->GetName() << "加班时间为" << work_time - 40 << "小时" << endl;
		}
		else 
		{
			cout << "正式员工" << employee->GetName() << "请假时间为" << 40 - work_time << "小时" << endl;
		}
	}

	void Visit(ParttimeEmployee *employee)
	{
		int work_time = employee->GetWorkTime();
		cout << "正式员工" << employee->GetName() << "实际工时为" << work_time << endl;
	}
};

FulltimeEmployee::FulltimeEmployee(string name,double weekly_wage,int work_time)
{
	this->name = name;
	this->weekly_wage = weekly_wage;
	this->work_time = work_time;
}

void FulltimeEmployee::Accept(Department *department)
{
	department->Visit(this);
}	

void FulltimeEmployee::SetName(string name)
{
	this->name = name;
}
string FulltimeEmployee::GetName()
{
	return name;
}

void FulltimeEmployee::SetWeeklyWage(double weekly_wage)
{
	this->weekly_wage = weekly_wage;
}
double FulltimeEmployee::GetWeeklyWage()
{
	return weekly_wage;
}

void FulltimeEmployee::SetWorkTime(string name)
{
	this->work_time = work_time;
}
int FulltimeEmployee::GetWorkTime()
{
	return work_time;
}

ParttimeEmployee::ParttimeEmployee(string name,double weekly_wage,int work_time)
{
	this->name = name;
	this->weekly_wage = weekly_wage;
	this->work_time = work_time;
}

void ParttimeEmployee::Accept(Department *department)
{
	department->Visit(this);
}	

void ParttimeEmployee::SetName(string name)
{
	this->name = name;
}
string ParttimeEmployee::GetName()
{
	return name;
}

void ParttimeEmployee::SetWeeklyWage(double weekly_wage)
{
	this->weekly_wage = weekly_wage;
}
double ParttimeEmployee::GetWeeklyWage()
{
	return weekly_wage;
}

void ParttimeEmployee::SetWorkTime(string name)
{
	this->work_time = work_time;
}
int ParttimeEmployee::GetWorkTime()
{
	return work_time;
}

//对象结构
class EmployeeList
{
public:
	void Accept(Department *department)	
	{
		for (auto &e : employees)
		{
			e->Accept(department);
		}
	}

	void AddEmployee(Employee *employee)
	{
		employees.push_back(employee);
	}

	void RemoveEmployee(Employee *employee)
	{
		employees.remove(employee);
	}

private:
	list <Employee *>employees;
};

//客户调用
int main(int argc, char const *argv[])
{
	EmployeeList *employee_list = new EmployeeList();

	Employee *fte1 = new FulltimeEmployee("张无忌",3200,45);
	Employee *fte2 = new FulltimeEmployee("杨过",2000,40);
	Employee *fte3 = new FulltimeEmployee("段誉",2400,38);
	Employee *fte4 = new ParttimeEmployee("洪七公",80,20);
	Employee *fte5 = new ParttimeEmployee("郭靖",60,18);

	employee_list->AddEmployee(fte1);
	employee_list->AddEmployee(fte2);
	employee_list->AddEmployee(fte3);
	employee_list->AddEmployee(fte4);
	employee_list->AddEmployee(fte5);

	employee_list->Accept(new FADepartment());
	employee_list->Accept(new HRDepartment());

	return 0;
}