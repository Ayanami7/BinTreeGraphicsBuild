#pragma once

#include <QDialog>
#include <QPainter>
#include <QMouseEvent>
#include "MyButton.h"

class MyDialog  : public QDialog
{
	Q_OBJECT

public:
	MyDialog(int w, int h, int r, QWidget* parent = nullptr);
	~MyDialog();

	//重写无边框窗口的鼠标拖动规则
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);

	virtual void paintEvent(QPaintEvent* event);
private:
	int Radius = 15;
	int titleHeight = 60;
	QPoint m_lastpos;
	bool m_pressed = false;

	MyButton* closeBtn;
};
