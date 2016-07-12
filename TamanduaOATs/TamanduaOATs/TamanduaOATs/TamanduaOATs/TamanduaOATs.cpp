#include <Python.h> //python.h是包含python一些定义的头文件，在python的include目录下
#include <windows.h>
#include "OatTable.h"
#include "iostream"
#include <fstream>
#include <stdio.h>
#include <string>
#include "vector"
using namespace std;
#pragma comment(lib,"python27.lib")

static PyObject *TamanduaOATs_OATs(PyObject *self,PyObject *args);

extern "C"_declspec(dllexport)void initTamanduaOATs()
{
         static PyMethodDef TamanduaOATsMethods[] = {
                   {"OATs",TamanduaOATs_OATs,METH_VARARGS},{NULL,NULL,NULL}
         };
         PyObject *m = Py_InitModule("TamanduaOATs",TamanduaOATsMethods);
}
		 
char* Oatc(int m_nTotalFactor, int m_nFacNum ,int m_nList[])
{

	int nlenlevel =m_nFacNum;
	char* strOutFile;
	if(nlenlevel < 2)
		return "0";
	int m_nstrength = 2;//强度	
	COatTable ots(m_nTotalFactor,m_nstrength);
	ots.AssignLevel(m_nFacNum,m_nList);
	ots.GetTable();
	
	strOutFile=ots.PrintTable();

	return strOutFile;
	//return 1;
}


//第一个self参数我们用不着，具体查手册，第二个参数是python传给我们的参数,它是一个python的参数tuple 
static PyObject *TamanduaOATs_OATs(PyObject *self,PyObject *args)
{

		 char *msg;
		 int m_totalfactor;
		 int m_Facnum;
		 //int m_listLen;
		 char *result;
         PyObject* outF;
		 
		 
		 if(!PyArg_ParseTuple(args,"iis",&m_totalfactor,&m_Facnum,&msg))
                   return NULL;
		 //int* m_level=(int*)malloc(m_Facnum);
		int* m_level = new int[m_Facnum];
		 int len = strlen(msg);
		 int order=0;
		 char tmp[16]={0};
		 int j=0;


		 for(int i=0;i<len;i++)
		 {
			 if(','!=msg[i])
			 {
				 tmp[j++]=msg[i];

			 }
			 else
			 {
				 m_level[order++] = atoi(tmp);//遇到逗号表示该整数完成，将其转换后存到动态分配的数组中
				   memset(tmp, 0, 16);//清空临时字符串
				   j = 0;
			 }
			   if(i+1 == len)//到达原字符串尾部直接将临时字符串转换成整数并存储
			  {
			   m_level[order++] = atoi(tmp);
			  }
		 }



		 /*outF = (PyObject*)Py_BuildValue("i",m_level[0]); 
          return outF;*/
		 //-----------------------

		 //-----------------------
	

		 /*char *tokenPtr = strtok(msg,",");

		 int istep=0;
		 while(tokenPtr!=NULL&&istep<m_Facnum)
		 {

			 *(m_level+istep)=atoi(tokenPtr);
			 istep++;
			 tokenPtr=strtok(NULL,",");
		 }
		 delete tokenPtr;
		 tokenPtr=NULL;*/
		 //outF = (PyObject*)Py_BuildValue("i",m_level[0]); 



   //      return outF;
		 result = Oatc(m_totalfactor,m_Facnum,m_level);
		
		 outF = (PyObject*)Py_BuildValue("s",result); 



         return outF;
}