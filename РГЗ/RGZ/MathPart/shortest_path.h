#include "graph.h"
#include "iostream"
#include <vector>
#include <list>
#include <queue>
#include <chrono>
using namespace std;
//The class for adding to the priority queue
class CompareDist
{
public:
    bool operator()(pair<int, double> n1, pair<int, double> n2) {
        return n1.second > n2.second;
    }
};

vector<int> shortest_path(const Graph &graph, int start_vertex, int end_vertex);