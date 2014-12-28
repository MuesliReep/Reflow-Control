#include "profile.h"

Profile::Profile() {

  x = QVector<double> (301);
  y = QVector<double> (301);
  createProfile();
}

Profile::~Profile() {

}

QVector<double> Profile::getX() {
  return x;
}

QVector<double> Profile::getY() {
  return y;
}

void Profile::createProfile() {

  for(int i=0; i<x.size(); i++) {
    x[i] = i;
    y[i] = i;

  }

  // pre heat
  // soak
  // reflow
  // cool down
}
