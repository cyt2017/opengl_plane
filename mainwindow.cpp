#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer();

    ui->widget->init();
    ui->widget->parent = this;
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimeout()));
    timer->start(20);

    this->installEventFilter(ui->widget);
}

MainWindow::~MainWindow()
{
    if(timer)
    {
        timer->deleteLater();
    }
    delete ui;
}

void MainWindow::onTimeout()
{
    ui->widget->drawImage();
}
