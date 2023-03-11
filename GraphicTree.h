#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsSimpleTextItem>
#include <QMouseEvent>

#include <QQueue>
#include <QTimer>
#include <QTimeLine>

class GraphicTreeView;
class GraphicTreeVertex;
class GraphicTreeLine;

//自定义场景类
class GraphicTreeView : public QGraphicsView
{
	Q_OBJECT
	friend class MainWindow;
private:
	QGraphicsScene* myScene;	//场景对象
	QBrush regBrush = QBrush(QColor(108, 166, 205));

	bool isbuild = false;

	/* For creating a binary tree */
	int traversalType = 0;
	int VexID = 0;
	bool isCreating = false;
	GraphicTreeVertex* root = nullptr;
	GraphicTreeVertex* strtVex = nullptr;		//上一个顶点
	QGraphicsItem* sketchItem = nullptr;		//虚线

	GraphicTreeVertex* addVex(QPointF center, qreal radius = 15);
	GraphicTreeLine* addLine(GraphicTreeVertex* start, GraphicTreeVertex* end);

	void mousePressEvent(QMouseEvent* event);		//重写鼠标事件
	void mouseMoveEvent(QMouseEvent* event);

	bool hasVacancy(GraphicTreeVertex* vex);			//判断是否有空位
	bool inVertex(QPoint pos, GraphicTreeVertex* vex);			//判断是否位于顶点内
	void drawSketchLine(QPointF start, QPointF end);	//绘制虚线
	void clearSketchLine();							//擦除虚线
	void predTraversal(GraphicTreeVertex* vex, int depth);		//前序遍历
	void inTraversal(GraphicTreeVertex* vex, int depth);		//中序遍历
	void succTraversal(GraphicTreeVertex* vex, int depth);		//后序遍历
	void orderTraversal(GraphicTreeVertex* vex);	//层次遍历
	void playAnimation();							//播放动画

	QQueue<QTimeLine*> animeQueue;			//依次执行动画队列
	QQueue<GraphicTreeVertex*> vexQueue;	//顶点队列
	QQueue<int> depthQueue;					//深度队列
	QVector<GraphicTreeVertex*> resList;	//结果序列

	QVector<GraphicTreeVertex*> vexList;	//总结点列表
	QVector<GraphicTreeLine*> lineList;		//总边列表

	GraphicTreeVertex* currentVex;			//当前节点

signals:
	void itemChange();					//节点添加
	void build();						//开始构建
	void vexChange(GraphicTreeVertex* vex, int depth);	//节点被访问


public slots:
	void startTraversal();
	void reset();
	void deleteAll();

public:

	GraphicTreeView();
	const int vexSize() { return vexList.size(); }
	const int lineSize() { return lineList.size(); }
	int& Type() { return traversalType; }
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

	QTimeLine* visit();			//访问并创建时间线动画

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
	QColor defaultColor = QColor(0,238,238);

	QPen defaultPen;

	GraphicTreeVertex* startVex;
	GraphicTreeVertex* endVex;

public:
	GraphicTreeLine(GraphicTreeVertex* start, GraphicTreeVertex* end, QGraphicsItem* parent = nullptr);
};
