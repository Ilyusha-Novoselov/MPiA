#include "objects.h"
#include "graph.h"
#include "vector"
using namespace robopath;
using namespace std;
double random(double min, double max);
Point RandomSample();
vector<int> Near(vector<Point>& points_of_graph, Point& X, int k);
bool CollisionFree(Point& p1, Point& p2, vector<Triangle>& all_triangles);
vector<Point> PRM(int N, int k, Point& qinit, Point& qgoal, vector<Triangle>& all_triangles, Graph& g);