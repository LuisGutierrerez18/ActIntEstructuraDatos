/**
 * Actividad 4-2
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
#include "IpAt.h"
#include "DLinkedList.h"
#include <fstream>
#include <iostream>
#include <sstream>


int main() {
  DLinkedList<std::pair <int,string>> shortstPathList;
  std::ifstream archivo("bitacoraGrafos-1.txt");
  std::stringstream inputInfo;
  inputInfo << archivo.rdbuf();
  archivo.close();
  // Construye un grafo
  Graph<std::string> g1;

  // Lee de archivo un grafo, directed=1, weighted=1
  // lista de adyacencia
  g1.readGraph(inputInfo, 1, 1);
  //g1.print(10);
  g1.calculateOutDegrees("gradosIp.txt");
  g1.writeTop5OutDegrees("gradosIp.txt", "mayores_grados_ips.txt");
  
  std::string line;
  std::ifstream infile("mayores_grados_ips.txt");
  std::getline(infile, line);
  char ipAddr[16];
  int one, two;
  
  sscanf(line.c_str(), "%d,%15[^,],%d", &one, ipAddr, &two);
  std::cout << "El botmaster se encuentra en la ip: " << ipAddr << std::endl;

  std::ofstream outputFile("distancia_botmaster.txt");
  if (outputFile.is_open()) {
    // Redirigir la salida estándar hacia el archivo
    
    std::streambuf *coutbuf =
    std::cout.rdbuf();               // Guardar el buffer actual de cout
    std::cout.rdbuf(outputFile.rdbuf()); // Redirigir cout al archivo
    // Llamar a la función shortestPath para imprimir los resultados en el
    // archivo
    g1.shortestPath(one); // Suponiendo que 'one' es el nodo desde el que quieres
                        // encontrar el camino más corto
    // Restaurar la salida estándar
    std::cout.rdbuf(coutbuf); // Restaurar el buffer de cout

    // Cerrar el archivo 
    outputFile.close();
  }

  std::vector<std::pair<int,string>> shrtPath = g1.getShortPathList();
  int n = shrtPath.size();

  
  for (int i = 0; i < n; i++){
    shortstPathList.addLast(shrtPath[i]);
  }
  shortstPathList.heapSort();
  shortstPathList.invert();
  std::pair <int,string> minElementC = shortstPathList.getData(1);
  std::cout << "Resultados: " << std::endl;
  std::cout << "El elemento mas cercano al botmaster es " << minElementC.second << " a una distancia de " << minElementC.first << std::endl;
  
  
  
  

  
  
}