#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <vector>
#include "sweep-line.hpp"
#include <pthread.h>
using namespace std;


// Mide la ejecución de un algoritmo para un valor de n, generando n puntos aleatorios
void measureExecutionTime(int n, int iteration) {
    
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
    // Write the execution time in the file
    // Open file, named as results_n 
    ofstream myfile;
    auto filename = "results/resultado_" + to_string(n) + ".txt";
    cout << filename << endl;
    myfile.open(filename, ios::app);
    myfile << iteration << "," << duration << endl;
    myfile.close();
}

int main() {
    //Abre un archivo para escribir los resultados
    long int n = 5000000;
    int iterations = 100;
    cout << "Starting the execution" << endl;
    for (int j = n; j <= 50000000; j+=5000000) {
        for (int i = 1; i <= iterations; i++) {
            measureExecutionTime(j, i);
        }
    }
    return 0;
}