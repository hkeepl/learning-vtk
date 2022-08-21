/**********************************************************************

  �ļ���: vtkAlgorithmFilter.h
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#ifndef __vtkAlgorithmFilter_h
#define __vtkAlgorithmFilter_h

#include "vtkAlgorithm.h"

class vtkDataSet;
class vtkTestDataObject;

class vtkAlgorithmFilter : public vtkAlgorithm
{
public:
	static vtkAlgorithmFilter *New();
	vtkTypeMacro(vtkAlgorithmFilter,vtkAlgorithm);

	void PrintSelf(ostream& os, vtkIndent indent);

	virtual int ProcessRequest(vtkInformation*,
		vtkInformationVector**,
		vtkInformationVector*);

	vtkTestDataObject* GetOutput();
	vtkTestDataObject* GetOutput(int);
	virtual void SetOutput(vtkDataObject* d);

	vtkDataObject* GetInput();
	vtkDataObject* GetInput(int port);

	void SetInput( vtkDataObject* );
	void SetInput( int, vtkDataObject* );

	void AddInput( vtkDataObject* );
	void AddInput( int, vtkDataObject* );

	vtkGetMacro(Factor, double);
	vtkSetMacro(Factor, double);

protected:
	vtkAlgorithmFilter();
	~vtkAlgorithmFilter();

	virtual int RequestDataObject(
		vtkInformation* request,
		vtkInformationVector** inputVector,
		vtkInformationVector* outputVector );

	virtual int RequestInformation(
		vtkInformation* request,
		vtkInformationVector** inputVector,
		vtkInformationVector* outputVector );

	virtual int RequestData(
		vtkInformation* request,
		vtkInformationVector** inputVector,
		vtkInformationVector* outputVector );

	virtual int RequestUpdateExtent(
		vtkInformation*,
		vtkInformationVector**,
		vtkInformationVector* );

	virtual int FillOutputPortInformation( int port, vtkInformation* info );
	virtual int FillInputPortInformation( int port, vtkInformation* info );

private:
	vtkAlgorithmFilter( const vtkAlgorithmFilter& ); // Not implemented.
	void operator = ( const vtkAlgorithmFilter& );  // Not implemented.

	double Factor;
};

#endif