/**
 * Actividad integradora #5
 * Integrantes del equipo:
 *   Moisés Abel Díaz Nava A01799628
 *   Luis Enrique Gutierrez Mendioroz. A00837481
 *
 * Compilacion para debug:
 *    g++ -std=c++17 -g -o main *.cpp
 * Ejecucion con valgrind:
 *    nix-env -iA nixpkgs.valgrind
 *    valgrind --leak-check=full ./main < TestCases/graph01.txt
 *
 * Compilacion para ejecucion:
 *    g++ -std=c++17 -O3 -o main *.cpp
 * Ejecucion:
 *    ./main < TestCases-Act4.2/graph04.txt
 **/

#include "Graph.h"
#include "HashTable.h"
#include "IpAt.h"
#include <fstream>
#include <iostream>
#include <sstream>

int main() {
  std::ifstream archivo("bitacoraGrafos-1.txt");
  std::stringstream inputInfo;
  inputInfo << archivo.rdbuf();
  archivo.close();
  // Construye un grafo
  Graph<std::string> g1;

  // Lee de archivo un grafo, directed=1, weighted=1
  // lista de adyacencia
  g1.readGraph(inputInfo, 1, 1);
  // g1.print(10);
  g1.displayDegrees("gradosInOut.txt");
  HashTable<int, std::tuple<std::string, int, int>> hashTable;
  hashTable.setMaxSize(g1.getNumNodes());
  hashTable.readHash("gradosInOut.txt");
  hashTable.print();
  std::cout << "table Alfa: " << hashTable.getAlfa() << std::endl;
  std::cout << "Table Colisiones: " << hashTable.getColisiones() << std::endl;
  std::string lineToFind;
  int continueO = 1;
  while (continueO != 0) {
    std::cout << "Escribe la ip que deseas buscar: " << std::endl;
    cin >> lineToFind;
    int index = hashTable.findIPSummary(lineToFind);
    if (index == -1) {
      std::cout << "\tElement not found" << std::endl;
    } else {
      hashTable.getIpSummary(index);
      g1.printData(index);
    }
    std::cout << "Desea buscar otra ip? (1/0): \n ";
    cin >> continueO;
    if(continueO > 1 && continueO < 0){
      std::cout << "Ingrese una opción valida \n";
    }
  }
}