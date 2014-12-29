#include "profile.h"

Profile::Profile() {

  x = QVector<double> (301);
  y = QVector<double> (301);

}

Profile::~Profile() {

}

void Profile::createProfile() {

  for(int i=0; i<x.size(); i++) {
    x[i] = i;
    // y[i] = i;

  }

  // pre heat
  for(int i=0; i<preHeatTime;i++) {
    y[i] = (double)i * ((preHeatTemp-startTemp) / preHeatTime) + startTemp;
  }
  // soak
  for(int i=0;i<soakTime;i++) {
    y[i+preHeatTime] = preHeatTemp + (double)i * ((soakTemp-preHeatTemp) / soakTime);
  }
  // reflow
  for(int i=0;i<reflowTime;i++) {
    y[i+preHeatTime+soakTime] = soakTemp + (double)i * ((reflowTemp-soakTemp) / reflowTime);
  }
  // cool down
  for(int i=0;i<cooldownTime;i++) {
    //  y[i+preHeatTime+soakTime+reflowTime] = reflowTemp - (double)i * ((reflowTemp-cooldownTemp) / cooldownTime);
  }
}

// Getters & Setters

QVector<double> Profile::getX() { return x; }
QVector<double> Profile::getY() { return y; }

void Profile::setPreHeatTime(double PreHeatTime) { preHeatTime = PreHeatTime; updateParameters(); }
void Profile::setSoakTime(double SoakTime) { soakTime = SoakTime; updateParameters(); }
void Profile::setReflowTime(double ReflowTime) { reflowTime = ReflowTime; updateParameters(); }

void Profile::setStartTemp(double StartTemp) { startTemp = StartTemp; updateParameters(); }
void Profile::setPreHeatTemp(double PreHeatTemp) { preHeatTemp = PreHeatTemp; updateParameters(); }
void Profile::setSoakTemp(double SoakTemp) { soakTemp = SoakTemp; updateParameters(); }
void Profile::setReflowTemp(double ReflowTemp) { reflowTemp = ReflowTemp; updateParameters(); }

void Profile::updateParameters() {

  cooldownTime  = 300 - preHeatTime + soakTime + reflowTime;

  startTemp     = 21;
  cooldownTemp  = startTemp;

  createProfile();
}
