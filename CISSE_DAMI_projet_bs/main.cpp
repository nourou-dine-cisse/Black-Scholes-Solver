#include <iostream>
#include "EDP.hpp"
#include "Option.hpp"

int main()
{
	std::cout << "Black Scholes Solved !" << std::endl;
	Actif actif;
	actif.S0 = 100.0;
	Call callOption(100.0, 1.0);
	EDPComplete edp(callOption, actif);
	std::cout << "Option Strike: " << edp.getOption().getK() << std::endl;
	std::cout << "Actif Initial Price: " << edp.getActif().S0 << std::endl;
	return 0;
}