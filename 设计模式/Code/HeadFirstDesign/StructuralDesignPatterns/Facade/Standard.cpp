/*
* @Description: “外观模式”标准代码
*/

#include <iostream>

using namespace std;

//子系统A
class SubSystemA
{
public: 
    void MethodA()
    {
        //业务实现代码
        cout << "SubSystemA MethodA()" << endl;
    }
};
 
//子系统B
class SubSystemB
{
public: 
    void MethodB()
    {
        //业务实现代码
        cout << "SubSystemB MethodB()" << endl;
     }
};

//子系统C
class SubSystemC
{
public:
    void MethodC()
    {
        //业务实现代码
        cout << "SubSystemC MethodC()" << endl;
    }
};

//外观类
class Facade
{
public:    
    Facade()
    {
        syb_system_a = new SubSystemA();
        syb_system_b = new SubSystemB();
        syb_system_c = new SubSystemC();
    }

    void Method()
    {
        syb_system_a->MethodA();
        syb_system_b->MethodB();
        syb_system_c->MethodC();
    }

private:
    SubSystemA *syb_system_a;
    SubSystemB *syb_system_b;
    SubSystemC *syb_system_c;
};

//客户调用
int main()
{
    //客户只需要接触外观类,就能完成业务
    Facade *facade = new Facade();
    facade->Method();
    
    return 0;
}