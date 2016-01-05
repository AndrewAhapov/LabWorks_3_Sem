#include "iostream"
#include "Equations.h"

Equations::Equations(int _size)
{
	size = _size;
	solution = new double[_size];
	matrix = new double*[_size];
		for (int i = 0; i<_size; i++)
			matrix[i] = new double[_size+1];
	
}
Equations::~Equations(void)
{
	delete[] matrix;
	delete[] solution;
}
	
//matrix filling
void Equations::setMatrix()
{
	std::cout<<"\nEnter your equations:\n";
	for(int i = 0; i<size; i++)
		for(int j = 0; j<=size; j++)
			std::cin >> matrix[i][j];
}

//show matrix
void Equations::getMatrix()
{
	std::cout<<"\n\nYour equations: \n";
	for(int i = 0; i<size; i++)
	{
		for(int j = 0; j<=size; j++)
		{
			std::cout << matrix[i][j];
			if(j<size-1) std::cout<<"X"<<j+1<<" + ";
			else if(j==size-1)std::cout<<"X"<<j+1<<" = ";
		}
		std::cout<<"\n";
	}
}

//matrix's determinant
double Equations::determinant(int n, double **mat)
{
	int c, subi, i, j, subj;
	double **submat = new double*[size], d = 0;
		for(int i = 0; i < n; i++)
			submat[i] = new double;
	if (n == 1) 
		d = mat[0][0];
    if (n == 2) 
        return( (mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]));
    else if(n > 2)
        for(c = 0; c < n; c++)
        {  
            subi = 0;  
            for(i = 1; i < n; i++)
            {  
                subj = 0;
                for(j = 0; j < n; j++)
                {    
                    if (j == c) continue;
                    submat[subi][subj] = mat[i][j];
                    subj++;
                }
                subi++;
            }
		 d = d + (pow(-1 ,c) * mat[0][c] * determinant(n - 1 ,submat));
        }
    return d;
}

//matrix with changed values
double** Equations::changingMatrix(int n)
{
	double **changedMatrix = new double*[size];
		for(int i = 0; i<size; i++)
			changedMatrix[i] = new double;
		for(int i = 0; i<size; i++)
			for(int j = 0; j<size; j++)
				changedMatrix[i][j] = matrix[i][j];
		for(int i = 0; i<size; i++)
			changedMatrix[i][n] = matrix[i][size];

	return changedMatrix;

}

//solution calculating
void Equations::findSolution()
{
	mainDeterminant = determinant(size, matrix);
	if(mainDeterminant!=0)
		for(int i = 0; i<size; i++)
			solution[i] = determinant(size, changingMatrix(i))/mainDeterminant;
	else solution = NULL;
}

//showing solution
void Equations::getSolution()
{
	if(solution!=NULL){
	std::cout<<"\nSolution of your system: \n";
	for(int i = 0; i<size; i++)
		std::cout<<"X"<<i+1<<" = "<<solution[i]<<";\n";
	}
	else std::cout<<"\nYour system has infinitely many solutions or it has no solution!\n";
}
