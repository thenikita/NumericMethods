#pragma once
#include <vector>

class ParticleChain
{
public:
	ParticleChain( int particleAmount, int time );
	~ParticleChain();

private:
	int particleAmount;
	double coefs[100][5];
	double A = 0.5;
	double a = 0.1;
	double alpha = 0.4;
	double dt = 0.1;
	double currentTime = 0;
	double accuracy = 0.000001;
	bool borderConditionsEnabled = false;
	int targetTime = 0;

	class Particle
	{
	public:
		Particle(double coordinate, double deviation, double speed);
		~Particle();

		void SetCoordinate(double coordinate);
		void SetDeviation(double deviation);
		void SetSpeed(double speed);

		double GetCoordinate();
		double GetDeviation();
		double GetSpeed();

	private:
		double coordinate;
		double deviation;
		double speed;
	};
	std::vector<Particle> particles;

private:
	void EnableBorderConditions();
	bool CheckForBorderConditions();
	void GenerateParticles();
	std::vector <double> GetChain();
	void MakeIterations();
	void ToString(std::vector<double> chain);
	double f(double left, double middle, double right);
};

