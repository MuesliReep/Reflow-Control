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
    connect(ui->spinBoxLimit,SIGNAL(valueChanged(double)),this,SLOT(slotUpdateLimit(double)));
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

  stageBracket = new QCPItemBracket(temperaturePlot);
  temperaturePlot->addItem(stageBracket);
  stageBracket->left->setCoords(90, 217);
  stageBracket->right->setCoords(180, 217);
  stageBracket->setLength(13);

  labelMaxRamp = new QCPItemText(temperaturePlot);
  temperaturePlot->addItem(labelMaxRamp);
  labelMaxRamp->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
  labelMaxRamp->position->setType(QCPItemPosition::ptAxisRectRatio);
  labelMaxRamp->position->setCoords(0.5, 0); // place position at center/top of axis rect
  labelMaxRamp->setFont(QFont(font().family(), 16)); // make font a bit larger
  labelMaxRamp->setPen(QPen(Qt::black)); // show black border around text

  labelStartTemp = new QCPItemText(temperaturePlot);
  temperaturePlot->addItem(labelStartTemp);
  labelStartTemp->setFont(QFont(font().family(), 16));

  labelEndTemp = new QCPItemText(temperaturePlot);
  temperaturePlot->addItem(labelEndTemp);
  labelEndTemp->setFont(QFont(font().family(), 16));

  // Add start temperature arrow
  startArrow = new QCPItemCurve(temperaturePlot);
  temperaturePlot->addItem(startArrow);
  startArrow->setHead(QCPLineEnding::esSpikeArrow);

  // Add end temperature arrow
  endArrow = new QCPItemCurve(temperaturePlot);
  temperaturePlot->addItem(endArrow);
  endArrow->setHead(QCPLineEnding::esSpikeArrow);

  temperaturePlot->replot();

  //Set profile parameters
  profile.updateParameters((double)ui->spinBoxPreHeatTime->value(),(double)ui->spinBoxPreHeatTemp->value(),(double)ui->spinBoxSoakTime->value(),(double)ui->spinBoxSoakTemp->value(),(double)ui->spinBoxReflowTime->value(),(double)ui->spinBoxReflowTemp->value());

  profile.setPreHeatBase(ui->spinBoxBase->value());
  profile.setPreHeatTau(ui->spinBoxTau->value());

  updateProfileParameters();
}

void MainWindow::updateProfileParameters()
{
  profile.updateParameters();
  temperaturePlot->graph(0)->setData(profile.getX(),profile.getY());

  // update heating stage bracket
  stageBracket->left->setCoords(0, profile.getY()[90]+10);
  stageBracket->right->setCoords(90, profile.getY()[90]+10);
  stageBracket->setLength(13);

  // update starting arrow
  startArrow->start->setCoords(20, 20);
  startArrow->startDir->setCoords(15, 20);
  startArrow->endDir->setCoords(10, profile.getY()[0]);
  startArrow->end->setCoords(5, profile.getY()[0]);

  // update end arrow
  endArrow->start->setCoords(120, 100);
  endArrow->startDir->setCoords(110, 100);
  endArrow->endDir->setCoords(90, profile.getY()[90]);
  endArrow->end->setCoords(90, profile.getY()[90]);

  // Update plot labels
  char buffer [50];

  // update max ramp text label
  double maxRamp = profile.findMaxRamp(0,90);
  sprintf(buffer, "Ramp: %1.1f C/Sec",maxRamp);
  labelMaxRamp->setText(buffer);

  // update start temperature label
  sprintf(buffer, "Ramp: %1.1f C",profile.getY()[90]);
  labelStartTemp->setText(buffer);

  // update end temperature label
  sprintf(buffer, "%1.1f C",profile.getY()[0]);
  labelEndTemp->setText(buffer);

  // TODO: set X & Y plot ranges to profile values

  temperaturePlot->replot();
}
