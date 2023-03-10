#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsSimpleTextItem>
#include <QMouseEvent>

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
	GraphicTreeVertex* root = nullptr;
	GraphicTreeVertex* strtVex = nullptr;
	QGraphicsItem* sketchItem = nullptr;

	GraphicTreeVertex* addVex(QPointF center, qreal radius = 15);
	GraphicTreeLine* addLine(GraphicTreeVertex* start, GraphicTreeVertex* end);

	void mousePressEvent(QMouseEvent* event);		//重写鼠标事件
	void mouseMoveEvent(QMouseEvent* event);

	bool hasVacancy(GraphicTreeVertex* vex);			//判断是否有空位
	bool inVertex(QPoint pos, GraphicTreeVertex* vex);			//判断是否位于顶点内
	void drawSketchLine(QPointF start, QPointF end);	//绘制虚线
	void clearSketchLine();							//擦除虚线

signals:
	void itemChange();

public:
	/* 测试用 暂时未封装 */
	QVector<GraphicTreeVertex*> vexList;	//总结点列表
	QVector<GraphicTreeLine*> lineList;		//总边列表

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

	/* for Animation */
	QTimeLine* curAnimation = nullptr;
	void startAnimation();

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

	void showAnimation();		//显示动画

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
