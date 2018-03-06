#pragma once
#include <vector>

class Soliton
{
public:
	Soliton(int particleAmount, double time);
	~Soliton();
private:
	double A = 0.005;
	double delta = 0.01;
	int particleAmount;
	double dt = 0.00002;
	double dx = 0.01;
	double targetTime;
	double currentTime = 0;

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
	std::vector<Particle> particlesT;

private:
	void GenerateParticles();
	void ToString();
	void MakeIterations();
	double f(int i);
};

