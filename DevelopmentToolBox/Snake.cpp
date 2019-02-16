#include "Snake.h"
#include <QTime>
Snake::Snake(QWidget * parent) :
	QWidget(parent)
{
	SnakePen.setColor(QColor(0, 0, 255, 255));
	SnakeBrush.setColor(QColor(0, 0, 255, 255));
	SnakeBrush.setStyle(Qt::SolidPattern);

	FencePen.setColor(QColor(0, 0, 0, 255));
	FencePen.setWidth(10);
	FenceBrush.setColor(QColor(0, 0, 0, 0));
    FenceBrush.setStyle(Qt::SolidPattern);
	Init();
	connect(&InterfaceRefreshTimer, SIGNAL(timeout()), this, SLOT(InterfaceRefresh()));
	Running = false;
    Speed = 50;
}

void Snake::StartGame()
{
	SnakeBody.clear();
	QPoint Head = this->rect().center();
}

void Snake::SetSpeed(int Value)
{
    Speed = Value;
	InterfaceRefreshTimer.setInterval(Speed);
}


void Snake::Init()
{
	InterfaceRefreshTimer.stop();
	SnakeBody.clear();
	QPoint m_TmmpPoint = this->rect().center();
	for (int i = 0; i < 50; i++) {
        m_TmmpPoint.setX(m_TmmpPoint.x() + 1);
		SnakeBody.append(m_TmmpPoint);
	 }
	X_Axis = 0;
	Y_Axis = 0;
	update();
}

void Snake::InterfaceRefresh()
{
	if (Running == false) {
		InterfaceRefreshTimer.stop();
	}
	if (X_Axis == 0 && Y_Axis == 0) {
		return;
	}
	QPoint m_TmmpPoint(SnakeBody[0].x() + X_Axis, SnakeBody[0].y() + Y_Axis);
	//咬到自己判定
	int Count = 0;
	for (int i = 0; i < SnakeBody.count(); i++) {
		if (m_TmmpPoint == SnakeBody.at(i)) {
			Count++;
			if (Count > 0) {
				emit GameOver();
				InterfaceRefreshTimer.stop();
			}
			break;
		}
	}
	SnakeBody.push_front(m_TmmpPoint);
	SnakeBody.removeLast();
	//吃食物判定

	//撞墙判定
	if (SnakeBody[0].x() < 15 || SnakeBody[0].y() < 15) {
		emit GameOver();
		InterfaceRefreshTimer.stop();
	}
	if (SnakeBody[0].x() > this->rect().width() - 15 || SnakeBody[0].y() > this->rect().height() - 15) {
		emit GameOver();
		InterfaceRefreshTimer.stop();
	}
	update();
}

void Snake::keyPressEvent(QKeyEvent * event)
{

}

void Snake::keyReleaseEvent(QKeyEvent * event)
{
	if (Running == false) {
        InterfaceRefreshTimer.start(Speed);
		Running = true;
		return;
	}
	switch (event->key())
	{
	case Qt::Key_Up:
		if (SnakeBody[0].y() > SnakeBody[1].y()) {
			return;
		}
        Y_Axis = -1;
		X_Axis = 0;
		break;
	case Qt::Key_Right:
		if (SnakeBody[0].x() < SnakeBody[1].x()) {
			return;
		}
        X_Axis = 1;
		Y_Axis = 0;
		break;
	case Qt::Key_Left:
		if (SnakeBody[0].x() > SnakeBody[1].x()) {
			return;
		}
        X_Axis = -1;
		Y_Axis = 0;
		break;
	case Qt::Key_Down:
		if (SnakeBody[0].y() < SnakeBody[1].y()) {
			return;
		}
        Y_Axis = 1;
		X_Axis = 0;
		break;
	default:
		break;
	}
}

void Snake::mouseDoubleClickEvent(QMouseEvent * event)
{

}

void Snake::mouseMoveEvent(QMouseEvent * event)
{

}

void Snake::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton) {
		this->setFocus();
	}
}

void Snake::mouseReleaseEvent(QMouseEvent * event)
{

}

void Snake::moveEvent(QMoveEvent * event)
{

}

void Snake::paintEvent(QPaintEvent * event)
{
    SnakePen.setWidth(10);
	Painter.begin(this);
	Painter.setPen(SnakePen);
	Painter.setBrush(SnakeBrush);
    foreach(auto var, SnakeBody) {
        Painter.drawPoint(var);
    }
	Painter.end();
}

void Snake::resizeEvent(QResizeEvent * event)
{
    Init();
}
