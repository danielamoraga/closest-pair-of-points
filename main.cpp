#include "sweep-line.hpp"
using namespace std;


int main()
{

	// Points on a plane P[i] = {x, y}
	vector<pair<int, int> > P = {
		{ 1, 2 }, { 2, 3 }, { 3, 4 }, { 5, 6 }, { 2, 1 }
	};
	int n = P.size();
	
	// Function call
	ClosestPairResult result = closestPair(P, n);
    cout << "The smallest distance is " << result.distance << endl;
    cout << "The closest pair of points are (" << result.point1.first << ", " << result.point1.second << ") and (" << result.point2.first << ", " << result.point2.second << ")" << endl;
	return 0;
}