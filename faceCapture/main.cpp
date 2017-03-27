#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "cstringt.h"
#include "io.h"
#include <string>
#include <vector>
#include <fstream>

//#include <opencv/cvaux.hpp>
using namespace::cv;
using namespace std;

vector<string> filenamesGlobal;

vector<string> getFilesName(string path){
	//文件句柄  
	long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	string p;
	vector<string>filenames;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之  
			//如果不是,加入列表  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFilesName(p.assign(path).append("\\").append(fileinfo.name));
			}
			else
			{
				filenames.push_back(fileinfo.name);  // 直接获取名字即可
				//files.push_back(p.assign(path).append("\\").append(fileinfo.name));  
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
	return filenames;
}

int main(int argc, const char * argv[]) {
	//定义保存POSE文件夹下的所有文件夹名的字符串
	char  fileName[10575][20];


	//读取文件夹下file.txt文件中的所有文件夹的名字
	FILE *read = fopen("E:\\CASIA-WebFace_Normalization\\file.txt", "r");
	int j = 0;
	while (!feof(read)) {
		fscanf(read, "%s", fileName[j]);
		//strcat(fileName[j], "\\");
		j++;
	}
	//____________________________________________________
	//    char fileName[7][15] = {"Accessory/","Aging/","Background/","Distance/","Expression/","Lighting/","Normal/"};



	//遍历所有文件夹中的图像，切割人脸区域并保存至result2文件夹中
	int i;
	for (i = 0; i<10575; i++) {

		//读取POSE文件夹下的字文件中的txt文件
		char filePath[150] = "E:\\CASIA-WebFace\\CASIA-WebFace (1)\\CASIA-WebFace\\";  //定义保存文件路径的字符串
		char filePath1[150];
		strcat(filePath, fileName[i]); //把子文件夹名拼接上E:\\CASIA-WebFace-Normalization\\0000045
		strcpy(filePath1, filePath);
		strcat(filePath1, "\\");  //E:\\CASIA-WebFace-Normalization\\0000045\\

		
		filenamesGlobal = getFilesName(filePath);
		
		for (int j = 0; j < filenamesGlobal.size(); j++)
		{
			char faceName[50];     //定义图像名
			char facepath[150];    //定义图像的路径
			strcpy(faceName, filenamesGlobal[j].c_str());
			strcpy(facepath, filePath1);
			strcat(facepath, faceName);

			//根据图像的路径加载图像
			IplImage* img;
			img = cvLoadImage(facepath, CV_LOAD_IMAGE_COLOR);
			printf("images loaded!");


			//定义图像保存的路径
			char filePathSave[150] = "E:\\CASIA-COLOR\\";
			char faceNameFinal[150];
			strcpy(faceNameFinal, fileName[i]);
			strcat(faceNameFinal, faceName);
			strcat(filePathSave, faceNameFinal);//把图像名拼接上
			
			cvSaveImage(filePathSave, img, 0);//保存图像
			
			cvReleaseImage(&img);
		}

	}
	printf("images saved!\n");

}