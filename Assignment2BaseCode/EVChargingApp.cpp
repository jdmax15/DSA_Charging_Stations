#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <queue>
#include <map>
#include <iomanip>

using namespace std;

#include "Location.h"
#include "WeightedGraph.h"
#include "EVCharging.h"

int main() {
	EVCharging charging;
	charging.printLocations();
	charging.printAdjacencyMatrix();
	charging.sortLocations();
	charging.printAdjacentStations();
	charging.findNearestStation();
	return 0;
}
