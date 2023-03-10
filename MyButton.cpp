#include "MyButton.h"

MyButton::MyButton(QString imgSrc, int len)
{
	QPixmap pic(imgSrc);
	QPixmap mpic = pic.scaled(len, len);

	/*Debug Code*/
	//QString str = QString("w:%1 h:%2").arg(mpic.width()).arg(mpic.height());
	//qDebug() << str;

	this->setFixedSize(len, len);
	this->setStyleSheet("QPushButton{border:none}");
	this->setIcon(mpic);
	this->setIconSize(QSize(len, len));
}

MyButton::~MyButton()
{}

void MyButton::setHover(bool flag) { this->hoverEnable = flag; }

void MyButton::enterEvent(QEvent* event)
{
	if (this->hoverEnable)
	{
		emit entered();
	}
}

void MyButton::leaveEvent(QEvent* event)
{
	if (this->hoverEnable)
	{
		emit leave();
	}
}
