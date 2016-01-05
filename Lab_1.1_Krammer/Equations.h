#pragma once
class Equations
{
private:
	double **matrix;
	double *solution;
	int size;
	double mainDeterminant;

public:
	Equations(int _size);

	~Equations(void);
	
	//matrix filling
	void setMatrix();

	//show matrix
	void getMatrix();

	//matrix's determinant
	double determinant(int n, double** mat);

	//matrix with changed values
	double** changingMatrix(int);

	//solution calculating
	void findSolution();

	//showing solution
	void getSolution();


};

