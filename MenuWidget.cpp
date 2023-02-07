#include "MenuWidget.h"

MenuWidget::MenuWidget(int w, int h, int r, QWidget* parent)
	: QWidget(parent), Radius(r)
{
	setFixedSize(w, h);
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
}

MenuWidget::~MenuWidget()
{}

void MenuWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;

	QPen pen1(QColor(100, 100, 100, 190));
	pen1.setWidth(3);
	painter.setPen(pen1);
	painter.setBrush(QBrush(QColor(250, 255, 250, 255)));
	QRect rect = this->rect();
	rect.setWidth(rect.width() - 1);
	rect.setHeight(rect.height() - 1);
	painter.drawRoundedRect(rect, Radius, Radius);

}
