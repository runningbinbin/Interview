/*
* @Description:	“单例模式”标准代码
*/

#include <stdio.h>
#include <iostream>

using namespace std;

//编译宏，同一个时刻，只有一个才有效
#define COMMON_LAZY_SINGLETON 					1	//最简单的懒汉模式，多线程调用可能会创建多个实例
#define MULTITHREAD_LAZY_SINGLETON 				0	//在最简单的懒汉模式基础上优化，防止创建多个实例，但是即使创建实例后仍需同步，性能低
#define MULTITHREAD_EFFICIENT_LAZY_SINGLETON 	0	//多线程优化方式，创建实例后不再同步
#define EAGER_SINGLETON 						0	//饿汉模式

#if COMMON_LAZY_SINGLETON
//最简单的懒汉式
//时间换空间
//弊端： 当多线程调用时，有可能创建多个实例
//   在懒汉式的单例类中，其实有两个状态，单例未初始化和单例已经初始化。
//    假设单例还未初始化，有两个线程同时调用GetInstance方法，这时执行 m_pInstance == NULL 
//    肯定为真，然后两个线程都初始化一个单例，最后得到的指针并不是指向同一个地方，不满足单例类的定义了，
//    所以懒汉式的写法会出现线程安全的问题！在多线程环境下，要对其进行修改。
class LazySingleton
{
	//私有构造器
private:
	LazySingleton()
	{

	}

public:
	//静态方法
	static LazySingleton* GetInstance()
	{
		if (NULL == instance)
		{
			instance = new LazySingleton();
		}	
			
		return instance;
	}

private:
	static LazySingleton *instance;	
};

LazySingleton* LazySingleton::instance = NULL;
#endif 
 
#if MULTITHREAD_LAZY_SINGLETON
//多线程懒汉（针对 最简单的懒汉式 做出的优化）
//弊端：一旦实例化了对象，之后就不在需要同步了，之后每次调用都是累赘，性能低
class LazySingleton
{
	//私有构造器
private:
	LazySingleton()
	{

	}

public:
	//静态方法
	static LazySingleton* GetInstance()
	{
		pthread_mutex_lock(&mutex);
		if (NULL == instance)
			instance = new LazySingleton();
		pthread_mutex_unlock(&mutex);	

		return instance;
	}

private:
	static LazySingleton *instance;
	static pthread_mutex_t mutex;	
};

LazySingleton* LazySingleton::instance = NULL;
#endif 


#if MULTITHREAD_EFFICIENT_LAZY_SINGLETON
//多线程懒汉模式优化
//双重检查加锁，实例不存在则进入加锁创建，反之直接
class LazySingleton
{
	//私有构造器
private:
	LazySingleton()
	{

	}

public:
	//静态方法
	static LazySingleton* GetInstance()
	{
		if (NULL == instance)
		{
			pthread_mutex_lock(&mutex);
			if (NULL == instance)
				instance = new LazySingleton();
			pthread_mutex_unlock(&mutex);
		}	
		
		return instance;
	}


private:
	static LazySingleton *instance;	
	static pthread_mutex_t mutex;
};
LazySingleton* LazySingleton::instance = NULL;
#endif 


#if EAGER_SINGLETON
//饿汉模式
//空间换时间
class EagerSingleton
{
	//私有构造器
private:
	EagerSingleton()
	{

	}

public:
	//静态方法
	static EagerSingleton* GetInstance()
	{
		return instance;
	}

private:
	static EagerSingleton *instance;	
};

EagerSingleton* EagerSingleton::instance = new Singleton();
#endif 


//客户调用
int main()
{
	#if COMMON_LAZY_SINGLETON || MULTITHREAD_LAZY_SINGLETON || MULTITHREAD_EFFICIENT_LAZY_SINGLETON
	LazySingleton *singleton = LazySingleton::GetInstance();
	#else
	EagerSingleton *singleton = EagerSingleton::GetInstance();
	#endif 

	return 0;
}