#include "Enemy.h"
#include <QLineF>
#include <QTimer>
#include <QDebug> // TODO: remove
#include <QBrush>
#include <cassert>


Enemy::Enemy( int stepSize, QGraphicsItem *parent):
    QGraphicsRectItem(parent),
    targetPoint_(0),
    stepSize_(stepSize),
    points_()
{
    // periodically move the enemy
    QTimer* moveTimer = new QTimer(this);
    connect(moveTimer,SIGNAL(timeout()),this,SLOT(move()));
    moveTimer->start(500);

    // draw
    setRect(0,0,stepSize,stepSize);
    QBrush brush;
    brush.setColor(Qt::red);
    brush.setStyle(Qt::SolidPattern);
    setBrush(brush);

}

/// Will move the Enemy along its list of points.
///
/// This should be called periodically as each call only moves it one step.
void Enemy::move(){
    // if enemy is already at the last point, don't do anything, just get out
    // of this function
    if (atLastPoint()){
        return;
    }

    // assuming the enemy is NOT at the last point, move him towards his
    // target
    moveTowardsTarget();

    // if he has reached his target, set next target
    if (targetReached()){
        setNextTarget();
    }
}

/// Sets the points the Enemy should follow.
void Enemy::setPoints(const std::vector<QPointF> &points){
    // change the vector of points
    points_ = points;

    // start from the beggining
    targetPoint_ = 1;
}

/// Returns true if the Enemy has reached its current target point.
bool Enemy::targetReached(){
    const int EPSILON = 50;

    // approach:
    // - create a line b/w enemy pos and target point
    // - check the length of this line to determine if the enemy is close enough
    QPointF target = points_[targetPoint_];
    QLineF line(pos(),target);

    return (line.length() < EPSILON);
}

/// Returns true if the Enemy is at his last point.
bool Enemy::atLastPoint(){
    // if at last point, then targetPoint_ (which is an index representing the
    // point in points_ which the enemy is heading towards) will be bigger
    // than the size of points
    int veclength = points_.size();
    int targetPt = targetPoint_;
    bool cond = targetPt >= veclength;
    return (cond);
}

/// Sets the next point in the list of points as the target point.
void Enemy::setNextTarget(){
    // targetPoint_ is an index that represents the point in points_ the
    // enemy is currently heading towards, incrementing this index effectively
    // makes it so that the enemy should head towards the next point in its list
    ++targetPoint_;
}

/// Moves the enemy towards the target point
void Enemy::moveTowardsTarget(){
    // approach:
    // - create line from pos of enemy to pos of target
    // - set the length of this line to stepSize_
    // - move by the dx and dy of this line

    QPointF target = points_[targetPoint_];
    QLineF line(pos(),target);
    line.setLength(stepSize_);
    moveBy(line.dx(),line.dy());
}
