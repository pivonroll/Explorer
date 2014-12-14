#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *widget = new QWidget(this);

    m_layout = new QGridLayout;
    widget->setLayout(m_layout);

    setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
