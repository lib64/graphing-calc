#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <iostream>
#include <math.h>

const QString MainWindow::LINE_EDIT_RED = "QLineEdit { background: rgb(255, 0, 0, 100);}";
const QString MainWindow::LINE_EDIT_WHITE = "QLineEdit { background: rgb(255, 255, 255);}";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(_scene);

    on_lineEdit_2_textChanged(ui->lineEdit_2->text());
    on_lineEdit_5_textChanged(ui->lineEdit_5->text());
    on_lineEdit_3_textChanged(ui->lineEdit_3->text());
    on_lineEdit_6_textChanged(ui->lineEdit_6->text());
    on_lineEdit_4_textChanged(ui->lineEdit_4->text());
    on_lineEdit_7_textChanged(ui->lineEdit_7->text());

    _size.setWidth(640);
    _size.setHeight(480);

    QImage image(_size.width(),_size.height(),QImage::Format::Format_RGB32);
    image.fill(Qt::white);
    _pixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    _scene->addItem(_pixmapItem);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawOrigin(QPainter &painter)
{
    QPen pen(Qt::gray);
    painter.setPen(pen);


    int width = abs(_xmin - _xmax);
    int height = abs(_ymin - _ymax);
    painter.drawLine(width/2,0,width/2,height);
    painter.drawLine(0,height/2,width,height/2);
}

void MainWindow::graphFunction(Interpreter &interpreter)
{
    QImage image(_size.width(),_size.height(),QImage::Format::Format_RGB32);
    image.fill(Qt::white);
    QPainter painter(&image);

    drawOrigin(painter);

    QPen pen(Qt::red);
    pen.setWidth(2);
    painter.setPen(pen);

    QPoint prev;
    bool first = true;

    int width = abs(_xmin - _xmax);
    int height = abs(_ymin - _ymax);

    for(int x = _xmin; x < _xmax; x++) {

        double yf = interpreter.interpret(x);
        if(isnan(yf)) {
            continue;
        }
        int y = -static_cast<int>(yf);

        if(!first) {
            painter.drawLine(prev, QPoint(x+width/2,y+height/2));
        } else {
            first = false;
        }
        prev.setX(x+width/2);
        prev.setY(y+height/2);
    }

    _pixmapItem->setPixmap(QPixmap::fromImage(image));
}

bool MainWindow::isWindowValid() const
{
    return _is_xmin && _is_xmax &&
           _is_ymin && _is_ymax &&
           _is_xscl && _is_yscl;
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    if(!isWindowValid()) {
        return;
    }
    if(arg1.isEmpty()) {
        return;
    }
    try {
        Lexer lexer(arg1.toStdString());
        vector<LexerToken> tokens = lexer.lex();

        Parser parser(tokens);
        AstNode *root = parser.parseMain();

        Interpreter interpreter(root);
        graphFunction(interpreter);

        ui->lineEdit->setStyleSheet(LINE_EDIT_WHITE);
    } catch (...) {
        QImage image(_size.width(),_size.height(),QImage::Format::Format_RGB32);
        image.fill(Qt::white);
        _pixmapItem->setPixmap(QPixmap::fromImage(image));
        ui->lineEdit->setStyleSheet(LINE_EDIT_RED);
    }
}

//xmin
void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    bool ok;
    _xmin = arg1.toInt(&ok);
    if(!ok) {
        _is_xmin = false;
        ui->lineEdit_2->setStyleSheet(LINE_EDIT_RED);
    } else {
        _is_xmin = true;
        ui->lineEdit_2->setStyleSheet(LINE_EDIT_WHITE);
    }
}
//ymin
void MainWindow::on_lineEdit_5_textChanged(const QString &arg1)
{
    bool ok;
    _ymin = arg1.toInt(&ok);
    if(!ok) {
        _is_ymin = false;
        ui->lineEdit_5->setStyleSheet(LINE_EDIT_RED);
    } else {
        _is_ymin = true;
        ui->lineEdit_5->setStyleSheet(LINE_EDIT_WHITE);
    }
    on_lineEdit_textChanged(ui->lineEdit->text());
}
//xmax
void MainWindow::on_lineEdit_3_textChanged(const QString &arg1)
{
    bool ok;
    _xmax = arg1.toInt(&ok);
    if(!ok) {
        _is_xmax = false;
        ui->lineEdit_3->setStyleSheet(LINE_EDIT_RED);
    } else {
        _is_xmax = true;
        ui->lineEdit_3->setStyleSheet(LINE_EDIT_WHITE);
    }
    on_lineEdit_textChanged(ui->lineEdit->text());
}
//ymax
void MainWindow::on_lineEdit_6_textChanged(const QString &arg1)
{
    bool ok;
    _ymax = arg1.toInt(&ok);
    if(!ok) {
        _is_ymax = false;
        ui->lineEdit_6->setStyleSheet(LINE_EDIT_RED);
    } else {
        _is_ymax = true;
        ui->lineEdit_6->setStyleSheet(LINE_EDIT_WHITE);
    }
    on_lineEdit_textChanged(ui->lineEdit->text());
}
//xscl
void MainWindow::on_lineEdit_4_textChanged(const QString &arg1)
{
    bool ok;
    _xscl = arg1.toInt(&ok);
    if(!ok) {
        _is_xscl = false;
        ui->lineEdit_4->setStyleSheet(LINE_EDIT_RED);
    } else {
        _is_xscl = true;
        ui->lineEdit_4->setStyleSheet(LINE_EDIT_WHITE);
    }
    on_lineEdit_textChanged(ui->lineEdit->text());
}
//yscl
void MainWindow::on_lineEdit_7_textChanged(const QString &arg1)
{
    bool ok;
    _yscl = arg1.toInt(&ok);
    if(!ok) {
        _is_yscl = false;
        ui->lineEdit_7->setStyleSheet(LINE_EDIT_RED);
    } else {
        _is_yscl = true;
        ui->lineEdit_7->setStyleSheet(LINE_EDIT_WHITE);
    }
    on_lineEdit_textChanged(ui->lineEdit->text());
}
