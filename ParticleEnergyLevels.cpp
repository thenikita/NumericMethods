#include "stdafx.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "ParticleEnergyLevels.h"

using namespace std;

const double PI = 3.14159;

ParticleEnergyLevels::ParticleEnergyLevels()
{
	cout << "************************************************\n";
	cout << "Particle energy leveling program. \nEnter the alpha: ";

	double alpha;
	cin >> alpha;
	cout << "alpha is set to: " << alpha << endl;

	cout << "Enter different neighbour amounts: ";

	double l[3];
	cin >> l[0];
	cin >> l[1];
	cin >> l[2];

	cout << "Neighbour amount is set to: ";
	cout << l[0] << " " << l[1] << " " << l[2] << endl;

	int i = 0;

	for (double k = -3.1; k < 3.1; k += 0.01)
	{
		std::vector<double> frequencies;

		frequencies = GetFrequency(k, l);

		results[i][3] = frequencies[0];
		results[i][4] = frequencies[1];
		results[i][5] = frequencies[2];
		i++;
	}

	i = 0;
	for (double k = -3.1/2.0; k <= 3.1/2.0; k += 0.01)
	{
		std::vector<double> levels;
		std::vector<double> frequencies;

		levels = GetLevels(k, alpha);
		//frequencies = GetFrequency(k, l);

		results[i][0] = levels[0];
		results[i][1] = levels[1];
		results[i][2] = levels[2];
		levels.clear();

		//results[i][3] = frequencies[0];
		//results[i][4] = frequencies[1];
		//results[i][5] = frequencies[2];
		i++;

	}

	ShowResults();
	
	system("PAUSE");
}


ParticleEnergyLevels::~ParticleEnergyLevels()
{
}


std::vector<double> ParticleEnergyLevels::GetLevels(double k, double alpha)
{
	std::vector <double> result;
		double D = (alpha + 1) * (alpha + 1) - 4 * alpha * (1 - cos(k) * cos(k));
		result.insert(result.begin(), k);
		result.insert(result.begin()+1, sqrt((alpha + 1 + sqrt(D)) / 2));
		result.insert(result.begin()+2, sqrt((alpha + 1 - sqrt(D)) / 2));
	return result;
}

std::vector<double> ParticleEnergyLevels::GetFrequency(double k, double l[3])
{
	std::vector<double> result;

	for (int i = 0; i < 3; i++)
	{
		double frequency = 0;
		
		for (int j = 0; j <= l[i]; j++)
		{
			frequency += pow(sin(k*j / 2.0), 2);
		}

		frequency = sqrt(frequency);

		result.push_back(frequency);
	}

	return result;
}

void ParticleEnergyLevels::ShowResults()
{
	ofstream file;
	file.open("file.txt");
	cout << "Results for ENERGY LEVELS:\n";
	file << "PRIVEDENNIE" << endl;
	for (int i = 0; i < 310; i++)
	{
		file << results[i][0] << " ";
		file << results[i][1] << " ";
		file << results[i][2] << " " << endl;
	}

	file << "RASHIRENNIE" << endl;
	for (int i = 0; i < 155; i++)
	{
		file << results[i][0] + PI<< " ";
		file << results[i][1] << endl;
	}
	for (int i = 155; i < 310; i++)
	{
		file << results[i][0] << " ";
		file << results[i][2] << endl;
	}

	file << "POVTORYAUSHIESYA" << endl;
	for (int i = 0; i < 310; i++)
	{
		file << results[i][0] << " ";
		file << results[i][1] << " ";
		file << results[i][2] << " " << endl;
	}
	for (int i = 0; i < 310; i++)
	{
		file << results[i][0] + PI << " ";
		file << results[i][1] << " ";
		file << results[i][2] << " " << endl;
	}
	for (int i = 0; i < 310; i++)
	{
		file << results[i][0] + 2 * PI << " ";
		file << results[i][1] << " ";
		file << results[i][2] << " " << endl;
	}

	file << "Results for FREQUENCIES:\n";
	for (int i = 0; i < 620; i++)
	{
		file << -3.1 + i * 0.01 << " ";
		file << results[i][3] << " ";
		file << results[i][4] << " ";
		file << results[i][5] << " " << endl;
	}
} 