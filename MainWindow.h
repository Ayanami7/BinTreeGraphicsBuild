#pragma once

#include <QWidget>
#include <QPoint>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QLabel>
#include <QPixMap>
#include <QTimer>
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

private:
	void resetType();

	void setGitDialog();
	void setLogDialog();
	void setPropertyWidget();

protected slots:
	void openMenu();
	void openGitDialog();
	void openLogDialog();
	void updateUpHalf();
	//void updateDownHalf();
	void changeType();

private:
	int Radius = 30;
	int titleHeight = 160;
	QPoint m_lastpos;
	bool m_menu_hidden = true;
	bool m_pressed = false;
	QPropertyAnimation* slideProperty= nullptr;

	//widget pointer

	QPushButton* traverBtn1;
	QPushButton* traverBtn2;
	QPushButton* traverBtn3;
	QPushButton* traverBtn4;

	MyDialog* logDialog;
	MyDialog* gitDialog;
	DisplayWidget* displayWidget;
	MenuWidget* menuWidget;
	PartWidget* infoWidget;

	//property infomation
	QLabel* lab5;
	QLabel* lab6;
	QLabel* lab7;
	QLabel* lab8;

	Ui::MainWindowClass ui;
};
