/*
 * EVCharging.h
 *
 *  Created on: 26 Apr 2026
 *      Author: Dongmo
 */

#ifndef EVCHARGING_H_
#define EVCHARGING_H_

#include <algorithm>

class EVCharging {// you may also declare this class as an extension of WeightedGraph
private:
	map<int, Location> locations;//It can also be unordered_map
	int numberOfLocations;
	WeightedGraphType* weightedGraph;
public:
	EVCharging();
	~EVCharging();
	void inputLocations();
	void printLocations();
	void printAdjacencyMatrix();
	void sortLocations();
	void printAdjacentStations();
	void findNearestStation();
	void findCheapestStation();
};

EVCharging::EVCharging() {
	inputLocations();
	weightedGraph = new WeightedGraphType(numberOfLocations);
}

EVCharging::~EVCharging() {
	delete weightedGraph;
}
void EVCharging::inputLocations() {
	ifstream infile;
	char fileName[50] = "MyLocations.txt";

//	cout << "Enter charging location file name: ";
//	cin >> fileName;
//	cout << endl;

	infile.open(fileName);

	if (!infile) {
		cout << "Cannot open input file." << endl;
		return;
	}

	int locationIndex = 0;
	Location s;
	string charger;
	string price;

	while (getline(infile, s.locationName, ',') &&
		   getline(infile, charger, ',') &&
		   getline(infile, price)) {
		s.chargerInstalled = (stoi(charger) == 1) ? true : false;
		s.chargingPrice = stod(price);
		s.index = locationIndex;
		locations[locationIndex] = s;
		locationIndex++;
	}

	numberOfLocations = locationIndex;
}

void EVCharging::printLocations() {
	cout << "List of locations and charging information " << endl;
	cout << setw (8) << "Index" << setw (20) << "Location name" << setw (20) <<"Charging station" << setw(20) << "Charging price" << endl;

	map<int, Location>::iterator it = locations.begin();

	for (; it != locations.end(); it++) {
		it->second.printLocation();
	}

    cout << endl;
}

void EVCharging::printAdjacencyMatrix() {
	cout << "Adjacency matrix (0 means no direct connection, non-zero value represents the distance of adjacent locations)\n" << endl;
	cout << setw(13) << " ";
	for (int i = 0; i < numberOfLocations; i++) {
		cout << setw(13) << locations[i].locationName;
	}
	cout << endl;
	for (int i = 0; i < numberOfLocations; i++) {
		cout << setw(13) << locations[i].locationName;
		for (int j = 0; j < numberOfLocations; j++) {
			cout << setw(13) << (weightedGraph->getWeight(i,j) == DBL_MAX ? 0.0 : weightedGraph->getWeight(i,j));
		}
		cout << endl;
	}
}

void EVCharging::sortLocations() {
	vector<Location> stations;
	for (int i = 0; i < numberOfLocations; i++) {
		if (locations[i].chargerInstalled == true)
			stations.push_back(locations[i]);
	}
	sort(stations.begin(), stations.end());

	cout << "\nList of stations sorted by price:" << endl;
	cout << setw (8) << "Index" << setw (20) << "Location name" << setw (20) <<"Charging station" << setw(20) << "Charging price" << endl;

	vector<Location>::iterator it = stations.begin();

	for (; it != stations.end(); it++) {
		it->printLocation();
	}

    cout << endl;

}

void EVCharging::printAdjacentStations() {

	int index;

	cout << "Enter a location index: \n";

	cin >> index;

	list<int> adjList = weightedGraph->getAdjacencyList(index);

	bool found = false;

	cout << "\nAdjacent Locations with an available charging station for " << locations[index].locationName << ":" << endl << endl;

	cout << setw (8) << "Index" << setw (20) << "Location name" << setw (20) <<"Charging station" << setw(20) << "Charging price" << endl;


	for (int i : adjList) {
		if (locations[i].chargerInstalled) {
			locations[i].printLocation();
			found = true;
		}
	}

	if (!found) {
		cout << "NONE\n" << endl;
	}

}

void EVCharging::findCheapestStation() {
	int index;
	double kwh;

	cout << "Enter a location index: " << endl;
	cin >> index;

	cout << "Enter amount to charge (10-50 kWh): " << endl;
	cin >> kwh;

	weightedGraph->shortestPath(index);

	double minCost = DBL_MAX;
	int cheapest = -1;

	for (int i = 0; i < numberOfLocations; i++) {
		if (i == index)
			continue;

		if (!locations[i].chargerInstalled)
			continue;

		if (locations[i].chargingPrice == 0 && kwh > 25)
			continue;

		double d = weightedGraph->getSmallestWeight(i);

		if (d == DBL_MAX)
			continue;

		double travelCost = d * 2 * 0.10;
		double chargingCost = kwh * locations[i].chargingPrice;
		double totalCost = travelCost + chargingCost;

		if (totalCost < minCost) {
			minCost = totalCost;
			cheapest = i;
		}
	}

	if (cheapest == -1) {
		cout << "NONE" << endl;
	} else {
		double dist = weightedGraph->getSmallestWeight(cheapest);
		double travelCost = dist * 2 * 0.10;
		double chargingCost = kwh * locations[cheapest].chargingPrice;

		cout << "\nCheapest charging station from " << locations[index].locationName << ":" << endl;
		cout << setw(8) << "Index" << setw(20) << "Location name" << setw(20) << "Charging station" << setw(20) << "Charging price" << endl;
		locations[cheapest].printLocation();
		cout << fixed << setprecision(2);
		cout << "\nCost breakdown:" << endl;
		cout << "  Distance:      " << dist << " km" << endl;
		cout << "  Travel cost:   " << dist << " km x 2 (return) x $0.10/km = $" << travelCost << endl;
		cout << "  Charging cost: " << kwh << " kWh x $" << locations[cheapest].chargingPrice << "/kWh = $" << chargingCost << endl;
		cout << "  Total cost:    $" << travelCost << " + $" << chargingCost << " = $" << minCost << endl;
		cout << defaultfloat;
	}
}

void EVCharging::findNearestStation() {
	int index;

	cout << "Enter a location index: " << endl;
	cin >> index;

	weightedGraph->shortestPath(index);

	double minDist = DBL_MAX;
	int nearest = -1;

	for (int i = 0; i < numberOfLocations; i++) {
		if (i == index)
			continue;

		if (!locations[i].chargerInstalled)
			continue;

		double d = weightedGraph->getSmallestWeight(i);

		if (d < minDist) {
			minDist = d;
			nearest = i;
		}
	}

	if (nearest == -1) {
		cout << "NONE" << endl;
	} else {
		cout << "\nNearest charging station from " << locations[index].locationName << ":" << endl;
		cout << setw(8) << "Index" << setw(20) << "Location name" << setw(20) << "Charging station" << setw(20) << "Charging price" << endl;
		locations[nearest].printLocation();
		cout << "\nDistance: " << minDist << " km" << endl;
	}
}

#endif /* EVCHARGING_H_ */
