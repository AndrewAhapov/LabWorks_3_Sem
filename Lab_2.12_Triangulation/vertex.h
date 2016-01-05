#pragma once;
#include <vector>

class vertex
{
private:
	class Node
	{
	private:
		int x, y;
		Node *next, *prev;
		friend class vertex;
	public:
		Node(int, int);
		~Node();
	};
	struct bridge{
		Node*from, *to;
		int lenght;
		};
	Node *first, *last;
	int size;
	std::vector <bridge> edges; //our triangulation edges
public:
	_declspec(dllexport)vertex();
	_declspec(dllexport)~vertex();
	bool empty();
	_declspec(dllexport)void push(int, int);
	void pop();
	void qSort(std::vector<bridge>&,int,int);
	_declspec(dllexport)Node *getFirst();
	_declspec(dllexport)Node *getLast();
	_declspec(dllexport)void ways(Node*);
	_declspec(dllexport)void triangulate();
	bool isCross(bridge*, bridge*);
	_declspec(dllexport)void draw();
};