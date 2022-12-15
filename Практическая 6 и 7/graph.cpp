#include "graph.h"

#include <stdexcept>

using namespace std;

Graph::Graph(initializer_list<tuple<int, int, double>> edges) {
    for (const auto &e: edges) {
        add_edge(get<0>(e), get<1>(e), get<2>(e));            
    }
}

double random(double min, double max)
{
    return (double)(rand()) / RAND_MAX * (max - min) + min;
}

void Graph::random_graph(int kol_vertices)
{
    for (int i = 0; i < kol_vertices - 1; i++)
        for (int j = i + 1; j < kol_vertices; j++)
            add_edge(i, j, random(1, 1000));  
}

void Graph::add_vertex(int vertex) {
    if (!has_vertex(vertex)) {
        vertices[vertex] = std::map<int, double>();
    }
}

void Graph::add_edge(int start_vertex, int end_vertex, double weight) {
    add_vertex(start_vertex);
    add_vertex(end_vertex);
    graph_edges.push_back(std::make_tuple(start_vertex, end_vertex, weight));
    vertices[start_vertex][end_vertex] = weight;
    vertices[end_vertex][start_vertex] = weight;
}

std::vector<int> Graph::get_vertices() const {
    std::vector<int> result;
    for (const auto &p: vertices) {
        result.push_back(p.first);
    }
    return result;
}

std::vector<std::tuple<int, int, double>> Graph::get_edges() const {
    std::vector<std::tuple<int, int, double>> result;
    for (const auto& p : graph_edges) {
        result.push_back(p);
    }
    return result;
}

std::vector<int> Graph::get_adjacent_vertices(int src_vertex) const {    
    const auto it = vertices.find(src_vertex);
    if (it == vertices.end()) {
        return std::vector<int> {};
    }
    vector<int> result;
    for (const auto &p: it->second) {
        result.push_back(p.first);
    }
    return result;
}

vector<pair<int, double>> Graph::get_adjacent_edges(int src_vertex) const {
    const auto it = vertices.find(src_vertex);
    if (it == vertices.end()) {
        return vector<pair<int, double>> {};
    }
    vector<pair<int, double>> result;
    for (const auto &p: it->second) {
        result.push_back(make_pair(p.first, p.second));
    }
    return result;
}

bool Graph::has_vertex(int vertex) const {
    return (vertices.find(vertex) != vertices.end());
}

bool Graph::has_edge(int start_vertex, int end_vertex) const {    
    const auto it = vertices.find(start_vertex);
    if (it == vertices.end()) {
        return false;
    }
    return (it->second.find(end_vertex) != it->second.end());
}

double Graph::edge_weight(int start_vertex, int end_vertex) const {        
    const auto it_s = vertices.find(start_vertex);
    if (it_s == vertices.end()) {
        throw invalid_argument("Edge doesn't exist");
    }
    const auto it_e = it_s->second.find(end_vertex);
    if (it_e == it_s->second.end()) {
        throw invalid_argument("Edge doesn't exist");   
    }
    return it_e->second;
}

void Graph::remove_vertex(int vertex) {
    /// Remove adjacent edges.
    auto adjacent_vertices = get_adjacent_vertices(vertex);
    for (const auto &adj_v: adjacent_vertices) {
        remove_edge(adj_v, vertex);
    }
    /// Remove the vertex itself.
    vertices.erase(vertex);    
}

void Graph::remove_edge(int start_vertex, int end_vertex) {
    auto it_s = vertices.find(start_vertex);
    if (it_s != vertices.end()) {
        it_s->second.erase(end_vertex);
    }
    auto it_e = vertices.find(end_vertex);
    if (it_e != vertices.end()) {
        it_e->second.erase(start_vertex);
    }
}