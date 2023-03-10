#include "GraphicTree.h"
#include <qdebug.h>

/* function of class GraphicTreeView */
GraphicTreeView::GraphicTreeView()
{
	//初始化场景及视图
	this->myScene = new QGraphicsScene;
	this->setScene(this->myScene);

	//尺寸及外观设定
	this->myScene->setSceneRect(0, 0, 1080 - 30, 720 - 30);
	this->setFixedSize(1050, 690);
	this->move(15, 15);

	this->setMouseTracking(true);
	this->setRenderHint(QPainter::Antialiasing);
	this->setStyleSheet("padding:0px;border:0px");	//去除边框线

	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);	//关闭竖向滚轮
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);	//关闭横向滚轮

	root = addVex(QPoint(525, 120));
	strtVex = root;
	
}

GraphicTreeVertex* GraphicTreeView::addVex(QPointF center, qreal radius)
{
	GraphicTreeVertex* vex = new GraphicTreeVertex(center, radius, VexID++);
	this->myScene->addItem(vex);
	vexList.push_back(vex);
	return vex;
}

GraphicTreeLine* GraphicTreeView::addLine(GraphicTreeVertex* start, GraphicTreeVertex* end)
{
	GraphicTreeLine* line = new GraphicTreeLine(start, end);
	this->myScene->addItem(line);
	lineList.push_back(line);
	return line;
}

void GraphicTreeView::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		if (isCreating)
		{
			//位置检测
			if (event->pos().y() - 15 < strtVex->center.y())
			{
				clearSketchLine();
				isCreating = !isCreating;
				return;
			}

			//碰撞检测
			for (int i = 0; i < vexList.size(); i++)
			{
				if (inVertex(event->pos(), vexList[i]))
				{
					clearSketchLine();
					isCreating = !isCreating;
					return;
				}
			}

			clearSketchLine();
			GraphicTreeVertex* endVex = addVex(event->pos());
			endVex->showAnimation();
			addLine(strtVex, endVex);
			emit itemChange();
			if (endVex->center.x() <= strtVex->center.x())
				strtVex->left = endVex;
			else
				strtVex->right = endVex;
			isCreating = !isCreating;
		}
		else
		{
			bool flag = false;
			for (int i = 0; i < vexList.size(); i++)
			{
				if (inVertex(event->pos(), vexList[i]) && hasVacancy(vexList[i]))
				{
					flag = true;
					strtVex = vexList[i];
				}
			}
			if (flag) {
				isCreating = !isCreating;
			}
		}
	}
}

void GraphicTreeView::mouseMoveEvent(QMouseEvent* event)
{
	if (isCreating) {
		clearSketchLine();
		drawSketchLine(strtVex->pos() + strtVex->rect().center(), event->pos());
	}
}

bool GraphicTreeView::hasVacancy(GraphicTreeVertex* vex)
{
	if (vex->left == nullptr || vex->right == nullptr)
		return true;
	return false;
}

bool GraphicTreeView::inVertex(QPoint pos, GraphicTreeVertex* vex)
{
	if (pos.x() >= vex->center.x() - vex->radius && pos.x() <= vex->center.x() + vex->radius &&
		pos.y() >= vex->center.y() - vex->radius && pos.y() <= vex->center.y() + vex->radius)
		return true;
	else
		return false;
}

void GraphicTreeView::drawSketchLine(QPointF start, QPointF end)
{
	QGraphicsLineItem* newLine = new QGraphicsLineItem(start.x(), start.y(), end.x(), end.y());
	QPen pen;
	pen.setWidth(3);
	pen.setStyle(Qt::DashLine);
	pen.setBrush(QColor(58, 143, 192, 100));
	pen.setCapStyle(Qt::RoundCap);
	newLine->setPen(pen);
	scene()->addItem(newLine);
	sketchItem = newLine;
}

void GraphicTreeView::clearSketchLine()
{
	if (sketchItem != nullptr)
	{
		this->myScene->removeItem(sketchItem);	//删除虚线并置空
		sketchItem = nullptr;				
	}
}

void GraphicTreeView::predTraversal(GraphicTreeVertex* vex)
{
	if (vex == nullptr)
		return;
	qDebug() << vex->nameText;
	predTraversal(vex->left);
	predTraversal(vex->right);
}

void GraphicTreeView::inTraversal(GraphicTreeVertex* vex)
{
	if (vex == nullptr)
		return;
	inTraversal(vex->left);
	qDebug() << vex->nameText;
	inTraversal(vex->right);
}

void GraphicTreeView::succTraversal(GraphicTreeVertex* vex)
{
	if (vex == nullptr)
		return;
	succTraversal(vex->left);
	succTraversal(vex->right);
	qDebug() << vex->nameText;
}

void GraphicTreeView::orderTraversal(GraphicTreeVertex* vex)
{

}

void GraphicTreeView::startTraversal()
{
	emit build();					//通知系统开始构建二叉树
	if (traversalType == 1 || 0)	//若不选择则默认为先序
		predTraversal(root);
	else if (traversalType == 2)
		inTraversal(root);
	else if (traversalType == 3)
		succTraversal(root);
	else if (traversalType == 4)
		orderTraversal(root);
}


/* function of class GraphicTreeVertex */
GraphicTreeVertex::GraphicTreeVertex(QPointF point, qreal r, int nameID, QGraphicsItem* parent)
	:QGraphicsEllipseItem(point.x() - r, point.y() - r, 2 * r, 2 * r, parent),
	center(point),
	radius(r)
{
	nameText = QString::asprintf("V%d", nameID);
	nameTag = new QGraphicsSimpleTextItem(this);
	nameTag->setPos(center + QPointF(radius, -radius - QFontMetrics(nameFont).height()));
	nameTag->setFont(nameFont);
	nameTag->setText(nameText);
	nameTag->setZValue(this->zValue());
	nameTag->setBrush(Qt::black);
	nameTag->setFlags(QGraphicsItem::ItemIsSelectable);
	this->setPen(Qt::NoPen);
	this->setBrush(regBrush);
}

GraphicTreeVertex::~GraphicTreeVertex()
{

}

void GraphicTreeVertex::showAnimation()
{
	QTimeLine* timeLine = new QTimeLine(800, this);		//800ms
	timeLine->setFrameRange(0, 100);					//100帧
	QEasingCurve curve = QEasingCurve::OutBounce;
	qreal difRadius = 6;								//变化大小为5
	connect(timeLine, &QTimeLine::frameChanged, timeLine, [=](int frame) {
		qreal curProgress = curve.valueForProgress(frame / 100.0);
		qreal curRadius = radius + difRadius - difRadius * curProgress;
		this->setRect(QRectF(center.x() - curRadius, center.y() - curRadius, curRadius * 2, curRadius * 2));
		});
	curAnimation = timeLine;
	startAnimation();
}

void GraphicTreeVertex::startAnimation() 
{
	if (curAnimation != nullptr) 
		curAnimation->start();      
}

GraphicTreeLine::GraphicTreeLine(GraphicTreeVertex* start, GraphicTreeVertex* end, QGraphicsItem* parent)
	:startVex(start), endVex(end), QGraphicsLineItem(parent)
{
	defaultPen.setColor(this->defaultColor);
	defaultPen.setWidth(this->linewidth);
	defaultPen.setStyle(this->lineStyle);
	defaultPen.setCapStyle(this->lineCapStyle);
	this->setPen(defaultPen);
	this->setLine(startVex->center.x(), startVex->center.y(), endVex->center.x(), endVex->center.y());
	this->setZValue(-2);
}
