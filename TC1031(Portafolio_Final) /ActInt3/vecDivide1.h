#include "data.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Complejidad: O(n)
string vecdivide1(string strng, char separator) {
  const char* str = strng.c_str(); 
  int i = 0;
  // String temporal para dividir al string
  string s;
  while (str[i] != '\0') {
    if (str[i] != separator) {
      // Append the char to the temp string.
      s += str[i];
    } else {
      return s;
    }
    i++;
  }
  return s;
}