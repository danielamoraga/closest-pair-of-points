#include <iostream>
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
void measureExecutionTime(int n) {
    
    vector<pair<float, float>> coordinates;
    
    // Genera objetos random
    random_device rd;
    mt19937 g(rd());
    uniform_real_distribution<> dis(0, 1);
    
    // Genera n puntos aleatorios
    for (int i = 0; i < n; i++) {
        coordinates.push_back({dis(g), dis(g)});
    }

    // Run the algorithm and measure the execution time
    auto start = std::chrono::high_resolution_clock::now();
    ClosestPairResult result = closestPair(coordinates, n);
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the execution time in milliseconds
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // Print the execution time
    std::cout << "Execution time for n = " << n << ": " << duration << " milliseconds" << std::endl;
}

int main() {
    // Create a vector to store the threads
    std::vector<std::thread> threads;

    // Define the range of n values
    int startN = 0;
    int endN = 99;
    int step = 1;

    // Create 9 threads to measure the execution time for each algorithm
    for (int n = startN; n <= endN; n += step) {
        cout<<"n: "<<n<<endl;
        threads.emplace_back(measureExecutionTime, n);
        if (threads.size() == 100) {
            // Wait for all threads to finish
            for (auto& thread : threads) {
                thread.join();
            }
            threads.clear();
        }
    }

    // Wait for the remaining threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
