#pragma once

#include <QtWidgets/QWidget>
#include "ui_mainwidget.h"

#include "def/mainwidgetdef.hpp"
#include "def/threadmanagerdef.hpp"
#include "def/threaddef.hpp"

class SendWidget;
struct TipString;
class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = Q_NULLPTR);
	virtual ~MainWidget();

	bool IsCanLogin();
	void SwitchWidget(int mode);
	void OnSendWidgetConnect();		// 管理QTcpSocket连接

	void SendLoginUserInfo();

Q_SIGNALS:
	void SigLoginFail();

private:
    Ui::MainWidgetClass ui;
	SendWidget *m_send_widget;
	const TipString &m_gstring;

};
