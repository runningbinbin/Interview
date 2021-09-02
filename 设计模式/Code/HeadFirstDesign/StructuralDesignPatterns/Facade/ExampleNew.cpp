/*
* @Description: 使用“外观模式”设计的家庭影院
*/

#include <stdio.h>
#include <stdbool.h>
#include <iostream>

using namespace std;


//爆米花机-子系统
class PopcornPopper
{
public:
	void On()
	{
		cout << "popcorn popper on" << endl;
	}	
	void Off()
	{
		cout << "popcorn popper off" << endl;
	}	
	void Pop()
	{
		cout << "popcorn popper pop" << endl;
	}	
};

//影院灯光-子系统
class TheaterLights
{
public:		
	void On()
	{
		cout << "theater lights on" << endl;
	}	
	void Off()
	{
		cout << "theater lights off" << endl;
	}	
	void Dim(int LightRate)
	{
		this->LightRate = LightRate;
		cout << "theater lights set light rate to " << LightRate << "%" <<endl;
	}	

public:
	int LightRate;				//亮度等级
};

//屏幕-子系统
class Screen
{
public:
	void Up()
	{
		cout << "screen up" << endl;
	}	
	void Down()
	{
		cout << "screen down" << endl;
	}		
};

//投影仪-子系统
class Projector
{
public:
	void On()
	{
		cout << "projector on" << endl;
	}	
	void Off()
	{
		cout << "projector off" << endl;
	}	
	void SetInput(int Input)
	{
		cout << "projector set input Input" << endl;
	}		
	void WideScreenMode()
	{
		cout << "projector WideScreenMode" << endl;
	}

public:
	int Input;
};

//dvd-子系统
class DvdPlayer
{
public:
	void On()
	{
		cout << "projector on" << endl;
	}	
	void Off()
	{
		cout << "projector off" << endl;
	}
	void Play(string PlayWhat)
	{
		cout << "dvd player play" << PlayWhat <<endl;
	}	
	void Stop()
	{
		cout << "dvd player stop" <<endl;
	}		
};


//功放-子系统
class Amplifer
{
public:
	void On()
	{
		cout << "amplifer on" << endl;
	}	
	void Off()
	{
		cout << "amplifer off" << endl;
	}
	void SetDVD()
	{
		cout << "amplifer set dvd" << endl;
	}	
	void SetVolume(int Volume)
	{
		this->Volume = Volume;
		cout << "amplifer set volume to " << Volume <<endl;
	}	

public:
	int Volume;							//音量
};

//外观
class HomeTheaterFacade
{
public:
	HomeTheaterFacade()
	{
		popcornPopper = new PopcornPopper();
		lights = new TheaterLights();
		screen = new Screen();
		projector = new Projector();
		amplifer = new Amplifer();
		dvdPlayer = new DvdPlayer();
	}	

public:
	void WatchMovie(string PlayWhat)
	{
		cout << "get ready to watch" << PlayWhat << endl;
		popcornPopper->On();
		popcornPopper->Pop();

		lights->Dim(10);

		screen->Down();

		projector->On();
		projector->SetInput(1);
		projector->WideScreenMode();

		amplifer->On();
		amplifer->SetDVD();
		amplifer->SetVolume(5);

		dvdPlayer->On();
		dvdPlayer->Play(PlayWhat);
	}

	void EndMovie()
	{
		popcornPopper->Off();
		lights->On();
		screen->Up();
		projector->Off();
		amplifer->Off();
		dvdPlayer->Stop();
		dvdPlayer->Off();
	}

public:
	PopcornPopper *popcornPopper;
	TheaterLights *lights;
	Screen *screen;
	Projector *projector;
	Amplifer *amplifer;
	DvdPlayer *dvdPlayer;
};

//客户调用
int main()
{	
	HomeTheaterFacade homeTheaterFacade;
	homeTheaterFacade.WatchMovie("Movie");
	homeTheaterFacade.EndMovie();	

	return 0;
}