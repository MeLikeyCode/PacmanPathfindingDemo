#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "PathingMap.h"
#include "Player.h"
#include <vector>
#include "Enemy.h"

class Game: public QGraphicsView {
    Q_OBJECT
public:
    // constructors
    Game( int numCellsWide,  int numCellsLong,
          int cellSize, QWidget* parent=nullptr);

    // modifiers ("setters")
    void createEnemy( int x,  int y);
    void fill( int x,  int y);
    bool filled(int x, int y);

    // helper functions (readers)
    Node pointToNode(const QPointF& point);
    QPointF nodeToPoint(const Node& node);

public slots:
    void setEnemyPathsToPlayer();

private:
    // main private attributes
    PathingMap pathingMap_;       // pathing map
    QGraphicsScene* scene_;       // scene
    Player* player_;              // player
    std::vector<Enemy*> enemies_; // enemies
    int cellSize_;       // cell size

    // helper functions
    void drawMap(const std::vector<std::vector<int>>& vec);

};

#endif // GAME_H
