#pragma once

#include <QWidget>
#include <QPainter>

class MenuWidget : public QWidget
{
	Q_OBJECT

public:
	MenuWidget(int w, int h, int r, QWidget* parent = nullptr);
	~MenuWidget();

	virtual void paintEvent(QPaintEvent* event);

private:
	int Radius;

};
