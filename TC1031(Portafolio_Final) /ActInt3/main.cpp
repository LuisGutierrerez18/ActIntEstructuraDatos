/*
Integrantes:
  Moisés Abel Díaz Nava. A01799628
  Luis Enrique Gutierrez Mendioroz. A00837481

Actividad integradora #3 - Estructuras de datos jerarquicas
Compilación para ejecutar:
g++ -O3 -Wall -o main *.cpp
ejecutar:
./main
*/

#include "DLinkedList.h"
#include "data.h"
#include "maxPriorityQueue.h"
#include "vecCount.h"
#include "vecDivide.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  DLinkedList<Data> vec2;
  string inicioVec;
  string finVec;
  ifstream archivo("bitacoraHeap-1.txt");
  for (int i = 0; i < 16807; i++) {
    char arr[200];
    // Input using the getline function.
    // Aqui se coloca la entrada de la bitacora
    archivo.getline(arr, 200);
    // se convierte en objeto data
    Data vec = vecdivide(arr);
    // se coloca en un vector de tipo data
    vec2.addLast(vec);
  }

  archivo.close();
  vec2.heapSort();

  
  std::ofstream archivoSalida("bitacora_ordenada.txt");
  std::streambuf *coutbuf = std::cout.rdbuf();
  std::cout.rdbuf(archivoSalida.rdbuf());
  
  for (int i = 0; i < 16807; i++) {
    cout << vec2.getIpAd(i) << endl;
  }

  archivoSalida.close();

  vector<vecCount> ipAccess;

  MaxPriorityQueue<vecCount> heapAccess;

  int j = 0;
  int i = 0;
  int k = 0;

  while (j < 16807) {
    string stringTL = vec2.getIpAd(i);
    int count = 0;
    string stringTL2 = vec2.getIpAd(j);
    while (stringTL == stringTL2 && j < 16807) {
      stringTL2 = vec2.getIpAd(j);
      count++;
      j++;
      cout << j << endl;
    }
    vecCount ipAccess1(vec2.getIpAd(i), count);
    count = 0;
    ipAccess.push_back(ipAccess1);
    cout << ipAccess[k].getIpAd() << " " << ipAccess[k].getCount() << endl;
    k++;
    i = j;
    if (i == vec2.getNumElements()) {
      i = i - 1;
    }
  }

  int n = ipAccess.size();
  cout << n << endl;

  for (int i = 0; i < n; i++) {
    heapAccess.enqueue(ipAccess[i]);
  }

  
  std::ofstream archivoSalida2("ips_con_mayor_acceso.txt");
  std::streambuf *coutbuf2 = std::cout.rdbuf();
  std::cout.rdbuf(archivoSalida2.rdbuf());
  
  heapAccess.print10();

  archivoSalida2.close();

  return 0;
}