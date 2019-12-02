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

private slots:
    void on_lineEdit_textChanged(const QString &arg1);


private:
    Ui::MainWindow *ui;
    QGraphicsScene *_scene;
    QGraphicsPixmapItem *_pixmapItem;
    QSize _size;
};

#endif // MAINWINDOW_H
