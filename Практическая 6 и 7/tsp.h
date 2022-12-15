#include "graph.h"
#include <set>
#include <vector>
#include "iostream"
using namespace std;
/// Solve Travelling Salesman Problem (TSP) for the graph:
/// Find the shortest (with a minimal total weight) tour and return it as an array of vertices.
vector<int> tsp_native(const Graph& graph, int start_vertex);
std::vector<int> tsp_bnb(const Graph &graph, int start_vertex);
vector<int> tsp_greedy(const Graph& graph, int start_vertex);
double Length(const Graph& graph, vector<int>& Path);

vector<int> transform(vector<int>& path, int a, int b, int c, int d);
vector<int> TwoOpt(const Graph& graph, vector<int>& path);
vector<int> tsp(const Graph& graph, int start_vertex);
