#ifndef NODE_H
#define NODE_H

#include <vector>

class Graph;

/// Represents a node.
/// @author Abdullah Aghazadah
/// @date 4-20-15
///
/// A Node object is defined by its x and y values. Two Nodes are equivalent if they have the
/// same x and y values.
///
/// @see Graph PathGrid Edge
class Node{
public:
    // constructors
    Node();
    Node( int x,  int y); // every node needs an x and y coordinate - it is what defines them!

    // readers (getters)
    int x() const;
    int y() const;

    // modifiers (setters)
    void setX( int x);
    void setY( int y);

private:
    int x_;
    int y_;
};

// non member comparison operator
bool operator==(const Node& lhs, const Node& rhs);

// make node hashable
namespace std {
template <> struct hash<Node>
{
    size_t operator()(const Node& node) const{
        return hash<int>()(node.x()) + hash<int>()(node.y());
    }
};
}

#endif // NODE_H
