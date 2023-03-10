#pragma once

#include <QWidget>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "GraphicTree.h"


class DisplayWidget : public QWidget
{
	Q_OBJECT

public:
	DisplayWidget(int w, int h, int r, QWidget* parent = nullptr);
	~DisplayWidget();

	virtual void paintEvent(QPaintEvent* event);

	GraphicTreeView* view();

private:
	int Radius;
	GraphicTreeView* myView = nullptr;

};
