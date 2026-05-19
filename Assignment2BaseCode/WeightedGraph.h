/*
 * WeightedGraph.h
 *
 *  Created on: 24 Apr 2026
 *      Author: Dongmo
 */
#ifndef H_weightedGraph
#define H_weightedGraph

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cfloat>

using namespace std;

class WeightedGraphType {
protected:
	int gSize;      //number of vertices
	list<int> *graph; // Store adjacency list
	double **weights; // Store weights of edges
	double *smallestWeight;
	int *prev;
public:
	WeightedGraphType(int size = 0);
	~WeightedGraphType();

	list<int> getAdjacencyList(int index) {
		return graph[index];
	}

	double getWeight(int i, int j) {
		return weights[i][j];
	}

	double getSmallestWeight(int j) { return smallestWeight[j]; }
	int getPrev(int j) { return prev[j]; }

	void shortestPath(int vertex);
	void printAdjacencyList();
	void printAdjacencyMatrix();
};

WeightedGraphType::WeightedGraphType(int size) {
	gSize = 0;
	ifstream infile;
	char fileName[50] = "MyWeights.txt";

//	cout << "Enter graph adjacency matrix file name: ";
//	cin >> fileName;
//	cout << endl;

	infile.open(fileName);

	if (!infile) {
		cout << "Cannot open input file." << endl;
		return;
	}

	gSize = size;

	graph = new list<int> [gSize];

	weights = new double*[gSize];

	for (int i = 0; i < gSize; i++)
		weights[i] = new double[gSize];

	smallestWeight = new double[gSize];
	prev = new int[gSize];

	for (int i = 0; i < gSize; i++) {
		for (int j = 0; j < gSize; j++) {
			double value;
			infile >> value;
			if (value == 0)
				weights[i][j] = DBL_MAX; //system constant - maximum value of double
			else {
				weights[i][j] = value;
				graph[i].push_back(j);
			}
		}
	}
	infile.close();
}

WeightedGraphType::~WeightedGraphType() {
	for (int i = 0; i < gSize; i++)
		delete[] weights[i];

	delete[] weights;

	delete[] smallestWeight;
	delete[] prev;

	for (int index = 0; index < gSize; index++)
		graph[index].clear();

	delete[] graph;
}

void WeightedGraphType::shortestPath(int vertex) {
	for (int j = 0; j < gSize; j++)
		smallestWeight[j] = weights[vertex][j];

	bool *weightFound;
	weightFound = new bool[gSize];

	for (int j = 0; j < gSize; j++)
		weightFound[j] = false;

	for (int j = 0; j < gSize; j++)
		prev[j] = -1;

	for (int j = 0; j < gSize; j++)
		if (weights[vertex][j] != DBL_MAX)
			prev[j] = vertex;

	weightFound[vertex] = true;
	smallestWeight[vertex] = 0;

	for (int i = 0; i < gSize - 1; i++) {
		double minWeight = DBL_MAX;
		int v = -1;

		for (int j = 0; j < gSize; j++)
			if (!weightFound[j])
				if (smallestWeight[j] < minWeight) {
					v = j;
					minWeight = smallestWeight[v];
				}

		if (v == -1) break;

		weightFound[v] = true;

		for (int j = 0; j < gSize; j++)
			if (!weightFound[j])
				if (minWeight != DBL_MAX && weights[v][j] != DBL_MAX)
					if (minWeight + weights[v][j] < smallestWeight[j]) {
						smallestWeight[j] = minWeight + weights[v][j];
						prev[j] = v;
					}
	}

	delete[] weightFound;
}

void WeightedGraphType::printAdjacencyMatrix() { //print adjacency matrix for debug purpose
	cout<<"\nAdjacency Matrix" << endl;
	for (int i = 0; i < gSize; i++) {
		for (int j = 0; j < gSize; j++) {
			cout << setw(8) << (weights[i][j] == DBL_MAX ? 0.0 : weights[i][j]); //as adjacency value, zero means no direct connection
		}
		cout << endl;
	}
}

void WeightedGraphType::printAdjacencyList() { //print adjacency list for debug purpose
	cout<<"\nAdjacency List" << endl;
	for (int index = 0; index < gSize; index++) {
		cout << index << ": ";
		for (int e : graph[index])
			cout << e << " ";
		cout << endl;
	}

	cout << endl;
}


#endif
