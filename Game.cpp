#include "Game.h"
#include <cassert>
#include <QDebug>
#include <QTimer>

Game::Game( int numCellsWide,  int numCellsLong,  int cellSize, QWidget *parent):
    QGraphicsView(parent),
    pathingMap_(numCellsWide,numCellsLong,cellSize),
    scene_(new QGraphicsScene(this)),
    player_(new Player(this,cellSize)),
    enemies_(),
    cellSize_(cellSize)
{
    //set size of window/scene
    setScene(scene_);
    setSceneRect(0,0,numCellsWide*cellSize,numCellsLong*cellSize);

    // add the player to the scene/give him keyboard focus
    player_->setPos(3*cellSize,1*cellSize);
    scene_->addItem(player_);
    player_->setFocus();

    // create some enemies
    createEnemy(1,1);
    createEnemy(14,1);
    createEnemy(14,10);

    // draw the map
    std::vector<std::vector<int>> vec {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {1,0,1,0,1,1,1,1,1,1,1,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {1,0,1,0,1,1,1,1,1,1,1,1,0,1,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    };
    drawMap(vec);

    // make enemies follow player
    QTimer* followTimer = new QTimer(this);
    connect(followTimer,SIGNAL(timeout()),this,SLOT(setEnemyPathsToPlayer()));
    followTimer->start(1000);


}

/// Creates an enemy at the specified cell.
void Game::createEnemy( int x,  int y){
    Enemy* enemy = new Enemy(cellSize_);
    enemy->setPos(cellSize_*x,cellSize_*y);
    scene_->addItem(enemy);
    enemies_.push_back(enemy);
}

/// Fills the specified cell.
///
/// Marks it filled in the pathingMap_ and draws a gray square to visually
/// represent it.
void Game::fill( int x,  int y){
    pathingMap_.fillCell(x,y);

    // draw rectangle
    QGraphicsRectItem* rect = new QGraphicsRectItem(0,0,cellSize_,cellSize_);
    rect->setPos(x*cellSize_,y*cellSize_);
    QBrush brush;
    brush.setColor(Qt::gray);
    brush.setStyle(Qt::SolidPattern);
    rect->setBrush(brush);
    scene_->addItem(rect);
}

/// Returns true if the specified cell is filled.
///
/// Delegates to the PathingMap attribute.
bool Game::filled(int x, int y){
    return pathingMap_.filledCell(x,y);
}

/// Sets all the paths of the enemies to the location of the player
void Game::setEnemyPathsToPlayer(){
    for (Enemy* enemy:enemies_){
        std::vector<Node> nodePath = pathingMap_.shortestPath(enemy->pos().x(),
                                                              enemy->pos().y(),
                                                              player_->pos().x(),
                                                              player_->pos().y());
        std::vector<QPointF> path;
        for (Node node:nodePath){
            path.push_back(QPointF(node.x(),node.y()));
        }

        enemy->setPoints(path);
    }
}

/// Draws the map based on the provided 2d vector of ints.
///
/// A value of 0 in the vector represents open ground. Anything else represents
/// a block of wall.
void Game::drawMap(const std::vector<std::vector<int> > &vec){
    // make sure the vec is big enough to fill all the cell
    assert(vec.size() == pathingMap_.numCellsLong());
    assert(vec[0].size() == pathingMap_.numCellsWide());

    // draw map based on 2d vector
    for (int y = 0, n = pathingMap_.numCellsLong(); y < n; y++){
        for (int x = 0, p = pathingMap_.numCellsWide(); x < p; x++){
            if (vec[y][x] != 0){
                fill(x,y);
            }
        }
    }
}

/// Returns the cell (represented as a Node object) at the specified point.
Node Game::pointToNode(const QPointF &point){
    return Node(point.x()/cellSize_,point.y()/cellSize_);
}

/// Returns a point representing the top left corner of the specified cell.
QPointF Game::nodeToPoint(const Node &node){
    return QPointF(node.x()*cellSize_,node.y()*cellSize_);
}
