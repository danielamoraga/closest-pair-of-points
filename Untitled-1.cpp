#include <bits/stdc++.h>
using namespace std;

// Estructura para representar un par de puntos y su distancia
struct ClosestPairResult {
    long long distance;
    pair<int, int> point1;
    pair<int, int> point2;
};

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Combina los hashes utilizando una técnica simple
        return h1 ^ h2;
    }
};


// Función para calcular la distancia entre dos puntos
long calculateDistance(pair<int, int> p1, pair<int, int> p2) {
    return (p1.first - p2.first) * (p1.first - p2.first) +
           (p1.second - p2.second) * (p1.second - p2.second);
}

// Función para la solución aleatorizada
ClosestPairResult randomizedClosestPair(vector<pair<int, int>> coordinates, int n) {
    // Seleccionar n pares de puntos al azar
    random_shuffle(coordinates.begin(), coordinates.end());

    // Calcular la distancia mínima entre puntos de cada par
    ClosestPairResult result;
    result.distance = numeric_limits<long long>::max();


    for (int i = 0; i < n; i += 2) {
        long dist = calculateDistance(coordinates[i], coordinates[i + 1]);
        if (dist < result.distance) {
            result.distance = dist;
            result.point1 = coordinates[i];
            result.point2 = coordinates[i + 1];
        }
    }

    // Calcular el tamaño de la cuadrícula
    double d = sqrt(result.distance);
    int gridSize = ceil(sqrt(n));

    // Hash Table para almacenar puntos en la cuadrícula
    unordered_map<pair<int, int>, vector<pair<int, int>>, pair_hash> grid;

    // Agrupar puntos en función de la cuadrícula a la que pertenecen
    for (int i = 0; i < n; i++) {
        int x = coordinates[i].first / d;
        int y = coordinates[i].second / d;
        grid[{x, y}].push_back(coordinates[i]);
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

// Código principal
int main() {
    // Puntos en el plano P[i] = {x, y}
    vector<pair<int, int>> P = {
        {1, 2}, {2, 3}, {3, 4}, {5, 6}, {2, 1}};

    int n = P.size();

    // Llamada a la función aleatorizada
    ClosestPairResult result = randomizedClosestPair(P, n);

    // Mostrar el resultado
    cout << "La distancia más pequeña es " << result.distance << endl;
    cout << "Par de puntos más cercano: (" << result.point1.first << ", " << result.point1.second << ") y ("
         << result.point2.first << ", " << result.point2.second << ")" << endl;

    return 0;
}
