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


    /*
    QPainter painter(&image);
    QPen pen(Qt::white);
    pen.setWidth(5);
    painter.setPen(pen);
    painter.drawLine(0,0,100,100);
    */

    QImage image(640,480,QImage::Format::Format_RGB32);
    image.fill(Qt::white);
    _pixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    _scene->addItem(_pixmapItem);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::graphFunction(double (Interpreter::*function)(double), Interpreter &interpreter)
{
    std::cout << (interpreter.*function)(10.0) << std::endl;
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    try {
        Lexer lexer(arg1.toStdString());
        vector<LexerToken> tokens = lexer.lex();

        Parser parser(tokens);
        AstNode *root = parser.parseMain();

        Interpreter interpreter(root);
        graphFunction(&Interpreter::interpret, interpreter);

    } catch (...) {

    }
}









