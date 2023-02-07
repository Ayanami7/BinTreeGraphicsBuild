#pragma once

#include <QWidget>
#include <QPoint>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QLabel>
#include "ui_MainWindow.h"
#include "MyButton.h"
#include "MyDialog.h"
#include "MenuWidget.h"
#include "DisplayWidget.h"
#include "PartWidget.h"

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	//重写无边框窗口的鼠标拖动规则
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);

	virtual void paintEvent(QPaintEvent* event);

protected slots:
	void openMenu();

private:
	int Radius = 25;
	int titleHeight = 160;
	QPoint m_lastpos;
	bool m_menu_hidden = true;
	bool m_pressed = false;
	QPropertyAnimation* slideProperty= nullptr;

	//控件
	MyButton* closeBtn;
	MyButton* settingBtn;
	MyButton* closeMenuBtn;
	MyButton* githubBtn;

	DisplayWidget* displayWidget;
	MenuWidget* menuWidget;
	PartWidget* infoWidget;

	Ui::MainWindowClass ui;
};
