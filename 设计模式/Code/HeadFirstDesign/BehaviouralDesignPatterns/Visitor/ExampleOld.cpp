/*
* @Description:	员工薪资及工作时间系统最初设计
*/

#include <iostream>
#include <list>

using namespace std;

class Employee
{
public:	
	Employee(string type)
	{
		this->type = type;
	}

	string GetType()
	{
		return this->type;
	}

private:
	string type;			//员工类型:正式员工和临时工
};

class EmployeeList
{
public:	
    //增加员工
	void AddEmployee(Employee employee) 
	{
		employees.push_back(employee);
	}
    
    //处理员工数据
	void Handle(string department_name)
	{
		//财务部处理员工数据
		if(department_name == "财务部") 
		{
			for(auto &obj : employees)
			{
				if(obj.GetType() == "FulltimeEmployee")
				{
					cout << "财务部处理全职员工数据！" << endl;			
				}
				else 
				{
					cout << "财务部处理兼职员工数据！" << endl;
				}
			}
		}
		//人力资源部处理员工数据
		else if(department_name == "人力资源部") 
		{
			for(auto &obj : employees)
			{
				if(obj.GetType() == "FulltimeEmployee")
				{
					cout << "人力资源部处理全职员工数据！" << endl;					
				}
				else 
				{
					cout << "人力资源部处理兼职员工数据！" << endl;
				}
			}			
		}
	}

private:
 	list <Employee> employees;		//员工集合	
};


int main()
{
	Employee employee1("FulltimeEmployee");
	Employee employee2("ParttimeEmployee");

	EmployeeList employees;
	employees.AddEmployee(employee1);
	employees.AddEmployee(employee2);

	employees.Handle("财务部");
	employees.Handle("人力资源部");

	return 0;
}