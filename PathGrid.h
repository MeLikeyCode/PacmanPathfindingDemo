#ifndef PATHGRID_H
#define PATHGRID_H

#include <vector>
#include "Node.h"
#include <unordered_map>
#include "Graph.h"

/// Represents a grid of 1 by 1 cells, each of which has an x,y coordinates (ints), each coordinate can either be filled or unfilled.
/// @author Abdullah Aghazadah
/// @date 4-26-15
///
/// A PathGrid can be thought of as a minimalistic pathing map. This class can be "scaled up" to make pathing
/// maps of any size (see PathingMap for an example).
class PathGrid{
public:
    // constructors
    PathGrid( int numCols,  int numRows);

    // readers ("getters")
    std::vector<Node> nodes() const;
    bool filled(const Node& node) const;
    bool filled( int x,  int y) const;
    std::vector<Node> unfilledNeighbors(const Node& of) const;
    Graph graph() const;
    std::vector<Node> shortestPath(const Node& from, const Node& to) const;
    std::vector<Node> column( int i) const;
    std::vector<Node> row( int i) const;

    // modifiers ("setters")
    void fill(const Node& node);
    void fill( int x,  int y);
    void unfill(const Node& node);
    void unfill( int x,  int y);
    void fillColumn( int i);
    void fillRow( int i);
    void setFilling(const std::vector<std::vector<int>>& vec);

private:
    // main private attributes
    std::vector<std::vector<Node>> nodes_;
    std::unordered_map<Node,bool> filled_;

};

#endif // PATHGRID_H
