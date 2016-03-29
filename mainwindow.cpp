#include <iostream>
#include <QFileDialog>
#include <QTextStream>
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

void MainWindow::on_runButton_pressed()
{
    QString shaderSourceCode = ui->plainTextEdit->toPlainText();
    QString output = ui->openGLWidget->compileShader(shaderSourceCode);
    ui->consoleOutput->setPlainText(output);
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName();

    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QByteArray contents = file.readAll();

    ui->plainTextEdit->setPlainText(contents);

    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    QString filename = QFileDialog::getSaveFileName();

    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QString contents = ui->plainTextEdit->toPlainText();

    QTextStream out(&file);
    out << contents;

    file.close();
}
