#include "tsp.h"
#include <limits>
#include <algorithm>
#include <iostream>
#include <list>
const int N = 1e8;
/////////////////////////////////////////////////////////////////////////////
//tsp_native
void Permutations(vector<int> vertices, set<vector<int>>& result, int t) {
    vector<int> b;
    if (t == vertices.size() - 1) 
        result.insert(vertices);
    else {
        for (int j = t; j < vertices.size(); ++j)
        { 
            swap(vertices[t], vertices[j]); 
            t++;
            Permutations(vertices, result, t); 
            t--;
            swap(vertices[t], vertices[j]);
        }
    }
}

vector<int> tsp_native(const Graph &graph, int start_vertex) {
    if (graph.get_vertices().size() < 2)
        return {};
    double sum_min = 100000000;
    set<vector<int>> permutations;
    vector<int> result;
    Permutations(graph.get_vertices(), permutations, 0);
    try {
        for (auto path : permutations)
        {
            if (path.front() != start_vertex)
                continue;
            double sum = 0;
            for (int i = 0; i < path.size(); i++)
            {
                if (i == path.size() - 1)
                    sum += graph.edge_weight(path[i], path[0]);
                else
                    sum += graph.edge_weight(path[i], path[i + 1]);
            }
            if (sum < sum_min)
            {
                sum_min = sum;
                result = path;
            }
        }
    }
    catch (std::invalid_argument error) { return {}; };
    return result;
}

/////////////////////////////////////////////////////////////////////////////
//tsp_bnb

vector<int> MinPath(const Graph& graph, vector<int>& p1, vector<int>& p2)
{
    if (p1.size() == 0)
        return p2;
    double d1 = Length(graph, p2), d2 = Length(graph, p1);
    if (d1 < d2) 
        return p2;
    else
        return p1;
}

double Length(const Graph& graph, vector<int>& Path)
{
    if (Path.size() == 0)
        return 0;
    double sum = 0;
    for (int i = 0; i < Path.size() - 1; i++)
        sum += graph.edge_weight(Path[i], Path[i + 1]);
    sum += graph.edge_weight(Path[Path.size()-1], Path[0]);
    return sum;
}

double Lower_Bound(const Graph& graph, vector<int> visited) {
    double summ = 0;
    for (int i = 1; i < size(visited); i++)
        summ += graph.edge_weight(visited[i - 1], visited[i]);
    for (auto vertex : graph.get_vertices())
        if (find(visited.begin(), visited.end(), vertex) == visited.end())
        {
            auto a = graph.get_adjacent_edges(vertex);
            vector<double> weights;
            for (auto pair : a)
                weights.push_back(pair.second);
            double w[2];
            partial_sort_copy(weights.begin(), weights.end(), w, w + 2);
            summ += (w[0] + w[1]) / 2;

        }
    return summ;
}

vector<int> BnB(const Graph& graph, vector<int>& visited, vector<int>& best_path)
{
    if (visited.size() == graph.get_vertices().size())
        return MinPath(graph, best_path, visited);
    vector<int> vertices{ graph.get_vertices() };
    vector<int> VNext;
    vector<int> path;
    for (auto& i : visited)
        vertices.erase(find(vertices.begin(),vertices.end(),i));
    for (auto& v : vertices)
    {
        VNext = visited;
        VNext.push_back(v);
        if (Lower_Bound(graph, VNext) < Length(graph, best_path))
        {
            auto path = BnB(graph, VNext, best_path);
            best_path = MinPath(graph, best_path, path);
        }
    }
    return best_path;
}

vector<int> tsp_bnb(const Graph& graph, int start_vertex) {
    if (graph.get_vertices().size() < 2)
        return {};
    vector<int> visited{ start_vertex };
    vector<int> best_path{ graph.get_vertices() };
    try { return BnB(graph, visited, best_path); }
    catch (std::invalid_argument error) { return {}; }
}

/////////////////////////////////////////////////////////////////////////////
//tsp_greedy

vector<int> tsp_greedy(const Graph& graph, int start_vertex) {
    int n = graph.get_vertices().size();
    int current = start_vertex;
    vector<int> path = { start_vertex };
    try {
        while (path.size() != n) {
            vector<int> next = {};
            for (auto vertex : graph.get_adjacent_vertices(current))
                if (find(path.begin(), path.end(), vertex) == path.end())
                    next.push_back(vertex);
            if (next.size() == 0) return {};
            int min_vertex = next[0];
            int min_dist = graph.edge_weight(current, next[0]);
            for (int i = 1; i < next.size(); i++)
                if (min_dist > graph.edge_weight(current, next[i])) {
                    min_vertex = next[i];
                    min_dist = graph.edge_weight(current, next[i]);
                }
            path.push_back(min_vertex);
            current = min_vertex;
        }
        return path;
    }
    catch (invalid_argument) {
        return {};
    }

}

/////////////////////////////////////////////////////////////////////////////
//tsp_local

vector<int> transform(vector<int>& path, int a, int b, int c, int d) {
    vector<int> result;
    for (int i = 0; path[i] != a; i++)
        result.push_back(path[i]);
    result.push_back(a);
    bool flag = false;
    for (int i = path.size() - 1; i >= 0; i--) 
    {
        if (path[i] == c) 
            flag = true;
        if (flag) 
            result.push_back(path[i]);
        if (path[i] == b) 
            break;
    }
    for (int i = 0; i < path.size(); i++)
    {
        if (path[i] == d) 
            flag = false;
        if (!flag) 
            result.push_back(path[i]);
    }
    return result;
}

vector<int> TwoOpt(const Graph& graph, vector<int>& path)
{
    vector<pair<pair<int, int>, pair<int, int>>> pair_non_adj;
    for (int i = 0; i < path.size() - 2; i++)
        for (int j = i + 2; j < path.size(); j++)
        {
            auto e_1 = make_pair(path[i], path[i + 1]);
            auto e_2 = make_pair(path[j], path[j + 1]);
            if(j + 1< path.size())
                pair_non_adj.push_back(make_pair(e_1, e_2));
        }
    for (auto pair_of_edges : pair_non_adj)
    {
        auto e_1 = pair_of_edges.first;
        auto e_2 = pair_of_edges.second;
        double old_weight = graph.edge_weight(e_1.first, e_1.second) + graph.edge_weight(e_2.first, e_2.second);
        double new_weight = graph.edge_weight(e_1.first, e_2.first) + graph.edge_weight(e_1.second, e_2.second);
        if (new_weight < old_weight)
            return transform(path, e_1.first, e_1.second, e_2.first, e_2.second);
    }
    return path;
}

vector<int> tsp(const Graph& graph, int start_vertex)
{
    if (graph.get_vertices().size() < 2)
        return {};
    try 
    {
        auto current_path = tsp_greedy(graph, start_vertex);
        if (current_path.size() == 0)
            return {};
        while (true)
        {
            auto improved_path = TwoOpt(graph, current_path);
            if (Length(graph, improved_path) < Length(graph, current_path))
                current_path = improved_path;
            else
                return current_path;
        }
    }
    catch (invalid_argument) {
        return {};
    }
}





