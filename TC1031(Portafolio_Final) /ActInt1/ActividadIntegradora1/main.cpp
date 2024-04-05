/*
Integrantes:
  Moisés Abel Díaz Nava. A01799628
  Luis Enrique Gutierrez Mendioroz. A00837481
  
Actividad integradora #1 - Conceptos básicos y algoritmos fundamentales
Compilación para ejecutar:
g++ -O3 -Wall -o main *.cpp
ejecutar:
./main <TestCasesActInt/Testcase1-1.txt> bitacora_ordenada.txt
./main <TestCasesActInt/Testcase1-2.txt> bitacora_ordenada.txt
./main <TestCasesActInt/Testcase1-3.txt> bitacora_ordenada.txt
./main <TestCasesActInt/Testcase2-1.txt> bitacora_ordenada.txt
./main <TestCasesActInt/Testcase2-2.txt> bitacora_ordenada.txt
./main <TestCasesActInt/Testcase2-3.txt> bitacora_ordenada.txt
./main <TestCasesActInt/Testcase3-1.txt> bitacora_ordenada.txt
./main <TestCasesActInt/Testcase3-2.txt> bitacora_ordenada.txt
./main <TestCasesActInt/Testcase3-3.txt> bitacora_ordenada.txt
para cada caso de prueba y metodo de ordenamiento
la información se guarda en un archivo llamado bitacora_ordenada.txt, empezando por el resultado de la busqueda realizada y seguido de todos los registros ordenados.
*/

#include "data.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int comparaciones = 0;
int swaps = 0;

bool compararPorAtributo(Data &obj1, Data &obj2) {
  comparaciones++;
  return obj1.getTimeInt() < obj2.getTimeInt();
}

void bubbleSort(vector<Data> &vec, bool ascendente) {
  int n = vec.size();
  for (int i = 0; i < n - 1; ++i) {
    comparaciones++;
    for (int j = 0; j < n - i - 1; ++j) {
      if ((ascendente && vec[j].getTimeInt() > vec[j + 1].getTimeInt()) ||
          (!ascendente && vec[j].getTimeInt() < vec[j + 1].getTimeInt())) {
        swap(vec[j], vec[j + 1]);
        swaps++;
      }
    }
  }
}

int partition(vector<Data> &vec, int low, int high) {
  int pivot = vec[high].getTimeInt();
  int i = low - 1;
  for (int j = low; j < high; ++j) {
    comparaciones++;
    if (vec[j].getTimeInt() < pivot) {
      ++i;
      swap(vec[i], vec[j]);
    }
  }
  swap(vec[i + 1], vec[high]);
  swaps++;
  return i + 1;
}

// Función recursiva de QuickSort
void quickSort(vector<Data> &vec, int low, int high) {
  if (low < high) {
    int pi = partition(vec, low, high);
    quickSort(vec, low, pi - 1);
    quickSort(vec, pi + 1, high);
  }
}

//Algoritmo de busqueda
void searchAlgorithm(vector<Data> vec, string inicio, string fin) {
  int n = vec.size();
  int iniEsta = 0;
  int finEsta = 0;
  for (int i = 0; i < n; i++) {
    if (vec[i].getFechaHoraString() == inicio) {
      iniEsta =1;
      for (int j = i; j < n; j++) {
        cout << vec[j].getFechaHoraString() << " " << vec[j].getIpAd() << " "
             << vec[j].getErrMessage() << endl;
        if (vec[j].getFechaHoraString() == fin) {
          finEsta = 1;
          cout << "Numero de salidas de la busqueda: " << j - i + 1 << endl;
          return;
        }
      }
      if(finEsta == 0){
        cout << "No se encontro la fecha de fin" << endl;
      }
    }
    else if(iniEsta == 0){
      cout << "No se encontro el inicio de la busqueda" << endl;
    }
  }
}

// Codigo base de la función "vecDivide" obtenido de
// https://favtutor.com/blogs/split-string-cpp
Data vecdivide(char arr[]) {
  char separator = ' ';
  int i = 0;
  int j = 0;
  vector<string> dataList;
  // String temporal para dividir al string
  string s;
  while (arr[i] != '\0') {
    if (arr[i] != separator) {
      // Append the char to the temp string.
      s += arr[i];
    } else {
      dataList.push_back(s);
      // cout << ErrList[j] << " ";
      j++;
      s.clear();
    }
    i++;
  }
  dataList.push_back(s);
  // cada dato individual de la bitacora (Dia, mes, hora, ip, error) es guardado
  // en un obejto de la clase data, donde se le asignara el valor de cada uno a
  // los atributos de data
  Data ErrorList(dataList);
  return ErrorList;
}

int main() {
  vector<Data> vec2;
  
  for (int i = 0; i < 16807; i++) {
    char arr[200];
    // Input using the getline function.
    // Aqui se coloca la entrada de la bitacora
    cin.getline(arr, 200);
    // se convierte en objeto data
    Data vec = vecdivide(arr);
    // se coloca en un vector de tipo data
    vec2.push_back(vec);
  }

  int metodo;
  int casoPrueba;
  cout << "Ingrese el metodo de ordenamiento a utilizar: 1 = función Sort de "
          "C++, 2 = bubbleSort, 3 = quicksort. ";
  cin >> metodo;
  cout << metodo << endl;
  cout << "Ingrese el caso de prueba a utilizar: 1, 2, 3. ";
  cin >> casoPrueba;
  cout << casoPrueba << endl;
  string inicioVec;
  string finVec;

  if (casoPrueba == 1) {
    inicioVec = "Jun 01 00:22:36";
    finVec = "Jun 01 08:23:57";
  }

  else if (casoPrueba == 2) {
    inicioVec = "Oct 26 13:37:41";
    finVec = "Oct 30 23:48:41";
  }

  else if (casoPrueba == 3) {
    inicioVec = "Oct 20 23:45:19";
    finVec = "Oct 21 00:29:14";
  }

  if (metodo == 1) {
    auto startTime = std::chrono::high_resolution_clock::now();
    sort(vec2.begin(), vec2.end(), compararPorAtributo);
    int n = vec2.size();
    cout << endl;
    searchAlgorithm(vec2, inicioVec, finVec);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto totalTime = endTime - startTime;
    cout << "Tiempo de ejecución en ms: "
         << totalTime / std::chrono::milliseconds(1) << endl;
    cout << "Comparaciones realizadas: " << comparaciones << endl;
    cout << endl;
    for (int i = 0; i < n; i++) {
      cout << vec2[i].getMes() << " " << vec2[i].getDia() << " "
           << vec2[i].getHoraMinSec() << " " << vec2[i].getIpAd() << " "
           << vec2[i].getErrMessage() << endl;
    }
  }
  if (metodo == 2) {
    auto startTime = std::chrono::high_resolution_clock::now();
    bubbleSort(vec2, true);
    int n = vec2.size();
    cout << endl;
    searchAlgorithm(vec2, inicioVec, finVec);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto totalTime = endTime - startTime;
    cout << "Tiempo de ejecución en ms: "
         << totalTime / std::chrono::milliseconds(1) << endl;
    cout << "Comparaciones realizadas: " << comparaciones << endl;
    cout << "Intercambios realizados: " << swaps << endl;
    cout << endl;
    for (int i = 0; i < n; i++) {
      cout << vec2[i].getMes() << " " << vec2[i].getDia() << " "
           << vec2[i].getHoraMinSec() << " " << vec2[i].getIpAd() << " "
           << vec2[i].getErrMessage() << endl;
    }
  }
  if (metodo == 3) {
    auto startTime = std::chrono::high_resolution_clock::now();
    int n = vec2.size();
    quickSort(vec2, 0, n - 1);
    cout << endl;
    searchAlgorithm(vec2, inicioVec, finVec);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto totalTime = endTime - startTime;
    cout << "Tiempo de ejecución en ms: "
         << totalTime / std::chrono::milliseconds(1) << endl;
    cout << "Comparaciones realizadas: " << comparaciones << endl;
    cout << "Intercambios realizados: " << swaps << endl;
    cout << endl;
    for (int i = 0; i < n; i++) {
      cout << vec2[i].getMes() << " " << vec2[i].getDia() << " "
           << vec2[i].getHoraMinSec() << " " << vec2[i].getIpAd() << " "
           << vec2[i].getErrMessage() << endl;
    }
  }
  return 0;
}