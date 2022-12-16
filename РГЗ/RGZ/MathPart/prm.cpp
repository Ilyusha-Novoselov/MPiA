#include "objects.h"
#include "graph.h"
#include "vector"
#include "ctime"
#include "iostream"
#include "math.h"
const int inf = 1e8;
using namespace robopath;
using namespace std;
double random(double min, double max)
{
	return (double)(rand()) / RAND_MAX * (max - min) + min;
}

Point RandomSample()
{
	Point result;
	result.x = random(0, 910);
	result.y = random(0, 430);
	return result;
}

vector<int> Near(vector<Point>& points_of_graph, Point& X, int k)
{
	vector<int> result;
	auto points = points_of_graph;
	for (int i = 0; i < k; i++)
	{
		double min_dist = inf;
        int p = 0;
        for (unsigned int j = 0; j < points.size(); j++)
		{
			if (points[j].x == X.x && points[j].y == X.y)
				continue;
			double dist = X.distanceTo(points[j]);
			if (dist < min_dist)
			{
				min_dist = dist;
				p = j;
			}
		}
		result.push_back(p);
		points[p].x = inf;
		points[p].y = inf;
	}
	return result;
}


bool CollisionFree(Point& p1, Point& p2, vector<Triangle>& all_triangles, vector<Point> points_of_graph, Circle Qinit, Circle Qgoal)
{
	LineSegment line(p1, p2);
	for (auto& t : all_triangles)
		if (t.collidesWith(line))
			return false;
	for (auto p : points_of_graph)
	{
        if ((p.x == p1.x && p.y == p1.y) || (p.x == p2.x && p.y == p2.y))
			continue;
		if (Circle(p, 7).collidesWith(line))
			return false;
	}
	if (Qinit.collidesWith(line) || Qgoal.collidesWith(line))
		return false;
	return true;
}


bool CollisionFree(Point& p1, Point& p2, vector<Triangle>& all_triangles, vector<Point> points_of_graph)
{
    LineSegment line(p1, p2);
    for (auto& t : all_triangles)
        if (t.collidesWith(line))
            return false;
    for (auto p : points_of_graph)
    {
        if ((p.x == p1.x && p.y == p1.y) || (p.x == p2.x && p.y == p2.y))
            continue;
        if (Circle(p, 7).collidesWith(line))
            return false;
    }
    return true;
}

bool CollisionFree(Point& p1, Point& p2, vector<Triangle>& all_triangles)
{
	LineSegment line(p1, p2);
	for (auto& t : all_triangles)
		if (t.collidesWith(line))
			return false;
	return true;
}



vector<Point> PRM(int N, int k, Point& qinit, Point& qgoal, vector<Triangle>& all_triangles, Graph& g)
{
	Point qrand;
	Circle Qinit(qinit, 7);
	Circle Qgoal(qgoal, 7);
	vector<Point> points_of_graph;
    int kol_vertices = 0, count = 0;
	vector<int> Parent(kol_vertices);
	set<pair<int, int>> visited;
    bool has_qinit = false, has_qgoal = false;
	bool collision = false;
    int n = pow(N,2);
    if(N != 0)
    {while (kol_vertices < N)
		{
            count++;
            if(count > 50*n)
                return {};
			qrand = RandomSample();
			for (auto& t : all_triangles)
				if (t.collidesWith(Circle(qrand, 7)))
				{
					collision = true;
					break;
				}
			for (auto p : points_of_graph)
				if (Circle(p, 7).collidesWith(Circle(qrand, 7)))
				{
					collision = true;
					break;
				}
			if (Qinit.collidesWith(Circle(qrand, 7)) || Qgoal.collidesWith(Circle(qrand, 7)))
				collision = true;
			if (!collision)
			{
				g.add_vertex(kol_vertices);
				points_of_graph.push_back(qrand);
				kol_vertices++;
			}
			collision = false;
        }

	auto vertices = g.get_vertices();
	for (auto& Q : vertices)
	{
		auto Qnear = Near(points_of_graph, points_of_graph[Q], k);
		for (auto& Qn : Qnear)
		{
			if (CollisionFree(points_of_graph[Q], points_of_graph[Qn], all_triangles, points_of_graph, Qinit, Qgoal))
			{
				g.add_edge(Q, Qn, points_of_graph[Q].distanceTo(points_of_graph[Qn]));
			}
		}
	}
	
	auto nearby = Near(points_of_graph, qinit, 3);
	for (auto& n : nearby)
	{
		if (CollisionFree(qinit, points_of_graph[n], all_triangles))
		{
			g.add_vertex(kol_vertices);
			points_of_graph.push_back(qinit);
            has_qinit = true;
			g.add_edge(kol_vertices, n, points_of_graph[n].distanceTo(qinit));
			kol_vertices++;
			break;
		}
	}

	nearby = Near(points_of_graph, qgoal, 3);
	for (auto& n : nearby)
	{
		if (CollisionFree(qgoal, points_of_graph[n], all_triangles))
		{
			g.add_vertex(kol_vertices);
			points_of_graph.push_back(qgoal);
            has_qgoal = true;
			g.add_edge(kol_vertices, n, points_of_graph[n].distanceTo(qgoal));
			kol_vertices++;
			break;
		}
    }
    //
    bool collision_free = CollisionFree(qinit, qgoal, all_triangles, points_of_graph);
    if(!has_qinit && !has_qgoal && collision_free)
    {
        g.add_vertex(kol_vertices);
        g.add_vertex(kol_vertices + 1);
        points_of_graph.push_back(qinit);
        points_of_graph.push_back(qgoal);
        g.add_edge(kol_vertices,kol_vertices + 1,points_of_graph[kol_vertices].distanceTo(points_of_graph[kol_vertices + 1]));
        kol_vertices++;
        kol_vertices++;
    }
    if(has_qinit && has_qgoal && collision_free)
        g.add_edge(kol_vertices - 1,kol_vertices - 2,points_of_graph[kol_vertices - 1].distanceTo(points_of_graph[kol_vertices - 2]));
    if(!has_qinit && has_qgoal && collision_free)
    {
        g.add_vertex(kol_vertices);
        points_of_graph.push_back(qinit);
        g.add_edge(kol_vertices,kol_vertices - 1,points_of_graph[kol_vertices].distanceTo(points_of_graph[kol_vertices - 1]));
        kol_vertices++;
    }
    if(has_qinit && !has_qgoal && collision_free)
    {
        g.add_vertex(kol_vertices);
        points_of_graph.push_back(qgoal);
        g.add_edge(kol_vertices,kol_vertices - 1,points_of_graph[kol_vertices].distanceTo(points_of_graph[kol_vertices - 1]));
        kol_vertices++;
    }
    //
    }
    else
    {
        g.add_vertex(0);
        g.add_vertex(1);
        points_of_graph.push_back(qinit);
        points_of_graph.push_back(qgoal);
        if (CollisionFree(points_of_graph[0], points_of_graph[1], all_triangles))
            g.add_edge(0,1,points_of_graph[0].distanceTo(points_of_graph[1]));
    }

	return points_of_graph;
}
