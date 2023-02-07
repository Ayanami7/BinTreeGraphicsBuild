#pragma once

#include <QDialog>
#include <QPainter>
#include <QMouseEvent>
#include <QWidget>

class PartWidget  : public QWidget
{
	Q_OBJECT

public:
	PartWidget(int w, int h, int r, QColor c, QWidget* parent = nullptr);
	virtual ~PartWidget();

	virtual void paintEvent(QPaintEvent* event);

private:
	int Radius;
	QColor color;
};
