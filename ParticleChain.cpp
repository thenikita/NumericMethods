//#include "stdafx.h"
#include "ParticleChain.h"
#include <iostream>
#include <fstream>
#include <cmath>
//#include <Windows.h>

using std::vector;
using std::cout;
using std::endl;

const double PI = 3.14159;

ParticleChain::ParticleChain(int particleAmount, int time)
{

	ParticleChain::targetTime = time;

	ParticleChain::particleAmount = particleAmount;
	cout << "Particles: " << ParticleChain::particleAmount << endl;

	GenerateParticles();

	for (int i = 0; i < ParticleChain::particleAmount; i++)
	{
		cout << particles[i].GetCoordinate() << " " << particles[i].GetDeviation() << endl;
	}
	MakeIterations();

	system("PAUSE");
}


ParticleChain::~ParticleChain()
{
}

vector<double> ParticleChain::GetChain()
{
	vector<double> chain;

	for (int i = 0; i < particleAmount; i++)
	{
		chain.push_back(particles[i].GetDeviation());
	}

	return chain;
}

void ParticleChain::MakeIterations()
{
	std::ofstream file;
	file.open("file.txt");

	std::ofstream middle;
	middle.open("middle.txt");

	coefs[0][0] = 0;
	coefs[0][1] = 0;
	coefs[0][2] = 0;
	coefs[0][3] = 0;
	coefs[0][4] = 0;

	coefs[particleAmount - 1][0] = 0;
	coefs[particleAmount - 1][1] = 0;
	coefs[particleAmount - 1][2] = 0;
	coefs[particleAmount - 1][3] = 0;
	coefs[particleAmount - 1][4] = 0;

	//ToString(GetChain());

	while ( currentTime < targetTime )
	{
		currentTime += dt;
		
		//speeds
		//K1
		for (int i = 1; i < particleAmount - 1; i++)
		{
			double right = particles[i + 1].GetDeviation();
			double left = particles[i - 1].GetDeviation();
			double middle = particles[i].GetDeviation();

			coefs[i][0] = dt * f(left, middle, right);

			//cout << "K1 = " << coefs[i][0] << " ";
		}
		//cout << endl;
		
		//K2
		for (int i = 1; i < particleAmount - 1; i++)
		{
			double right = particles[i + 1].GetDeviation()
							+ coefs[i + 1][0] / 3.0;
			double left = particles[i - 1].GetDeviation()
							+ coefs[i - 1][0] / 3.0;
			double middle = particles[i].GetDeviation() 
							+ coefs[i][0] / 3.0;

			coefs[i][1] = dt * f(left, middle, right);

			//cout << "K2 = " << coefs[i][0] << " ";
		}
		//cout << endl;

		//K3
		for (int i = 1; i < particleAmount - 1; i++)
		{
			double right = particles[i + 1].GetDeviation()
							+ coefs[i + 1][0] / 6.0
							+ coefs[i + 1][1] / 6.0;
			double left = particles[i - 1].GetDeviation()
							+ coefs[i - 1][0] / 6.0
							+ coefs[i - 1][1] / 6.0;
			double middle = particles[i].GetDeviation()
							+ coefs[i][0] / 6.0
							+ coefs[i][1] / 6.0;

			coefs[i][2] = dt * f(left, middle, right);
			
			//cout << "K3 = " << coefs[i][2] << " ";
		}
		//cout << endl;

		//K4
		for (int i = 1; i < particleAmount - 1; i++)
		{
			double right = particles[i + 1].GetDeviation()
							+ coefs[i + 1][0] / 8.0
							+ coefs[i + 1][2] / 8.0 * 3;
			double left = particles[i - 1].GetDeviation()
							+ coefs[i - 1][0] / 8.0
							+ coefs[i - 1][2] / 8.0 * 3;
			double middle = particles[i].GetDeviation()
							+ coefs[i][0] / 8.0
							+ coefs[i][2] / 8.0 * 3;

			coefs[i][3] = dt * f(left, middle, right);

			//cout << "K4 = " << coefs[i][3] << " ";
		}
		//cout << endl;

		//K5
		for (int i = 1; i < particleAmount - 1; i++)
		{
			double right = particles[i + 1].GetDeviation()
				+ coefs[i + 1][0] / 2.0
				- coefs[i + 1][2] / 2.0 * 3
				+ coefs[i + 1][3] * 2;
			double left = particles[i - 1].GetDeviation()
				+ coefs[i - 1][0] / 2.0
				- coefs[i - 1][2] / 2.0 * 3
				+ coefs[i - 1][3] * 2;
			double middle = particles[i].GetDeviation()
				+ coefs[i][0] / 2.0
				- coefs[i][2] / 2.0 * 3
				+ coefs[i][3] * 2;

			coefs[i][4] = dt * f(left, middle, right);

			//cout << "K5 = " << coefs[i][4] << " ";
		}
		//cout << endl;

		//applying speed
		for (int i = 1; i < particleAmount - 1; i++)
		{
			double speed = particles[i].GetSpeed() + (1 / 6.0) * (coefs[i][0]
																+ 4 * coefs[i][3]
																+ coefs[i][4]);
			particles[i].SetSpeed(speed);
			//cout << "speed#"<< i << " = " << particles[i].GetSpeed() << " ";
		}
		//cout << endl;

		//deviations
		//K1
		for (int i = 1; i < particleAmount - 1; i++)
		{
			coefs[i][0] = dt * particles[i].GetSpeed();

			//cout << "K1 = " << coefs[i][0] << " ";

		}
		//cout << endl;

		//K2
		for (int i = 1; i < particleAmount - 1; i++)
		{
			coefs[i][1] = dt * (particles[i].GetSpeed()
									+ (1.0/3.0) * coefs[i][0]);
			//cout << "K2 = " << coefs[i][1] << " ";
		}
		//cout << endl;

		//K3
		for (int i = 1; i < particleAmount - 1; i++)
		{
			coefs[i][2] = dt * (particles[i].GetSpeed()
									+ (1.0/6.0) * coefs[i][0]
									+ (1.0/6.0) * coefs[i][1]);

			//cout << "K3 = " << coefs[i][2] << " ";

		}
		//cout << endl;

		//k4
		for (int i = 1; i < particleAmount - 1; i++)
		{
			coefs[i][3] = dt * (particles[i].GetSpeed()
									+ (1.0 / 8.0) * coefs[i][0]
									+ (3.0 / 8.0) * coefs[i][2]);

			//cout << "K4 = " << coefs[i][3] << " ";

		}
		//cout << endl;

		//K5
		for (int i = 1; i < particleAmount - 1; i++)
		{
			coefs[i][4] = dt * (particles[i].GetSpeed()
									+ (1.0 / 2.0) * coefs[i][0]
									+ (3.0 / 2.0) * coefs[i][2]
									+ (3.0 / 8.0) * coefs[i][3]);

			//cout << "K5 = " << coefs[i][4] << " ";

		}
		//cout << endl;

		//ERROR
		double error = 0;
		for (int i = 1; i < particleAmount - 1; i++)
		{
			error += 1 / 30.0 * (2.0 * coefs[i][0]
					- 9.0 * coefs[i][2]
					+ 8.0 * coefs[i][3]
					- coefs[i][4]);

		}
		error /= (particleAmount - 2);
		//cout << "E = " << error << endl;

		if (abs(error) > accuracy / 2.0)
		{
			//currentTime -= dt;
			dt /= 2.0;
			//cout << "big error" << endl;
		}
		else if (abs(error) <= (accuracy / 32.0))
		{
			dt *= 2.0;
			//cout << "small error" << endl;
		}

		//cout << dt << " " << currentTime << " " << endl;

		//applying deviations
		for (int i = 1; i < particleAmount - 1; i++)
		{
			double dev = particles[i].GetDeviation() + (1 / 6.0) * (coefs[i][0]
																	+ 4 * coefs[i][3]
																	+ coefs[i][4]);

			particles[i].SetDeviation(dev);
			//cout << "dev#" << i << " = " << particles[i].GetDeviation() << " ";
		}
		//cout << endl;

		//ToString(GetChain());
		
		//Sleep(10);
		
		
		middle << currentTime << " " << particles[15].GetDeviation() << endl;

	}

	//TESTOUTPUT
	for (int i = 0; i < particleAmount; i++)
	{
		file << particles[i].GetCoordinate() << endl;
	}
	for (int i = 0; i < particleAmount; i++)
	{
		file << particles[i].GetDeviation() << endl;
	}
	//TESTOUTPUT
}

void ParticleChain::ToString(std::vector<double> chain)
{

	//cout << "******************STEP**********************" << endl;
	for (int i = 0; i < chain.size(); i++)
	{
		cout << " | " << chain.at(i) << " | ";
	}
	cout << "\r";
}

double ParticleChain::f(double l, double m, double r)
{
	return (1 + alpha * (r - l)) * (r + l - 2 * m);
}

void ParticleChain::GenerateParticles()
{
	Particle firstParticle(0, 0, 0);
	particles.push_back(firstParticle);

	for (int i = 1; i < particleAmount - 1; i++)
	{
		double coordinate, deviation;

		coordinate = a * i;

		deviation = A * sin(PI * i / (particleAmount - 1));

		Particle ithParticle(coordinate, deviation, 0);

		particles.push_back(ithParticle);
	}
	Particle temp(a * (particleAmount - 1), 0, 0);
	particles.push_back(temp);
}



ParticleChain::Particle::Particle(double coordinate, double deviation, double speed)
{
	SetCoordinate(coordinate);
	SetDeviation(deviation);
	SetSpeed(speed);
}

ParticleChain::Particle::~Particle()
{
}

void ParticleChain::Particle::SetCoordinate(double coordinate)
{
	Particle::coordinate = coordinate;
}

void ParticleChain::Particle::SetDeviation(double deviation)
{
	Particle::deviation = deviation;
}

void ParticleChain::Particle::SetSpeed(double speed)
{
	Particle::speed = speed;
}

void ParticleChain::EnableBorderConditions()
{
	ParticleChain::borderConditionsEnabled = true;
}

double ParticleChain::Particle::GetCoordinate()
{
	return Particle::coordinate;;
}

double ParticleChain::Particle::GetDeviation()
{
	return Particle::deviation;
}

double ParticleChain::Particle::GetSpeed()
{
	return Particle::speed;
}

bool ParticleChain::CheckForBorderConditions()
{
	return ParticleChain::borderConditionsEnabled;
}
