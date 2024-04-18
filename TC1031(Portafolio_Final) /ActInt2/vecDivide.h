#include "data.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


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