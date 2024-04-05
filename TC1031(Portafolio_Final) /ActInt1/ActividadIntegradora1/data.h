#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

class Data {
private:
  string mes;
  string mesInt;
  int dia;
  string horaMinSec;
  string ipAd;
  string ErrMessage;
  string fechaHoraString;

// Valores extraidos en forma de string o int


  vector<string> array;
// Vector que contiene los valores de cada linea del archivo
  string fechaHora;
// Valor de la fecha y hora en formato string
  chrono::system_clock::time_point epochSecond;
  int timeInt;
// Valor de la fecha y hora en formato epoch segundos (Usar para el ordenamiento de las fechas)

public:
  Data(vector<string>);
  string getMes();
  int getDia();
  string getErrMessage();
  string getHoraMinSec();
  string getIpAd();
  string getFechaHora();
  string getFechaHoraString();
  int getTimeInt();
  chrono::system_clock::time_point getEpochSecond();
};