#include "paintscene.h"
#include "paint.h"
#include "vector"
#include "list"
#include <QPainter>
#include <QInputDialog>
using namespace robopath;
vector<Point> previous_points_of_graph;
int k = 1, N = 150, kol_edges = 8;
int flag = 0; //Флаг, который показывает, нажата ли кнопка, или нет
int flag_robot = 0;
int flag_end = 0;
bool have_collision = false, previous_collision = false;
Point previous_start(-1e8,-1e8), previous_end(-1e8,-1e8);
std::vector<Point> points; //Текущие координаты точек треугольника
std::vector<Triangle> all_triangles; //Все треугольники
paintScene::paintScene(QObject *parent) : QGraphicsScene(parent)
{

}

paintScene::~paintScene()
{

}

void paintScene::paint_triangle(Triangle& t) //Отрисовка треугольника
{
    auto points = t.points;
    QPolygonF pol;
    QBrush brush;
    brush.setColor(Qt::blue);
    brush.setStyle(Qt::SolidPattern);
    QPen pen(Qt::black);
    pol << QPointF(points[0].x, points[0].y) << QPointF(points[1].x, points[1].y) << QPointF(points[2].x, points[2].y);
    addPolygon(pol, pen, brush);
}

void paintScene::paint_line(string color, Point &p_1, Point &p_2) //Отрисовка ребер
{
    QPolygonF pol;
    QPen pen(Qt::black);
    if(color == "black")
    {
        pol << QPointF(p_1.x, p_1.y) << QPointF(p_2.x, p_2.y);
        addPolygon(pol, pen);
    }
    if(color == "magenta")
    {
        pen = QPen(Qt::magenta);
        pen.setWidth(3);
        pol << QPointF(p_1.x, p_1.y) << QPointF(p_2.x, p_2.y);
        addPolygon(pol, pen);
    }
}

void paintScene::paint_point(string color, Point &p) //Отрисовка точки
{
    QBrush brush;
    QPen pen(Qt::black);
    brush.setStyle(Qt::SolidPattern);
    if(color == "green")
    {
        brush.setColor(Qt::green);
        addEllipse(p.x - 7,p.y - 7,14,14, pen, brush);
    }
    if(color == "red")
    {
        brush.setColor(Qt::red);
        addEllipse(p.x - 7,p.y - 7,14,14, pen, brush);
    }
    if(color == "black")
    {
        brush.setColor(Qt::black);
        addEllipse(p.x - 7,p.y - 7,14,14, pen, brush);
    }
    if(color == "black_small")
    {
        brush.setColor(Qt::black);
        addEllipse(p.x - 4,p.y - 4,8,8, pen, brush);
    }
    if(color == "white")
    {
        pen = QPen(Qt::white);
        brush.setColor(Qt::white);
        addEllipse(p.x - 7,p.y - 7,14,14, pen, brush);
    }
}

void paintScene::repaint(Point& qinit, Point& qgoal) //Отрисовка сцены заново
{
    for(auto triangle: all_triangles)
        paint_triangle(triangle);
    paint_point("green", qinit);
    paint_point("red", qgoal);
}

void paintScene::clear_scene(Point& previous_start, Point& previous_end, vector<Triangle>& all_triangles)
{
    all_triangles.clear();
    previous_start = Point(-1e8, -1e8);
    previous_end = Point(-1e8, -1e8);
}

void paintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if((flag==1&&flag_robot==1) || (flag==1&&flag_end==1) || (flag_end==1&&flag_robot==1))
    {
        emit signal_nopath(2);
        emit signal_color(1);
        emit signal_color(2);
        emit signal_color(3);
        flag = 0;
        flag_robot = 0;
        flag_end = 0;
        k = 1;
        points.clear();
    }
    else
    {if(flag==1) //Если кнопка "Добавить треугольник" была нажата
    {
        if(k==3)
        {
            Point p;
            p.x= event->scenePos().x();
            p.y = event->scenePos().y();
            points.push_back(p);
            Triangle t(points[0], points[1], points[2]);
            emit signal_delete_items_from_scene();
            repaint(previous_start, previous_end);
            if(!t.collidesWith(Circle(previous_start,7))&&!t.collidesWith(Circle(previous_end,7))) // Проверка на пересечение с роботом/концом пути робота
            {
                all_triangles.push_back(t);
                paint_triangle(t);
                emit signal_color(1);
            }
            else
                emit signal_color(1);
            points.clear();
            k = 1;
            flag = 0;
        }
    else
        {
            Point p(event->scenePos().x(),event->scenePos().y());
            paint_point("black_small", p);
            points.push_back(p);
            k++;
        }
    }
    if(flag_robot==1) //Ставим робота на сцену
    {
        previous_start = Point(event->scenePos().x(),event->scenePos().y());
        emit signal_delete_items_from_scene();
        repaint(previous_start, previous_end);
        paint_point("green", previous_start);
        emit signal_color(2);
        flag_robot = 0;
    }
    if(flag_end==1) //Ставим конец пути робота на сцену
    {
        previous_end = Point(event->scenePos().x(),event->scenePos().y());
        emit signal_delete_items_from_scene();
        repaint(previous_start, previous_end);
        paint_point("red", previous_end);
        emit signal_color(3);
        flag_end = 0;
    }}
}

void paintScene::slot_triangle()
{
    flag = 1;
    emit signal_delete_items_from_scene();
    repaint(previous_start,previous_end);
}

void paintScene::slot_robot()
{
    flag_robot = 1;
    emit signal_delete_items_from_scene();
    repaint(previous_start, previous_end);
}
void paintScene::slot_end()
{
    flag_end = 1;
    emit signal_delete_items_from_scene();
    repaint(previous_start, previous_end);
}
void paintScene::slot_getpath()
{
    if(previous_start.x == -1e8 || previous_end.x == -1e8)
        emit signal_nopath(1);
    else
    {
    bool no_path = false;
    Graph g;
    for(auto t : all_triangles)
        if(t.collidesWith(Circle(previous_start, 7)) || t.collidesWith(Circle(previous_end, 7)))
        {
            no_path = true;
            break;
        }
    if(!no_path)
    {
        vector<Point> points_of_graph = PRM(N, kol_edges, previous_start, previous_end, all_triangles, g);
        if(!previous_points_of_graph.empty())
        {
            emit signal_delete_items_from_scene();
            repaint(previous_start, previous_end);
        }
        previous_points_of_graph = points_of_graph;
        for(auto p : points_of_graph)
        {
            if((p.x == previous_start.x && p.y == previous_start.y) || (p.x == previous_end.x && p.y == previous_end.y))
                continue;
            paint_point("black", p);
        }
        auto edges = g.get_edges();
        for(auto e : edges)
            paint_line("black", points_of_graph[get<0>(e)], points_of_graph[get<1>(e)]);
        auto path = shortest_path(g, N, N+1);
        if(path.size() == 0)
            emit signal_nopath(1);
        else
            for(unsigned int i = 0; i < path.size() - 1; i++)
                paint_line("magenta", points_of_graph[path[i]], points_of_graph[path[i+1]]);
    }
    else
        emit signal_nopath(1);}
}

void paintScene::slot_clear()
{
    clear_scene(previous_start, previous_end, all_triangles);
}

void paintScene::slot_kolgraph(int &n)
{
    N = n;
}

void paintScene::slot_koledge(int &k)
{
    kol_edges = k;
}

void paintScene::slot_save()
{
    emit signal_get_all_objects(previous_start, previous_end, all_triangles);
}

void paintScene::slot_load(Point &qi, Point &qg, vector<Triangle> &triangles)
{
    if(qi.x == -20)
        previous_start = Point(-1e8, -1e8);
    else
        previous_start = Point(qi.x, qi.y);
    if(qg.x == -20)
        previous_end = Point(-1e8, -1e8);
    else
        previous_end = Point(qg.x, qg.y);
    all_triangles = triangles;
    emit signal_delete_items_from_scene();
    repaint(qi,qg);
}
