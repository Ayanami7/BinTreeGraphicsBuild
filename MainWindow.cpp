#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
}

MainWindow::~MainWindow()
{}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_lastpos = event->globalPos();
		m_pressed = true;
		QString str = QString("Press x:%1 y:%2").arg(event->globalX()).arg(event->globalY());
		qDebug() << str;
	}
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{

	if (m_pressed)
	{
		this->move(this->x() + (event->globalX() - m_lastpos.x()),
			this->y() + (event->globalY() - m_lastpos.y()));
		QString str = QString("Move x:%1 y:%2").arg(event->globalX()).arg(event->globalY());
		qDebug() << str;
		m_lastpos = event->globalPos();
	}
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
	Q_UNUSED(event);
	m_pressed = false;
	QString str = QString("Release x:%1 y:%2").arg(event->globalX()).arg(event->globalY());
	qDebug() << str;
}

void MainWindow::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);  // ·´¾â³Ý;
	painter.setBrush(QBrush(Qt::white));
	painter.setPen(Qt::transparent);
	QRect rect = this->rect();
	rect.setWidth(rect.width() - 1);
	rect.setHeight(rect.height() - 1);
	painter.drawRoundedRect(rect, 25, 25);
	QWidget::paintEvent(event);
}

void MainWindow::on_closeButton_clicked()
{
	this->close();
}
