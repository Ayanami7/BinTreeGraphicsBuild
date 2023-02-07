#pragma once

#include <QWidget>
#include <QPainter>

class DisplayWidget : public QWidget
{
	Q_OBJECT

public:
	DisplayWidget(int w, int h, int r, QWidget* parent = nullptr);
	~DisplayWidget();

	virtual void paintEvent(QPaintEvent* event);

private:
	int Radius;
};
