#include "Population.h"
#include "omp.h"

//distance between two Nodes
float distance(int first, int second, Graph myGraph){
	if(second == -1) return abs(FLT_MAX);
	return sqrtf(pow((myGraph.graph[first].x-myGraph.graph[second].x), 2) + pow((myGraph.graph[first].y-myGraph.graph[second].y), 2));
}


float distanceSumm(vector<int>forSumm, Graph graph){
	float dist = 0;
	for(int i = 0; i<forSumm.size()-1; i++)
		dist += distance(forSumm[i], forSumm[i+1], graph);
	dist += distance(forSumm[0], forSumm[forSumm.size()-1], graph);
		return dist;
}

void shuflle(vector <int> &forShuffle){
	for(int i = 0; i< forShuffle.size(); i++)
		swap(forShuffle[i], forShuffle[rand()%forShuffle.size()]);
}

void Population::draw(Graph myGraph){
	glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0f, 0.0f, 0.0f);
		myGraph.draw();
		glLineWidth(2.0);
		glBegin(GL_LINES);
			glVertex2d(myGraph.graph[TopWay.nodeWay[0]].x, myGraph.graph[TopWay.nodeWay[0]].y);
			glVertex2d(myGraph.graph[TopWay.nodeWay[TopWay.nodeWay.size()-1]].x, myGraph.graph[TopWay.nodeWay[TopWay.nodeWay.size()-1]].y);
		for(int j = 0; j<TopWay.nodeWay.size()-1; j++){
			glVertex2d(myGraph.graph[TopWay.nodeWay[j]].x, myGraph.graph[TopWay.nodeWay[j]].y);
			glVertex2d(myGraph.graph[TopWay.nodeWay[j+1]].x, myGraph.graph[TopWay.nodeWay[j+1]].y);
		}
		glEnd();
		glFlush();
		nextGen(myGraph);
	}

Population::Population(int num, Graph graph)
{
	Way oneWay;
	oneWay.dist = 0;
	for(int i = 0; i< num; i++)
		oneWay.nodeWay.push_back(i);
	//to craete way we shuflle
	//array of vertex's number
	for(int i = 0; i< 6; i++){
		shuflle(oneWay.nodeWay);
		oneWay.dist = 0;
		for(int j = 0; j< num-1; j++)
			oneWay.dist += distance(oneWay.nodeWay[j], oneWay.nodeWay[j+1], graph);
		oneWay.dist += distance(oneWay.nodeWay[0], oneWay.nodeWay[num-1], graph);
		Ways.push_back(oneWay);
	}
	TopWay = Ways[0];
	draw(graph);
}


Population::~Population(void)
{
	Ways.~vector();
}

//sorting population
void Population::qSort(vector<Way>&s_arr, int first, int last)
{
	float i = first, j = last, x = s_arr[(first + last) / 2].dist;
    do {
		while (s_arr[i].dist < x) i++;
		while (s_arr[j].dist > x) j--;

        if(i <= j) {
			if (s_arr[i].dist > s_arr[j].dist) swap(s_arr[i], s_arr[j]);
            i++;
            j--;
        }
    } while (i <= j);

    if (i < last)
        qSort(s_arr, i, last);
    if (first < j)
        qSort(s_arr, first, j);
}

void Population::bornGen(Graph graph, int wSize){
	int good, down1, down2, g1, g2,  up1, up2;
	float bestDistUp, bestDistDown, dist;

	omp_set_num_threads(5);
	#pragma omp parallel for //pharallel region for creating nextGen
	for(int j = 0; j<Ways.size()/2; j++)
	{
		dist = 0;
		vector<int>child;

		child.push_back(Ways[j].nodeWay[0]);

		for(int i = 1; i< wSize; i++)
		{
			g1 = 0, g2 = 0;
			float bestDistUp, bestDistDown, dist = 0;
			while(Ways[j].nodeWay[g1] != child[child.size()-1]) 
				g1++;
			while(Ways[j+1].nodeWay[g2] != child[child.size()-1])
				g2++;
			up1 = g1+1; 
			up2 = g2+1;
			down1 = g1-1; down2 = g2-1;
			if(up1 == wSize) up1 = 0;
			if(up2 == wSize) up2  = 0;
			if(down1 == -1) down1 = wSize-1;
			if(down2 == -1) down2  = wSize-1;

			//finding best gen
			bestDistUp = distance(Ways[j].nodeWay[g1], Ways[j].nodeWay[up1], graph);
			good = Ways[j].nodeWay[up1];
			if(bestDistUp > distance(Ways[j+1].nodeWay[g2], Ways[j+1].nodeWay[up2], graph)){
				bestDistUp = distance(Ways[j+1].nodeWay[g2], Ways[j+1].nodeWay[up2], graph);
				good = Ways[j+1].nodeWay[up2];
			}

			bestDistDown = distance(Ways[j].nodeWay[g1], Ways[j].nodeWay[down1], graph);
			if(bestDistUp > bestDistDown){
				swap(bestDistUp, bestDistDown);
				good = Ways[j].nodeWay[down1];
			}
			if(bestDistUp>=distance(Ways[j+1].nodeWay[g2], Ways[j+1].nodeWay[down2], graph)){
				bestDistUp = distance(Ways[j+1].nodeWay[g2], Ways[j+1].nodeWay[down2], graph);
				good = Ways[j+1].nodeWay[down2];
			}

			if(good == -1){
				up1 = 0; up2 = 0;
				while(Ways[j].nodeWay[up1] == -1  || Ways[j].nodeWay[up1] == child[child.size()-1])
					up1++;
				while(Ways[j+1].nodeWay[up2] != Ways[j].nodeWay[up1])
					up2++;
				good = Ways[j].nodeWay[up1];
			}
			Ways[j].nodeWay[g1] = -1;
			Ways[j+1].nodeWay[g2] = -1;
			child.push_back(good);
			dist += bestDistUp;
		}

		//add child to population
		dist += distance(child[0], child[child.size()-1], graph);
		Ways[j].nodeWay = child;
		Ways[j].dist = dist;
		Ways.push_back(Ways[j]);
		if(j + 2 < wSize)
			Ways[j] = Ways[j+2];
		Ways.erase(Ways.begin()+j+1);
	}
}

void Population::shuflleW(vector<Way>&forShuffle){
	for(int i = 0; i< forShuffle.size(); i++)
		swap(forShuffle[i], forShuffle[rand()%forShuffle.size()]);
}

void Population::nextGen(Graph graph){
	srand(time(0));
	//in case if best way hasn't changed
	//we make some mutations
	if(TopWay.dist > Ways[0].dist)
		TopWay = Ways[0];
	else{
		for(int i = 0; i<Ways.size(); i+=2){
		int k = Ways[i].nodeWay.size();
		//in this case 'mutation' is random
		//swap of vertexes in ways
		//Mutation applies only to the
		//worst part of population
		swap(Ways[i].nodeWay[rand()%k], Ways[i].nodeWay[rand()%k]);
		swap(Ways[i].nodeWay[rand()%k], Ways[i].nodeWay[rand()%k]);
		swap(Ways[i].nodeWay[rand()%k], Ways[i].nodeWay[rand()%k]);
		Ways[i].dist = distanceSumm(Ways[i].nodeWay,graph);
		}
		//also we shuflled ways to 
		//change order of pairing
		shuflleW(Ways);
	}
	bornGen(graph, Ways[0].nodeWay.size());
	qSort(Ways, 0, Ways.size()-1);
	if(TopWay.dist > Ways[0].dist)
		TopWay = Ways[0];
	else Ways[0] = TopWay;
	draw(graph);
}