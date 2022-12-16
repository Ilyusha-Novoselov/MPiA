#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <MathPart/objects.h>

class paintScene : public QGraphicsScene
{

    Q_OBJECT

public:
    explicit paintScene(QObject *parent = 0);
    ~paintScene();
    void paint_triangle(Triangle& t);
    void paint_line(string color, Point& p_1, Point& p_2);
    void paint_point(string color, Point& p);
    void repaint(Point& qinit, Point& qgoal);
    void clear_scene(Point& previous_start, Point& previous_end, vector<Triangle>& all_triangles);
private:
    QPointF previousPoint;      // Координаты предыдущей точки

private:
    // Для рисования используем события мыши
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
signals:
    void signal_nopath(int i);
    void signal_color(int num_button);
    void signal_get_all_objects(Point& qinit, Point& qgoal, vector<Triangle>& all_triangles);
    void signal_delete_items_from_scene();

public slots:
    void slot_triangle();
    void slot_robot();
    void slot_end();
    void slot_getpath();
    void slot_clear();
    void slot_kolgraph(int& n);
    void slot_koledge(int& k);
    void slot_save();
    void slot_load(Point& qi, Point& qg, vector<Triangle>& triangles);

};

#endif // PAINTSCENE_H
