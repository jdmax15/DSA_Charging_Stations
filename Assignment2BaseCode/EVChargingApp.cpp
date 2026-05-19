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
	int choice;

	do {
		cout << "\n--- Sydney EV Charging Menu ---" << endl;
		cout << "1. Print locations" << endl;
		cout << "2. Print adjacency matrix" << endl;
		cout << "3. List stations by price" << endl;
		cout << "4. Find adjacent charging stations" << endl;
		cout << "5. Find nearest charging station" << endl;
		cout << "6. Find cheapest charging station" << endl;
		cout << "0. Exit" << endl;
		cout << "Enter choice: ";
		cin >> choice;
		cout << endl;

		switch (choice) {
		case 1:
			charging.printLocations();
			break;
		case 2:
			charging.printAdjacencyMatrix();
			break;
		case 3:
			charging.sortLocations();
			break;
		case 4:
			charging.printAdjacentStations();
			break;
		case 5:
			charging.findNearestStation();
			break;
		case 6:
			charging.findCheapestStation();
			break;
		case 0:
			cout << "Exiting." << endl;
			break;
		default:
			cout << "Invalid choice." << endl;
			break;
		}
	} while (choice != 0);

	return 0;
}
