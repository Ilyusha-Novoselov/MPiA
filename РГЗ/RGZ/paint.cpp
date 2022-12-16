#include "paint.h"
#include "paintscene.h"
#include "ui_paint.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QTextStream>
#include <fstream>
Point qi, qg;
vector<Triangle> triangles;
int k_1 = 0;
Paint::Paint(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Paint)
{
    ui->setupUi(this);

    scene = new paintScene();       // Инициализируем графическую сцену
    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену
    scene->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
    connect(this, &Paint::signal_triangle, scene, &paintScene::slot_triangle);
    connect(this, &Paint::signal_robot, scene, &paintScene::slot_robot);
    connect(this, &Paint::signal_end, scene, &paintScene::slot_end);
    connect(this, &Paint::signal_getpath, scene, &paintScene::slot_getpath);
    connect(scene, &paintScene::signal_nopath, this, &Paint::slot_nopath);
    connect(scene, &paintScene::signal_color, this, &Paint::slot_color);
    connect(scene, &paintScene::signal_get_all_objects, this, &Paint::slot_get_all_objects);
    connect(scene, &paintScene::signal_delete_items_from_scene, this, &Paint::slot_delete_items_from_scene);
    connect(this, &Paint::signal_clear, scene, &paintScene::slot_clear);
    connect(this, &Paint::signal_kolgraph, scene, &paintScene::slot_kolgraph);
    connect(this, &Paint::signal_koledge, scene, &paintScene::slot_koledge);
    connect(this, &Paint::signal_save, scene, &paintScene::slot_save);
    connect(this, &Paint::signal_load, scene, &paintScene::slot_load);
    QFont f;
    f.setBold(true);
    f.setFamily("Times New Roman");
    f.setPointSize(10);
    ui->pushButton->setStyleSheet("color:red");
    ui->pushButton_2->setStyleSheet("color:red");
    ui->pushButton_3->setStyleSheet("color:red");
    ui->pushButton->setFont(f);
    ui->pushButton_2->setFont(f);
    ui->pushButton_3->setFont(f);
    ui->pushButton_4->setFont(f);
    ui->pushButton_5->setFont(f);
    ui->pushButton_6->setFont(f);
    ui->pushButton_7->setFont(f);
    ui->pushButton_8->setFont(f);
    ui->pushButton_9->setFont(f);
    f.setItalic(true);
    ui->label->setFont(f);
    ui->label_2->setFont(f);
    ui->label_3->setFont(f);
    ui->label_4->setFont(f);
}

Paint::~Paint()
{
    delete ui;
}


void Paint::on_pushButton_clicked() //Кнопка с треугольником
{
    emit signal_triangle();
    QPushButton *button = static_cast<QPushButton*>(sender());
        button->setStyleSheet("color:green");
}


void Paint::on_pushButton_2_clicked() //Кнопка с роботом
{
    emit signal_robot();
    QPushButton *button = static_cast<QPushButton*>(sender());
        button->setStyleSheet("color:green");
}


void Paint::on_pushButton_3_clicked() //Кнопка с конечной позицией робота
{
    emit signal_end();
    QPushButton *button = static_cast<QPushButton*>(sender());
        button->setStyleSheet("color:green");
}


void Paint::on_pushButton_4_clicked()
{
    emit signal_getpath();
}

void Paint::slot_nopath(int i)
{
    if(i == 1)
        QMessageBox::warning(this,tr("Ошибка"),tr("Нет пути"));
    if(i == 2)
        QMessageBox::warning(this,tr("Предупреждение"),tr("Нельзя нажимать несколько кнопок подряд"));
}

void Paint::slot_color(int num_button)
{
    QFont f;
    f.setBold(true);
    f.setFamily("Times New Roman");
    f.setItalic(true);
    f.setPointSize(13);
    if(num_button == 1)
        ui->pushButton->setStyleSheet("color:red");
    if(num_button == 2)
        ui->pushButton_2->setStyleSheet("color:red");
    if(num_button == 3)
        ui->pushButton_3->setStyleSheet("color:red");
}

void Paint::slot_get_all_objects(Point &qinit, Point &qgoal, vector<Triangle> &all_triangles)
{
    qi = qinit;
    qg = qgoal;
    triangles = all_triangles;
}

void Paint::slot_delete_items_from_scene()
{
    ui->graphicsView->scene()->clear();
}

void Paint::on_pushButton_5_clicked()
{
    emit signal_clear();
    ui->graphicsView->scene()->clear();
}


void Paint::on_pushButton_6_clicked()
{
    bool ok;
    int i = QInputDialog::getInt(this, tr("Ввод кол-ва точек графа"),
                          tr("Количество точек графа:"), 150, 0, 1300, 1, &ok);
    emit signal_kolgraph(i);
}


void Paint::on_pushButton_7_clicked()
{
    bool ok;
    int j = QInputDialog::getInt(this, tr("Ввод кол-ва ребер вершины"),
                          tr("Количество вершин:"), 8, 3, 100, 1, &ok);
    emit signal_koledge(j);
}


void Paint::on_pushButton_8_clicked()
{
      emit signal_save();
      QFileDialog fileDialog;
      QString newPath = fileDialog.getSaveFileName(this, tr("Open file"), path, tr("Text files (*.txt)"));

       if (newPath.isEmpty())
           return;

       path = newPath;

       QFile file(newPath);
          if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
          {
                       QMessageBox::warning(this,tr("Error"),tr("Ошибка"));
              return;
          }
          else
          {
              QTextStream textStream(&file);
              textStream<< qi.x << " " << qi.y << endl;
              textStream<< qg.x << " " << qg.y << endl;
              for(auto t : triangles)
              {
                  auto points = t.getPoints();
                  for(unsigned int i = 0; i < points.size(); i++)
                  {
                      if(i == points.size() - 1)
                          textStream<< points[i].x << " " << points[i].y;
                      else
                          textStream<< points[i].x << " " << points[i].y << " ";
                  }
                  textStream<< endl;
              }
              QMessageBox::about(this, "Уведомление", "Сохранение прошло успешно");
              file.close();
          }
}

void split(const QByteArray & a, QList<QByteArray> & l)
{
    QByteArray b;
    for (int i = 0; i < a.size(); i++)
    {
        if(a[i] == 'e')
        {
            b.clear();
            b="-20";
            i+=4;
        }
        if(a[i] == ' ' || a[i] == '\n')
        {
            l.push_back(b);
            b.clear();
        }
        else
            b.push_back(a[i]);
    }
}

void Paint::on_pushButton_9_clicked()
{
    QString fileName;
        fileName = QFileDialog::getOpenFileName(this,tr("Open File"),tr(""),tr("Text File (*.txt)"));
             if(fileName == "")
        {
            return;
        }
        else
        {
           QFile file(fileName);
           if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
           {
                           QMessageBox::warning(this,tr("error"),tr("open file failed"));
               return;
           }
           else
           {
               if(!file.isReadable())
               {
                   QMessageBox::warning(this,tr("error"),tr("the file is not readable"));
               }
               else
               {
                   QByteArray block = file.readAll();
                   QList<QByteArray> all_numbers;
                   split(block, all_numbers);
                   qi.x = all_numbers[0].toInt();
                   qi.y = all_numbers[1].toInt();
                   qg.x = all_numbers[2].toInt();
                   qg.y = all_numbers[3].toInt();
                   triangles.clear();
                   Point a,b,c;
                   int i = 4;
                   while(i<all_numbers.size())
                   {
                       Point a,b,c;
                       a.x = all_numbers[i].toInt();
                       a.y = all_numbers[i+1].toInt();
                       b.x = all_numbers[i+2].toInt();
                       b.y = all_numbers[i+3].toInt();
                       c.x = all_numbers[i+4].toInt();
                       c.y = all_numbers[i+5].toInt();
                       triangles.push_back(Triangle(a,b,c));
                       i+=6;
                   }
                   file.close();
                   emit signal_load(qi,qg,triangles);
               }
           }
        }
}

