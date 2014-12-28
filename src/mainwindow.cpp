#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Setup Temperature plot

    QVector<double> x(301), y(101);
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }

    ui->tempPlot->addGraph();
    ui->tempPlot->graph(0)->setData(x,y);

    ui->tempPlot->xAxis->setLabel("Time (s)");
    ui->tempPlot->yAxis->setLabel("Temparature (C)");

    ui->tempPlot->xAxis->setRange(-1, 1);
    ui->tempPlot->yAxis->setRange(0, 1);
    ui->tempPlot->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}
