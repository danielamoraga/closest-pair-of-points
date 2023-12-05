// Estructura para representar el par de puntos y su distancia
#include <utility>
#include <vector>
#include <bits/stdc++.h>
#include <unordered_map>
#include <algorithm>


using namespace std;

struct ClosestPairResult {
    float distance;
    pair<float, float> point1;
    pair<float, float> point2;
};