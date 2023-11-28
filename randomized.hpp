#include <algorithm>
#include <vector>
#include <bits/stdc++.h>
#include <unordered_map>
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
double calculateDistance(pair<int, int> p1, pair<int, int> p2) {
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}

// Función para encontrar los puntos más cercanos
unordered_map<pair<int, int>, pair<int, int>, PairHash> findClosestPoints(const vector<pair<int, int>>& points, double d) {
    unordered_map<pair<int, int>, pair<int, int>, PairHash> closestPoints;

    // Dividir el plano en una grilla de cuadrículas y agrupar los puntos
    unordered_map<pair<int, int>, vector<pair<int, int>>, PairHash> grid;

    for (const auto& point : points) {
        // Calcular las coordenadas de la grilla a la que pertenece el punto
        int gridX = static_cast<int>(point.first / d);
        int gridY = static_cast<int>(point.second / d);
        pair<int, int> gridKey = make_pair(gridX, gridY);

        // Agregar el punto a la grilla correspondiente en la hash table
        grid[gridKey].push_back(point);
    }

    // Iterar sobre cada punto
    for (const auto& point : points) {
        pair<int, int> closestPoint;
        double minDistance = numeric_limits<double>::max();

        // Encontrar el punto más cercano en la misma grilla
        for (const auto& neighborPoint : grid[{static_cast<int>(point.first / d), static_cast<int>(point.second / d)}]) {
            if (point.first == neighborPoint.first && point.second == neighborPoint.second) {
                continue;  // No comparar el punto consigo mismo
            }

            double distance = calculateDistance(point, neighborPoint);
            if (distance < minDistance) {
                minDistance = distance;
                closestPoint = neighborPoint;
            }
        }

        // Iterar sobre las grillas circundantes
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                std::pair<int, int> neighborKey = {static_cast<int>(point.first / d) + dx, static_cast<int>(point.second / d) + dy};

                // Verificar si la grilla vecina existe en la hash table
                if (grid.count(neighborKey) > 0) {
                    // Encontrar el punto más cercano en la grilla vecina
                    for (const auto& neighborPoint : grid[neighborKey]) {
                        double distance = calculateDistance(point, neighborPoint);
                        if (distance < minDistance) {
                            minDistance = distance;
                            closestPoint = neighborPoint;
                        }
                    }
                }
            }
        }

        // Almacenar el punto más cercano en la hash table
        closestPoints[point] = closestPoint;
    }
    return closestPoints;
}

pair<pair<int, int>, pair<int, int>> closestPairRandomized(vector<pair<int, int>> coordinates, int n, int d) {
    // Vector pair to store points on plane
    vector<pair<int, int>> v;
    for (int i = 0; i < n; i++)
        v.push_back({ coordinates[i].first, coordinates[i].second });

    // Generate n random pairs
    std::vector<pair<int, int>> randomPairs;
    int numPoints = coordinates.size();

    srand(time(0));

    for (int i = 0; i < n; ++i) {
        // Generar índices aleatorios
        int index1 = rand() % numPoints;
        int index2 = rand() % numPoints;

        // Agregar el par de puntos al vector
        randomPairs.push_back(coordinates[index1]);
        randomPairs.push_back(coordinates[index2]);
    }

    /*  Se divide el plano en una grilla de cuadrillas de d × d, y se agrupan los puntos en función de
        la grilla a la que pertenecen (para hacer esto de manera eficiente, se debe utilizar una Hash
        Table implementada por ustedes, donde las llaves son las coordenadas del cuadrado, y en ella
        se guardan los puntos contenidos en el) */
    unordered_map<pair<int, int>, vector<pair<int, int>>, PairHash> grid;

    for (const auto& point : coordinates) {
        // Calcular las coordenadas de la cuadrícula a la que pertenece el punto
        int gridX = static_cast<int>(point.first / d);
        int gridY = static_cast<int>(point.second / d);
        std::pair<int, int> gridKey = std::make_pair(gridX, gridY);

        // Agregar el punto a la cuadrícula correspondiente en la hash table
        grid[gridKey].push_back(point);
    }
    
    /*  Para cada punto, se compara la distancia entre este, y todos los puntos pertenecientes a su
        misma casilla, y a las 8 casillas vecinas, la idea es que, si el d es suficientemente bueno, los
        puntos con los que se compara cada iteración deben ser pocos */
    findClosestPoints(coordinates, d);
    auto minElement = min_element(coordinates.begin(), coordinates.end());
    pair<int, int> minimo = *minElement;
    return minimo;
}