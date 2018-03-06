#include "stdafx.h"
#include "Soliton.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <Windows.h>

using std::cout;
using std::cin;
using std::endl;

const double PI = 3.14159;

Soliton::Soliton(int particleAmount, double time)
{
	Soliton::particleAmount = particleAmount;

	Soliton::targetTime = time;

	cout << "Generating..." << endl;
	GenerateParticles();

	cout << "Iterating..." << endl;
	MakeIterations();

	cout << "Done!!!" << endl;

	ToString();

	system("PAUSE");
}


Soliton::~Soliton()
{
}


void Soliton::GenerateParticles()
{
	Particle zeroParticle(0, A, 0);
	particles.push_back(zeroParticle);
	particles.push_back(zeroParticle);
	particles.push_back(zeroParticle);

	for (int i = 3; i < particleAmount + 1; i++)
	{
		double coordinate, deviation;

		coordinate = dx * (i - 2);

		deviation = A * cos(2* PI * (i - 2) / (particleAmount - 1));

		Particle ithParticle(coordinate, deviation, 0);

		particles.push_back(ithParticle);
	}
	particles.push_back(zeroParticle);
	particles[particleAmount + 1].SetCoordinate(dx * (particleAmount - 1));

	particles.push_back(zeroParticle);
	particles.push_back(zeroParticle);

	particles[0].SetDeviation(
		particles[particleAmount].GetDeviation());
	particles[1].SetDeviation(
		particles[particleAmount + 1].GetDeviation());
	particles[particleAmount + 2].SetDeviation(
		particles[2].GetDeviation());
	particles[particleAmount + 3].SetDeviation(
		particles[3].GetDeviation());

	for (int i = 0; i < particleAmount + 5; i++)
	{
		particlesT.push_back(zeroParticle);
	}

	ToString();
}

void Soliton::ToString()
{
	std::ofstream file;
	file.open("file.txt");

	cout << "logging..." << endl;

	file << "+++++++++" << endl;
	for (int i = 2; i <= particleAmount + 1; i++)
	{
		file << particles[i].GetCoordinate() << endl;
	}

	file << "+++++++++" << endl;
	for (int i = 2; i <= particleAmount + 1; i++)
	{
		file << particles[i].GetDeviation() << endl;
	}
}

void Soliton::MakeIterations()
{
	while (currentTime < targetTime)
	{
		currentTime += dt;
		cout << "time is: " << currentTime << "\r";

		for (int i = 2; i < particleAmount + 2; i++)
		{
			particlesT[i].SetDeviation(f(i));
		}

		for (int i = 2; i < particleAmount + 2; i++)
		{
			particles[i].SetDeviation(particlesT[i].GetDeviation());
		}

		particles[0].SetDeviation(
			particles[particleAmount].GetDeviation());
		particles[1].SetDeviation(
			particles[particleAmount + 1].GetDeviation());
		particles[particleAmount + 2].SetDeviation(
			particles[2].GetDeviation());
		particles[particleAmount + 3].SetDeviation(
			particles[3].GetDeviation());
	
		//ToString();
	}
	cout << endl;
}

double Soliton::f(int i)
{
	double i0 = particles[i - 2].GetDeviation();
	double i1 = particles[i - 1].GetDeviation();
	double i2 = particles[i].GetDeviation();
	double i3 = particles[i + 1].GetDeviation();
	double i4 = particles[i + 2].GetDeviation();


	double temp0 = (i4 - i0) / (2 * pow(dx, 3));
	double temp1 = (i3 - i1) / (pow(dx, 3));
	double temp2 = delta * delta * (temp0 - temp1);
	double temp3 = 3 * i2 * (i3 - i1) / dx;
	double temp4 = dt * (temp3 + temp2);
	return i2 - temp4;
}


Soliton::Particle::Particle(double coordinate, double deviation, double speed)
{
	SetCoordinate(coordinate);
	SetDeviation(deviation);
	SetSpeed(speed);
}

Soliton::Particle::~Particle()
{
}

void Soliton::Particle::SetCoordinate(double coordinate)
{
	Particle::coordinate = coordinate;
}

void Soliton::Particle::SetDeviation(double deviation)
{
	Particle::deviation = deviation;
}

void Soliton::Particle::SetSpeed(double speed)
{
	Particle::speed = speed;
}


double Soliton::Particle::GetCoordinate()
{
	return Particle::coordinate;;
}

double Soliton::Particle::GetDeviation()
{
	return Particle::deviation;
}

double Soliton::Particle::GetSpeed()
{
	return Particle::speed;
}