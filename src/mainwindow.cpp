#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
