/*
* @Description: 使用“桥接模式”设计的“跨平台不同格式的图像显示”
*/

#include <iostream>

using namespace std;

//像素矩阵类,
//像素矩阵类：辅助类，各种格式的文件最终都被转化为像素矩阵，不同的操作系统提供不同的方式显示像素矩阵
class Matrix 
{
	//此处代码省略
};


//抽象操作系统实现类-抽象实现类
class ImageImp 
{
public:
	//显示像素矩阵m
	virtual void DoPaint(Matrix *m) = 0;  
};

//Windows操作系统实现类-具体实现类
class WindowsImp : public ImageImp 
{
public: 
    void DoPaint(Matrix *m) 
    {
    	//调用Windows系统的绘制函数绘制像素矩阵
    	cout << "在Windows操作系统中显示图像：" << endl;
    }
};

//Linux操作系统实现类-具体实现类
class LinuxImp : public ImageImp 
{
public: 
    void DoPaint(Matrix *m) 
    {
    	//调用Linux系统的绘制函数绘制像素矩阵
    	cout << "在Linux操作系统中显示图像：" << endl;
    }
};

//Unix操作系统实现类-具体实现类
class UnixImp : public ImageImp 
{
public: 
    void DoPaint(Matrix *m) 
    {
    	//调用Unix系统的绘制函数绘制像素矩阵
    	cout << "在Unix操作系统中显示图像：" << endl;
    }
};

//抽象图像类-抽象类
class Image 
{
public:
	void SetImageImp(ImageImp *imp) 
	{
		this->imp = imp;
	} 
 
	virtual void ParseFile(string file_name) = 0;

protected:
 	ImageImp *imp;
};

//JPG格式图像-扩充类
class JPGImage : public Image 
{
public:
 	void ParseFile(string file_name) 
 	{
        //模拟解析JPG文件并获得一个像素矩阵对象m;
        Matrix *m = new Matrix(); 
        imp->DoPaint(m);

        cout << file_name << "格式为JPG" << endl;
    }
};
//PNG格式图像-扩充类
class PNGImage : public Image 
{
public:
 	void ParseFile(string file_name) 
 	{
        //模拟解析PNG文件并获得一个像素矩阵对象m;
        Matrix *m = new Matrix(); 
        imp->DoPaint(m);

        cout << file_name << "格式为PNG" << endl;
    }
};
//BMP格式图像-扩充类
class BMPImage : public Image 
{
public:
 	void ParseFile(string file_name) 
 	{
        //模拟解析BMP文件并获得一个像素矩阵对象m;
        Matrix *m = new Matrix(); 
        imp->DoPaint(m);

        cout << file_name << "格式为BMP" << endl;
    }
};
//GIF格式图像-扩充类
class GIFImage : public Image 
{
public:
    void ParseFile(string file_name) 
    {
        //模拟解析BMP文件并获得一个像素矩阵对象m;
        Matrix *m = new Matrix(); 
        imp->DoPaint(m);

        cout << file_name << "格式为GIF" << endl;
    }
};


//客户调用
int main()
{
	//JPG格式图片在Windows显示
	Image *image = new JPGImage();
	image->SetImageImp(new WindowsImp());
	image->ParseFile("小龙女.jpg");

	//PNG格式图片在Linux显示
	Image *image2 = new PNGImage();
	image2->SetImageImp(new LinuxImp());
	image2->ParseFile("小龙女.png");

	return 0;
}