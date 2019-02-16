#ifndef SNAKE_H
#define SNAKE_H
#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMoveEvent>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QPainter>
#include <QPen>
#include <QResizeEvent>
#include <QResizeEvent>

class Snake :public QWidget
{
	Q_OBJECT

signals:
	void ScoreChange(unsigned long int Value);
	void GameOver();

public:
    Snake(QWidget * parent);
public slots:
    void StartGame();
    void SetSpeed(int Value);
    void Init();
    void InterfaceRefresh();
private:
	unsigned long int Integral;
	unsigned int Speed;
    QList<QPoint> SnakeBody;
	QTimer InterfaceRefreshTimer;
    //边界
	QPoint TopLeft;
	QPoint BottomRight;
	
	QPainter Painter;

	QPen SnakePen;
	QBrush SnakeBrush;

	QPen FencePen;
	QBrush FenceBrush;

	int X_Axis;
	int Y_Axis;
	bool Running;
    bool FenceRepainting;
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void moveEvent(QMoveEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
};

#endif // SNAKE_H
