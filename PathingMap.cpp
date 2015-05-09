#include "PathingMap.h"

/// Constructs a PathingMap with the specified number of cells wide/long and with the specified cell size.
PathingMap::PathingMap( int numCellsWide,  int numCellsLong,  int cellSize):
    numCellsWide_(numCellsWide),
    numCellsLong_(numCellsLong),
    cellSize_(cellSize),
    pathGrid_(numCellsWide,numCellsLong) {

    // constructor code goes here
}

/// Returns true if the specified location is filled.
bool PathingMap::filled( int x,  int y) const{
    // convert it to grid coordinates // TODO: maybe a helper function that can convert to/from pathGrid coordinates
    int xGrid = x / cellSize_;
    int yGrid = y / cellSize_;

    return pathGrid_.filled(xGrid,yGrid);
}

/// Returns true if the specified cell is filled.
bool PathingMap::filledCell( int x,  int y) const{
    return pathGrid_.filled(x,y);
}

/// Returns a vector of Nodes that represent the top left corner of each cell.
std::vector<Node> PathingMap::nodes() const{
    // just return scaled up versions of the nodes in pathGrid
    std::vector<Node> nodes;

    // for each node in the original pathGrid
    for (Node node:pathGrid_.nodes()){
        // scale it up and add it to nodes
        int scaledX = (node.x() * cellSize_);
        int scaledY = (node.y() * cellSize_);
        node.setX(scaledX);
        node.setY(scaledY);
        nodes.push_back(node);
    }

    return nodes;
}

/// Returns a vector of Nodes (which have an x and y location) that goes from one location to another.
std::vector<Node> PathingMap::shortestPath( int xfrom,  int yfrom,  int xto,  int yto) const{
    // get the vector from the pathGrid
    std::vector<Node> path = pathGrid_.shortestPath(Node(xfrom/cellSize_,yfrom/cellSize_),Node(xto/cellSize_,yto/cellSize_));
    std::vector<Node> scaledPath;

    // scale it up
    for (Node node:path){
        // scale it up and add it to nodes
        int scaledX = (node.x() * cellSize_);
        int scaledY = (node.y() * cellSize_);
        node.setX(scaledX);
        node.setY(scaledY);
        scaledPath.push_back(node);
    }

    return scaledPath;
}

/// Returns the width of the map.
int PathingMap::width() const{
    return cellSize_ * numCellsWide_;
}

/// Returns the height of the map.
int PathingMap::height() const{
    return cellSize_ * numCellsLong_;
}

/// Returns the cell size of the map.
int PathingMap::cellSize() const{
    return cellSize_;
}

/// Returns the number of cells in the vertical direction.
int PathingMap::numCellsLong() const{
    return numCellsLong_;
}

/// Returns the number of cells in the horizontal direction.
int PathingMap::numCellsWide() const{
    return numCellsWide_;
}

/// Fills the cell at the specified location.
void PathingMap::fill( int x,  int y){
    // convert it to grid coordiantes
    int xGrid = x / cellSize_;
    int yGrid = y / cellSize_;

    pathGrid_.fill(xGrid,yGrid);
}

/// Fills the specified cell.
void PathingMap::fillCell( int x,  int y){
    pathGrid_.fill(x,y);
}

/// Fills the specified columns.
void PathingMap::fillColumn( int i){
    pathGrid_.fillColumn(i);
}

/// Fills the specified row.
void PathingMap::fillRow( int i){
    pathGrid_.fillRow(i);
}

/// Unfills the cell at the specified location
void PathingMap::unfill( int x,  int y){
    // convert it to grid coordiantes
    int xGrid = x / cellSize_;
    int yGrid = y / cellSize_;

    pathGrid_.unfill(xGrid,yGrid);
}

/// Unfills the specified cell.
void PathingMap::unfillCell( int x,  int y){
    pathGrid_.unfill(x,y);
}

/// Fill/unfill cells based on values of a 2d vector.
///
/// A value of 0 means unfilled, anything else means fill.
void PathingMap::setFilling(const std::vector<std::vector<int> > &vec){
    pathGrid_.setFilling(vec);
}
