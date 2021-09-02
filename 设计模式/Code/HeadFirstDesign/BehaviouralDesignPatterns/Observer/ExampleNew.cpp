/*
* @Description: 使用“观察者模式”设计的"气象站更新软件"
*/

#include <stdio.h>
#include <iostream>
#include <list>
using namespace std;


#define SUBJECT_PUSH		0			//主题推方式
#define OBSERVER_PULL		1			//观察者拉取方式

#if SUBJECT_PUSH
//抽象观察者
class Observer
{
public:	
	virtual void Update(float temp, float humidity, float pressure) = 0;
};

//抽象主题
class Subject
{
public:
	//增加观察者
	void Registerobserver(Observer *observer)
	{
		observers.push_back(observer);
	}
	//删除观察者
	void Removeobserver(Observer *observer)
	{
		observers.remove(observer); 
	}

	//通知观察者
	virtual void Notifyobserver() = 0;

protected:
	list <Observer*> observers;
};

//具体主题
class WeatherData : public Subject
{
public:
	void Notifyobserver()
	{
		if (changed)
		{	
			for (auto &obs : observers)
			{
				obs->Update(this->temp,this->humidity,this->pressure);
			}
			changed = false;
		} 
	}

	void SetChanged()
	{
		changed = true;
	}

	void MeasurementsChanged()
	{
		//当温差超过半度才通知观察者(此处假设温差超过半度，否则需要在通知之前，
		//获取新的温度和上次的温度，算出温差已决定是否调用此接口)
		SetChanged();	

		Notifyobserver();
	}

	//设置数值
	void SetMeasurements(float temp, float humidity, float pressure)
	{
		this->temp = temp;
		this->humidity = humidity;
		this->pressure = pressure;
		MeasurementsChanged();
	}

public:	

	float temp;
	float humidity;
	float pressure;

	bool changed;			//通知标志
};

//具体观察者
class CurrentConditionsDisplay : public Observer
{
public:
	CurrentConditionsDisplay(Subject *subject)
	{
		subject->Registerobserver(this);
	}

public:
	void Update(float temp, float humidity, float pressure)
	{
		this->temp = temp;
		this->humidity = humidity;
		this->pressure = pressure;

		cout << "CurrentConditionDisplay" << \
		",temp = " << this->temp <<\
		",humidity = " << this->humidity <<\
		",pressure = " << this->pressure << endl;
	}	

public:
	float temp;
	float humidity;	
	float pressure;
};

//具体观察者
class StaticsDisplay : public Observer
{
public:
	StaticsDisplay(Subject *subject)
	{
		subject->Registerobserver(this);
	}

public:
	void Update(float temp, float humidity, float pressure)
	{
		this->temp = temp;
		this->humidity = humidity;
		this->pressure = pressure;

		cout << "staticsDisplay" << \
		",temp = " << this->temp <<\
		",humidity = " << this->humidity <<\
		",pressure = " << this->pressure << endl;
	}	

public:
	float temp;
	float humidity;	
	float pressure;	
};

//具体观察者
class ForecastDisplay : public Observer
{
public:
	ForecastDisplay(Subject *subject)
	{
		subject->Registerobserver(this);
	}

public:
	void Update(float temp, float humidity, float pressure)
	{
		this->temp = temp;
		this->humidity = humidity;
		this->pressure = pressure;

		cout << "forecastDisplay" << \
		",temp = " << this->temp <<\
		",humidity = " << this->humidity <<\
		",pressure = " << this->pressure << endl;
	}	

public:
	float temp;
	float humidity;	
	float pressure;	
};
#endif 

#if OBSERVER_PULL

class Subject;

//抽象观察者
class Observer
{
public:	
	virtual void Update(Subject *subject) = 0;
};

//抽象主题
class Subject
{
public:
	//增加观察者
	void Registerobserver(Observer *observer)
	{
		observers.push_back(observer);
	}
	//删除观察者
	void Removeobserver(Observer *observer)
	{
		observers.remove(observer); 
	}

	//通知观察者
	virtual void Notifyobserver() = 0;

protected:	
	list <Observer*> observers;
};


//具体主题
class WeatherData : public Subject
{
public:
	void Notifyobserver()
	{
		if (changed)
		{	
			for (auto &obs : observers)
			{
				obs->Update(this);
			}
			changed = false;
		} 
	}

	void SetChanged()
	{
		this->changed = true;
	}

	void MeasurementsChanged()
	{
		//当温差超过半度才通知观察者(此处假设温差超过半度，否则需要在通知之前，
		//获取新的温度和上次的温度，算出温差已决定是否调用此接口)
		this->SetChanged();	

		this->Notifyobserver();
	}

	//设置数值
	void SetMeasurements(float temp, float humidity, float pressure)
	{
		this->temp = temp;
		this->humidity = humidity;
		this->pressure = pressure;
		MeasurementsChanged();
	}

	//方便观察者拉取
	float Gettemperature()
	{
		return temp;
	}
	float Gethumidity()
	{
		return humidity;
	}
	float Getpressure()
	{
		return pressure;
	}

public:	

	float temp;
	float humidity;
	float pressure;

	bool changed;			//通知标志
};

//具体观察者
class CurrentConditionsDisplay : public Observer
{
public:
	CurrentConditionsDisplay(Subject *subject)
	{
		subject->Registerobserver(this);
	}

public:
	void Update(Subject *subject)
	{
		WeatherData *weatherData = (WeatherData *)subject;
		this->temp = weatherData->Gettemperature();
		this->humidity = weatherData->Gethumidity();
		this->pressure = weatherData->Getpressure();

		cout << "CurrentConditionDisplay" << \
		",temp = " << this->temp <<\
		",humidity = " << this->humidity <<\
		",pressure = " << this->pressure << endl;
	}	

public:
	float temp;
	float humidity;	
	float pressure;
};

//具体观察者
class StaticsDisplay : public Observer
{
public:
	StaticsDisplay(Subject *subject)
	{
		subject->Registerobserver(this);
	}

public:
	void Update(Subject *subject)
	{	
		WeatherData *weatherData = (WeatherData *)subject;
		this->temp = weatherData->Gettemperature();
		this->humidity = weatherData->Gethumidity();
		this->pressure = weatherData->Getpressure();

		cout << "staticsDisplay" << \
		",temp = " << this->temp <<\
		",humidity = " << this->humidity <<\
		",pressure = " << this->pressure << endl;
	}	

public:
	float temp;
	float humidity;	
	float pressure;	
};

//具体观察者
class ForecastDisplay : public Observer
{
public:
	ForecastDisplay(Subject *subject)
	{
		subject->Registerobserver(this);
	}

public:
	void Update(Subject *subject)
	{
		WeatherData *weatherData = (WeatherData *)subject;
		this->temp = weatherData->Gettemperature();
		this->humidity = weatherData->Gethumidity();
		this->pressure = weatherData->Getpressure();

		cout << "forecastDisplay" << \
		",temp = " << this->temp <<\
		",humidity = " << this->humidity <<\
		",pressure = " << this->pressure << endl;
	}	

public:
	float temp;
	float humidity;	
	float pressure;	
};
#endif 

//客户调用
int main()
{
	#if SUBJECT_PUSH
	WeatherData *weatherData = new WeatherData();
	CurrentConditionsDisplay currentConditionsDisplay(weatherData);
	StaticsDisplay staticsDisplay(weatherData);
	ForecastDisplay forecastDisplay(weatherData);
	weatherData->SetMeasurements(1.1, 1.2, 1.3);
	#elif OBSERVER_PULL
	WeatherData *weatherData = new WeatherData();
	CurrentConditionsDisplay currentConditionsDisplay(weatherData);
	StaticsDisplay staticsDisplay(weatherData);
	ForecastDisplay forecastDisplay(weatherData);
	weatherData->SetMeasurements(1.1, 1.2, 1.3);	
	#endif 

	return 0;
}