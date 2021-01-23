#include "mainwidget.h"

#include <QMessageBox>

#include "def/basedef.hpp"
#include "def/tcpserverconfigdef.hpp"
#include "def/prompttextdef.hpp"
#include "def/msghandlerdef.hpp"

#include "sendwidget/sendwidget.h"
#include "configmanager/configmanager.hpp"
#include "other/networkconfig/tcpserverconfig.hpp"
#include "other/prompttextconfig/prompttextconfig.hpp"

#include "threadmanager/threadmanager.hpp"
#include "network/tcpclient.hpp"

#include "msg/msguser.hpp"

#include "tool/serializememory.hpp"


MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent), m_gstring(CONFIG_MGR.GetPromptTextConfig()->GetTipString())
{
    ui.setupUi(this);

	TcpServerConfig *ts_cfg = CONFIG_MGR.GetTcpServerConfig();
	ServerInfo *info = NULL;
	if (ts_cfg)
	{
		info = ts_cfg->GetServerInfo();
		if (!info)
		{
			assert(0);
		}
	}
	m_send_widget = new SendWidget;

	// 登录
	connect(ui.pushButton_login, &QPushButton::clicked,
		[=]()mutable
	{
		if (!this->IsCanLogin())
		{
			return;
		}
		this->setWindowTitle(QString::fromLocal8Bit(m_gstring.g_string[TipString::G_LINK_STATUS_ING].c_str()));
		THREAD_MGR.Start(
			[&]()mutable -> void
		{
			//TCP_C.Disconnect();
			if (TCP_C.Connect())
			{
				Q_EMIT TCP_C.SigConnectSuccess();
			}
			else
			{
				Q_EMIT TCP_C.SigConnectTimeout();
				return;
			}
		}
		,RUN_THREAD_CONNECT_TO_SRVER,RUN_MODE_DETACH); // thread start
	}
	);

	// 连接超时
	connect(&TCP_C,&TcpClient::SigConnectTimeout,this,
		[=]()mutable
	{
		THREAD_MGR.StopAll();

		this->setWindowTitle(QString::fromLocal8Bit(m_gstring.g_string[TipString::G_MAIN_WIDGET_TITLE].c_str()));
		QMessageBox::warning(this
			, QString::fromLocal8Bit(m_gstring.g_string[TipString::G_LINK_TIMEOUT_TIP].c_str())
			, QString::fromLocal8Bit(m_gstring.g_string[TipString::G_LINK_TIMEOUT_CONTENT].c_str()));
	}
		);

	// 连接成功
	connect(&TCP_C, &TcpClient::SigConnectSuccess, this,
		[=]()mutable
	{
		this->setWindowTitle(QString::fromLocal8Bit(m_gstring.g_string[TipString::G_MAIN_WIDGET_TITLE].c_str()));

		THREAD_MGR.Stop(RUN_THREAD_CONNECT_TO_SRVER);
		this->SwitchWidget(SWITCH_MAIN_TO_SEND);

		this->SendLoginUserInfo();
		
		THREAD_MGR.Start(
			[=]()mutable -> void
		{
			TCP_C.Read();

		}, RUN_THREAD_READ,RUN_MODE_DETACH);
	}
	);

	connect(&TCP_C, &TcpClient::SigServerClose, this,
		[=]()mutable
	{
		THREAD_MGR.StopAll(); // 关闭所有线程
		QMessageBox::warning(this
			, QString::fromLocal8Bit(m_gstring.g_string[TipString::G_LINK_TIMEOUT_TIP].c_str())
			, QString::fromLocal8Bit(m_gstring.g_string[TipString::G_LINK_TIMEOUT_CONTENT].c_str()));

		this->SwitchWidget(SWITCH_SEND_TO_MAIN);
		TCP_C.Disconnect();
	}
		);

	// 输入为空，不能登录
	connect(this, &MainWidget::SigLoginFail, this,
		[=]()mutable
	{
		QMessageBox::warning(this
			, QString::fromLocal8Bit(m_gstring.g_string[TipString::G_LOGIN_EMPTY_TXT_TIP].c_str())
			, QString::fromLocal8Bit(m_gstring.g_string[TipString::G_LOGIN_EMPTY_TXT_CONTENT].c_str()));
	}
	);


	this->OnSendWidgetConnect();
}

MainWidget::~MainWidget()
{
	delete m_send_widget;
	m_send_widget = NULL;

	THREAD_MGR.StopAll();

}

bool MainWidget::IsCanLogin()
{
	if (ui.lineEdit_user->text().compare("") == 0 || ui.lineEdit_passwd->text().compare("") == 0)
	{
		Q_EMIT this->SigLoginFail();
		return false;
	}
	return true;
}

void MainWidget::SwitchWidget(int mode)
{
	switch (mode)
	{
	case SWITCH_MAIN_TO_SEND:
	{
		if (m_send_widget != NULL)
		{
			m_send_widget->show();
			this->hide();
		}
	}
	break;
		
	case SWITCH_SEND_TO_MAIN:
	{
		if (m_send_widget != NULL)
		{
			this->show();
			m_send_widget->hide();
		}
	}
	break;

		
	}
}

void MainWidget::OnSendWidgetConnect()
{
	// 返回登录
	connect(m_send_widget, &SendWidget::SigRetMainWidget, this,
		[=]()mutable
	{
		TCP_C.Disconnect();
		this->SwitchWidget(SWITCH_SEND_TO_MAIN);
	}
	);
}

void MainWidget::SendLoginUserInfo()
{
	UserLoginReqCS info;
	info.header.msg_type = USER_LOGIN_MSG_CS;
	memcpy(info.login_name, ui.lineEdit_user->text().toStdString().data(), sizeof(info.login_name));
	memcpy(info.login_passwd, ui.lineEdit_passwd->text().toStdString().data(), sizeof(info.login_passwd));

	TCP_C.Send((const char *)&info, sizeof(UserLoginReqCS));

}
