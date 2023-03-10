#pragma once

#include <Windows.h>
#include <QDebug>
#include <QPushButton>
#include <QPixmap>
#include <QTime>

class MyButton : public QPushButton
{
	Q_OBJECT

public:
	MyButton(QString imgSrc, int len);
	~MyButton();

	virtual void enterEvent(QEvent* event);
	virtual void leaveEvent(QEvent* event);

	void setHover(bool flag);

signals:
	void entered();
	void leave();
private:
	bool hoverEnable = false;
};
