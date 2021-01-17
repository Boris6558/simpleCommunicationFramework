#include "mainwidget/mainwidget.h"
#include <QtWidgets/QApplication>

#include "dump/dump.hpp"
#include "configmanager/configmanager.hpp"
#include "other/networkconfig/tcpserverconfig.hpp"

#include "threadmanager/threadmanager.hpp"

int main(int argc, char *argv[])
{
	MiniDump::EnableAutoDump(true);

	// ��ʼ����������
	CONFIG_MGR.InitAllCfg();


    QApplication a(argc, argv);
	MainWidget w;
	w.show();

    return a.exec();
}
