#include "data.h"
#include "stdio.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;


//Codigo para pasar un string a un timepoint para la medición del tiempo obtenido de: https://www.geeksforgeeks.org/date-and-time-parsing-in-cpp/
chrono::system_clock::time_point GFG(const string &datetimeString,
                                     const string &format) {
  tm tmStruct = {};
  istringstream ss(datetimeString);
  ss >> get_time(&tmStruct, format.c_str());
  return chrono::system_clock::from_time_t(mktime(&tmStruct));
}

Data::Data(vector<string> arr) {
  for (int i = 0; i < 4; i++) {
    if (i == 0) {
      mes = arr[i];
      fechaHoraString.append(mes + " ");
      if (mes == "Jun"){
        fechaHora.append("06");
        fechaHora.append(" ");
      }
      if (mes == "Jul"){
        fechaHora.append("07");
        fechaHora.append(" ");
      }
      if (mes == "Aug"){
        fechaHora.append("08");
        fechaHora.append(" ");
      }
      if (mes == "Sep"){
        fechaHora.append("09");
        fechaHora.append(" ");
      }
      if (mes == "Oct"){
        fechaHora.append("10");
        fechaHora.append(" ");
      }
    }
    if (i == 1) {
      fechaHora.append(arr[i] + " ");
      fechaHoraString.append(arr[i] + " ");
      int diaint = stoi(arr[i]);
      dia = diaint;
    }
    if (i == 2) {
      horaMinSec = arr[i];
      fechaHora.append(arr[i]);
      fechaHoraString.append(arr[i]);
    }
    if (i == 3) {
      ipAd = arr[i];
    }
  }
  string ErrorMessage;
  int n = arr.size();
  for (int i = 4; i < n; i++) {
    string errorMessage = arr[i];
    ErrorMessage = ErrorMessage.append(" ");
    ErrorMessage = ErrorMessage.append(errorMessage);
  }
  ErrMessage = ErrorMessage;
  const string format = "%m %d %H:%M:%S";
  chrono::system_clock::time_point parsedTime = GFG(fechaHora, format);
  epochSecond = parsedTime;
  auto duration = std::chrono::time_point_cast<std::chrono::seconds>(parsedTime).time_since_epoch();
  long long intTime = duration.count();
  timeInt = intTime;
}

string Data::getMes() { return mes; }

int Data::getDia() { return dia; }

string Data::getErrMessage() { return ErrMessage; }

string Data::getHoraMinSec() { return horaMinSec; }

string Data::getIpAd() { return ipAd; }

string Data::getFechaHora() { return fechaHora; }

int Data::getTimeInt() { return timeInt;}

string Data::getFechaHoraString() {return fechaHoraString; }

chrono::system_clock::time_point Data::getEpochSecond() { return epochSecond; }

