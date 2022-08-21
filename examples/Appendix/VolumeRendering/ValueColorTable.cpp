/**********************************************************************

  �ļ���: ValueColorTable.cpp
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#include "stdafx.h"
#include "ValueColorTable.h"
#include "math.h"

enum TableType
{
	Continus,
	Discrete
};

CValueColorTable::CValueColorTable(void)
{
	//Ĭ��ֵ
	m_iType = Continus;

	AddKeyPoint(0, RGB(165, 0, 0));
	AddKeyPoint(0.33, RGB(255, 203, 15));
	AddKeyPoint(0.66, RGB(255, 230, 170));
	AddKeyPoint(1.0, RGB(255, 196, 150));
}

CValueColorTable::CValueColorTable(double min, double max)
{
	//Ĭ��ֵ
	m_iType = Continus;

	double range = max-min;
	if (range <= 0)
	{
		AddKeyPoint(min, RGB(165, 0, 0));
		AddKeyPoint(0.33, RGB(255, 203, 15));
		AddKeyPoint(0.66, RGB(255, 230, 170));
		AddKeyPoint(1.0, RGB(255, 196, 150));
	}
	else
	{
		AddKeyPoint(min, RGB(165, 0, 0));
		AddKeyPoint(min+0.33*range, RGB(255, 203, 15));
		AddKeyPoint(min+0.66*range, RGB(255, 230, 170));
		AddKeyPoint(max, RGB(255, 196, 150));
	}
	
}

//�������캯��
CValueColorTable::CValueColorTable(const CValueColorTable &ValueColorTable)
{
	m_Values.RemoveAll();
	m_Colors.RemoveAll();
	
	//��ȡ��ɫ��
	m_Values.Copy( ValueColorTable.m_Values );
	m_Colors.Copy( ValueColorTable.m_Colors );

	m_iType = ValueColorTable.m_iType;
}

CValueColorTable::~CValueColorTable(void)
{
	RemoveAll();
}

void CValueColorTable::LoadDefaultColorTable()
{
	RemoveAll();

	//Ĭ��ֵ
	m_iType = Continus;
	AddKeyPoint(0, RGB(0, 0, 255));
	AddKeyPoint(0.33, RGB(0, 255, 0));
	AddKeyPoint(0.66, RGB(255, 255, 0));
	AddKeyPoint(1.0, RGB(255, 0, 0));
	
}


//��ʼ��
void CValueColorTable::SetValueColorTable(CArray<double,double> &values, CArray<long,long> &colors)
{
	RemoveAll();

	m_Values.Copy(values);
	m_Colors.Copy(colors);
}

void CValueColorTable::SetValueColorTable(CValueColorTable Source)
{
	RemoveAll();
	
	Source.GetValueColorTable(m_Values, m_Colors);
	m_iType = Source.GetType();
}

//��ֵ�����
CValueColorTable& CValueColorTable::operator=(CValueColorTable &ValueColorTable)
{
	RemoveAll();

	ValueColorTable.GetValueColorTable(m_Values, m_Colors);
	m_iType = ValueColorTable.GetType();

	return *this;
}

//�õ�ֵ�ķ�Χ
double CValueColorTable::GetValueRange()
{
	if(m_Values.GetSize() > 0) return m_Values.GetAt(m_Values.GetSize()-1)-m_Values.GetAt(0);
	else return -1;
}

//�õ��ؼ����ƫ����
double CValueColorTable::GetOffSetAt(int index)
{
	if (GetValueRange() == 0) return 1;

	if(m_iType == Continus)
		return (m_Values.GetAt(index)-m_Values.GetAt(0))/GetValueRange();
	else
		return (m_Values.GetAt(index)-m_Values.GetAt(0))/(GetValueRange()+1);
}

//��ӹؼ���
void CValueColorTable::AddKeyPoint(double value, long color)
{
	m_Values.Add(value);
	m_Colors.Add(color);
}

//����ؼ���
void CValueColorTable::InsertAt(int index, double value, long color)
{
	m_Values.InsertAt(index,value);
	m_Colors.InsertAt(index,color);
}

//����һ���ؼ���
void CValueColorTable::InsertKeyPoint(double value, long color)
{
	//����ֵ�ҵ�����ֵ����
	for (int index=0; index<m_Values.GetSize()-1; index++)
	{
		if(value>=m_Values.GetAt(index) && value<=m_Values.GetAt(index+1))
		{
			m_Values.InsertAt(index+1,value);
			m_Colors.InsertAt(index+1,color);
			break;
		}
	}
}

BOOL CValueColorTable::SetValue( int iIndex, double value, long color )
{
	m_Values.SetAt( iIndex , value );
	m_Colors.SetAt( iIndex,  color );

	return TRUE;
}

void CValueColorTable::displayValue()
{
#ifdef _DEBUG
	for ( INT_PTR i = 0;  i< m_Values.GetSize(); i ++ )
	{
		TRACE("\nValue %f\n", m_Values.GetAt( i ) );
	}
#endif // _DEBUG
}

//���ùؼ���
void  CValueColorTable::SetKeyPoint(int index, double value, long color)
{
	DeleteKeyPoint(index);
	InsertKeyPoint(value,color);
}

//ɾ��һ���ؼ���
void CValueColorTable::DeleteKeyPoint(int index)
{
	m_Values.RemoveAt(index);
	m_Colors.RemoveAt(index);
}

//���
void CValueColorTable::RemoveAll()
{
	m_Values.RemoveAll();
	m_Colors.RemoveAll();
}

//ֵ����ɫת��
int CValueColorTable::GetColorByValue(double value, Color &color)
{
	if ( value <= m_Values.GetAt( 0 ))
	{
		color.SetFromCOLORREF( m_Colors.GetAt( 0 ) );
		return -1;
	}

	INT_PTR iIndex = m_Values.GetSize();
	if ( value >= m_Values.GetAt( iIndex - 1 ) )
	{
		color.SetFromCOLORREF( m_Colors.GetAt( iIndex - 1 ));
		return 1;
	}

	////////////////////����ֵ�ҵ�����ֵ����,���������////////////////////
	if(m_iType == Continus)
	{
		for (int index=0; index<m_Values.GetSize()-1; index++)
		{
			if(value>=m_Values.GetAt(index) && value<=m_Values.GetAt(index+1))
			{
				//����ƫ��
				double pp = (value-m_Values.GetAt(index))/(m_Values.GetAt(index+1)-m_Values.GetAt(index));
				//�������ڲ�ֵ������ɫ
				long c1,c2;
				int r1,r2,g1,g2,b1,b2;

				c1 = m_Colors.GetAt(index);
				c2 = m_Colors.GetAt(index+1);

				r1 = (c1)&(0x000000FF);
				g1 = ((c1)&(0x0000FF00))>>8;
				b1 = ((c1)&(0x00FF0000))>>16;

				r2 = (c2)&(0x000000FF);
				g2 = ((c2)&(0x0000FF00))>>8;
				b2 = ((c2)&(0x00FF0000))>>16;

				//������ɫ��ֵ
				int r,g,b;
				r = (int)((r2-r1)*pp+r1);
				g = (int)((g2-g1)*pp+g1);
				b = (int)((b2-b1)*pp+b1);

				color.SetFromCOLORREF(RGB(r,g,b));
				break;
			}
		}
	}
	//////////////////////////////��ɢ�����/////////////////////////////////
	else
	{
		bool bFind = false;
		for (int index=0; index<m_Values.GetSize(); index++)
		{
			if(value == m_Values.GetAt(index))
			{
				COLORREF colorRef = m_Colors.GetAt(index);
				color.SetFromCOLORREF(colorRef);
				bFind = true;
				break;
			}
		}

		if (!bFind) color.SetFromCOLORREF(RGB(255, 255, 255));
	}
	

	return 0;
}

//��ȡ�ؼ�����
int CValueColorTable::GetSize()
{
	return (int)m_Values.GetSize();
}

//��ȡ�ؼ����ֵ����ɫ
double CValueColorTable::GetValueAt(int index)
{
	if ( m_Colors.GetSize() <= index )
	{
		return 1.0;
	}

	return m_Values.GetAt(index);
}

long CValueColorTable::GetColorAt(int index)
{
	if ( m_Colors.GetSize() <= index )
	{
		return RGB(255,0,0);
	}

	return m_Colors.GetAt(index);
}

//�õ���С���ֵ
void CValueColorTable::GetValueMinMax(double &min, double &max)
{
	min = m_Values.GetAt(0);
	max = m_Values.GetAt(m_Values.GetSize()-1);
}

double CValueColorTable::GetValueByOffset(double offset)
{
	if (m_iType == 0)
		return m_Values.GetAt(0)+offset*GetValueRange();
	else
		return m_Values.GetAt(0)+offset*(GetValueRange()+1);
}

//��ȡֵ�������ɫ����
void CValueColorTable::GetValueColorTable(CArray <double, double> &values, CArray <long, long> &colors)
{
	values.Copy(m_Values);
	colors.Copy(m_Colors);
}

BOOL CValueColorTable::getColorValuePosition(vector<double> & vecPos, vector<long> &vecColor, vector<double> &vecValue )
{
	if ( getColorPosition( vecPos ) )
	{
		INT_PTR iIndex = 0;
		for ( ; iIndex < m_Colors.GetSize(); iIndex ++  )
		{
			vecColor.push_back( m_Colors.GetAt( iIndex ) );
		}

		iIndex = 0;
		for ( ; iIndex < m_Values.GetSize(); iIndex ++ )
		{
			vecValue.push_back( m_Values.GetAt( iIndex ) );
		}

		return TRUE;
	}

	return FALSE;
}


//////////////////////////////////////////////////////////////////////////
//  ֻ�ı������Сֵ
//////////////////////////////////////////////////////////////////////////
BOOL CValueColorTable::setMinMaxKeyPoint( double dMin, double dMax )
{

	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
//  �м����������Сֵ�仯
//////////////////////////////////////////////////////////////////////////
BOOL CValueColorTable::SetMinMaxKeyPointFollow( double dMin, double dMax )
{
	if ( dMin > dMax )
	{
		return FALSE;
	}

	if ( m_Values.GetSize() == 0 )
	{
		m_Values.Add( dMin );
		m_Values.Add( dMax );

		return TRUE;
	}

	TRACE("\n����ǰ�ģ�\n");
	displayValue();

	double dOldValueRange = GetValueRange();
	double dNewValueRange = dMax - dMin;
	
	double dOldMin = m_Values.GetAt( 0 );
	double dOldMax = m_Values.GetAt( m_Values.GetSize() - 1 );
	INT_PTR iIndex = 0;
	for ( ; iIndex < m_Values.GetSize(); iIndex ++ )
	{
		double dValue = dMin + dNewValueRange *(m_Values.GetAt( iIndex ) - dOldMin) / dOldValueRange;
		m_Values.SetAt( iIndex, dValue );
	}
	
	TRACE("\n���ĺ��: \n");
	displayValue();

	return TRUE;

}

BOOL CValueColorTable::getColorPosition( vector<double> & vecPos )
{
	if ( m_Values.GetSize() <= 0 )
	{
		return FALSE;
	}

	double dRange = GetValueRange();
	if ( abs(dRange) < 0.000001 )
	{
		INT_PTR iIndex = 0;
		INT_PTR iSize = m_Values.GetSize();

		for (; iIndex < m_Values.GetSize(); iIndex ++ )
		{
			double dPosition = (double)iIndex/(double)(iSize - 1);
			// TRACE( "\nPosition--[%f]\n", dPosition );
			if ( dPosition <= 1.0 && dPosition >= 0.0 )
			{
				vecPos.push_back( dPosition );
			}
		}

		return TRUE;
	}
	else {

		INT_PTR iIndex = 0;
		for (; iIndex < m_Values.GetSize(); iIndex ++ )
		{
			double dPosition = (m_Values.GetAt( iIndex ) - m_Values.GetAt( 0 )) / dRange ;
			if ( dPosition <= 1.0 && dPosition >= 0.0 )
			{
				vecPos.push_back( dPosition );
			}
		}
		
		return TRUE;

	}

	return FALSE;
}

//������ɫ������
void CValueColorTable::SetType(int iType)
{
	m_iType = iType;
}
int  CValueColorTable::GetType()
{
	return m_iType;
}