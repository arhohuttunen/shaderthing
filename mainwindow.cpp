#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shaderthingopenglwidget.h"

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

void MainWindow::on_pushButton_pressed()
{
    QString shaderSourceCode = ui->plainTextEdit->toPlainText();
    QString output = ui->openGLWidget->compileShader(shaderSourceCode);
    ui->consoleOutput->setPlainText(output);
}
