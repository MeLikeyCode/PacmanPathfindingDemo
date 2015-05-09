#ifndef PATHINGMAP_H
#define PATHINGMAP_H

#include "PathGrid.h"

/// Represents a pathing map in which each cell is either filled or unfilled.
/// @author Abdullah Aghazadah
/// @date 4-28-15
///
/// A PathingMap can be thought of as a region of space that is occupied by cells. These cells can
/// either be filled or unfilled. One can easily determine the shortest path between any two cells.
class PathingMap{
public:
    // constructor
    PathingMap( int numCellsWide,  int numCellsLong,  int cellSize);

    // readers ("getters")
    bool filled( int x,  int y) const;
    bool filledCell( int x,  int y) const;
    std::vector<Node> nodes() const;
    std::vector<Node> shortestPath( int xfrom,  int yfrom,  int xto,  int yto) const;
    int width() const;
    int height() const;
    int cellSize() const;
    int numCellsLong() const;
    int numCellsWide() const;

    // modifiers ("setters")
    void fill( int x,  int y); // fill a cell
    void fillCell( int x,  int y); // fill the cell at a location
    void fillColumn( int i); // fill all cells of column
    void fillRow( int i); // fill all cells of row
    void unfill( int x,  int y);
    void unfillCell( int x,  int y);
    void setFilling(const std::vector<std::vector<int>>& vec);

private:
    // main private attributes
    PathGrid pathGrid_;
    int cellSize_;
    int numCellsWide_;
    int numCellsLong_;
};

#endif // PATHINGMAP_H
