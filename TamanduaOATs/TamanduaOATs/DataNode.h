// DataNode.h: interface for the CDataNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATANODE_H__1EA68E4F_AF17_4924_9A1F_AACB47CFBF03__INCLUDED_)
#define AFX_DATANODE_H__1EA68E4F_AF17_4924_9A1F_AACB47CFBF03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "vector"
using namespace std;

class CDataNode  
{
public:
	CDataNode(int num);
	virtual ~CDataNode();

public:
	int GetValue()const {return m_vecValue[m_nIndex];}
	void ResetIndex(int nIndex = 0){m_nIndex = nIndex;}
	void AddIndex(){++m_nIndex;}
	bool IsFull()const {return m_nIndex+1 == m_total;}
	int GetIndex()const{return m_nIndex;}
	
public:
	int m_total;              //值的个数
	int m_nIndex;            //要取第几个值
	vector<int> m_vecValue;   //值的列表
};

#endif // !defined(AFX_DATANODE_H__1EA68E4F_AF17_4924_9A1F_AACB47CFBF03__INCLUDED_)
