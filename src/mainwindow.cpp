#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "profile.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupPlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupPlot() {
  //Setup Temperature plot

  // QVector<double> x(301), y(301);
  // for (int i=0; i<101; ++i)
  // {
  //   x[i] = i; // x goes from -1 to 1
  //   y[i] = x[i]*x[i]; // let's plot a quadratic function
  // }


  Profile profile = Profile();


  ui->tempPlot->addGraph();
  ui->tempPlot->graph(0)->setData(profile.getX(),profile.getY());
  // ui->tempPlot->graph(0)->setData(x, y);

  ui->tempPlot->xAxis->setLabel("Time (s)");
  ui->tempPlot->yAxis->setLabel("Temparature (C)");

  ui->tempPlot->xAxis->setRange(0, 300);
  ui->tempPlot->yAxis->setRange(0, 300);
  ui->tempPlot->replot();
}
