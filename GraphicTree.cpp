#include "GraphicTree.h"
#include <qdebug.h>
#include <windows.h>

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
			if (strtVex->left == nullptr)
				strtVex->left = endVex;
			else
				strtVex->right = endVex;
			
			/* 检查左右子节点 */
			if (!hasVacancy(strtVex))
			{
				if (strtVex->left->center.x() > strtVex->right->center.x())
				{
					std::swap(strtVex->left, strtVex->right);
				}
			}
			else if (strtVex->left == nullptr && strtVex->right != nullptr)
			{
				if (strtVex->right->center.x() < strtVex->center.x())
				{
					std::swap(strtVex->left, strtVex->right);
				}
			}
			else if (strtVex->left != nullptr && strtVex->right == nullptr)
			{
				if (strtVex->left->center.x() > strtVex->center.x())
				{
					std::swap(strtVex->left, strtVex->right);
				}
			}
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

void GraphicTreeView::predTraversal(GraphicTreeVertex* vex, int depth)
{
	if (vex == nullptr)
		return;
	/* process the current node */
	animeQueue.push_back(vex->visit());
	vexQueue.push_back(vex);
	depthQueue.push_back(depth);
	resList.push_back(vex);
	/* End */
	predTraversal(vex->left, depth + 1);
	predTraversal(vex->right, depth + 1);
}

void GraphicTreeView::inTraversal(GraphicTreeVertex* vex, int depth)
{
	if (vex == nullptr)
		return;
	inTraversal(vex->left, depth + 1);
	/* process the current node */
	animeQueue.push_back(vex->visit());
	vexQueue.push_back(vex);
	depthQueue.push_back(depth);
	resList.push_back(vex);
	/* End */
	inTraversal(vex->right, depth + 1);
}

void GraphicTreeView::succTraversal(GraphicTreeVertex* vex, int depth)
{
	if (vex == nullptr)
		return;
	succTraversal(vex->left, depth + 1);
	succTraversal(vex->right, depth + 1);
	/* process the current node */
	animeQueue.push_back(vex->visit());
	vexQueue.push_back(vex);
	depthQueue.push_back(depth);
	resList.push_back(vex);
	/* End */
}

void GraphicTreeView::orderTraversal(GraphicTreeVertex* vex)
{
	QQueue<GraphicTreeVertex*> queue;
	queue.push_back(vex);
	GraphicTreeVertex* temp;
	int depth = 0;
	while (!queue.empty())
	{
		depth++;
		int count = 0;
		int size = queue.size();
		while (count < size)
		{
			temp = queue.front();
			queue.pop_front();
			count++;
			/* process the current node */
			animeQueue.push_back(temp->visit());
			depthQueue.push_back(depth);
			vexQueue.push_back(temp);
			resList.push_back(temp);
			/* End */
			if (temp->left != nullptr)
			{
				queue.push_back(temp->left);
			}
			if (temp->right != nullptr)
			{
				queue.push_back(temp->right);
			}
		}


	}
}

void GraphicTreeView::startTraversal()
{
	if (!isbuild)
	{
		isbuild = !isbuild;
		emit build();					//通知系统开始构建二叉树
		if (traversalType == 1 || traversalType == 0)	//若不选择则默认为先序
			predTraversal(root, 1);
		else if (traversalType == 2)
			inTraversal(root, 1);
		else if (traversalType == 3)
			succTraversal(root, 1);
		else if (traversalType == 4)
			orderTraversal(root);
		playAnimation();
	}
}

void GraphicTreeView::playAnimation()
{
	if (animeQueue.size() > 0)
	{
		QTimeLine* next = animeQueue.front();
		connect(next, &QTimeLine::finished, [=]() {playAnimation(); next->deleteLater(); });
		emit vexChange(vexQueue.front(), depthQueue.front());
		animeQueue.pop_front();
		vexQueue.pop_front();
		depthQueue.pop_front();

		//next->setDuration(next->duration());
		next->start();
	}
}

void GraphicTreeView::reset()
{
	isbuild = false;
	resList.clear();
	for (int i = 0; i < vexList.size(); i++)
	{
		vexList[i]->setBrush(regBrush);
	}
	emit vexChange(nullptr, 0);
}

void GraphicTreeView::deleteAll()
{
	isbuild = false;
	this->myScene->clear();
	resList.clear();
	vexList.clear();
	lineList.clear();

	traversalType = 0;
	VexID = 0;
	isCreating = false;
	sketchItem = nullptr;
	root = addVex(QPoint(525, 120));
	strtVex = root;
	emit vexChange(nullptr, 0);		//改变属性栏后两行
	emit itemChange();				//前两行
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

QTimeLine* GraphicTreeVertex::visit()
{
	QTimeLine* timeLine = new QTimeLine(600, this);
	timeLine->setFrameRange(0, 200);
	QEasingCurve curve = QEasingCurve::OutBounce;
	qreal difRadius = 6;
	connect(timeLine, &QTimeLine::frameChanged, timeLine, [=](int frame) {
		this->setBrush(visitedBrush);
		qreal curProgress = curve.valueForProgress(frame / 200.0);
		qreal curRadius = radius + difRadius - difRadius * curProgress;
		this->setRect(QRectF(center.x() - curRadius, center.y() - curRadius, curRadius * 2, curRadius * 2));
		});
	return timeLine;
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
