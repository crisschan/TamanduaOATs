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
	void AssignLevel(int num, int* level);     //����ˮƽ����
	void SetStrength(int strength);   //����ǿ��
	void GetTable();
	string GetProgramDir();
	
	//string PrintTable();   //��ӡ�������������
	char* PrintTable();
public:
	/*��������*/
	int m_totalfactor;  //�ܱ�������
	int m_strength;     //ǿ��
	int m_Facnum; //��������
	vector<int>  m_vecFactorLevel;    //ÿ��������ˮƽ��
	

	/*����ĳ�ԱΪ�м����ĸ�����Ա*/
	vector<CDataNode>  m_vecLevelValue;  //ÿ�����صĵ�ǰˮƽֵ��������̽��
	
	int m_curCol;       //��ǰ��,�±��1��ʼ
	int m_StartFactor;  /*����һ�п�ʼ���У�ÿ�и�ֵ��ǰ���о�Ϊ0�����ֵ���ó�����������ǿ��ֵ֮��*/
	
	int m_bIsValid;    //��ǰ��ļ����������ָ������Ļ�˷����
	vector<int> m_curRecord;    //��ǰ�м�¼����¼��ǰ��
					 
	/* �������*/
	vector< vector<int> >  m_vecOAT;    //������ɵ�������
public:
	void Calculate();    //�õ������Ľ��
	void FillTable();
	void Clear();     //����ǰ��������
	
	int GetCurValue(){return m_vecLevelValue[m_curCol-1].GetValue();}   //�õ���ǰ����ֵ̽
	bool ValueIsFit(int value)const;    //�Ե�ǰֵ���м��

	void AddCurLine();   //����ǰ��¼д����������,�����һ�����н�
	void InsertValue(int value){m_curRecord[m_curCol-1] = value;}    //��һ���Ϸ���ȡֵд����ǰλ��
	
	bool HasNextNode();  //�ж��Ƿ�����һ�����н�
	
	int FindCarryIndex()const;       //����ҵ���һ�����Խ���+1��������
	void ResetIndex();    //����ǰ�е�ȡֵ�����㡣
	void AddIndex();      //ȥ��ǰ������һ������ֵ

	void PrintCurRec();
};

#endif // !defined(AFX_OATTABLE_H__6A32BEE1_B56E_4CB8_A7B8_20B3F828CC9F__INCLUDED_)
