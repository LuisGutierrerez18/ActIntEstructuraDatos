#ifndef VECCOUNT_H
#define VECCOUNT_H

#include "data.h"
#include "stdio.h"
#include <iomanip>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>

class vecCount {
public:
  int count;
  string IpAd;

  vecCount();
  vecCount(string, int count);
  string getIpAd();
  int getCount();
  bool operator<(const vecCount& other) const {
      return count < other.count;
  }
};

vecCount::vecCount(){
   IpAd = "", count = 0; 
}

//Complejidad: O(1)
vecCount::vecCount(string Ip, int count1) {
  count = count1;
  IpAd = Ip;
}

//Complejidad: O(1)
int vecCount::getCount() { return count; }
//Complejidad: O(1)
string vecCount::getIpAd(){ return IpAd; }

#endif


// Clase para el MaxHeap

