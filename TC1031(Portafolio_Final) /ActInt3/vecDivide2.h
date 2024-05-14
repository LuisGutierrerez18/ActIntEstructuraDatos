#include "data.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Complejidad: O(n)
vector <int> vecdivide2(string strng, char separator) {
  const char* str = strng.c_str(); 
  int i = 0;
  vector<int> dataList;
  // String temporal para dividir al string
  string s;
  int sint;
  while (str[i] != '\0') {
    if (str[i] != separator) {
      // Append the char to the temp string.
      s += str[i];
    } else {
      sint = stoi(s);
      dataList.push_back(sint);
      s.clear();
    }
    i++;
  }
  sint = stoi(s);
  dataList.push_back(sint);
  return dataList;
}