#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void graphFunction(Interpreter &interpreter);

    bool isWindowValid() const;

private slots:
    void on_lineEdit_textChanged(const QString &arg1);
    void on_lineEdit_2_textChanged(const QString &arg1);
    void on_lineEdit_5_textChanged(const QString &arg1);
    void on_lineEdit_3_textChanged(const QString &arg1);
    void on_lineEdit_6_textChanged(const QString &arg1);
    void on_lineEdit_4_textChanged(const QString &arg1);
    void on_lineEdit_7_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *_scene;
    QGraphicsPixmapItem *_pixmapItem;
    QSize _size;

    int _xmin, _xmax;
    int _ymin, _ymax;
    int _xscl, _yscl;

    bool _is_xmin, _is_xmax;
    bool _is_ymin, _is_ymax;
    bool _is_xscl, _is_yscl;

};

#endif // MAINWINDOW_H
