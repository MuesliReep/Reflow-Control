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

private:
  QVector<double> x;
  QVector<double> y;
  void createProfile();

};

#endif // PROFILE_H
