#include "MyDialog.h"

MyDialog::MyDialog(int w, int h, int r, QWidget* parent)
	: QDialog(parent), Radius(r)
{
	this->setFixedSize(w, h);
	setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
	setAttribute(Qt::WA_TranslucentBackground);
}

MyDialog::~MyDialog()
{
	delete closeBtn;
}

void MyDialog::mousePressEvent(QMouseEvent* event)
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
	}
}

void MyDialog::mouseMoveEvent(QMouseEvent* event)
{
	if (m_pressed)
	{
		this->move(this->x() + (event->globalX() - m_lastpos.x()),
			this->y() + (event->globalY() - m_lastpos.y()));
		m_lastpos = event->globalPos();
	}
}

void MyDialog::mouseReleaseEvent(QMouseEvent* event)
{
	Q_UNUSED(event);
	m_pressed = false;
}

void MyDialog::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;

	QPen pen1(QColor(0, 0, 0, 255));
	pen1.setWidth(2);
	painter.setPen(pen1);
	painter.setBrush(QBrush(QColor(250, 255, 250, 255)));
	QRect rect = this->rect();
	rect.setWidth(rect.width() - 1);
	rect.setHeight(rect.height() - 1);;
	painter.drawRoundedRect(rect, Radius, Radius);
}

void MyDialog::setCloseBtn() 
{
	closeBtn = new MyButton(":/image/resource/img/close.png", 30);
	closeBtn->setParent(this);
	closeBtn->move(this->width() - 30 - 15, 15);
	connect(closeBtn, &MyButton::clicked, this, &MyDialog::close);
}
