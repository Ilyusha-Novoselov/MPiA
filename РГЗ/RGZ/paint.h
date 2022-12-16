#ifndef PAINT_H
#define PAINT_H

#include <QWidget>
#include <QTimer>
#include <QResizeEvent>

#include <paintscene.h>

namespace Ui {
class Paint;
}

class Paint : public QWidget
{
    Q_OBJECT

public:
    explicit Paint(QWidget *parent = 0);
    ~Paint();

signals:
    void signal_triangle();
    void signal_robot();
    void signal_end();
    void signal_getpath();
    void signal_clear();
    void signal_kolgraph(int& n);
    void signal_koledge(int& k);
    void signal_save();
    void signal_load(Point& qinit, Point& qgoal, vector<Triangle>& all_triangles);

private slots:
    void on_pushButton_clicked(); //Кнопка для построения треугольника

    void on_pushButton_2_clicked(); //Кнопка для построения робота

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

public slots:
    void slot_nopath(int i);
    void slot_color(int num_button);
    void slot_get_all_objects(Point& qinit, Point& qgoal, vector<Triangle>& all_triangles);
    void slot_delete_items_from_scene();

private:
    Ui::Paint *ui;
    paintScene *scene;  // Объявляем кастомную графическую сцену
    QString path; //Путь сохранения файла
};

#endif // PAINT_H
