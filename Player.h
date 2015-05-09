#ifndef PLAYER_H
#define PLAYER_H

// inheriting from:
#include <QGraphicsRectItem>
#include <QObject>

// using:
class QKeyEvent;
class QGraphicsItem;
class Game;

class Player: public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    // constructor
    Player(Game* game, int stepSize, QGraphicsItem* parent = nullptr);

    // nested enum class - describes the direction the player is moving towards
    enum class Direction {UP, DOWN, LEFT, RIGHT, NONE};

    // event handlers
    void keyPressEvent(QKeyEvent* keyPress);

public slots:
    void move();

private:
    // main private attributes
    Direction movementDirection_;
    int stepSize_;
    Game* game_;

    // helper functions
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    bool frontBlocked();
};

#endif // PLAYER_H
