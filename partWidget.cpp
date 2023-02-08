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
}
