#pragma once
#include "Graph.h"

class Population
{
private:
	struct Way{
		vector<int> nodeWay;
		float dist;
	};
	vector<Way> Ways; 
	Way TopWay;
public:
	Population(int,  Graph);
	~Population(void);
	void draw(Graph);
	void qSort(vector<Way>&, int, int);
	void nextGen(Graph);
	void bornGen(Graph, int);
	void shuflleW(vector<Way>&);
};