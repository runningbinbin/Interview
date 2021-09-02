/*
* @Description: "气象站更新软件"最初设计
*/

#include <iostream>

using namespace std;


//用weatherData取得数据并更新三个布告板的显示：目前状况（温度、湿度、气压）、气象统计和天气预报

//目前状况-布告栏1
class CurrentConditionsDisplay
{
public:
	void Update(float temp,float humidity,float pressure)
	{
		cout << "currentConditionsDisplay" <<\
		",temp: " << temp << \
		",humidity: " << humidity << \
		",pressure: " << pressure << endl;
	}
};

//气象统计-布告栏2
class StaticsDisplay
{
public:
	void Update(float temp,float humidity,float pressure)
	{
		cout << "staticsDisplay" <<\
		",temp: " << temp << \
		",humidity: " << humidity << \
		",pressure: " << pressure << endl;
	}
};

//天气预报-布告栏3
class ForecastDisplay
{
public:
	void Update(float temp,float humidity,float pressure)
	{
		cout << "forecastDisplay" <<\
		",temp: " << temp << \
		",humidity: " << humidity << \
		",pressure: " << pressure << endl;
	}
};

//weatherData类
class WeatherData
{
public:
	WeatherData(CurrentConditionsDisplay *currentConditionsDisplay,\
		StaticsDisplay *staticsDisplay,\
		ForecastDisplay *forecastDisplay)
	{
		this->currentConditionsDisplay = currentConditionsDisplay;
		this->staticsDisplay = staticsDisplay;
		this->forecastDisplay = forecastDisplay;
	}

public:
	float Gettemperature()
	{
		return 25.2;
	}	

	float Gethumidity()
	{
		return 252;
	}

	float Getpressure()
	{
		return 2520;
	}

	//一旦气象测量更新，此方法会被调用
	void MeasurementsChanged()
	{
		float temp = Gettemperature();
		float humidity = Gethumidity();
		float pressure = Getpressure();

		//针对具体实现编程，而非针对接口编程，后期增加/删除必须更改程序
		//这里看起来是一个统一的接口update,参数也一样
		currentConditionsDisplay->Update(temp,humidity,pressure);
		staticsDisplay->Update(temp,humidity,pressure);
		forecastDisplay->Update(temp,humidity,pressure);
	}

public:
	CurrentConditionsDisplay *currentConditionsDisplay;	
	StaticsDisplay *staticsDisplay;
	ForecastDisplay *forecastDisplay;
};

int main()
{
	WeatherData weatherData(new CurrentConditionsDisplay(),\
		new StaticsDisplay(),\
		new ForecastDisplay());
	weatherData.MeasurementsChanged();

	return 0;
}	