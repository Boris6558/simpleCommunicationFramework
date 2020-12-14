#pragma once

#include <QWidget>
#include "ui_sendwidget.h"

class SendWidget : public QWidget
{
	Q_OBJECT

public:
	SendWidget(QWidget *parent = Q_NULLPTR);
	~SendWidget();

Q_SIGNALS:
	void SigRetMainWidget();

private:
	Ui::SendWidget ui;
};
