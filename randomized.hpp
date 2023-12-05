#include "structure.hpp"
using namespace std;

struct PairHash {
    template <class T1, class T2>
    size_t operator () (const std::pair<T1, T2>& p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);

        // Combina los valores hash para las dos partes de std::pair
        return h1 ^ h2;
    }
};

// Función para calcular la distancia entre dos puntos
long calculateDistance(pair<int, int> p1, pair<int, int> p2) {
    return sqrt(pow(p1.first - p2.first, 2) + 
                pow(p1.second - p2.second, 2));
}

ClosestPairResult randomizedClosestPair(vector<pair<int, int>> coordinates, int n) {
    // Vector pair para almacenar puntos en el plano
    vector<pair<int, int>> v;
    for (int i = 0; i < n; i++){
        v.push_back({coordinates[i].first, coordinates[i].second});
    }

    ClosestPairResult result;
    result.distance = INT_MAX;
    vector<pair<int, int>> randomPairs;

    //Objeto random entre 0 y n-1
    random_device rd;
    mt19937 g(rd());
    uniform_int_distribution<> dis(0, n-1);
    //Elige un elemento aleatorio del vector y lo pone en otro vector, haciendo n pares aleatorios
    for (int i = 0; i < n; ++i) {
        int index1 = dis(g);
        int index2 = dis(g);
        randomPairs.push_back(coordinates[index1]);
        randomPairs.push_back(coordinates[index2]);
    }
    //Calcular la distancia entre los puntos de cada par
    for (int i = 0; i < randomPairs.size(); i+=2) {
        long int dis = calculateDistance(randomPairs[i], randomPairs[i+1]);
        // Actualizar la distancia mínima y los puntos correspondientes
        if (result.distance > dis) {
            result.distance = dis;
            result.point1 = {randomPairs[i].first, randomPairs[i].second};
            result.point2 = {randomPairs[i+1].first, randomPairs[i+1].second};
        }
    }
    //Calcula el tamaño de la grilla
    long d = sqrt(result.distance);
    long gridSize = ceil(sqrt(n));

    //Divide el plano en una grilla de cuadrículas de d × d, y se agrupan los puntos en función de la grilla a la que pertenecen
    unordered_map<pair<int, int>, vector<pair<int, int>>, PairHash> grid;
    //Agrupa los puntos en la grilla correspondiente
    for (long i = 0; i < n; i++){
        long x = v[i].first / d;
        long y = v[i].second / d;
        pair<int, int> gridKey = make_pair(x, y);
        grid[gridKey].push_back(v[i]);
        cout << "Point: (" << v[i].first << ", " << v[i].second << ") added to grid: (" << x << ", " << y << ")\n";

    }

    // Comparar la distancia entre puntos en la misma cuadrícula y en las vecinas
    for (int i = 0; i < n; i++) {
        int x = coordinates[i].first / d;
        int y = coordinates[i].second / d;

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                pair<int, int> neighbor = {x + dx, y + dy};

                if (grid.find(neighbor) != grid.end()) {
                    for (const auto &neighborPoint : grid[neighbor]) {
                        long dist = calculateDistance(coordinates[i], neighborPoint);
                        if (dist < result.distance) {
                            result.distance = dist;
                            result.point1 = coordinates[i];
                            result.point2 = neighborPoint;
                        }
                    }
                }
            }
        }
    }

    return result;

}

