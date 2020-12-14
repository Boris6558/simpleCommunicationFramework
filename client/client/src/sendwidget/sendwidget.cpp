#include "sendwidget.h"
#include <QPushButton>

#include <string>
#include <cstring>

#include "network/tcpclient.hpp"
#include "def/msghandlerdef.hpp"

SendWidget::SendWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.pushButton_ret_login, &QPushButton::clicked,
		[=]()mutable
	{
		Q_EMIT this->SigRetMainWidget();
	}
		);

	connect(ui.pushButton_send, &QPushButton::clicked,
		[=]()mutable
	{
		TCP_C.Send(ui.plainTextEdit->toPlainText().toStdString(), SEND_MEESAGE_MSG_CS);
	}
	);
}

SendWidget::~SendWidget()
{
}
