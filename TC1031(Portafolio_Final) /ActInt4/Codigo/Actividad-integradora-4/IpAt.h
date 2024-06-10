#include <iostream>
#include <vector>
#include <limits>
#include <algorithm> // Para std::min_element

using namespace std;

int encontrarMenorValor(const vector<int>& nums) {
    // Verificar si el vector está vacío
    if (nums.empty()) {
        cerr << "El vector está vacío." << endl;
        return numeric_limits<int>::max(); // Devuelve el valor máximo de int como señal de error
    }

    // Usar std::min_element para encontrar el menor valor en el vector
    auto minElement = min_element(nums.begin(), nums.end());

    // Retornar el menor valor encontrado
    return *minElement;
}