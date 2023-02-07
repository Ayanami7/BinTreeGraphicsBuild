#pragma once

#include <QWidget>
#include <QPoint>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include "ui_MainWindow.h"
#include "MyButton.h"
#include "MenuWidget.h"
#include "DisplayWidget.h"

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

protected slots:
	void openMenu();

private:
	int Radius = 25;
	QPoint m_lastpos;
	bool m_menu_hidden = true;
	bool m_pressed = false;
	QPropertyAnimation* slideProperty= nullptr;

	//控件
	MyButton* closeBtn;
	MyButton* openMenuBtn;
	MyButton* closeMenuBtn;
	MyButton* settingBtn;
	DisplayWidget* displayWidget;
	MenuWidget* menuWidget;

	Ui::MainWindowClass ui;
};
