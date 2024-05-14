#ifndef DATA_H
#define DATA_H

#include "stdio.h"
#include "vecDivide1.h"
#include "vecDivide2.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Data {
private:
  string ipAd;
  vector<int> ipAdInt;
  long long int ipTotal;
  vector<string> array;
  // Vector que contiene los valores de cada linea del archivo
  // Valor de la fecha y hora en formato epoch segundos (Usar para el
  // ordenamiento de las fechas)

public:
  Data(vector<string>);
  string getIpAd();
  vector<int> getIpAdInt();
  long long int getIpTotal();
};

Data::Data(vector<string> arr) {
  for (int i = 0; i < 4; i++) {
    if (i == 3) {
      string ipAdTemp;
      ipAdTemp = arr[i];
      char sep1 = ':';
      ipAd = vecdivide1(ipAdTemp, sep1);
      char sep2 = '.';
      ipAdInt = vecdivide2(ipAd, sep2);
    }
  }
  int pos3 = pow(256,3);
  int pos2 = pow(256,2);
  int pos1 = pow(256,1);
  int size = ipAdInt.size();
  for (int i = 0; i < size; i++) {
    if (i == 0) {
      ipTotal = ipAdInt[i] * pos3;
    }
    if (i == 1) {
      ipTotal = ipTotal + ipAdInt[i] * pos2;
    }
    if (i == 2) {
      ipTotal = ipTotal + ipAdInt[i] * pos1;
    }
    if (i == 3) {
      ipTotal = ipTotal + ipAdInt[i];
    }
  }
}

string Data::getIpAd() { return ipAd; }

vector<int> Data::getIpAdInt() { return ipAdInt; }

long long int Data::getIpTotal() { return ipTotal; }
#endif // _DATA_H_