/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * A simple program that uses the JacobiSolver class to solve
 * a system of linear equations. The program takes a single
 * parameter: the file containing the system of linear
 * equations (as generated by gen_lineq.py)
 */

#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;

#include "LinearEquations.h"
#include "JacobiSolver.h"

int main(int argc, char** argv)
{
	if(argc!=2)
		cerr << "Usage: itersolver FILENAME";

	ifstream ifs;
	char* fname = argv[1];
	ifs.open(fname);

	// Read the system of linear equations
	LinearEquations leq = LinearEquations::fromText(ifs);

	// Create the solver
	JacobiSolver jacobi(leq);

	// If the system is not too big, print it out.
	if(leq.numEq <= 20)
		cout << "Solving the following system: " << endl << endl << leq << endl;

	// Solve the system
	if (jacobi.solve() == 0)
	{
		// If the algorithm converges, print the values
		// of x and b

		for(int i=0; i<leq.numVar; i++)
			cout << "x_" << i << " = " << jacobi.getSolvedX(i) << endl;
		cout << endl;
		for(int j=0; j<leq.numEq; j++)
		{
			cout << "b_" << j << " = " << jacobi.getSolvedB(j);
			cout << " (" << leq.b[j] << ")" << endl;
		}

		cout << "Solved in " << jacobi.getNumIterations() <<" iterations." << endl << endl;
	}
	else
		cout << "Solver did not converge" << endl;

	ifs.close();
}