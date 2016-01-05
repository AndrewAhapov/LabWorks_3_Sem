#include <iostream>
#include "GL/freeglut.h"
using namespace std;

enum NodeColor { BLACK, RED };

class TreeNode {
public:
	friend class TreeMap;
	int key;
	bool isLeaf;
	NodeColor color;
	TreeNode *left, *right, *parent;
	int data;
	TreeNode(int _key = 0, int pos = 0, TreeNode *parent = NULL, bool _isLeaf = false);
};

class TreeMap {

	TreeNode *root;
	// Color functions
	void paintBlack(TreeNode *tar);
	void paintRed(TreeNode *tar);
	int	getColor(TreeNode *tar);

	// Returns brother
	TreeNode *getBro(TreeNode *tar);

	// Right and left rotations
	void rotRight(TreeNode *tar);
	void rotLeft(TreeNode *tar);

	// Maintain Red-Black tree balance after inserting rbNode 'tar' 
	void insert(int key, int pos);

	// rbNode is new root
	void insertCase0(TreeNode *tar);

	// Parent is black - no violation
	void insertCase1(TreeNode *tar);

	// Parent is red, uncle is red
	void insertCase2(TreeNode *tar);

	// Red parent, black uncle, parent is lSon (rSon), tar is rSon (lSon);
	void insertCase3(TreeNode *tar);

	// Red parent, black uncle, parent is lSon (rSon), tar is lSon (rSon);
	void insertCase4(TreeNode *tar);

	// Internal methods searching 
	// for element to delete
	TreeNode *findValidDel(TreeNode *tar);

	// Replaces rbNode src in tree with tar
	void replacerbNode(TreeNode *src, TreeNode *tar);

	// Delete rbNode 'tar'
	void deleterbNode(TreeNode *tar);

	// 1) Child is new root
	void deleteCase1(TreeNode *tar);

	// 2) Brother is red
	void deleteCase2(TreeNode *tar);

	// 3) Brother is black, its children are black
	void deleteCase3(TreeNode *tar);

	// 4) Bro and its children are black, but parent is red
	void deleteCase4(TreeNode *tar);

	// 5) Bro is black, one son is black, second is red
	void deleteCase5(TreeNode *tar);

	// 6) Bro is black, one son is black, second is red
	void deleteCase6(TreeNode *tar);

public:
	TreeMap();
	TreeNode *getRoot(); 
	void push(int key, int pos);
	void pop(int key);
	void draw();
};