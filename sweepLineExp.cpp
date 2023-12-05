#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <vector>
#include "sweep-line.hpp"
#include <pthread.h>
using namespace std;

// Driver code
/*
Para probar los algoritmos, debería entregarle un set de tamaño n de puntos pertenecientes al 
rango [0, 1) x [0, 1). Pruebe con n de 5 a 50 millones con un paso de 5 millones.
Para cada arreglo de tamaño n, debería ejecutar cada algoritmo una cantidad considerable de veces (> 100).
Luego, debería generar un histograma con los tiempos de ejecución de cada algoritmo.
Debe utilizar el mismo arreglo en las repeticiones y en ambos algoritmos para poder compararlos.
También, deben graficar cómo crecen las medias en función del tamaño del input.
Por último, analice el tiempo promedio para varios inputs aleatorios y muestre que el costo de tiempo
en sus implementacionesse asemejan a lo conocido por la teoría.*/

//Objeto random entre 0 y 1



// Mide la ejecución de un algoritmo para un valor de n, generando n puntos aleatorios
void measureExecutionTime(int n, int iterations, ofstream &myfile) {
    
    vector<pair<float, float>> coordinates;
    
    // Genera objetos random
    random_device rd;
    mt19937 g(rd());
    uniform_real_distribution<> dis(0, 1);
    
    // Genera n puntos aleatorios
    for (int i = 0; i < n; i++) {
        coordinates.push_back({dis(g), dis(g)});
        // cout << "(" << coordinates[i].first << " ," << coordinates[i].second << ")" << endl;
    }

    // Run the algorithm and measure the execution time
    auto start = std::chrono::high_resolution_clock::now();
    ClosestPairResult result = closestPair(coordinates, n);
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the execution time in milliseconds
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // Print the execution time
    cout << iterations << " " << duration << endl;
    // Write the execution time in the file
    myfile << iterations << " " << duration << endl;
}

int main() {
    //Abre un archivo para escribir los resultados
    ofstream myfile;
    myfile.open ("results.txt");
    long int n = 5000000;
    int iterations = 10;
    cout << "Starting the execution" << endl;
    for (int i = 0; i < iterations; i++) {
        cout << "Iteration " << i << endl;
        measureExecutionTime(n, iterations, myfile);

    }
    myfile.close();
    return 0;
}