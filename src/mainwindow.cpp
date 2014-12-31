#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    temperaturePlot = ui->tempPlot;

    profile = Profile();

    setupPlot();

    //Connect signals
    connect(ui->spinBoxPreHeatTemp,SIGNAL(valueChanged(int)),this,SLOT(slotUpdatePreHeatTemp(int)));
    connect(ui->spinBoxPreHeatTime,SIGNAL(valueChanged(int)),this,SLOT(slotUpdatePreHeatTime(int)));
    connect(ui->spinBoxSoakTemp,SIGNAL(valueChanged(int)),this,SLOT(slotUpdateSoakTemp(int)));
    connect(ui->spinBoxSoakTime,SIGNAL(valueChanged(int)),this,SLOT(slotUpdateSoakTime(int)));
    connect(ui->spinBoxReflowTemp,SIGNAL(valueChanged(int)),this,SLOT(slotUpdateReflowTemp(int)));
    connect(ui->spinBoxReflowTime,SIGNAL(valueChanged(int)),this,SLOT(slotUpdateReflowTime(int)));

    connect(ui->spinBoxBase,SIGNAL(valueChanged(double)),this,SLOT(slotUpdateBase(double)));
    connect(ui->spinBoxTau,SIGNAL(valueChanged(double)),this,SLOT(slotUpdateTau(double)));
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

  temperaturePlot->addGraph();
  temperaturePlot->graph(0)->setData(profile.getX(),profile.getY());
  // temperaturePlot->graph(0)->setData(x, y);

  temperaturePlot->xAxis->setLabel("Time (sec)");
  temperaturePlot->yAxis->setLabel("Temparature (C)");

  temperaturePlot->xAxis->setRange(0, 300);
  temperaturePlot->yAxis->setRange(0, 300);

  QCPItemBracket *bracket = new QCPItemBracket(temperaturePlot);
  temperaturePlot->addItem(bracket);
  bracket->left->setCoords(90, 217);
  bracket->right->setCoords(180, 217);
  bracket->setLength(13);

  temperaturePlot->replot();

  //Set profile parameters
  profile.updateParameters((double)ui->spinBoxPreHeatTime->value(),(double)ui->spinBoxPreHeatTemp->value(),(double)ui->spinBoxSoakTime->value(),(double)ui->spinBoxSoakTemp->value(),(double)ui->spinBoxReflowTime->value(),(double)ui->spinBoxReflowTemp->value());

  profile.setBase(ui->spinBoxBase->value());
  profile.setTau(ui->spinBoxTau->value());

  updateProfileParameters();
}

void MainWindow::updateProfileParameters()
{
  profile.updateParameters();
  temperaturePlot->graph(0)->setData(profile.getX(),profile.getY());
  temperaturePlot->replot();
}
