#pragma once
class Madelung
{
public:
	Madelung();
	~Madelung();

private:
	double h = 0.0001;
	double a1, a2, a3;
	double G1;
	double G;
	double F;
	double Fnext;

private:
	double CalculateError(double A);
	double CalculateFunction(
                             double Ng,
                             double Nr,
                             double r,
                             double g,
                             double q,
                             double G);
};

