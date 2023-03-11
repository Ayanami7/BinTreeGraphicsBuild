#include "MainWindow.h"


MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setFixedSize(1600, 960);
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);

	//窗口居中
	QDesktopWidget* desk = QApplication::desktop();
	int wd = desk->width();
	int ht = desk->height();
	this->move((wd - width()) / 2, (ht - height()) / 2);

	//close button
	MyButton* closeBtn = new MyButton(":/image/resource/img/close.png", 40);
	closeBtn->setParent(this);
	closeBtn->move(1530, 30);
	connect(closeBtn, &MyButton::clicked, this, &MainWindow::close);

	//setting button
	MyButton* settingBtn = new MyButton(":/image/resource/img/setting.png", 50);
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
	MyButton* closeMenuBtn = new MyButton(":/image/resource/img/closeMenu.png", 40);
	closeMenuBtn->setParent(menuWidget);
	closeMenuBtn->move(30, 30);
	connect(closeMenuBtn, &MyButton::clicked, this, &MainWindow::openMenu);

	//property bar
	this->setPropertyWidget();
	connect(displayWidget->view(), &GraphicTreeView::itemChange, this, &MainWindow::updateUpHalf);
	connect(displayWidget->view(), &GraphicTreeView::vexChange, this, &MainWindow::updateDownHalf);

	QFont font1("Sitka Display", 20, 50, true);

	traverBtn1 = new QPushButton();
	traverBtn1->setText("pred");
	traverBtn1->setParent(this);
	traverBtn1->setFont(font1);
	traverBtn1->setStyleSheet("QPushButton{background-color: rgb(121,205,205,90); border-radius: 15px;}"
		"QPushButton:hover{background-color: rgb(119,136,153,150);}");
	traverBtn1->resize(180, 60);
	traverBtn1->move(1170, 500);
	connect(traverBtn1, &QPushButton::clicked, this, [=]() {this->displayWidget->view()->Type() = 1; });
	connect(traverBtn1, &QPushButton::clicked, this, &MainWindow::changeType);

	traverBtn2 = new QPushButton();
	traverBtn2->setText("in");
	traverBtn2->setParent(this);
	traverBtn2->setFont(font1);
	traverBtn2->setStyleSheet("QPushButton{background-color: rgb(121,205,205,90); border-radius: 15px;}"
		"QPushButton:hover{background-color: rgb(119,136,153,150);}");
	traverBtn2->resize(180, 60);
	traverBtn2->move(1380, 500);
	connect(traverBtn2, &QPushButton::clicked, this, [=]() {this->displayWidget->view()->Type() = 2; });
	connect(traverBtn2, &QPushButton::clicked, this, &MainWindow::changeType);

	traverBtn3= new QPushButton();
	traverBtn3->setText("succ");
	traverBtn3->setParent(this);
	traverBtn3->setFont(font1);
	traverBtn3->setStyleSheet("QPushButton{background-color: rgb(121,205,205,90); border-radius: 15px;}"
		"QPushButton:hover{background-color: rgb(119,136,153,150);}");
	traverBtn3->resize(180, 60);
	traverBtn3->move(1170, 580);
	connect(traverBtn3, &QPushButton::clicked, this, [=]() {this->displayWidget->view()->Type() = 3; });
	connect(traverBtn3, &QPushButton::clicked, this, &MainWindow::changeType);

	traverBtn4 = new QPushButton();
	traverBtn4->setText("order");
	traverBtn4->setParent(this);
	traverBtn4->setFont(font1);
	traverBtn4->setStyleSheet("QPushButton{background-color: rgb(121,205,205,90); border-radius: 15px;}"
		"QPushButton:hover{background-color: rgb(119,136,153,150);}");
	traverBtn4->resize(180, 60);
	traverBtn4->move(1380, 580);
	connect(traverBtn4, &QPushButton::clicked, this, [=]() {this->displayWidget->view()->Type() = 4; });
	connect(traverBtn4, &QPushButton::clicked, this, &MainWindow::changeType);

	//构建时改变按钮状态S
	connect(this->displayWidget->view(), &GraphicTreeView::build, this, &MainWindow::changeType);

	//switch button
	MyButton* switchBtn = new MyButton(":/image/resource/img/switch.png", 80);
	switchBtn->setParent(this);
	switchBtn->move(1210, 720);
	connect(switchBtn, &MyButton::clicked, displayWidget->view(), &GraphicTreeView::reset);

	//start button
	MyButton* startBtn = new MyButton(":/image/resource/img/start.png", 80);
	startBtn->setParent(this);
	startBtn->move(1330, 720);
	connect(startBtn, &MyButton::clicked, displayWidget->view(), &GraphicTreeView::startTraversal);

	//delete button
	MyButton* deleteBtn = new MyButton(":/image/resource/img/delete.png", 80);
	deleteBtn->setParent(this);
	deleteBtn->move(1450, 720);
	connect(deleteBtn,&MyButton::clicked, this, &MainWindow::resetType);
	connect(deleteBtn, &MyButton::clicked, displayWidget->view(), &GraphicTreeView::deleteAll);


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
	MyButton* gitBtn = new MyButton(":/image/resource/img/github.png", 50);
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
	MyButton* logBtn = new MyButton(":/image/resource/img/more.png", 50);
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

	QLabel* lab1 = new QLabel("total vertexes", infoWidget);
	lab1->setFont(font2);
	lab1->resize(240, 60);
	lab1->move(20, 0);
	QLabel* lab2 = new QLabel("total edges", infoWidget);
	lab2->setFont(font2);
	lab2->resize(240, 60);
	lab2->move(20, 60);
	QLabel* lab3 = new QLabel("current depth", infoWidget);
	lab3->setFont(font2);
	lab3->resize(240, 60);
	lab3->move(20, 120);
	QLabel* lab4 = new QLabel("current ID", infoWidget);
	lab4->setFont(font2);
	lab4->resize(240, 60);
	lab4->move(20, 180);

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

	lab7 = new QLabel("0", infoWidget);
	lab7->setFont(font2);
	lab7->setAlignment(Qt::AlignRight | Qt::AlignVCenter);	//居中右对齐
	lab7->resize(140, 60);
	lab7->move(260, 120);

	lab8 = new QLabel("nullptr", infoWidget);
	lab8->setFont(font2);
	lab8->setAlignment(Qt::AlignRight | Qt::AlignVCenter);	//居中右对齐
	lab8->resize(140, 60);
	lab8->move(260, 180);

}

void MainWindow::updateUpHalf()
{
	QString vexes_str = QString::number(this->displayWidget->view()->vexSize());
	QString edges_str = QString::number(this->displayWidget->view()->lineSize());
	this->lab5->setText(vexes_str);
	this->lab6->setText(edges_str);
}

void MainWindow::updateDownHalf(GraphicTreeVertex* vex, int depth)
{
	QString depth_str = QString::number(depth);
	this->lab7->setText(depth_str);
	if (vex != nullptr)
		this->lab8->setText(vex->nameText);
	else
		this->lab8->setText("nullptr");
}


void MainWindow::changeType()
{
	if (this->displayWidget->view()->Type() == 1)
	{
		resetType();
		traverBtn1->setStyleSheet("QPushButton{background-color: rgb(119,136,153,150); border-radius: 15px;}"
			"QPushButton:hover{background-color: rgb(121,205,205,90);}");
	}
	else if (this->displayWidget->view()->Type() == 2)
	{
		resetType();
		traverBtn2->setStyleSheet("QPushButton{background-color: rgb(119,136,153,150); border-radius: 15px;}"
			"QPushButton:hover{background-color: rgb(121,205,205,90);}");
	}

	else if (this->displayWidget->view()->Type() == 3)
	{
		resetType();
		traverBtn3->setStyleSheet("QPushButton{background-color: rgb(119,136,153,150); border-radius: 15px;}"
			"QPushButton:hover{background-color: rgb(121,205,205,90);}");
	}

	else if (this->displayWidget->view()->Type() == 4)
	{
		resetType();
		traverBtn4->setStyleSheet("QPushButton{background-color: rgb(119,136,153,150); border-radius: 15px;}"
			"QPushButton:hover{background-color: rgb(121,205,205,90);}");
	}
	else
	{
		traverBtn1->setStyleSheet("QPushButton{background-color: rgb(119,136,153,150); border-radius: 15px;}"
			"QPushButton:hover{background-color: rgb(121,205,205,90);}");
	}
}

void MainWindow::resetType()
{
	traverBtn1->setStyleSheet("QPushButton{background-color: rgb(121,205,205,90); border-radius: 15px;}"
		"QPushButton:hover{background-color: rgb(119,136,153,150);}");
	traverBtn2->setStyleSheet("QPushButton{background-color: rgb(121,205,205,90); border-radius: 15px;}"
		"QPushButton:hover{background-color: rgb(119,136,153,150);}");
	traverBtn3->setStyleSheet("QPushButton{background-color: rgb(121,205,205,90); border-radius: 15px;}"
		"QPushButton:hover{background-color: rgb(119,136,153,150);}");
	traverBtn4->setStyleSheet("QPushButton{background-color: rgb(121,205,205,90); border-radius: 15px;}"
		"QPushButton:hover{background-color: rgb(119,136,153,150);}");
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

