#include <QApplication>
#include <QWidget>
#include <QDebug>
#include "Game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    // create a game of pacman
    Game* game = new Game(16,12,50); // (width, height, cell size)
    game->show();

    return a.exec();
}
