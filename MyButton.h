#pragma once

#include <QDebug>
#include <QPushButton>
#include <QPixmap>

class MyButton : public QPushButton
{
	Q_OBJECT

public:
	MyButton(QString imgSrc, int len);
	MyButton(QString imgSrc, int width, int height);
	~MyButton();

};
