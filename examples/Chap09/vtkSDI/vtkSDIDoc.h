/**********************************************************************

  �ļ���: vtkSDIDoc.h
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

// vtkSDIDoc.h : interface of the CvtkSDIDoc class
//


#pragma once

#include "vtkSmartPointer.h"
#include "vtkImageData.h"

class CvtkSDIDoc : public CDocument
{
protected: // create from serialization only
	CvtkSDIDoc();
	DECLARE_DYNCREATE(CvtkSDIDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CvtkSDIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();

public:
	vtkSmartPointer<vtkImageData> m_pImageData;
	virtual void SetTitle(LPCTSTR lpszTitle);
};


