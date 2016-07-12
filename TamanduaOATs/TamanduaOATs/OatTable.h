// OatTable.h: interface for the COatTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OATTABLE_H__6A32BEE1_B56E_4CB8_A7B8_20B3F828CC9F__INCLUDED_)
#define AFX_OATTABLE_H__6A32BEE1_B56E_4CB8_A7B8_20B3F828CC9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataNode.h"
#include "vector"
using namespace std;
class COatTable  
{
public:
	COatTable(int totalfactor, int strength);
	virtual ~COatTable();
public:
	void AssignLevel(int num, int* level);     //输入水平数组
	void SetStrength(int strength);   //设置强度
	void GetTable();
	string GetProgramDir();
	
	//string PrintTable();   //打印计算出的正交表
	char* PrintTable();
public:
	/*基本输入*/
	int m_totalfactor;  //总变量个数
	int m_strength;     //强度
	int m_Facnum; //变量个数
	vector<int>  m_vecFactorLevel;    //每个变量的水平数
	

	/*下面的成员为中间计算的辅助成员*/
	vector<CDataNode>  m_vecLevelValue;  //每个因素的当前水平值（用于试探）
	
	int m_curCol;       //当前列,下标从1开始
	int m_StartFactor;  /*从哪一列开始排列，每行该值以前的列均为0，最大值不得超过因子数与强度值之差*/
	
	int m_bIsValid;    //当前解的检测结果，用来指导后面的回朔方向
	vector<int> m_curRecord;    //当前行记录，记录当前解
					 
	/* 核心输出*/
	vector< vector<int> >  m_vecOAT;    //最后生成的正交表
public:
	void Calculate();    //得到初步的结果
	void FillTable();
	void Clear();     //计算前的清理工作
	
	int GetCurValue(){return m_vecLevelValue[m_curCol-1].GetValue();}   //得到当前的试探值
	bool ValueIsFit(int value)const;    //对当前值进行检测

	void AddCurLine();   //将当前记录写到正交表中,即输出一个可行解
	void InsertValue(int value){m_curRecord[m_curCol-1] = value;}    //将一个合法的取值写到当前位置
	
	bool HasNextNode();  //判断是否还有下一个待判解
	
	int FindCarryIndex()const;       //向后找到第一个可以进行+1操作的列
	void ResetIndex();    //将当前列的取值起点归零。
	void AddIndex();      //去当前结点的下一个可能值

	void PrintCurRec();
};

#endif // !defined(AFX_OATTABLE_H__6A32BEE1_B56E_4CB8_A7B8_20B3F828CC9F__INCLUDED_)
