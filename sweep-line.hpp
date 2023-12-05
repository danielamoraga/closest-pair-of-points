#include "structure.hpp"
using namespace std;
ClosestPairResult closestPair(vector<pair<float, float>> coordinates, int n)
{
    // Vector pair para almacenar puntos en el plano
    vector<pair<float, float>> v;
    for (int i = 0; i < n; i++)
        v.push_back({coordinates[i].first, coordinates[i].second});

    // Ordenar según las coordenadas x
    sort(v.begin(), v.end());

    // Distancia mínima entre puntos vista hasta ahora
    ClosestPairResult result;
    result.distance = INT_MAX;

    // Mantener los puntos en orden creciente
    set<pair<float, float>> st;
    st.insert({v[0].first, v[0].second});

    for (int i = 1; i < n; i++) {
        auto l = st.lower_bound({v[i].first - result.distance, v[i].second - result.distance});
        auto r = st.upper_bound({v[i].first, v[i].second + result.distance});
        if (l == st.end())
            continue;

        for (auto p = l; p != r; p++) {
            pair<float, float> val = *p;
            float dis = (v[i].first - val.first) * (v[i].first - val.first) +
                       (v[i].second - val.second) * (v[i].second - val.second);

            // Actualizar la distancia mínima y los puntos correspondientes
            if (result.distance > dis) {
                result.distance = sqrt(dis);
                result.point1 = {v[i].first, v[i].second};
                result.point2 = {val.first, val.second};
            }
        }
        st.insert({v[i].first, v[i].second});
    }

    return result;
}