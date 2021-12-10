#include "game.h"
#include <sstream>

Circle::Circle(int p, bool s) : points(p), state(s), nVisits(0) {}

int Circle::getPoints() const { return points; }

bool Circle::getState() const { return state; }

void Circle::changeState() {
    if (state == false)
        state = true;
    else
        state = false;
}

int Circle::getNVisits() const { return nVisits; }

void Circle::incNVisits() { nVisits++; }

BinaryTree<Circle> &Game::getGame() { return game; }

//-----------------------------------------------------------------

// a)
BinaryTree<Circle> constructorHelper(int height, size_t pos,
                                     vector<int> &points,
                                     vector<bool> &states) {
    if (height == 0)
        return {{points.at(pos), states.at(pos)}};

    return {{points.at(pos), states.at(pos)},
            constructorHelper(height - 1, 2 * pos + 1, points, states),
            constructorHelper(height - 1, 2 * pos + 2, points, states)};
}

Game::Game(int height, vector<int> &points, vector<bool> &states)
    : game(constructorHelper(height, 0, points, states)) {}

// b)
int Game::play(BTNode<Circle> *n) {
    Circle &c{n->getElement()};
    int points{c.getPoints()};

    if (n->getLeft())
        if (c.getState())
            points = play(n->getRight());
        else
            points = play(n->getLeft());

    c.changeState();
    c.incNVisits();

    return points;
}

int Game::play() { return play(game.getRootNode()); }

// c)
int Game::mostVisited() const {
    int max{INT32_MIN};
    bool skip{true};

    for (BTItrPre<Circle> i{game}; !i.isAtEnd(); i.advance())
        if (skip)
            skip = false;
        else
            max = std::max(max, i.retrieve().getNVisits());

    return max;
}
