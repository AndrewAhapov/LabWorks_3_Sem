#pragma once
#include <vector>
#include <GL\freeglut.h>
#include <iostream>
#include <time.h>
using namespace std;

class Graph
{
private:
	struct Node{
		float x, y;
		vector<int> connect;
	};
	vector<Node> graph;
	friend float distance(int, int, Graph);
	friend void Population(int);
	friend class Population;
public:
	Graph(int, int);
	~Graph(void);
	void draw();
	int size();
};
