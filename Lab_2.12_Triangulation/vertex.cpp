#include "stdafx.h"
#include "vertex.h"
#include "GL/glut.h"
#include <iostream>


vertex::Node::Node(int posX, int posY) {
	x = posX;
	y = posY;
	next = NULL;
	prev = NULL;
}
vertex::Node::~Node() {
	next = NULL;
	prev = NULL;
}

void vertex::draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(5.0);
	if(!edges.empty())
	for (int i = 0; i < edges.size(); i++) {
		glColor3f(0.0f, 0.5f, 1.0f);
		//drawing edges
		glBegin(GL_LINES);
		glVertex3f(edges[i].from->x, 400 - edges[i].from->y, 0.0);
		glVertex3f(edges[i].to->x, 400 - edges[i].to->y, 0.0);
		glEnd();
		//drawing vertex
		glBegin(GL_POINTS);
		glColor3f(1.0f, 0.5f, 0.0f);
		glVertex3f(edges[i].from->x, 400 - edges[i].from->y, 0.0);
		glVertex3f(edges[i].to->x, 400 - edges[i].to->y, 0.0);
		glEnd();
	}
	else if (!empty()) {
		glBegin(GL_POINTS);
		glColor3f(1.0f, 0.5f, 0.0f);
		glVertex3f(first->x, 400 - first->y, 0.0);
		glEnd();
	}
	glFlush();
}

vertex::vertex() {
	first = NULL;
	last = NULL;
	size = 0;
}

vertex::~vertex() {
	while (!empty())
		pop();
}

bool vertex::empty(){
	if (size == 0)
		return true;
	else return false;
}

//push new vertex
void vertex::push(int posX, int posY) {
	Node *curr = new Node(posX, posY); ;
	if (empty())
		first = curr;
	else {
		curr->prev = last;
		last->next = curr;
	}
	last = curr;
	size++;
	if(size>1)
	ways(last);
	
}

void vertex::pop() {
	if (empty()) return;
	Node* delNode = first;
	first = first->next;
	delNode->next = NULL;
	delNode->prev = NULL;
	size--;
}

vertex::Node *vertex::getFirst() {
	return first;
}

vertex::Node *vertex::getLast() {
	return last;
}


//add new ways
void vertex::ways(Node*last){
	Node* curr = last->prev;
	while(curr != NULL){
		bridge newBr;
		newBr.from = last;
		newBr.to = curr;
		newBr.lenght = pow((last->x-curr->x), 2)+pow((last->y-curr->y), 2);
		edges.push_back(newBr);
		curr = curr->prev;
	}
	qSort(edges, 0, edges.size()-1);
}

//sorting edges
void vertex::qSort(std::vector<bridge>&s_arr, int first, int last)
{
	int i = first, j = last, x = s_arr[(first + last) / 2].lenght;

    do {
		while (s_arr[i].lenght < x) i++;
		while (s_arr[j].lenght > x) j--;

        if(i <= j) {
			if (s_arr[i].lenght > s_arr[j].lenght) 
				std::swap(s_arr[i], s_arr[j]);
            i++;
            j--;
        }
    } while (i <= j);

    if (i < last)
        qSort(s_arr, i, last);
    if (first < j)
        qSort(s_arr, first, j);
}

//triangulation of vertex
void vertex::triangulate(){
	if(edges.size()!=0){
	bool cross;
	for(int i = 1; i < edges.size(); ){
		cross = 1;
		for(int j = i-1; j>=0; j--){
			if(!isCross(&edges[i], &edges[j]))
				cross = 0;
			else {
				cross = 1;
				break;
			}
		}
		if(!cross)
			i++;
		else edges.erase(edges.begin() + i); 
	}
	}
}

bool vertex::isCross(bridge *first, bridge *second ){
	//coordinates of first line
	int ax1 = first->from->x;
	int ay1 = first->from->y;
	int ax2 = first->to->x ;
	int ay2 = first->to->y ;
	//coordinates of second line
	int bx1 = second->from->x;
	int by1 = second->from->y;
	int bx2 = second->to->x ;
	int by2 = second->to->y ;
	float v1,v2,v3,v4;
   v1 =(bx2-bx1)*(ay1-by1)-(by2-by1)*(ax1-bx1);
   v2 =(bx2-bx1)*(ay2-by1)-(by2-by1)*(ax2-bx1);
   v3 =(ax2-ax1)*(by1-ay1)-(ay2-ay1)*(bx1-ax1);
   v4 =(ax2-ax1)*(by2-ay1)-(ay2-ay1)*(bx2-ax1);
   if((v1*v2<0) && (v3*v4<0)) //check cross
	   return true;
   else return false;
}