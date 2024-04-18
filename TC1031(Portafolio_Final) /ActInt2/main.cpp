/*
Integrantes:
  Moisés Abel Díaz Nava. A01799628
  Luis Enrique Gutierrez Mendioroz. A00837481
  Alan Corona Lopez A01642342

Actividad integradora #1 - Conceptos básicos y algoritmos fundamentales
Compilación para ejecutar:
g++ -O3 -Wall -o main *.cpp
ejecutar:
./main

*/

#include "DLinkedList.h"
#include "data.h"
#include "vecDivide.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main() {
  DLinkedList<Data> vec2;
  DLLNode<Data> *p;
  string inicioVec;
  string finVec;
  ifstream archivo("bitacora-1.txt");
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
  
  cout << "Numero de elementos en la lista: " << vec2.getNumElements() << endl;
  int n = vec2.getNumElements();
  int metodo;
  
  
  cout << "Ingrese la primera fecha de busqueda en formato MMM DD HH:MM:SS ";
  getline(cin, inicioVec);
  cout << inicioVec;
  cout << endl;
  
  
  cout << "Ingrese la segunda fecha de busqueda en formato MMM DD HH:MM:SS ";
  getline(cin, finVec);
  cout << finVec;
  cout << endl;
  
  cout << "Ingrese el metodo a utilizar, 1: quicksort, 2: mergesort. ";
  cin >> metodo;
  cout << metodo;
  cout << endl;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  /*
  casoPrueba == 1
    inicioVec Jun 01 00:22:36
    finVec = Jun 01 08:23:57
  casoPrueba == 2
    inicioVec = "Oct 26 13:37:41";
    finVec = "Oct 30 23:48:41";
  casoPrueba == 3
    inicioVec = "Oct 20 23:45:19";
    finVec = "Oct 21 00:29:14";
  */
  auto startTime = std::chrono::high_resolution_clock::now();
  if (metodo == 1){
    auto startTime = std::chrono::high_resolution_clock::now();
    vec2.qSort();
  }  

  if (metodo == 2){
    auto startTime = std::chrono::high_resolution_clock::now();
    vec2.mergeSort();
  }

  std::ofstream archivoSalida("bitacora_ordenada.txt");
  std::streambuf *coutbuf = std::cout.rdbuf();
  std::cout.rdbuf(archivoSalida.rdbuf());


  DLLNode<Data> *lower = vec2.lowerLim(inicioVec);
  DLLNode<Data> *upper = vec2.lowerLim(finVec);
  vec2.printInterval(lower, upper);

  auto endTime = std::chrono::high_resolution_clock::now();
  auto totalTime = endTime - startTime;
  cout << "Tiempo de ejecución en ms: "
       << totalTime / std::chrono::milliseconds(1) << endl;

  cout << endl;
  cout << "Bitacora ordenada completa" << endl;
  cout << endl;

  for (int i = 0; i < n; i++){
    cout << vec2.getFechaHoraString(i) << " " << vec2.getIpAd(i) << " " << vec2.getErrMessage(i) << endl;
  }
  archivoSalida.close();
  
  return 0;
}