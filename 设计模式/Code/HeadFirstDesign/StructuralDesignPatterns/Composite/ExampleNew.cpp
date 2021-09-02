/*
* @Description:	运用“组合模式”杀毒软件设计（既可对文件夹杀毒又可对文件杀毒）
*/

#include <stdio.h>
#include <iostream>
#include <list>
using namespace std;

//抽象文件类-抽象构件
class File 
{
public:
	//增加成员
	virtual void Add(File *c) = 0; 

	//删除成员
	virtual void Remove(File *c) = 0; 

	//获取成员
	virtual File* GetChild(int index) = 0; 

	//业务方法
	virtual void KillVirus() = 0;  
};

//图像文件类-叶子构件
class ImageFile : public File
{
public:
 	ImageFile(string name) 
 	{
		this->name = name;
	}

public:
	void Add(File *c)
	{
		cout << "unsupport options" << endl;
	}

	void Remove(File *c)
	{
		cout << "unsupport options" << endl;
	}

	File* GetChild(int index)
	{
		cout << "unsupport options" << endl;
	}

	void KillVirus() 
	{
		//简化代码，模拟杀毒
		cout << "----对图像文件'" + name + "'进行杀毒" << endl;
	}

private:
	string name;		//文件名
};

//文本文件类-叶子构件
class TextFile : public File
{
public:
 	TextFile(string name) 
 	{
		this->name = name;
	}
	
public:
	void Add(File *c)
	{
		cout << "unsupport options" << endl;
	}

	void Remove(File *c)
	{
		cout << "unsupport options" << endl;
	}

	File* GetChild(int index)
	{
		cout << "unsupport options" << endl;
	}
	void KillVirus() 
	{
		//简化代码，模拟杀毒
		cout << "----对文本文件'" + name + "'进行杀毒" << endl;
	}

private:
	string name;		//文件名
};

//视频文件类-叶子构件
class VideoFile : public File
{
public:
 	VideoFile(string name) 
 	{
		this->name = name;
	}
	
public:
	void Add(File *c)
	{
		cout << "unsupport options" << endl;
	}

	void Remove(File *c)
	{
		cout << "unsupport options" << endl;
	}

	File* GetChild(int index)
	{
		cout << "unsupport options" << endl;
	}
	void KillVirus() 
	{
		//简化代码，模拟杀毒
		cout << "----对文本文件'" + name + "'进行杀毒" << endl;
	}

private:
	string name;		//文件名
};

//文件夹类-组合构件
class Folder : public File
{
public:
 	Folder(string name) 
 	{
		this->name = name;
	}
	
public:
	void Add(File *c)
	{
		files.push_back(c);
	}

	void Remove(File *c)
	{
		files.remove(c);
	}

	File* GetChild(int index)
	{
		list <File *>::iterator iter = files.begin();

		for (int i = 0;i < index;i++)
		{
			iter++;	
		}

		return *iter;
	}

	void KillVirus() 
	{
		cout << "----对文件夹'" + name + "'进行杀毒" << endl;
		for(auto &f : files) 
		{
			f->KillVirus();
		}
	}

private:
	string name;					//文件夹名
	list<File *> files;				//该文件夹下面包含的文件及文件夹
};


//客户调用
int main()
{
	File *folder1 = new Folder("sunnny 的资料");
	File *folder2 = new Folder("图像文件");
	File *folder3 = new Folder("文本文件");
	File *folder4 = new Folder("视频文件");

	File *image1 = new ImageFile("小龙女.jpg"); 
	File *image2 = new ImageFile("张无忌.jpg"); 

	File *text1 = new TextFile("小龙女.txt"); 
	File *text2 = new TextFile("张无忌.txt"); 

	File *video1 = new VideoFile("小龙女.mp4"); 
	File *video2 = new VideoFile("张无忌.mp4"); 

	folder2->Add(image1);
	folder2->Add(image2);

	folder3->Add(text1);
	folder3->Add(text2);

	folder4->Add(video1);
	folder4->Add(video2);

	folder1->Add(folder2);
	folder1->Add(folder3);
	folder1->Add(folder4);

	folder1->KillVirus();

	return 0;
}