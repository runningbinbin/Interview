/*
* @Description:	杀毒软件最初设计（既可对文件夹杀毒又可对文件杀毒）
*/

#include <stdio.h>
#include <iostream>
#include <list>
using namespace std;

//图像文件类
class ImageFile 
{
public:
 	ImageFile(string name) 
 	{
		this->name = name;
	}

public:
	void KillVirus() 
	{
		//简化代码，模拟杀毒
		cout << "----对图像文件'" + name + "'进行杀毒" << endl;
	}

private:
	string name;		//文件名
};

//文本文件类
class TextFile 
{
public:
 	TextFile(string name) 
 	{
		this->name = name;
	}
	
public:
	void KillVirus() 
	{
		//简化代码，模拟杀毒
		cout << "----对文本文件'" + name + "'进行杀毒" << endl;
	}

private:
	string name;		//文件名
};

//文件夹类
class Folder 
{
public:
 	Folder(string name) 
 	{
		this->name = name;
	}
	
public:
	void AddFolders(Folder *f)
	{
		all_folders.push_back(f);
	}

	void AddImageFiles(ImageFile *i)
	{
		all_images.push_back(i);
	}
	void AddTextFiles(TextFile *t)
	{
		all_texts.push_back(t);
	}

	void KillVirus() 
	{
		cout << "----对文件夹'" + name + "'进行杀毒" << endl;
		for (auto &f : all_folders) 
		{
			f->KillVirus();
		}
		for (auto &i : all_images) 
		{
			i->KillVirus();
		}
		for (auto &t : all_texts) 
		{
			t->KillVirus();
		}
	}

private:
	string name;					//文件夹名

	list<Folder *> all_folders;		//该文件夹下面包含的文件夹
	list<ImageFile *> all_images;	//该文件夹下面包含的图片文件
	list<TextFile *> all_texts; 	//该文件夹下面包含的文本文件
};

int main()
{
	Folder *folder1 = new Folder("sunnny 的资料");
	Folder *folder2 = new Folder("图像文件");
	Folder *folder3 = new Folder("文本文件");

	ImageFile *image1 = new ImageFile("小龙女.jpg"); 
	ImageFile *image2 = new ImageFile("张无忌.jpg"); 

	TextFile *text1 = new TextFile("小龙女.txt"); 
	TextFile *text2 = new TextFile("张无忌.txt"); 

	folder2->AddImageFiles(image1);
	folder2->AddImageFiles(image2);

	folder3->AddTextFiles(text1);
	folder3->AddTextFiles(text2);

	folder1->AddFolders(folder2);
	folder1->AddFolders(folder3);

	folder1->KillVirus();

	return 0;
}