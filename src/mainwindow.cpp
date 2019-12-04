#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QColorDialog>
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

    _functionPen = QPen(Qt::red);
    _graphPen = QPen(Qt::gray);
    _background = QBrush(Qt::white);

    pushButton_setPallete();
    pushButton_2_setPallete();
    pushButton_3_setPallete();

    _pixmapItem = new QGraphicsPixmapItem();
    _scene->addItem(_pixmapItem);

    updatePixmap();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawOrigin(QPainter &painter)
{
    painter.setPen(_graphPen);
    painter.drawLine(getWidth()/2,0,getWidth()/2,getHeight());
    painter.drawLine(0,getHeight()/2,getWidth(),getHeight()/2);
}

void MainWindow::graphFunction(Interpreter &interpreter)
{
    QImage image(getWidth(),getHeight(),QImage::Format::Format_RGB32);
    image.fill(_background.color());
    QPainter painter(&image);

    drawOrigin(painter);

    painter.setPen(_functionPen);

    QPoint prev;
    bool first = true;

    for(int x = _xmin; x < _xmax; x++) {

        double yf = interpreter.interpret(x);
        if(isnan(yf)) {
            continue;
        }
        int y = -static_cast<int>(yf);

        if(!first) {
            painter.drawLine(prev, QPoint(x+getWidth()/2,y+getHeight()/2));
        } else {
            first = false;
        }
        prev.setX(x+getWidth()/2);
        prev.setY(y+getHeight()/2);
    }

    _pixmapItem->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::updatePixmap()
{
    QImage image(getWidth(),getHeight(),QImage::Format::Format_RGB32);
    image.fill(_background.color());
    QPainter painter(&image);
    drawOrigin(painter);
    _pixmapItem->setPixmap(QPixmap::fromImage(image));
}

bool MainWindow::isWindowValid() const
{
    return _is_xmin && _is_xmax &&
           _is_ymin && _is_ymax &&
            _is_xscl && _is_yscl;
}

int MainWindow::getWidth()
{
    return abs(_xmin - _xmax);
}

int MainWindow::getHeight()
{
    return abs(_ymin - _ymax);
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

        ui->graphicsView->centerOn(getWidth()/2,getHeight()/2);

        ui->lineEdit->setStyleSheet(LINE_EDIT_WHITE);
    } catch (...) {
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
    on_lineEdit_textChanged(ui->lineEdit->text());
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

void MainWindow::on_pushButton_clicked()
{
    _background = QColorDialog::getColor();
    updatePixmap();
    MainWindow::on_lineEdit_textChanged(ui->lineEdit->text());
    pushButton_setPallete();
}

void MainWindow::on_pushButton_2_clicked()
{
    _functionPen = QColorDialog::getColor();
    updatePixmap();
    MainWindow::on_lineEdit_textChanged(ui->lineEdit->text());
    pushButton_2_setPallete();
}

void MainWindow::on_pushButton_3_clicked()
{
    _graphPen = QColorDialog::getColor();
    updatePixmap();
    MainWindow::on_lineEdit_textChanged(ui->lineEdit->text());
    pushButton_3_setPallete();
}

void MainWindow::pushButton_setPallete()
{
    QPalette pal = ui->pushButton->palette();
    pal.setColor(QPalette::Button, _background.color());
    ui->pushButton->setAutoFillBackground(true);
    ui->pushButton->setPalette(pal);
    ui->pushButton->update();
}

void MainWindow::pushButton_2_setPallete()
{
    QPalette pal = ui->pushButton_2->palette();
    pal.setColor(QPalette::Button, _functionPen.color());
    ui->pushButton_2->setAutoFillBackground(true);
    ui->pushButton_2->setPalette(pal);
    ui->pushButton_2->update();
}

void MainWindow::pushButton_3_setPallete()
{
    QPalette pal = ui->pushButton_3->palette();
    pal.setColor(QPalette::Button, _graphPen.color());
    ui->pushButton_3->setAutoFillBackground(true);
    ui->pushButton_3->setPalette(pal);
    ui->pushButton_3->update();
}
