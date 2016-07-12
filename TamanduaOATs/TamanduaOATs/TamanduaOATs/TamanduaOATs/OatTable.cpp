// OatTable.cpp: implementation of the COatTable class.
//
//////////////////////////////////////////////////////////////////////

#include "OatTable.h"
#include "iostream"
#include <fstream>
#include <string> 
using namespace std;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COatTable::COatTable(int totalfactor, int strength) 
:m_totalfactor(totalfactor), m_strength(strength)
{

}

COatTable::~COatTable()
{
	/*vector<int>().swap(m_vecFactorLevel);
	vector<CDataNode>().swap(m_vecLevelValue);
	vector<int>().swap(m_curRecord);
	vector< vector<int> >().swap(m_vecOAT);*/
}

/*
** FacNum  - 变量个数
** levarr  - 变量所对应的水平数,该数组必须按升序排序
*/
void COatTable::AssignLevel(int FacNum, 
							 int* levarr)
{
	int i=0;
	m_vecFactorLevel.clear();
	//vector<int>().swap(m_vecFactorLevel);
	m_Facnum=FacNum;
	for(i=0; i<FacNum; ++i)
		m_vecFactorLevel.push_back(levarr[i]);
}


bool COatTable::HasNextNode()
{
	int CarryIndex;
	if (m_bIsValid) {
		//PrintCurRec();    // 输出目前的解，用于调试

		if(m_curCol != m_Facnum)//2016-2-16 criss 修改了
		{
			++m_curCol;
			ResetIndex();
			return true;
		}
		else
			AddCurLine();
	}
	//继续找下一个待判解
	if ((CarryIndex = FindCarryIndex()) !=0) {   //向上找到一个可以加1的位，即回朔过程
		m_curCol = CarryIndex;
		AddIndex();
		return true;
	}
	else
	{
		//-------------------------------
		if (m_StartFactor + m_strength <= m_Facnum) {   //将首因素指标加1
			m_curRecord[m_StartFactor-1] = 0;
			++m_StartFactor;
			m_curCol = m_StartFactor;
			ResetIndex();
			return true;
		}
		else{
			return false;
		}
	}
}

char* COatTable::PrintTable()//传入一个二维数组的引用
{
	//ofstream outfile("e:\\_temp");
	
	int i=0, j=0;
	int linenum = m_vecOAT.size();
	string strOutFile ="";
	char carrTemp[3];
	string strCtoS = "";
	
	for(i=0; i<linenum; ++i)
	{
		for(j=0; j<m_Facnum; ++j)
		{
			_itoa_s(m_vecOAT[i][j],carrTemp,10);
			strCtoS.assign(carrTemp);
			strOutFile=strOutFile+" "+strCtoS;
		}
		strOutFile=strOutFile+"\n";
	}
	int len = strOutFile.length();
	char *data;
	
	data = (char *)malloc((len+1)*sizeof(char));

	strOutFile.copy(data,len,0);
	//string(strOutFile).swap(strOutFile);
	//string(strCtoS).swap(strCtoS);
	return data;
}

void COatTable::AddCurLine()
{
	m_vecOAT.push_back(m_curRecord);
	//vector<int>().swap(m_curRecord);

}

int COatTable::FindCarryIndex()const
{
	int j=0;
	for(j = m_curCol; j>= m_StartFactor; --j)
		if (!m_vecLevelValue[j-1].IsFull())
			return j;
	return 0;
}

void COatTable::GetTable()
{
	Calculate();
	FillTable();
}

void COatTable::FillTable()
{
	int i=0,j=0;
	int linenum = m_vecOAT.size();
	vector<CDataNode> vecNode = m_vecLevelValue;
	for(j=0; j<m_Facnum;++j){
		vecNode[j].ResetIndex();
		for(i=0; i<linenum; ++i)
			if (m_vecOAT[i][j]==0) 
				break;
		for(;i<linenum;++i)
		{

			m_vecOAT[i][j] = vecNode[j].GetValue();
			/*
			#ifdef _DEBUG
				cout<<"m_vecOAT["<<i<<"," <<j<<" ] = "<<m_vecOAT[i][j]<<endl;
			#endif
			*/
			vecNode[j].AddIndex();
			if (vecNode[j].GetIndex() == m_vecFactorLevel[j]) 
				vecNode[j].ResetIndex();
		}
				
	}
	
}

void COatTable::ResetIndex()
{
	m_vecLevelValue[m_curCol-1].ResetIndex();
}

void COatTable::AddIndex()
{
	m_vecLevelValue[m_curCol-1].AddIndex();
}

void COatTable::Clear()
{
	m_vecOAT.clear();
	//vector< vector<int> >().swap(m_vecOAT);
	m_curRecord.assign(m_totalfactor,1);    //当前行记录
	m_vecLevelValue.clear();
	//vector<CDataNode>().swap(m_vecLevelValue);
	int i=0;
	for(i=0; i<m_Facnum; ++i)
		m_vecLevelValue.push_back(CDataNode(m_vecFactorLevel[i]));
	
	m_curCol  = 1;
    m_StartFactor  = 1;    
	m_bIsValid = true;
}

//打印当前的解
void COatTable::PrintCurRec()
{
	int i=0;
	for(i=0; i<m_curCol;++i)
		cout<<m_curRecord[i]<<"\t";
	cout<<endl;

}


//采用回朔法得到正交表，
void COatTable::Calculate()
{
	Clear();	

	int value=0;
	do{
		value = GetCurValue();
		
/*#ifdef _DEBUG
		cout<<"the current  column is: "<<m_curCol<<endl;
		cout<<"the index is: "<<m_vecLevelValue[m_curCol-1].GetIndex()+1<<endl;
		cout<<"the cur value is: "<<value<<endl;
#endif*/
		
		if (m_bIsValid = ValueIsFit(value))
			InsertValue(value);
	}while(HasNextNode());
}

bool COatTable::ValueIsFit(int value)const
{
	int count = 0;
	int totalline = m_vecOAT.size();
	int i=0,j=0;

	bool bResult = true;

	if (m_curCol < (m_StartFactor+m_strength-1) )
		bResult = true;
	else{
		for(i=0; i<totalline;++i)
		{
			count = 0;
			for(j=m_StartFactor-1; j<m_curCol-1; ++j)
			{
				if (m_curRecord[j] == m_vecOAT[i][j]) {
					++count;
					if(count == m_strength){
						bResult = false;
						break;
					}
				}
			}
			if (!bResult) 
				break;
			if ((count == m_strength-1) && value == m_vecOAT[i][m_curCol-1]){
				bResult = false;
				break;
			}
		}
	}

	
	return bResult;
}