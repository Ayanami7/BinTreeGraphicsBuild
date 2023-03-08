#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>

#include <QTimeLine>

class GraphicTreeView;
class GraphicTreeVertex;
class GraphicTreeLine;

//自定义场景类
class GraphicTreeView : public QGraphicsView
{
	Q_OBJECT

private:
	QGraphicsScene* myScene;	//场景对象
	QBrush regBrush = QBrush(QColor(108, 166, 205));

	/* For creating a binary tree */
	int VexID = 0;
	bool isCreating = false;

	GraphicTreeVertex* addVex(QPointF center, qreal radius = 10);
	GraphicTreeLine* addLine(GraphicTreeVertex* start, GraphicTreeVertex* end);

	void mousePressEvent(QMouseEvent* event);		//重写鼠标事件
	void mouseMoveEvent(QMouseEvent* event);

	QVector<GraphicTreeVertex*> vexList;
	QVector<GraphicTreeLine*> lineList;

public:
	GraphicTreeView();
};

//自定义顶点类
class GraphicTreeVertex : public QObject, public QGraphicsEllipseItem
{
	Q_OBJECT

private:
	QBrush regBrush = QBrush(QColor(108, 166, 205));
	QBrush visitedBrush = QBrush(QColor(162, 205, 90));
	QFont nameFont = QFont("Sitka Display", 13, QFont::Normal, true);

public:
	QPointF center;
	qreal radius;
	
	/* display text*/
	QGraphicsSimpleTextItem* nameTag = nullptr;
	QString nameText = "";
	void setName(QString s);	

	/* tree structure */
	QVector<GraphicTreeVertex*> nexts;
	GraphicTreeVertex* left = nullptr;
	GraphicTreeVertex* right = nullptr;

	GraphicTreeVertex(QPointF point, qreal r, int nameID, QGraphicsItem* parent = nullptr);
	~GraphicTreeVertex();
};

//自定义连接线类
class GraphicTreeLine : public QObject, public QGraphicsLineItem
{
	Q_OBJECT
private:
	qreal linewidth = 3;
	Qt::PenStyle lineStyle = Qt::SolidLine;
	Qt::PenCapStyle lineCapStyle = Qt::RoundCap;	//画笔端点风格
	//QColor defaultColor = QColor(159, 182, 205);
	QColor defaultColor = QColor(84, 255, 159);

	QPen defaultPen;

	GraphicTreeVertex* startVex;
	GraphicTreeVertex* endVex;

public:
	GraphicTreeLine(GraphicTreeVertex* start, GraphicTreeVertex* end, QGraphicsItem* parent = nullptr);
};
