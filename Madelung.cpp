//#include "stdafx.h"
#include "Madelung.h"

#include <iostream>
#include <math.h>

using namespace std;

const double PI = 3.14159;

Madelung::Madelung()
{
	//cout << CalculateError(2) << endl;
	G1 = 1;
	G = G1;
	F = CalculateFunction(6, 8, sqrt(3) / 2, 2 * PI, 1, 0.5) + 2 * 0.5 / sqrt(PI);
	while (G1 < 10)
	{
		Fnext = (CalculateFunction(6, 8, sqrt(3) / 2, 2 * PI, 1, G1) + 2 * (G1) / sqrt(PI));
		
        if (Fnext < F)
		{
			G = G1;
		}

		G1 = G1 + h;
		F = Fnext;
	}
	cout << "G = " << G << endl;

	a1 = CalculateFunction(6, 8, sqrt(3) / 2, 2 * PI, 1, G) + 2 * (G) / sqrt(PI);
	a2 = CalculateFunction(8, 6, 1, 2 * PI*sqrt(3), -1, G) + a1;
	a3 = CalculateFunction(24, 12, sqrt(2), 2 * PI*sqrt(5), +1, G) + a2;
	cout << "a1 = " << a1 << endl;
	cout << "a2 = " << a2 << endl;
	cout << "a3 = " << a3 << endl;

	system("pause");
}


Madelung::~Madelung()
{
}


double Madelung::CalculateError(double A)
{
	double h, F, S, x;

	int n, i;
	n = 10000;
	i = 1;
	h = A / n;
	x = 0;
	F = exp(-pow(x, 2));
	S = F;
	while (i < n)
	{
		x = x + h;
		F = exp(-pow(x, 2));
		S = S + 4 * F;
		i = i + 2;
		if (i < n)
		{
			x = x + h;
			F = exp(-pow(x, 2));
			S = S + 2 * F;
		}
		else { break; }
	}
	x = A;
	F = exp(-pow(x, 2));
	S = (S + F)*h / 3;
	return S;
}

double Madelung::CalculateFunction(double Ng, double Nr, double r, double g, double q, double G)
{
	double value = 4 * PI * Ng
                    * exp(-pow(g, 2) * 0.25 / pow(G, 2))
                    * (-2)
                    / pow(g, 2)
    
                + Nr * q * (1 - 2 * CalculateError(G*r)
                    / sqrt(PI)) / r;
	return value;
}

