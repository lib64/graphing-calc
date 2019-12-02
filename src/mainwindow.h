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

    void graphFunction(double (Interpreter::*func)(double), Interpreter &interpreter);

private slots:
    void on_lineEdit_textChanged(const QString &arg1);


private:
    Ui::MainWindow *ui;
    QGraphicsScene *_scene;
    QGraphicsPixmapItem *_pixmapItem;
};

#endif // MAINWINDOW_H
