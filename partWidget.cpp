#include "PartWidget.h"

PartWidget::PartWidget(int w, int h, int r, QColor c, QWidget* parent)
	: QWidget(parent), Radius(r), color(c)
{
	this->setFixedSize(w, h);
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
}

PartWidget::~PartWidget()
{}

void PartWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;

	QPen pen1(QColor(0, 0, 0, 255));
	pen1.setWidth(2);
	painter.setPen(pen1);
	painter.setBrush(QBrush(color));
	QRect rect = this->rect();
	rect.setWidth(rect.width());
	rect.setHeight(rect.height());;
	painter.drawRoundedRect(rect, Radius, Radius);

	QPen pen2(QColor(100, 100, 100, 150));
	pen1.setWidth(1);
	painter.setPen(pen2);
	int h = this->height() / 4;
	painter.drawLine(QPoint(0, h), QPoint(this->width(), h));
	painter.drawLine(QPoint(0, h * 2), QPoint(this->width(), h * 2));
	painter.drawLine(QPoint(0, h * 3), QPoint(this->width(), h * 3));
}
