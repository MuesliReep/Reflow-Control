#ifndef PROFILE_H
#define PROFILE_H

#include <stdio.h>

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

  void setPreHeatTime(double PreHeatTime);
  void setSoakTime(double SoakTime);
  void setReflowTime(double ReflowTime);

  void setStartTemp(double StartTemp);
  void setPreHeatTemp(double PreHeatTemp);
  void setSoakTemp(double soakTemp);
  void setReflowTemp(double ReflowTemp);


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

  void createProfile();

};

#endif // PROFILE_H
