#include "GraphicTree.h"

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

	/* test data */
	GraphicTreeVertex* vex1 = new GraphicTreeVertex(QPoint(50, 50), 20, 0);
	GraphicTreeVertex* vex2 = new GraphicTreeVertex(QPoint(200, 200), 20, 1);
	this->myScene->addItem(vex1);
	this->myScene->addItem(vex2);
	GraphicTreeLine* line1 = new GraphicTreeLine(vex1, vex2);
	this->myScene->addItem(line1);

}

GraphicTreeVertex* GraphicTreeView::addVex(QPointF center, qreal radius)
{
	return nullptr;
}

GraphicTreeLine* GraphicTreeView::addLine(GraphicTreeVertex* start, GraphicTreeVertex* end)
{
	return nullptr;
}

void GraphicTreeView::mousePressEvent(QMouseEvent* event)
{

}

void GraphicTreeView::mouseMoveEvent(QMouseEvent* event)
{

}

GraphicTreeVertex::GraphicTreeVertex(QPointF point, qreal r, int nameID, QGraphicsItem* parent)
	:QGraphicsEllipseItem(point.x() - r / 2, point.y() - r / 2, 2 * r, 2 * r, parent),
	center(point),
	radius(r)
{
	nameText = QString::asprintf("V%d", nameID);
	nameTag = new QGraphicsSimpleTextItem();
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

GraphicTreeLine::GraphicTreeLine(GraphicTreeVertex* start, GraphicTreeVertex* end, QGraphicsItem* parent)
	:startVex(start), endVex(end), QGraphicsLineItem(parent)
{
	defaultPen.setColor(this->defaultColor);
	defaultPen.setWidth(this->linewidth);
	defaultPen.setStyle(this->lineStyle);
	defaultPen.setCapStyle(this->lineCapStyle);
	this->setPen(defaultPen);
	this->setLine(startVex->center.rx(), startVex->center.ry(), endVex->center.rx(), endVex->center.ry());
	this->setZValue(-2);
}
