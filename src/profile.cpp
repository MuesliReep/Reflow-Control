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

  //TODO: Preheat max = +2.5C/sec cooldown max = -5C/sec


  // TODO: new ramp for preheat
  // set target temp
  // then set ramp
  // remaining should be curved off
  preHeatTarget = 160.0;
  preHeatRamp   = 1.78;
  preHeatCurve  = 5;

  // new preheat curve
  for(int i=1; i<preHeatTime;i++) {
    y[i]= pow((double)i,1.0/2.0) + startTemp;
  }

  //Set starting temperature
  y[0] = startTemp;

  // pre heat
  // for(int i=1; i<preHeatTime;i++) {
  //   y[i] = (double)i * ((preHeatTemp-startTemp) / preHeatTime) + startTemp;
  // }
  // soak
  for(int i=1;i<soakTime;i++) {
    y[i+preHeatTime] = preHeatTemp + (double)i * ((soakTemp-preHeatTemp) / soakTime);
  }
  // reflow
  for(int i=1;i<reflowTime;i++) {
    y[i+preHeatTime+soakTime] = soakTemp + (double)i * ((reflowTemp-soakTemp) / reflowTime);
  }
  // cool down
  for(int i=1;i<cooldownTime;i++) {
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

void Profile::setPreHeatTarget(double PreHeatTarget) { preHeatTarget = PreHeatTarget; updateParameters(); }
void Profile::setPreHeatRamp(double PreHeatRamp) { preHeatRamp = PreHeatRamp; updateParameters(); }

void Profile::updateParameters(double PreHeatTime, double PreHeatTemp, double SoakTime,double SoakTemp, double ReflowTime, double ReflowTemp) {

  preHeatTime = PreHeatTime;
  preHeatTemp = PreHeatTemp;
  soakTime    = SoakTime;
  soakTemp    = SoakTemp;
  reflowTime  = ReflowTime;
  reflowTemp  = ReflowTemp;

  // preHeatTarget = PreHeatTarget;
  // preHeatRamp   = PreHeatRamp;

  updateParameters();
}

void Profile::updateParameters( ) {

  cooldownTime  = 300 - (preHeatTime + soakTime + reflowTime); // TODO: 300 should be settable

  startTemp     = 21; // TODO: startTemp should be settable
  cooldownTemp  = startTemp;

  createProfile();
}
