#include "Graph.h"

void Graph::draw(){
	glColor3f(0.4f, 0.4f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(1.0);
	glBegin(GL_LINES);
	for(int i = 0; i<graph.size(); i++)
		for(int j = 0; j<graph[i].connect.size(); j++){
			glVertex2d(graph[i].x, graph[i].y);
			glVertex2d(graph[graph[i].connect[j]].x, graph[graph[i].connect[j]].y);
		}
	glEnd();
	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(5.0);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	for(int i = 0; i<graph.size(); i++)
			glVertex2d(graph[i].x, graph[i].y);
	glEnd();
	//glFlush();
}

bool connected(vector<int> connect, int k){
	for(int i = 0; i<connect.size(); i++)
		if(connect[i] == k) return true;
	return false;
}

Graph::Graph(int num, int probability)
{
	srand(time(0));
	Node newOne;
	for(int i = 0; i<num; i++){
		newOne.x = rand()%900;
		newOne.y = rand()%600;
		graph.push_back(newOne);
	}
	for(int i = 0; i<num; i++)
		for(int j = 0; j<num; j++){
			if(probability>rand()%100&&j!=i)
				if(!connected(graph[i].connect, j)){
					graph[i].connect.push_back(j);
					graph[j].connect.push_back(i);
				}
		}
}


Graph::~Graph(void){
	graph.clear();
}

int Graph::size(){
	return graph.size();
}
