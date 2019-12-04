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

    static const QString LINE_EDIT_RED;
    static const QString LINE_EDIT_WHITE;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void drawOrigin(QPainter &painter);

    void graphFunction(Interpreter &interpreter);

    void updatePixmap();

    bool isWindowValid() const;

    int getWidth();
    int getHeight();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);
    void on_lineEdit_2_textChanged(const QString &arg1);
    void on_lineEdit_5_textChanged(const QString &arg1);
    void on_lineEdit_3_textChanged(const QString &arg1);
    void on_lineEdit_6_textChanged(const QString &arg1);
    void on_lineEdit_4_textChanged(const QString &arg1);
    void on_lineEdit_7_textChanged(const QString &arg1);

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    void pushButton_setPallete();
    void pushButton_2_setPallete();
    void pushButton_3_setPallete();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *_scene;
    QGraphicsPixmapItem *_pixmapItem;

    int _xmin, _xmax;
    int _ymin, _ymax;
    int _xscl, _yscl;

    bool _is_xmin, _is_xmax;
    bool _is_ymin, _is_ymax;
    bool _is_xscl, _is_yscl;

    QPen _functionPen;
    QPen _graphPen;
    QBrush _background;

};

#endif // MAINWINDOW_H
