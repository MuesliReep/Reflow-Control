#ifndef PROFILE_H
#define PROFILE_H

#include <stdio.h>
#include <math.h>
#include <cmath>

#include <QVector>
#include <QFile>
#include <QString>
#include <QTextStream>

#include <QJsonDocument>
#include <QJsonObject>

using namespace std;

class Profile
{


public:

  Profile();
  ~Profile();
  Profile(bool fromFile);

  QVector<double> getX();
  QVector<double> getY();

  void saveToFile();
  bool loadFromFile();

  void updateParameters();
  void updateParameters(double PreHeatTime, double PreHeatTemp, double SoakTime,double SoakTemp, double ReflowTime, double ReflowTemp);

  void setPreHeatTime(double PreHeatTime);
  void setSoakTime(double SoakTime);
  void setReflowTime(double ReflowTime);

  void setStartTemp(double StartTemp);
  void setPreHeatTemp(double PreHeatTemp);
  void setSoakTemp(double soakTemp);
  void setReflowTemp(double ReflowTemp);

  void setPreHeatTarget(double PreHeatTarget);
  void setPreHeatRamp(double PreHeatRamp);

  void setPreHeatBase(double PreHeatBase);
  void setPreHeatTau(double PreHeatTau);
  void setPreHeatLimit(double PreHeatLimit);

  void setSoakBase(double SoakBase);
  void setSoakTau(double SoakTau);
  void setSoakLimit(double SoakLimit);

  double getPreHeatTemp();

  double findMaxRamp(int start, int end);

private:

  QVector<double> x;
  QVector<double> y;
  double preHeatTime;
  double soakTime;
  double reflowTime;
  double cooldownTime;

  double startTemp;
  double preHeatTemp;
  double soakTemp;
  double reflowTemp;
  double cooldownTemp;

  double preHeatTarget;
  double preHeatRamp;
  double preHeatCurve;

  double preHeatLimit;
  double preHeatBase;
  double preHeatTau;

  double soakLimit;
  double soakBase;
  double soakTau;

  void createProfile();

};

#endif // PROFILE_H
