#include "MainWindow.h"


MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setFixedSize(1600, 960);
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);

	//close button
	closeBtn = new MyButton(":/image/resource/img/close.png", 40);
	closeBtn->setParent(this);
	closeBtn->move(1530, 30);
	connect(closeBtn, &MyButton::clicked, this, &MainWindow::close);

	//setting button
	settingBtn = new MyButton(":/image/resource/img/setting.png", 50);
	settingBtn->setParent(this);
	settingBtn->move(1490, 890);
	connect(settingBtn, &MyButton::clicked, this, &MainWindow::openMenu);

	//log button and Widget
	this->setLogDialog();

	//GitHub button and Widget
	this->setGitDialog();
	
	//display widget
	displayWidget = new DisplayWidget(1080, 720, 15, this);
	displayWidget->move(60, titleHeight);

	//title bar
	QString title_str = "BinTree VisualBuild";
	QFont title_font("Sitka Display", 32, 50, true);
	QLabel* title = new QLabel(title_str, this);
	title->setFont(title_font);
	title->resize(500, 70);
	title->move(60, 35);
	title->show();

	//menu widget (slide)
	menuWidget = new MenuWidget(500, 960, 25, this);
	menuWidget->move(-menuWidget->width(), 0);
	slideProperty = new QPropertyAnimation(menuWidget, "geometry");

	//close menuwidget button
	closeMenuBtn = new MyButton(":/image/resource/img/closeMenu.png", 40);
	closeMenuBtn->setParent(menuWidget);
	closeMenuBtn->move(30, 30);
	connect(closeMenuBtn, &MyButton::clicked, this, &MainWindow::openMenu);

	//property bar
	this->setPropertyWidget();
	connect(displayWidget->view(), &GraphicTreeView::itemChange, this, &MainWindow::update);

}

MainWindow::~MainWindow()
{
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		if (event->y() < titleHeight)	//只有标题栏可以拖动
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
	painter.setBrush(QBrush(QColor(250, 255, 250, 255)));
	QRect rect = this->rect();
	rect.setWidth(rect.width() - 1);
	rect.setHeight(rect.height() - 1);
	painter.drawRoundedRect(rect, Radius, Radius);
}

void MainWindow::setGitDialog()
{
	gitBtn = new MyButton(":/image/resource/img/github.png", 50);
	gitBtn->setParent(this);
	gitBtn->move(1430, 890);

	gitDialog = new MyDialog(540, 320, 20, this);
	gitDialog->setCloseBtn();
	connect(gitBtn, &MyButton::clicked, this, &MainWindow::openGitDialog);

	QLabel* lab1 = new QLabel(tr("<a href = https://github.com/Ayanami7/BinTreeGraphicsBuild><img src=:/image/resource/img/atri.png width =128 height=128></a>"), gitDialog);
	lab1->setGeometry(206, 50, 128, 128);
	//QPixmap pic(":/image/resource/img/github2.png");
	//lab1->setPixmap(pic.scaled(128,128));
	lab1->setOpenExternalLinks(true);

	QLabel* lab2 = new QLabel("<a style='color: black' href = https://github.com/Ayanami7/BinTreeGraphicsBuild>https://github.com/Ayanami7/BinTreeGraphicsBuild",gitDialog);
	QFont font1("Sitka Display", 12, 50, true);
	font1.setUnderline(true);
	lab2->setFont(font1);
	lab2->resize(440, 30);
	lab2->move(60, 220);
	lab2->setOpenExternalLinks(true);
}

void MainWindow::setLogDialog()
{
	logBtn = new MyButton(":/image/resource/img/more.png", 50);
	logBtn->setParent(this);
	logBtn->move(1370, 890);

	logDialog = new MyDialog(400, 800, 20, this);
	logDialog->setCloseBtn();
	connect(logBtn, &MyButton::clicked, this, &MainWindow::openLogDialog);

}

void MainWindow::setPropertyWidget()
{
	QFont font1("Sitka Display", 18, 50);
	QLabel* title = new QLabel("Property", this);
	title->setFont(font1);
	title->resize(120, 40);
	title->move(1160, 150);
	title->show();

	infoWidget = new PartWidget(420, 240, 10, QColor(QColor(250, 255, 250, 255)), this);
	infoWidget->move(1160, 200);

	QFont font2("微软雅黑", 12, 50);
	font2.setBold(true);

	QLabel* lab1 = new QLabel("vertex", infoWidget);
	lab1->setFont(font2);
	lab1->resize(240, 60);
	lab1->move(20, 0);
	QLabel* lab2 = new QLabel("edge", infoWidget);
	lab2->setFont(font2);
	lab2->resize(240, 60);
	lab2->move(20, 60);
	QLabel* lab3 = new QLabel("text3", infoWidget);
	lab3->setFont(font2);
	lab3->resize(240, 60);
	lab3->move(20, 120);
	QLabel* lab4 = new QLabel("text4", infoWidget);
	lab4->setFont(font2);
	lab4->resize(240, 60);
	lab4->move(20, 180);

	/* 需要添加实时刷新系统 */

	lab5 = new QLabel("1", infoWidget);
	lab5->setFont(font2);
	lab5->setAlignment(Qt::AlignRight | Qt::AlignVCenter);	//居中右对齐
	lab5->resize(140, 60);
	lab5->move(260, 0);

	lab6 = new QLabel("0", infoWidget);
	lab6->setFont(font2);
	lab6->setAlignment(Qt::AlignRight | Qt::AlignVCenter);	//居中右对齐
	lab6->resize(140, 60);
	lab6->move(260, 60);

	lab7 = new QLabel("data3", infoWidget);
	lab7->setFont(font2);
	lab7->setAlignment(Qt::AlignRight | Qt::AlignVCenter);	//居中右对齐
	lab7->resize(140, 60);
	lab7->move(260, 120);

	lab8 = new QLabel("data4", infoWidget);
	lab8->setFont(font2);
	lab8->setAlignment(Qt::AlignRight | Qt::AlignVCenter);	//居中右对齐
	lab8->resize(140, 60);
	lab8->move(260, 180);

}

void MainWindow::update()
{
	QString vexes_str = QString::asprintf("%d", this->displayWidget->view()->vexList.size());
	QString edges_str = QString::asprintf("%d", this->displayWidget->view()->lineList.size());
	this->lab5->setText(vexes_str);
	this->lab6->setText(edges_str);
}

//signal slots
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

void MainWindow::openGitDialog()
{
	gitDialog->exec();
}

void MainWindow::openLogDialog()
{
	logDialog->show();
}

