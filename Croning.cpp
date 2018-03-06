#include "stdafx.h"
#include "Croning.h"

#include <math.h>
#include <iostream>
#include <Windows.h>

using std::cout;
using std::cin;
using std::endl;

const double PI = 3.14159;

Croning::Croning()
{
	ShowSolutions();

	//ShowGraphPoints();
	ShowEnergies();

	system("PAUSE");
}


Croning::~Croning()
{
}

double Croning::f(const double x)
{
	return omegaA / (x) * sin(x) + cos(x);
}

double Croning::dfdx(const double x)
{
	double dx = 0.000001;
	return (f(x + dx) - f(x)) / dx;
}

double Croning::renorm(double x)
{
	return acos(f(x));
}

void Croning::ShowGraphPoints()
{
	cout << "Calculating the graph..." << endl;

	for (double x = 0; x < 3 * PI; x += dk)
	{
		cout << x << endl;
	}

	cout << "+++++++++++" << endl;

	for (double x = 0; x < 3 * PI; x += dk)
	{
		cout << f(x) << endl;
	}
}

void Croning::ShowSolutions()
{
	effectivePoints[0] = FindSolution(2, -0.015, 1);
	effectivePoints[3] = FindSolution(6, 0.01, 1);
	effectivePoints[4] = FindSolution(7, -0.01, 1);

	effectivePoints[1] = FindSolution(3, -0.01, 2);
	effectivePoints[2] = FindSolution(4, 0.01, 2);
	
	FindEffectiveMasses();

	FindEnergies();
	
	cout << "+++++++++ZONES++++++++++++" << endl;
	cout << "++POINT+|+++++MASS++++|+++ENERGY++++|" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << effectivePoints[i] << " | " 
			<< effectiveMasses[i] << " | " 
			<< energies[i] << " | "
			<< endl;
	}
	cout << "\n+++++++++ZONES++++++++++++" << endl;
}

double Croning::FindSolution(double startPoint, double df, int mode)
{
	double currentxX = startPoint;
	double previousX = 0;

	//cout << "+++++++++TECHICAL++++++++++" << endl;
	while (abs(currentxX - previousX) > accuracy)
	{
		//cout << "i-1: " << previousX << "; i: " << currentxX << endl;
		previousX = currentxX;

		if (mode == 1)
		{
			currentxX = previousX - df * (omegaA * sin(previousX) + previousX * cos(previousX) - previousX);
		}
		else if(mode == 2)
		{
			currentxX = previousX - df * (omegaA * sin(previousX) + previousX * cos(previousX) + previousX);
		}
	}
	//cout << "+++++++++TECHICAL++++++++++" << endl;
	return currentxX;
}

void Croning::ShowEnergies()
{
	cout << "Calculating the energy..." << endl;

	for (double x = 0; x < 3 * PI; x += dk)
	{
		cout << x << endl;
	}

	cout << "+++++++++++" << endl;

	for (double x = 0; x < 3 * PI; x += dk)
	{
		cout << renorm(x) << endl;
	}

	cout << "+++++++++++" << endl;

	for (double x = 0; x < PI; x += dk)
	{
		cout << CalculateEnergyInPoint(x , 0) << endl;
	}
	for (double x = PI; x < 2 * PI; x += dk)
	{
		cout << CalculateEnergyInPoint(x, 0) << endl;
	}
	for (double x = 2 * PI; x < 3 * PI; x += dk)
	{
		cout << CalculateEnergyInPoint(x, 0) << endl;
	}

	cout << "+++++++++++" << endl;
}

void Croning::FindEffectiveMasses()
{
	for (int i = 0; i < 5; i++)
	{
		effectiveMasses[i] = CalculateEffectiveMassInPoint(effectivePoints[i]);
	}
}

double Croning::CalculateEffectiveMassInPoint(const double x)
{
	return m * dfdx(x) / (x);
}

void Croning::FindEnergies()
{
	for (int i = 0; i < 5; i++)
	{
		energies[i] = CalculateEnergyInPoint(effectivePoints[i], 0);
	}
}

double Croning::CalculateEnergyInPoint(double x, double e)
{
	//double m = CalculateEffectiveMassInPoint(x);
	return e + (h * h * x * x) / (2 * m * a * a);
}
