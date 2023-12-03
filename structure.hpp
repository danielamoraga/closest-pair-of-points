// Estructura para representar el par de puntos y su distancia
#include <utility>
#include <vector>
#include <bits/stdc++.h>
#include <unordered_map>
#include <algorithm>


using namespace std;

struct ClosestPairResult {
    double distance;
    pair<int, int> point1;
    pair<int, int> point2;
};