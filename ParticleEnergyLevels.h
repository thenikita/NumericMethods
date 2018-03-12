#include <vector>

#pragma once
class ParticleEnergyLevels
{
public:
	ParticleEnergyLevels();
	~ParticleEnergyLevels();

private:
	 std::vector<double> GetLevels( double k, double alpha );
	 std::vector<double> GetFrequency( double k, double l[3] );

	 void ShowResults();

	 double results[620][6];
};

