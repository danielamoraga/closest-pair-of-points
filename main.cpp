#include "sweep-line.hpp"
#include "randomized.hpp"

int main() {
    int n;
    cin >> n;
    // Generar n puntos pertenecientes al rango [0, 1) x [0, 1)
    
    vector<pair<int, int>> coordinates(n);
    for (int i = 0; i < n; ++i) {
        cin >> coordinates[i].first >> coordinates[i].second;
    }

    cout << closestPair(coordinates, n) << endl;
    return 0;
}