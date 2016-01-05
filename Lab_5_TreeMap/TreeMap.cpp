#include "TreeMap.h"

// --------------------------------------------
void rec_display_RB(TreeNode* head, float x, float y, float base)
{
	glRasterPos2f(x - 1, y - 2);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	char* str = new char[10];
	itoa(head->key, str, 10);
	glutBitmapString(GLUT_BITMAP_HELVETICA_12, (unsigned char*)str);
	glPointSize(10.0);
	glColor4f(0.3f, 0.7f, 0.0f, 1.0f);
	glRasterPos2f(x + 1, y - 2);
	char* st = new char[10];
	itoa(head->data, st, 10);
	glutBitmapString(GLUT_BITMAP_HELVETICA_12, (unsigned char*)st);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	if (head->color == RED) glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	if (head->left)
	{
		glVertex2d(x, y);
		glVertex2d(x - base / 2, y + 10);
	}
	if (head->right)
	{
		glVertex2d(x, y);
		glVertex2d(x + base / 2, y + 10);
	}
	glEnd();
	if (head->right) rec_display_RB(head->right, x + base / 2, y + 10, base / 2);
	if (head->left) rec_display_RB(head->left, x - base / 2, y + 10, base / 2);
}

void TreeMap::draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.1, 0.1, 0.1);
	if (getRoot() != NULL) rec_display_RB(getRoot(), 50.0, 10.0, 50);
	glutSwapBuffers();
}

// Color functions
void TreeMap::paintBlack(TreeNode *tar) {
	tar->color = BLACK;
}
void TreeMap::paintRed(TreeNode *tar) {
	tar->color = RED;
}
int TreeMap::getColor(TreeNode *tar) {
	return(tar ? tar->color : 0);
}

// Returns brother
TreeNode* TreeMap::getBro(TreeNode *tar) {
	TreeNode *parent = tar->parent;
	if (parent) {
		if (tar == parent->left) return parent->right;
		else return parent->left;
	}
	return NULL;
}

void TreeMap:: rotRight(TreeNode *tar) {
	// Save parent
	TreeNode *parent = tar->parent;
	bool wasRoot = !(bool)parent;

	bool wasLeftChild = false;
	if (parent && tar == parent->left) wasLeftChild = true;

	// Left son will be new root;
	TreeNode *newRoot = tar->left;		// Get pointer to new root
	newRoot->parent = parent;		// its parent was 'tar', switch to 'tar->parent'

	tar->left = newRoot->right;		// Attach right subtree of new root to 'tar'
	tar->left->parent = tar;

	newRoot->right = tar;	// Attach 'tar' as right subtree to new root
	tar->parent = newRoot;	// Switch its parent to 'newRoot'

							// Modify global parent key
	if (wasRoot) root = newRoot;
	else {
		if (wasLeftChild) parent->left = newRoot;
		else parent->right = newRoot;
	}
}

void TreeMap::rotLeft(TreeNode *tar) {
	TreeNode *parent = tar->parent;
	bool wasRoot = !(bool)parent;

	bool wasLeftChild = false;
	if (parent && tar == parent->left) wasLeftChild = true;

	// Right son will be new root;
	TreeNode *newRoot = tar->right;		// Get pointer to new root
	newRoot->parent = parent;	// its parent was 'tar', switch to 'tar->parent'

	tar->right = newRoot->left;		// Attach left subtree of new root to 'tar'
	tar->right->parent = tar;

	newRoot->left = tar;	// Attach 'tar' as left subtree to new root
	tar->parent = newRoot;	// Switch its parent to 'newRoot'

							// Modify global parent key
	if (wasRoot) root = newRoot;
	else {
		if (wasLeftChild) parent->left = newRoot;
		else parent->right = newRoot;
	}
}

void TreeMap::insert(int key, int pos) {

	TreeNode *parent = NULL;
	TreeNode *cur = root;

	// Find place for rbNode
	while (cur->isLeaf == false) {
		if (key < cur->key) {
			parent = cur;
			cur = cur->left;
		}
		else if (key > cur->key) {
			parent = cur;
			cur = cur->right;
		}
		else return;
	}

	cur = new TreeNode(key, pos, parent);
	insertCase0(cur);
}

// rbNode is new root
void TreeMap::insertCase0(TreeNode *tar) {
	if (tar->parent)
		insertCase1(tar);
	else root = tar;
	paintBlack(root);
}

// Parent is black - no violation
void TreeMap::insertCase1(TreeNode *tar) {
	if (tar->parent->color != BLACK) insertCase2(tar);
}

// Parent is red, uncle is red
void TreeMap::insertCase2(TreeNode *tar) {
	TreeNode *grandpa = tar->parent->parent;

	if (grandpa) {
		TreeNode *parent = tar->parent;
		TreeNode *uncle = getBro(parent);

		if (uncle->color == RED) {
			paintBlack(parent);
			paintBlack(uncle);
			paintRed(grandpa);

			insertCase0(grandpa);
		}
		else insertCase3(tar);
	}
}

// Red parent, black uncle, parent is lSon (rSon), tar is rSon (lSon);
void TreeMap::insertCase3(TreeNode *tar) {

	TreeNode *parent = tar->parent;
	TreeNode *uncle = getBro(parent);
	TreeNode *grandpa = parent->parent;

	if (parent == grandpa->left && tar == parent->right) {
		rotLeft(parent); tar = parent;
	}
	else if (parent == grandpa->right && tar == parent->left) {
		rotRight(parent); tar = parent;
	}
	insertCase4(tar);

}

// Red parent, black uncle, parent is lSon (rSon), tar is lSon (rSon);
void TreeMap::insertCase4(TreeNode *tar) {
	TreeNode *parent = tar->parent;
	TreeNode *uncle = getBro(parent);
	TreeNode *grandpa = parent->parent;

	paintBlack(parent);
	paintRed(grandpa);

	if (parent == grandpa->left && tar == parent->left) {
		rotRight(grandpa);
	}
	else {
		rotLeft(grandpa);
	}
}

TreeNode* TreeMap::findValidDel(TreeNode *tar) {
	// If rbNode has two not-leaf children:
	if (tar->left->isLeaf == false && tar->right->isLeaf == false) {
		TreeNode *ans = tar->right;
		while (ans->left->isLeaf == false) {
			ans = ans->left;
		}
		return ans;
	}
	else return tar;
}


void TreeMap::replacerbNode(TreeNode *src, TreeNode *tar) {
	TreeNode *parent = src->parent;
	if (parent) {
		if (src == parent->left) parent->left = tar;
		else parent->right = tar;
	}
	else root = tar;
	tar->parent = parent;
}

// Delete rbNode 'tar'
void TreeMap::deleterbNode(TreeNode *tar) {

	TreeNode *child = (tar->right->isLeaf ? tar->left : tar->right);
	replacerbNode(tar, child);

	if (tar->color == BLACK) {
		// Deleting black rbNode with red child
		if (child->color == RED) {
			paintBlack(child);
		}
		// Deleting black rbNode with black child
		else deleteCase1(child);
	}

}

// 1) Child is new root
void TreeMap::deleteCase1(TreeNode *tar) {
	if (tar->parent != NULL) deleteCase2(tar);
}

// 2) Brother is red
void TreeMap::deleteCase2(TreeNode *tar) {

	TreeNode *bro = getBro(tar);

	if (bro->color == RED) {

		paintRed(tar->parent);
		paintBlack(bro);

		if (tar == tar->parent->left)
			rotLeft(tar->parent);
		else
			rotRight(tar->parent);
	}
	deleteCase3(tar);
}

// 3) Brother is black, its children are black
void TreeMap::deleteCase3(TreeNode *tar) {
	TreeNode *bro = getBro(tar);

	TreeNode *lchild = bro->left;
	TreeNode *rchild = bro->right;

	if ((tar->parent->color == BLACK) &&
		(bro->color == BLACK) &&
		(lchild->color == BLACK) &&
		(rchild->color == BLACK)) {
		paintRed(bro);
		deleteCase1(tar->parent);
	}
	else {
		deleteCase4(tar);
	}
}

// 4) Bro and its children are black, but parent is red
void TreeMap::deleteCase4(TreeNode *tar) {
	TreeNode *bro = getBro(tar);

	TreeNode *lchild = bro->left;
	TreeNode *rchild = bro->right;

	if ((tar->parent->color == RED) &&
		(bro->color == BLACK) &&
		(lchild->color == BLACK) &&
		(rchild->color == BLACK)) {
		paintRed(bro);
		paintBlack(tar->parent);
	}
	else deleteCase5(tar);

}

// 5) Bro is black, one son is black, second is red
void TreeMap::deleteCase5(TreeNode *tar) {
	TreeNode *bro = getBro(tar);

	TreeNode *lchild = bro->left;
	TreeNode *rchild = bro->right;

	if (bro->color == BLACK) {

		if ((tar == tar->parent->left) &&
			(rchild->color == BLACK) &&
			(lchild->color == RED)) {
			paintRed(bro);
			paintBlack(lchild);
			rotRight(bro);
		}
		else if ((tar == tar->parent->right) &&
			(lchild->color == BLACK) &&
			(rchild->color == RED)) {
			paintRed(bro);
			paintBlack(rchild);
			rotLeft(bro);
		}
	}
	deleteCase6(tar);
}

// 6) Bro is black, one son is black, second is red
void TreeMap::deleteCase6(TreeNode *tar) {
	TreeNode *bro = getBro(tar);
	TreeNode *lchild = bro->left;
	TreeNode *rchild = bro->right;

	bro->color = tar->parent->color;
	paintBlack(tar->parent);

	if (tar == tar->parent->left) {
		paintBlack(rchild);
		rotLeft(tar->parent);
	}
	else {
		paintBlack(lchild);
		rotRight(tar->parent);
	}
}

TreeNode* TreeMap::getRoot() 
{
	return root;
}

void TreeMap::push(int key, int pos)
{
	insert(key, pos);
}

void TreeMap::pop(int key)
{
	TreeNode *cur = root;

	// Find rbNode with key
	while (!cur->isLeaf && cur->key != key) {
		if (key < cur->key) cur = cur->left;
		else cur = cur->right;
	}

	// If key not found
	if (cur->isLeaf) {
		//cout << "Not found!" << endl;
		return;
	}

	// If it was the only rbNode, put root
	if (cur == root && cur->left->isLeaf && cur->right->isLeaf) {
		delete cur;
		root = NULL;
		return;
	}

	TreeNode *toDel = findValidDel(cur);
	swap(toDel->key, cur->key);
	deleterbNode(toDel);
}

TreeMap::TreeMap() {
	root = new TreeNode(0, 0, NULL, true);
};
// Tree rbNode constructor
TreeNode::TreeNode(int _key, int _data, TreeNode *_parent, bool _isLeaf) :isLeaf(_isLeaf) {
	key = _key;
	parent = _parent;
	data = _data;
	if (parent) {
		if (key < parent->key) parent->left = this;
		else parent->right = this;
	}

	if (isLeaf) {
		color = BLACK;
		left = right = NULL;
	}
	else {
		color = RED;
		left = new TreeNode(0, 0, this, true), right = new TreeNode(0, 0, this, true);
	}
}


