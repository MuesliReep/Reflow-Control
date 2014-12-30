#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QCustomPlot.h"

#include "profile.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QCustomPlot *temperaturePlot;
    Profile profile;

    void setupPlot();
    void updateProfileParameters();

private slots:

    void slotUpdatePreHeatTime(int value) { profile.setPreHeatTime((double)value); updateProfileParameters();}
    void slotUpdatePreHeatTemp(int value) { profile.setPreHeatTemp((double)value); updateProfileParameters();}
    void slotUpdateSoakTime(int value) { profile.setSoakTime((double)value); updateProfileParameters();}
    void slotUpdateSoakTemp(int value) { profile.setSoakTemp((double)value); updateProfileParameters();}
    void slotUpdateReflowTemp(int value) { profile.setReflowTemp((double)value); updateProfileParameters();}
    void slotUpdateReflowTime(int value) { profile.setReflowTime((double)value); updateProfileParameters();}

    // void slotUpdatePreHeatTime(int value) { profile.setPreHeatTime((double)value); }
    // void slotUpdatePreHeatTemp(int value) { profile.setPreHeatTemp((double)value); }
    // void slotUpdateSoakTime(int value) { profile.setSoakTime((double)value); }
    // void slotUpdateSoakTemp(int value) { profile.setSoakTemp((double)value); }
    // void slotUpdateReflowTemp(int value) { profile.setReflowTemp((double)value); }
    // void slotUpdateReflowTime(int value) { profile.setReflowTime((double)value); }
};

#endif // MAINWINDOW_H
