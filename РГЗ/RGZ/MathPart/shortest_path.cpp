#include "shortest_path.h"
#include "algorithm"
#define inf 1000000
using namespace std;

vector<int> BuildPath(vector<int> Parent, int s, int e)
{
    vector<int> result;
    while (e != -1) 
    {
        result.push_back(e);
        e = Parent[e];
    }
    reverse(result.begin(), result.end());
    return result;
}

//O((V+E)lnV)
vector<int> shortest_path(const Graph &graph, int start_vertex, int end_vertex) {
    if(!graph.has_vertex(start_vertex) || start_vertex == end_vertex)
        return vector<int> {};
    priority_queue <pair<int, double>, vector<pair<int, double>>, CompareDist> Q;
    pair<int, double> u;
    vector<int> Parent(graph.get_vertices().size(), -1);
    vector <pair<int, double>> adjacent;
    vector<int> Distance(graph.get_vertices().size(), inf);
    Distance[start_vertex] = 0;
    Q.push({ start_vertex, 0 });
    while (!Q.empty())
    {
        u = Q.top();
        Q.pop();
        if (u.first == end_vertex)
            return BuildPath(Parent, start_vertex, end_vertex);
        adjacent = graph.get_adjacent_edges(u.first);
        for (int i = 0; i < adjacent.size(); i++)
            if (Distance[adjacent[i].first] > Distance[u.first] + adjacent[i].second)
            {
                Distance[adjacent[i].first] = Distance[u.first] + adjacent[i].second;
                Parent[adjacent[i].first] = u.first;
                Q.push({ adjacent[i].first,  Distance[adjacent[i].first]});
            }
    }
    return vector<int> {};
}
