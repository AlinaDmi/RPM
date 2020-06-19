#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class Canvas : public QGraphicsScene
{
    Q_OBJECT
private:
    QPointF previousPoint;
    QColor color;
    int size;

public:
    explicit Canvas(QObject *parent = nullptr);
    ~Canvas();

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

public slots:
    void setColor(QString color);
    void setSize (QString size);
};

#endif // CANVAS_H
