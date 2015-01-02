#ifndef PROFILE_H
#define PROFILE_H

#include <stdio.h>
#include <math.h>
#include <cmath>

#include <QVector>

using namespace std;

class Profile
{


public:

  Profile();
  ~Profile();
  QVector<double> getX();
  QVector<double> getY();
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

  void setBase(double Base);
  void setTau(double Tau);

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

  double base;
  double tau;

  void createProfile();

};

#endif // PROFILE_H
