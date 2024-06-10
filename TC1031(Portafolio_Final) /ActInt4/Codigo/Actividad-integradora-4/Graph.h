#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "LinkedList.h"
#include "StackLinkedList.h"
#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <queue>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// https://stackoverflow.com/questions/18429021/why-is-infinity-0x3f3f3f3f
#define INF 0x3f3f3f3f

template <class T> class Graph {
private:
  int numNodes;
  int numEdges;
  int directedGraph; // 1 dirigido; 0 no-dirigido
  int weightedGraph; // 1 ponderado; 0 no-ponderado
  // Cada nodo tiene un id y un objeto de datos tipo T
  std::map<int, T> nodesInfo;
  // Lista de adyacencia (vector de listas de pares <nodo,peso>)
  std::vector<LinkedList<std::pair<long long int, long long int>>> adjList;
  std::vector <std::pair<int,std::string>> shortPathList;

  void split(std::string line, std::vector<int> &res);
  void extractIPs(const std::string &line, std::vector<long long int> &res);
  std::unordered_map<long long int, int> nodeMap;
  int nodeIdCounter = 0;
  int getNodeIdentifier(long long int ipAddress);
  void readLogLine(const std::vector<long long int> &values);

public:
  Graph();
  ~Graph();
  void readGraph(std::istream &input, int _directed, int _weighted);
  void print(int flagInfo = 0);
  void DFS(int v);
  std::pair<std::vector<int>, std::vector<int>> shortestPath(int v);
  // TODO
  void BFS(int v);
  bool isBipartite();
  void calculateOutDegrees(const std::string &filename);
  void writeTop5OutDegrees(const std::string &inputFilename,
                           const std::string &outputFilename);
std::vector <std::pair<int,std::string>> getShortPathList();
};



template <class T> int Graph<T>::getNodeIdentifier(long long int ipAddress) {
  // Verificar si la IP ya tiene un identificador asignado
  if (nodeMap.find(ipAddress) == nodeMap.end()) {
    // Asignar un nuevo identificador si no existe
    nodeMap[ipAddress] = nodeIdCounter++;
  }
  // Retornar el identificador asignado
  return nodeMap[ipAddress];
}

template <class T> Graph<T>::Graph() {
  numNodes = 0;
  numEdges = 0;
  directedGraph = 1;
  weightedGraph = 1;
}

template <class T> Graph<T>::~Graph() {
  adjList.clear();
  numNodes = 0;
  numEdges = 0;
  directedGraph = 1;
  weightedGraph = 1;
}

template <class T>
void Graph<T>::split(std::string line, std::vector<int> &res) {
  size_t strPos = line.find(" ");
  size_t lastPos = 0;
  while (strPos != std::string::npos) {
    res.push_back(stoi(line.substr(lastPos, strPos - lastPos)));
    lastPos = strPos + 1;
    strPos = line.find(" ", lastPos);
  }
  res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}
template <class T>
void Graph<T>::extractIPs(const std::string &line,
                          std::vector<long long int> &res) {
  std::regex ipRegex(
      R"((\d{1,3})\.(\d{1,3})\.(\d{1,3})\.(\d{1,3}))"); // Expresión regular
                                                        // para coincidir con
                                                        // direcciones IP
  std::smatch match;
  std::string::const_iterator searchStart(line.cbegin());
  long long int ip;
  while (std::regex_search(searchStart, line.cend(), match, ipRegex)) {
    int pos3 = pow(256, 3);
    int pos2 = pow(256, 2);
    int pos1 = pow(256, 1);
    for (size_t i = 1; i <= 4; ++i) { // Extraer cada grupo de números en la IP
      if (i == 1) {
        ip = (std::stol(match[i])) * pos3;
      }
      if (i == 2) {
        ip = ip + (std::stol(match[i])) * pos2;
      }
      if (i == 3) {
        ip = ip + (std::stoi(match[i])) * pos1;
      }
      if (i == 4) {
        ip = ip + (std::stoi(match[i]));
      }
    }
    res.push_back(ip);
    searchStart =
        match.suffix().first; // Avanzar al siguiente segmento de la cadena
  }
  std::regex weightRegex(
      R"((\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}):\d+\s+(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}):\d+\s+(\d+))");
  if (std::regex_search(line, match, weightRegex)) {
    long long int weight =
        std::stol(match[3]); // Extraer el peso como un número entero
    res.push_back(weight);
  }
}

template <class T>
void Graph<T>::readGraph(std::istream &input, int _directed, int _weighted) {
  directedGraph = _directed;
  weightedGraph = _weighted;
  std::string line;
  int i = 0;
  std::vector<std::tuple<long long int, long long int, long long int>> edges;
  std::vector<std::pair<long long int, std::string>> decimalIPs;
  while (std::getline(input, line)) {
    if (i == 0) { // Ignorar primera linea de texto (comentario)
      i++;
      continue;
    }
    if (i == 1) { // Leemos numNodes y numEdges
      std::vector<int> res;
      split(line, res);
      numNodes = res[0];
      numEdges = res[1];
      // Reservar memoria para los renglones de la
      // lista de adyacencia (cero basada)
      adjList.resize(numNodes);
      i++;
      continue;
    }
    if (i > 1 && i < numNodes + 2) { // Para cada nodo se lee su informacion
      T data = line; // ATENCION: convertir al tipo de dato adecuado
      // map <key, data> con los nodos indexados cero basados
      std::vector<long long int> res;
      extractIPs(line, res);
      long long int decimalIP = res[0];
      std::string ipString =
          line; // La IP en su representación de cadena original
      decimalIPs.push_back({decimalIP, ipString});
      getNodeIdentifier(decimalIP);
      
      /*
      nodesInfo.insert(std::make_pair(i - 2, data));
      // Declara una lista de pares (nodo, peso) vacia para
      // cada renglon de adjList
      LinkedList<std::pair<long long int, int>> tmpList;
      adjList[i - 2] = tmpList;
      */
      i++;
      continue;
    }
    // Lee las aristas
    std::vector<long long int> res;
    extractIPs(line, res);

    // nodos cero basados
    long long int sourceIP = res[0] ;
    long long int destIP = res[1];

    // Si el grafo es ponderado se lee tambien el peso
    // grafo no ponderado entonces aristas con peso 1
    long long int weight = (weightedGraph == 1) ? res[2] : 1;
    edges.push_back(std::make_tuple(sourceIP, destIP, weight));

    i++;
    continue;
    /*
    int nodeU = getNodeIdentifier(sourceIP);
    int nodeV = getNodeIdentifier(destIP);

    // Siempre se agrega la arista (nodeU, nodeV)
    adjList[nodeU].addLast(std::make_pair(nodeV, weight));
    // Si el grafo es no dirigido agrega tambien la arista (nodeV, nodeU)
    if (directedGraph == 0)
      adjList[nodeV].addLast(std::make_pair(nodeU, weight));
    */
  }
  // Ordenar las IPs

  /*
  std::sort(decimalIPs.begin(), decimalIPs.end(),
            [](const auto &a, const auto &b) {
              return a.first < b.first; // Comparar las IPs decimales
            });
  */
  
  std::unordered_map<long long int, int> ipToId;
  for (int idx = 0; idx < decimalIPs.size(); ++idx) {
    nodesInfo.insert(std::make_pair(idx, decimalIPs[idx].second));
    LinkedList<std::pair<long long int, long long int>> tmpList;
    adjList[idx] = tmpList;
  }

  std::sort(edges.begin(), edges.end(), [](const auto &a, const auto &b) {
    return std::get<0>(a) < std::get<0>(b); // Comparación de las IP de origen
  });
  for (const auto &edge : edges) {
    long long int sourceIP = std::get<0>(edge);
    long long int destIP = std::get<1>(edge);
    long long int weight = std::get<2>(edge);

    // Asignar identificadores únicos a los nodos
    int sourceNodeId = getNodeIdentifier(sourceIP);
    int destNodeId = getNodeIdentifier(destIP);

    // Agregar la arista al grafo utilizando los identificadores de los nodos
    adjList[sourceNodeId].addLast(std::make_pair(destNodeId, weight));
    // Si el grafo es no dirigido, agregar la arista en la dirección inversa
    // también
    if (directedGraph == 0)
      adjList[destNodeId].addLast(std::make_pair(sourceNodeId, weight));
  }
}

template <class T> void Graph<T>::print(int flagInfo) {
  std::cout << "numNodes: " << numNodes << std::endl;
  std::cout << "numEdges: " << numEdges << std::endl;
  std::cout << "Adjacency List" << std::endl;
  for (int nodeU = 0; nodeU < numNodes; nodeU++) {
    if (flagInfo) // Se imprime la info del nodo
      std::cout << "vertex " << nodesInfo[nodeU] << ": ";
    else // Se imprime el numero de nodo
      std::cout << "vertex " << nodeU + 1 << ": ";
    NodeLinkedList<std::pair<long long int, long long int>> *ptr =
        adjList[nodeU].getHead();

    while (ptr != nullptr) {
      std::pair<long long int, int> par = ptr->data;
      int nodeV = par.first;
      long long int weight = par.second;
      std::string nodeData = (flagInfo) ? nodesInfo[nodeV] + ", " : "";
      if (weightedGraph == 1) // grafo ponderado
        std::cout << "{" << nodeData << nodeV + 1 << ", " << weight << "} ";
      else
        std::cout << "{" << nodeData << nodeV + 1 << "} ";
      ptr = ptr->next;
    }
    std::cout << std::endl;
  }
}

template <class T> void Graph<T>::DFS(int v) {
  // Declarar un set del STL de C++ (elementos unicos y ordenados)
  std::set<int> visited;
  // Crear un stack
  StackLinkedList<int> stack;
  // Marcar el vertice de partida v como visitado y se mete al stack
  visited.insert(v);
  stack.push(v);
  std::cout << "Recorrido DFS " << std::endl;
  while (!stack.isEmpty()) {
    // Extraemos un vertice del stack
    v = stack.getTop();
    stack.pop();
    // Procesar el vertice
    std::cout << v + 1 << ", ";
    // Obtener los vecinos del vertice v
    // Si estos no han sido visitados marcarlos como visitados
    // y los metemos al stack
    NodeLinkedList<std::pair<long long int, long long int>> *ptr =
        adjList[v].getHead();
    while (ptr != nullptr) {
      std::pair<long long int, int> par = ptr->data;
      int u = par.first; // nodo u es vecino de v
      // Verificar si el vertice u (vecino de v) ya fue visitado
      bool isVisited = visited.find(u) != visited.end();
      if (!isVisited) {    // no visitado
        visited.insert(u); // marcar como visitado
        stack.push(u);     // meter en el queue
      }
      ptr = ptr->next;
    }
  }
  std::cout << std::endl;
}

// BFS: https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/
// Complejidad: O(V + E), Donde V son los vertices y E son las aristas
template <class T> void Graph<T>::BFS(int v) {
  // Declarar un set del STL de C++ (elementos únicos y ordenados)
  std::set<int> visited;
  // Crear una cola
  std::queue<int> queue;
  // Marcar el vértice de partida v como visitado y se mete en la cola
  visited.insert(v);
  queue.push(v);
  std::cout << "Recorrido BFS " << std::endl;

  while (!queue.empty()) {
    // Extraemos un vértice de la cola
    v = queue.front();
    queue.pop();
    // Procesar el vértice
    std::cout << v + 1 << ", ";

    // Obtener los vecinos del vértice v
    NodeLinkedList<std::pair<long long int, long long int>> *ptr =
        adjList[v].getHead();
    while (ptr != nullptr) {
      std::pair<long long int, int> par = ptr->data;
      int u = par.first; // nodo u es vecino de v

      // Verificar si el vértice u (vecino de v) ya fue visitado
      if (visited.find(u) == visited.end()) { // no visitado
        visited.insert(u);                    // marcar como visitado
        queue.push(u);                        // meter en la cola
      }
      ptr = ptr->next;
    }
  }
  std::cout << std::endl;
}

// Algoritmo de Dijstra, complejidad O((n+m)*log n)
template <class T>
std::pair<std::vector<int>, std::vector<int>> Graph<T>::shortestPath(int v) {
  // vector de distancias con el resultado del algoritmo
  std::vector<int> dist(numNodes, INF);
  // vector con los predecesores en el camino mas corto desde v
  std::vector<int> prev(numNodes, -1);
  // Crear una priority queue del STL
  // https://www.geeksforgeeks.org/implement-min-heap-using-stl/
  std::priority_queue<std::pair<long long int, int>,
                      std::vector<std::pair<long long int, int>>,
                      std::greater<std::pair<long long int, int>>>
      pq;
  // Insertar el nodo de origen v en la cola de prioridad -- pares <dist, nodo>
  pq.push(std::make_pair(0, v));
  dist[v] = 0;
  prev[v] = -1;
  // Mientras la cola de prioiridad no este vacia
  while (!pq.empty()) {
    // Extraer un nodo nodeU de la cola de prioridad
    int nodeU = pq.top().second; // pares <dist, nodo>
    pq.pop();
    // Obtener los nodos vecinos de nodeU
    NodeLinkedList<std::pair<long long int, long long int>> *ptr =
        adjList[nodeU].getHead();
    while (ptr != nullptr) {
      std::pair<long long int, int> par = ptr->data;
      int nodeV = par.first;   // nodeV es vecino de nodeU
      int weight = par.second; // peso de la arista (nodeU, nodeV)
      if (dist[nodeV] > dist[nodeU] + weight) {
        // Actualizar la distancia mas corta hasta nodeV
        dist[nodeV] = dist[nodeU] + weight;
        prev[nodeV] = nodeU;
        pq.push(std::make_pair(dist[nodeV], nodeV));
      }
      ptr = ptr->next;
    }
  }
  // El resultado almacenado en dist y prev
  std::cout << "Vertices \t\t Distancia desde v" << std::endl;
  for (int i = 0; i < numNodes; i++) {
    if (dist[i] == INF)
      std::cout << i + 1 << "\t\tINF" << std::endl;
    else
      std::cout << nodesInfo[i] << "\t\t" << dist[i] << std::endl;
      shortPathList.push_back(std::make_pair(dist[i],nodesInfo[i]));
      
  }
  std::cout << "Vertices \t\t Predecesor" << std::endl;
  for (int i = 0; i < numNodes; i++) {
    if (prev[i] == -1)
      std::cout << i + 1 << "\t\tNULL" << std::endl;
    else
      std::cout << nodesInfo[i] << "\t\t" << prev[i] << std::endl;
      
  }
  return std::make_pair(dist, prev);
}

// https://www.geeksforgeeks.org/bipartite-graph/
// Complejidadd: O(V + E)
template <class T> bool Graph<T>::isBipartite() {
  std::vector<int> color(numNodes,
                         -1); // -1 = no tiene color, 0 y 1 son dos colores

  for (int start = 0; start < numNodes; ++start) {
    if (color[start] == -1) { // El nodo no esta coloreado
      std::stack<int> stack;
      stack.push(start);
      color[start] = 0; // Color 0

      while (!stack.empty()) {
        int node = stack.top();
        stack.pop();

        NodeLinkedList<std::pair<long long int, long long int>> *ptr =
            adjList[node].getHead();
        while (ptr != nullptr) {
          int neighbor = ptr->data.first;
          if (color[neighbor] == -1) {         // Si el vecino no tiene color
            color[neighbor] = 1 - color[node]; // assignar color opuesto
            stack.push(neighbor);
          } else if (color[neighbor] ==
                     color[node]) { // Si el nodo vecino tiene el mismo color
            return false;           // El grafo no es bipartito
          }
          ptr = ptr->next;
        }
      }
    }
  }

  return true; // All nodes have been colored properly
}

//O(V+E)
template <class T>
void Graph<T>::calculateOutDegrees(const std::string &filename) {
  std::ofstream outFile(filename);
  if (!outFile.is_open()) {
    std::cerr << "Error al abrir el archivo: " << filename << std::endl;
    return;
  }

  outFile << "vertex,out-degree\n";
  for (int nodeU = 0; nodeU < numNodes; ++nodeU) {
    int outDegree = 0;
    NodeLinkedList<std::pair<long long int, long long int>> *ptr =
        adjList[nodeU].getHead();
    while (ptr != nullptr) {
      ++outDegree;
      ptr = ptr->next;
    }
    outFile << nodeU << "," << outDegree << "\n";
  }

  outFile.close();
}

//O(N Log N)
template <class T>
void Graph<T>::writeTop5OutDegrees(const std::string &inputFilename,
                                   const std::string &outputFilename) {
  // Abrir el archivo de entrada
  std::ifstream infile(inputFilename);
  if (!infile.is_open()) {
    std::cerr << "Error al abrir el archivo " << inputFilename << std::endl;
    return;
  }

  // Vector para almacenar el grado de salida de cada IP
  std::vector<std::pair<int, int>> outDegrees;

  // Leer el archivo y almacenar el grado de salida de cada IP
  std::string line;
  while (std::getline(infile, line)) {
    // Ignorar la primera línea (encabezado)
    if (line.find("vertex,out-degree") != std::string::npos)
      continue;

    // Obtener el índice y el grado de salida
    int vertex, outDegree;
    sscanf(line.c_str(), "%d,%d", &vertex, &outDegree);

    // Almacenar en el vector
    outDegrees.push_back({vertex, outDegree});
  }

  // Cerrar el archivo de entrada
  infile.close();

  // Ordenar las IPs por su grado de salida en orden descendente
  std::sort(
      outDegrees.begin(), outDegrees.end(), [](const auto &a, const auto &b) {
        return a.second > b.second; // Orden descendente por grado de salida
      });

  // Abrir el archivo de salida para escribir
  std::ofstream outfile(outputFilename);
  if (!outfile.is_open()) {
    std::cerr << "Error al abrir el archivo " << outputFilename << std::endl;
    return;
  }

  // Escribir las 5 IPs con mayor grado de salida en el archivo
  for (int i = 0; i < std::min(5, static_cast<int>(outDegrees.size())); ++i) {
    outfile << outDegrees[i].first << ", " << nodesInfo[outDegrees[i].first]
            << "," << outDegrees[i].second << std::endl;
  }

  // Cerrar el archivo de salida
  outfile.close();
}

template <class T>
std::vector<std::pair<int,std::string>> Graph<T>::getShortPathList(){
  return shortPathList;
}

#endif // _GRAPH_H_
