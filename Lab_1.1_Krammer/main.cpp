#include <iostream>
#include "Equations.h"

int main()
{
	std::cout << "Enter number of equations: ";
	int n;
	std::cin >> n;
	Equations equationSystem(n);
	equationSystem.setMatrix();
	equationSystem.findSolution();
	equationSystem.getSolution();
	system("pause");
}