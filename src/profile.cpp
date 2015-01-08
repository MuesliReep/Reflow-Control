#include "profile.h"

const double EulerConstant = exp(1.0);

Profile::Profile() {
  Profile(false);
}

Profile::Profile(bool fromFile) {

  x = QVector<double> (301);
  y = QVector<double> (301);

}

Profile::~Profile() {

}

void Profile::createProfile() {

  //TODO: Preheat max = +2.5C/sec cooldown max = -5C/sec


  // TODO: new ramp for preheat
  // set target temp
  // then set ramp
  // remaining should be curved off
  preHeatLimit = 160.0;
  // preHeatRamp   = 1.78;
  // preHeatCurve  = 5;

  // new preheat curve : Exponential Decay Toward a Limiting Value  y = Limit − Base e ^(−i / Tau)
  for(int i=0; i<=preHeatTime;i++) {

    y[i]= (preHeatLimit) - preHeatBase * pow(EulerConstant,(double)-i/preHeatTau) ;
  }

  //Set starting temperature
  // y[0] = startTemp;

  // pre heat
  // for(int i=1; i<=preHeatTime;i++) {
  //   y[i] = (double)i * ((preHeatTemp-startTemp) / preHeatTime) + startTemp;
  // }
  // soak
  for(int i=1;i<=soakTime;i++) {
    y[i+preHeatTime] = preHeatTemp + (double)i * ((soakTemp-preHeatTemp) / soakTime);
  }
  // reflow
  for(int i=1;i<=reflowTime;i++) {
    y[i+preHeatTime+soakTime] = soakTemp + (double)i * ((reflowTemp-soakTemp) / reflowTime);
  }
  // cool down
  for(int i=1;i<=cooldownTime;i++) {
    //  y[i+preHeatTime+soakTime+reflowTime] = reflowTemp - (double)i * ((reflowTemp-cooldownTemp) / cooldownTime);
  }
}

//Find the maximum ramp speed in degrees per second
double Profile::findMaxRamp(int start, int end) {

  double maxValue = 0;
  bool positive   = true;

  // Find if the ramp is positive or negative
  if(y[start+1]-y[start] > maxValue)

  for(int i=start+1;i<=end;i++) {
    switch(positive) {
      case true:
        if(y[i]-y[i-1] > maxValue)
          maxValue = y[i]-y[i-1];
        break;
      case false:
        if(y[i]-y[i-1] < maxValue)
          maxValue = y[i]-y[i-1];
        break;
    }
  }

  return maxValue;
}

// Profile saving & loading functions

void Profile::saveToFile() {

  QFile *file = new QFile("C:/Dummy/config.txt");
  if(file->open(QFile::WriteOnly))
  {
    char buffer[50];
    // TODO: fill buffer with valid JSON

    file->write(buffer);
    file->flush();
    file->close();
  }

  delete file;
}

bool Profile::loadFromFile() {

  QFile *file = new QFile("C:/Dummy/profile.txt");
  bool result = false;

  // Check if profile file exists else return
  if( !file->exists() ) {
    qDebug() << "Profile file does not exist";
    return result;
  }

  // Read the profile values from file
  QString line;
  QTextStream in(file);
  while (!in.atEnd()) {
    line = in.readLine(); // TODO: append to line not overwrite
  }

  delete file;

  // Convert QString to JSON object
  // TODO: Create JSON object from QString

  return result;
}

// Getters & Setters

QVector<double> Profile::getX() { return x; }
QVector<double> Profile::getY() { return y; }

double Profile::getPreHeatTemp() { return preHeatTemp; }

void Profile::setPreHeatTime(double PreHeatTime) { preHeatTime = PreHeatTime; }
void Profile::setSoakTime(double SoakTime) { soakTime = SoakTime; }
void Profile::setReflowTime(double ReflowTime) { reflowTime = ReflowTime; }

void Profile::setStartTemp(double StartTemp) { startTemp = StartTemp; }
void Profile::setPreHeatTemp(double PreHeatTemp) { preHeatTemp = PreHeatTemp; }
void Profile::setSoakTemp(double SoakTemp) { soakTemp = SoakTemp; }
void Profile::setReflowTemp(double ReflowTemp) { reflowTemp = ReflowTemp; }

void Profile::setPreHeatTarget(double PreHeatTarget) { preHeatTarget = PreHeatTarget; }
void Profile::setPreHeatRamp(double PreHeatRamp) { preHeatRamp = PreHeatRamp; }

void Profile::setPreHeatBase(double PreHeatBase) { preHeatBase = PreHeatBase; }
void Profile::setPreHeatTau(double PreHeatTau) { preHeatTau = PreHeatTau; }
void Profile::setPreHeatLimit(double PreHeatLimit) { preHeatLimit = PreHeatLimit; }

void Profile::setSoakBase(double SoakBase) { soakBase = SoakBase; }
void Profile::setSoakTau(double SoakTau) { soakTau = SoakTau; }
void Profile::setSoakLimit(double SoakLimit) { soakLimit = SoakLimit; }

void Profile::updateParameters(double PreHeatTime, double PreHeatTemp, double SoakTime,double SoakTemp, double ReflowTime, double ReflowTemp) {

  preHeatTime = PreHeatTime;
  preHeatTemp = PreHeatTemp;
  soakTime    = SoakTime;
  soakTemp    = SoakTemp;
  reflowTime  = ReflowTime;
  reflowTemp  = ReflowTemp;

  // preHeatTarget = PreHeatTarget
  // preHeatRamp   = PreHeatRamp;

  updateParameters();
}

void Profile::updateParameters( ) {

  cooldownTime  = 300 - (preHeatTime + soakTime + reflowTime); // TODO: 300 should be settable

  startTemp     = 21; // TODO: startTemp should be settable
  cooldownTemp  = startTemp;

  createProfile();
}
