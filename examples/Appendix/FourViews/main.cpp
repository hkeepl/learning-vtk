/**********************************************************************

  �ļ���: main.cpp
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#include "MainWindow.h"
#include <QTextCodec>

//���򷢲�ʱ���������������䣬����ʱ�Ͳ��������̨�������
#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )

int main( int argc, char **argv ) 
{
	QApplication *app = new QApplication(argc, argv);
	QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

	MainWindow window;
	window.show();
	return app->exec();
};

