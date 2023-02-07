#include "DisplayWidget.h"

DisplayWidget::DisplayWidget(int w, int h, int r, QWidget* parent)
	: QWidget(parent), Radius(r)
{
	setFixedSize(w, h);
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
}

DisplayWidget::~DisplayWidget()
{}

void DisplayWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	QPen pen1(QColor(0, 0, 0, 255));
	QRect rect = this->rect();
	pen1.setWidth(2);
	painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
	painter.setBrush(QBrush(QColor(235, 235, 235, 255)));
	painter.setPen(pen1);
	rect.setWidth(rect.width());
	rect.setHeight(rect.height());
	painter.drawRoundedRect(rect, Radius, Radius);
}
