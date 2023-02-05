#pragma once

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QPainter>
#include <QDebug>
#include "ui_MainWindow.h"

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	//重写无边框窗口的鼠标拖动规则
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);

	virtual void paintEvent(QPaintEvent* event);



private slots:
	void on_closeButton_clicked();
private:
	QPoint m_lastpos;
	bool m_pressed = false;
	Ui::MainWindowClass ui;
};
