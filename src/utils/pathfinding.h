#ifndef SEMESTER_PROJECT_PATHFINDING_H
#define SEMESTER_PROJECT_PATHFINDING_H

#include <vector>
#include <cstdint>
#include <unordered_map>
#include <map>
#include <set>
#include <stack>
#include <cmath>
#include <queue>
#include <algorithm>

typedef std::pair<int, int> TPoint;

#define IMPASSABLE -1

/**
 * Create a path from backtrack table and goal coordinate
 * @param goal Goal, from which to construct the path
 * @return Vector of coordinates of the path
 */
std::vector<TPoint> deconstruct_path(TPoint goal, std::map<TPoint, TPoint> backtrack) {
    std::vector<TPoint> path;
    TPoint next = goal;

    while (backtrack.count(next) != 0) {
        path.insert(path.end(), next);
        next = backtrack[next];
    }

    std::reverse(path.begin(), path.end());

    return path;
}

/**
 * Check around a coordinate and push all available neighbours on out vector
 * @param center Center, around which to check
 * @param out Reference to a vector, which will receive the neighbours
 * @param parent Argument for inspector function
 * @param inspector Function returning double as a cost of travelling to that coordinate
 */
template<typename T, typename I>
void around(TPoint const & center, std::vector<std::pair<int, int>> &out, T const &parent, I const & inspector) {
    int x = center.first;
    int y = center.second;

    if (inspector(parent, x + 1, y) != IMPASSABLE)
        out.emplace_back(x + 1, y);
    if (inspector(parent, x - 1, y) != IMPASSABLE)
        out.emplace_back(x - 1, y);
    if (inspector(parent, x, y + 1) != IMPASSABLE)
        out.emplace_back(x, y + 1);
    if (inspector(parent, x, y - 1) != IMPASSABLE)
        out.emplace_back(x, y - 1);
}

/**
 * Calculate euclidian distance between two points
 * @param p First point
 * @param goal Second point
 * @return Euclidian distance between two points
 */
double distanceHeuristics ( TPoint &  p, TPoint & goal ) {
    double dx = p.first - goal.first;
    double dy = p.second - goal.second;
    return sqrt ( dx * dx + dy * dy );
}

/**
 * Sort type, to sort tuples of TPoint, double, according to the double
 */
struct sort {
    bool operator()(std::tuple<TPoint, double> a, std::tuple<TPoint, double> b) {
        return std::get<1>(a) > std::get<1>(b);
    }
};


/**
 * Perform a dijkstra search algorithm
 * @param start Starting point
 * @param goal Goal
 * @param parent Argument for the inspector functiom
 * @param inspector Function, that will be querried for information about the map
 * @return Vector of coordinates, making the found path, or an empty vector
 */
template<typename T, typename I>
std::vector<TPoint> dijkstra_search(TPoint start, TPoint goal, T const &parent, I inspector) {

    std::set<TPoint> expanded;
    std::map<TPoint, double> score;
    std::map<TPoint, TPoint> backtrack;
    std::priority_queue<std::tuple<TPoint, double>, std::vector<std::tuple<TPoint, double>>, sort> queue;

    queue.push(std::make_tuple(start, 0));
    score.insert({start, 0});

    while (!queue.empty()) {
        TPoint next = std::get<0>(queue.top());
        queue.pop();

        std::vector<TPoint> adjacent;
        around(next, adjacent, parent, inspector);

        if (next == goal) {
            break;
        }

        for (TPoint v : adjacent) {

            if (expanded.find(v) == expanded.end()) {
                expanded.insert(v);
            }

            double ngScore = score[next] + 1;

            if (score.count(v) == 0 || ngScore < score[v]) {
                queue.push(std::make_tuple(v, ngScore));
                backtrack[v] = next;
                score[v] = ngScore;
            }
        }
    }

    auto path = deconstruct_path(goal, backtrack);
    return path;
}

/**
 * Perform a A* search algorithm
 * @param start Starting point
 * @param goal Goal
 * @param parent Argument for the inspector functiom
 * @param inspector Function, that will be querried for information about the map
 * @return Vector of coordinates, making the found path, or an empty vector
 */
template<typename T, typename I>
std::vector<TPoint> astar_search ( TPoint start, TPoint goal, T const &parent, I inspector ) {

    std::priority_queue < std::tuple < TPoint, double >, std::vector < std::tuple < TPoint, double>>, sort > queue;
    std::map < TPoint, double > fScores;
    std::map < TPoint, double > gScores;
    std::map < TPoint, TPoint > backtrack;

    gScores.insert ( { start, 0 } );
    fScores.insert ( { start, distanceHeuristics ( start, goal ) } );
    queue.push ( std::make_tuple ( start, fScores[ start ] ) );

    while ( ! queue.empty ( ) ) {
        TPoint next = std::get < 0 > ( queue.top ( ) );
        queue.pop ( );

        if ( goal == next ) {
            break;
        }

        std::vector<TPoint> adjacent;
        around(next, adjacent, parent, inspector);

        for ( TPoint neighbour : adjacent ) {
            auto ngScore = gScores[ next ] + inspector(parent, neighbour.first, neighbour.second);
            auto nfScore = ngScore + distanceHeuristics ( neighbour, goal );

            if(gScores.count(neighbour) == 0 || ngScore < gScores[neighbour]){
                backtrack.insert ( { neighbour, next } );
                gScores[ neighbour ] = ngScore;
                fScores[ neighbour ] = nfScore;
                queue.push ( std::make_tuple ( neighbour, nfScore ) );
            }
        }
    }

    auto path = deconstruct_path ( goal, backtrack );
    return path;
}


#endif //SEMESTER_PROJECT_PATHFINDING_H
