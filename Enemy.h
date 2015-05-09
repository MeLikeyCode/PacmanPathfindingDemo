#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>
#include <vector>
#include <QPointF>

class Enemy:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    // constructors
    Enemy( int stepSize, QGraphicsItem* parent=nullptr);

    // modifiers ("setters")
    void setPoints(const std::vector<QPointF>& points);

public slots:
    // slots (modifier)
    void move();

private:
    // main private attributes
    std::vector<QPointF> points_;
    size_t targetPoint_;
    int stepSize_;

    // helper functions
    bool targetReached();
    bool atLastPoint();
    void setNextTarget();
    void moveTowardsTarget();
};

#endif // ENEMY_H
