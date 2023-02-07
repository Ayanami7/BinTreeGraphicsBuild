#include "MainWindow.h"


MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setFixedSize(1440, 900);
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);

	//设置按钮
	settingBtn = new MyButton(":/image/resource/img/setting.png", 40);
	settingBtn->setParent(this);
	settingBtn->move(1370, 830);

	//关闭按钮
	closeBtn = new MyButton(":/image/resource/img/close.png", 40);
	closeBtn->setParent(this);
	closeBtn->move(1370, 30);
	connect(closeBtn, &MyButton::clicked, this, &MainWindow::close);

	//显示窗口
	displayWidget = new DisplayWidget(900, 720, 15, this);
	displayWidget->move(90, 90);

	//展示菜单按钮
	openMenuBtn = new MyButton(":/image/resource/img/openMenu.png", 40);
	openMenuBtn->setParent(this);
	openMenuBtn->move(30, 30);
	connect(openMenuBtn, &MyButton::clicked, this, &MainWindow::openMenu);

	//菜单窗口
	menuWidget = new MenuWidget(500, 900, 25, this);
	menuWidget->move(-menuWidget->width(), 0);
	slideProperty = new QPropertyAnimation(menuWidget, "geometry");

	//关闭菜单按钮
	closeMenuBtn = new MyButton(":/image/resource/img/closeMenu.png", 40);
	closeMenuBtn->setParent(menuWidget);
	closeMenuBtn->move(30, 30);
	connect(closeMenuBtn, &MyButton::clicked, this, &MainWindow::openMenu);

}

MainWindow::~MainWindow()
{
	delete closeBtn;
	delete openMenuBtn;
	delete settingBtn;
	delete displayWidget;
	delete menuWidget;
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		if (event->y() < 90)	//只有标题栏可以拖动
		{
			m_lastpos = event->globalPos();
			m_pressed = true;
		}
		else
		{
			m_lastpos = event->globalPos();
			m_pressed = false;
		}
		/*Debug Code*/
		//QString str = QString("Press x:%1 y:%2").arg(event->globalX()).arg(event->globalY());
		//qDebug() << str;
	}
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{

	if (m_pressed)
	{
		this->move(this->x() + (event->globalX() - m_lastpos.x()),
			this->y() + (event->globalY() - m_lastpos.y()));
		m_lastpos = event->globalPos();

		/*Debug Code*/
		//QString str = QString("Move x:%1 y:%2").arg(event->globalX()).arg(event->globalY());
		//qDebug() << str;
	}
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
	Q_UNUSED(event);
	m_pressed = false;

	/*Debug Code*/
	//QString str = QString("Release x:%1 y:%2").arg(event->globalX()).arg(event->globalY());
	//qDebug() << str;
}

void MainWindow::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;

	QPen pen1(QColor(100, 100, 100, 100));
	pen1.setWidth(4);
	painter.setPen(pen1);
	painter.setBrush(QBrush(Qt::white));
	QRect rect = this->rect();
	rect.setWidth(rect.width() - 1);
	rect.setHeight(rect.height() - 1);
	painter.drawRoundedRect(rect, Radius, Radius);
}

void MainWindow::openMenu()
{
	if (m_menu_hidden)
	{
		slideProperty->setStartValue(QRect(-this->rect().width(), 0, menuWidget->width(), menuWidget->height()));
		slideProperty->setEndValue(QRect(0, 0, menuWidget->width(), menuWidget->height()));
		slideProperty->setDuration(600);
		slideProperty->start();
		m_menu_hidden = !m_menu_hidden;
	}
	else
	{
		slideProperty->setStartValue(QRect(0, 0, menuWidget->width(), menuWidget->height()));
		slideProperty->setEndValue(QRect(-this->rect().width(), 0, menuWidget->width(), menuWidget->height()));
		slideProperty->setDuration(600);
		slideProperty->start();

		m_menu_hidden = !m_menu_hidden;
	}
}
