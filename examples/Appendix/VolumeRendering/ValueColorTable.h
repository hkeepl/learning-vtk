/**********************************************************************

  �ļ���: ValueColorTable.h
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#pragma once

#include <afxtempl.h>
#include <vector>

using namespace std;

class  CValueColorTable
{
public:
	CValueColorTable(void);
	CValueColorTable(double min, double max);
	//�������캯��
	CValueColorTable(const CValueColorTable &ValueColorTable);

public:
	~CValueColorTable(void);
public:
	// ����ȱʡ����
	void LoadDefaultColorTable();
	//��ʼ��
	void SetValueColorTable(CArray<double,double> &values, CArray<long,long> &colors);
	void SetValueColorTable(CValueColorTable Source);
	//��ֵ�����
	CValueColorTable& operator=(CValueColorTable &ValueColorTable);
	//��ȡֵ�������ɫ����
	void GetValueColorTable(CArray <double, double> &values, CArray <long, long> &colors);
	//�õ�ֵ�ķ�Χ
	double GetValueRange();
	//�õ��ؼ����ƫ����
	double GetOffSetAt(int index);
	//��ȡ�ؼ�����
	int GetSize();
	//��ȡ�ؼ����ֵ����ɫ
	double GetValueAt(int index);
	long   GetColorAt(int index);
	//�õ���С���ֵ
	void   GetValueMinMax(double &min, double &max);
	//����ƫ�ƻ�ȡֵ
	double GetValueByOffset(double offset);
	//��ӹؼ���
	void AddKeyPoint(double value, long color);
	//����ؼ���
	void InsertAt(int index, double value, long color);
	//����һ���ؼ��㣬����ֵ�Զ��ҵ���Ӧ��λ��
	void InsertKeyPoint(double value, long color);
	//���ùؼ���
	void SetKeyPoint(int index, double value, long color);
	//ɾ��һ���ؼ���
	void DeleteKeyPoint(int index);
	//���
	void RemoveAll();
	//ֵ����ɫת��
	int GetColorByValue(double value, Color &color);
	
	
	BOOL SetValue( int, double, long );
	
	void displayValue();

	BOOL getColorValuePosition(vector<double> &, vector<long> &, vector<double> & );

	BOOL getColorPosition( vector<double> & );

	BOOL SetMinMaxKeyPointFollow( double, double );
	BOOL setMinMaxKeyPoint( double, double );

	//������ɫ������
	void SetType(int iType);
	int  GetType();

private:
	CArray<long ,long>  m_Colors;   //������ɫ������
	CArray<double,double> m_Values; //ֵ

	int m_iType;
};
