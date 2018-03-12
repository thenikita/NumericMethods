#pragma once
class Croning
{
public:
	Croning();
	~Croning();
private:
	double a = 2e-8;
	double omegaA = 4;
	double m = 9.1e-31;
	double h = 1.054e-34;

	double accuracy = 1e-3;
	double dk = 0.1;
	
	double effectiveMasses[5];
	double effectivePoints[5];
	double energies[5];

private:
	double f(double x);
	double dfdx(double x);
	double renorm(double x);

	void ShowGraphPoints();
	void ShowSolutions();
	double FindSolution(double startPoint, double df, int mode);

	void ShowEnergies();

	void FindEffectiveMasses();
	double CalculateEffectiveMassInPoint(double x);
	void FindEnergies();
	double CalculateEnergyInPoint(double x, double e);
};
