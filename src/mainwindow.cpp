#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(_scene);

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

void MainWindow::graphFunction(Interpreter &interpreter)
{
    QImage image(_size.width(),_size.height(),QImage::Format::Format_RGB32);
    image.fill(Qt::white);
    QPainter painter(&image);

    QPoint prev;

    bool first = true;

    for(int x = 0; x < _size.width(); x++) {

        int y = interpreter.interpret(x);

        if(!first) {
            painter.drawLine(prev, QPoint(x,y));
        } else {
            first = false;
        }

        prev.setX(x);
        prev.setY(y);
    }

    _pixmapItem->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    try {
        Lexer lexer(arg1.toStdString());
        vector<LexerToken> tokens = lexer.lex();

        Parser parser(tokens);
        AstNode *root = parser.parseMain();

        Interpreter interpreter(root);
        graphFunction(interpreter);

    } catch (...) {
        QImage image(_size.width(),_size.height(),QImage::Format::Format_RGB32);
        image.fill(Qt::white);
        _pixmapItem->setPixmap(QPixmap::fromImage(image));
    }
}









