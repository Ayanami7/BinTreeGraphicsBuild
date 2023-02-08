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

	//GitHub button and Widget
	gitBtn = new MyButton(":/image/resource/img/github.png", 50);
	gitBtn->setParent(this);
	gitBtn->move(1430, 890);

	gitDialog = new MyDialog(400, 300, 20, false);
	gitDialog->setCloseBtn();
	connect(gitBtn, &MyButton::clicked, this, &MainWindow::openGitDialog);
	
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
	QFont font1("Sitka Display", 18, 50);
	QLabel* lab1 = new QLabel("Property", this);
	lab1->setFont(font1);
	lab1->resize(120, 40);
	lab1->move(1190, 150);
	lab1->show();

	QLabel* lab2 = new QLabel("Log", this);
	lab2->setFont(font1);
	lab2->resize(120, 40);
	lab2->move(1190, 150);
	lab2->show();

	infoWidget = new PartWidget(360, 240, 20, QColor(Qt::white), this);
	infoWidget->move(1190, 220);

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

