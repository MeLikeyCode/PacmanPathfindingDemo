#include "Player.h"
#include <QTimer>
#include <cassert>
#include <QKeyEvent>
#include <QDebug> // TODO remove
#include <QBrush>
#include "Game.h"

Player::Player(Game *game, int stepSize, QGraphicsItem *parent):
    movementDirection_(Direction::NONE),
    stepSize_(stepSize),
    QGraphicsRectItem(parent),
    game_(game)
{

    // connect a timer to periodically move the player
    QTimer* moveTimer = new QTimer(this);
    connect(moveTimer,SIGNAL(timeout()),this,SLOT(move()));
    moveTimer->start(300);

    // set the rect
    setRect(0,0,stepSize,stepSize);
    QBrush brush;
    brush.setColor(Qt::blue);
    brush.setStyle(Qt::SolidPattern);
    setBrush(brush);

    // make focusable
    setFlag(QGraphicsItem::ItemIsFocusable,true);
}

/// Sets the direction in which the Player should move based on which _arrow_
/// key was pressed.
///
/// Does not do anything if the key pressed was not an _arrow_ key.
void Player::keyPressEvent(QKeyEvent *keyPress){
    switch (keyPress->key()){
    case Qt::Key_Up:
        movementDirection_ = Direction::UP;
        break;
    case Qt::Key_Down:
        movementDirection_ = Direction::DOWN;
        break;
    case Qt::Key_Left:
        movementDirection_ = Direction::LEFT;
        break;
    case Qt::Key_Right:
        movementDirection_ = Direction::RIGHT;
        break;
    default:
        ; // do nothing - since an arrow key was not pressed
    }
}

/// Moves the Player based on his current movementDirection_.
///
/// Moves the player in the direction dictated by its movementDirection_
/// attribute. The distance moved is determined by it's stepSize_ attribute.
/// This should be called periodically as it only moves by one step.
void Player::move(){
    // if front is blocked, don't move at all, return
    if (frontBlocked()){
        return;
    }

    // otherwise, move based on the direction
    switch (movementDirection_){
    case Direction::UP:
        moveUp();
        break;
    case Direction::DOWN:
        moveDown();
        break;
    case Direction::LEFT:
        moveLeft();
        break;
    case Direction::RIGHT:
        moveRight();
        break;
    case Direction::NONE:
        // do nothing (do not move if no direction)
        break;
    default:
        assert(false); // should not get here
    }
}

/// Moves the Player up by its stepSize_.
void Player::moveUp(){
    setPos(x(),y()-stepSize_);
}

/// Moves the Player down by its stepSize_.
void Player::moveDown(){
    setPos(x(),y()+stepSize_);
}

/// Moves the Player left by its stepSize_.
void Player::moveLeft(){
    setPos(x()-stepSize_,y());
}

/// Moves the Player right by its stepSize_.
void Player::moveRight(){
    setPos(x()+stepSize_,y());
}

/// Returns true if the front of the Player is blocked in the map.
bool Player::frontBlocked(){
    // find location of the cell in front
    int x = 0;
    int y = 0;
    Node cellPos = game_->pointToNode(pos());
    switch (movementDirection_){
    case Direction::UP:
        x = cellPos.x();
        y = cellPos.y() - 1;
        break;
    case Direction::DOWN:
        x = cellPos.x();
        y = cellPos.y() + 1;
        break;
    case Direction::LEFT:
        x = cellPos.x() - 1;
        y = cellPos.y();
        break;
    case Direction::RIGHT:
        x = cellPos.x() + 1;
        y = cellPos.y();
        break;
    }

    return game_->filled(x,y);
}
