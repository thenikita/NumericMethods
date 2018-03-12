//#include "stdafx.h"
#include <iostream>

#include "MainMenu.h"

#include "ParticleEnergyLevels.h"
#include "ParticleChain.h"
#include "Soliton.h"
#include "Madelung.h"
#include "Croning.h"

using namespace std;

MainMenu::MainMenu()
{
	cout << "Hello, now u can chosse sub-program to launch..." << endl;
	cout << "************************************************\n";
	cout << "The list of currentrly available subs:\n";
	cout << "1. Particle energy levels.\n";
	cout << "2. Differential eqs in chain of particles.\n";
	cout << "3. Soliton.\n";
	cout << "4. Madelunger.\n";
	cout << "5. Croning-Pennie.";
    cout << "\n************************************************\n";
    cout << endl;

	int selector;
	cin >> selector;

	RunSelectedProgram(selector);
}


MainMenu::~MainMenu()
{
}


void MainMenu::RunSelectedProgram( int selector )
{
	int a;
	int t;
	switch (selector)
	{
	default:
		cout << "C'mon brah..." << endl;
		break;

	case 1:
		ParticleEnergyLevels::ParticleEnergyLevels();
		break;

	case 2:
		cout << "Enter amount of particles: ";
		cin >> a;
		cout << "Enter target time: ";
		cin >> t;
		ParticleChain::ParticleChain(a, t);
		break;

	case 3:
		cout << "Enter amount of particles: ";
		cin >> a;
		cout << "Enter target time: ";
		cin >> t;
		Soliton::Soliton(a, t);
		break;

	case 4:
		Madelung::Madelung();
		break;

	case 5:
		cout << "Calculating Croning-Penny...";
		//double K;
		Croning::Croning();
		break;
	}
}
