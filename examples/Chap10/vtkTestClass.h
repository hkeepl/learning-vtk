/**********************************************************************

  �ļ���: vtkTestClass.h
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#ifndef __vtkTestClass_h
#define __vtkTestClass_h

#include <vtkObject.h>

class vtkTestClass: public vtkObject
{
public:
	vtkTypeMacro(vtkTestClass,vtkObject);
	static vtkTestClass *New();

	vtkGetMacro(Flag,  bool);
	vtkGetMacro(Speed, double);
	vtkGetVector3Macro(Position,double);

	vtkSetMacro(Flag,bool);
	vtkSetMacro(Speed,double);
	vtkSetVector3Macro(Position,double);

	vtkBooleanMacro(Flag, bool);

	void PrintSelf(ostream &os, vtkIndent indent);

private:
	double Speed;
	double Position[3];
	bool   Flag;

protected:
	vtkTestClass();
	~vtkTestClass();

private:
	vtkTestClass(const vtkTestClass&);  // Not implemented.
	void operator=(const vtkTestClass&);  // Not implemented.

};

#endif