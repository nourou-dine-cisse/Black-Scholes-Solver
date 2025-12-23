#include <iostream>
#include "EDP.hpp"
#include "Option.hpp"
#include "DifferenceFinie.hpp"

#include <iostream>
#include <iomanip>
#include "EDP.hpp"
#include "Option.hpp"
#include "DifferenceFinie.hpp"

int main()
{
	// Paramètres du sujet
	double T = 1.0;
	double r = 0.1;
	double sigma = 0.1;
	double K = 100.0;
	double L = 300.0;
	int M = 1000;
	int N = 1000;

	// Vecteurs temps et espace (N+1 points pour inclure L)
	std::vector<double> t(M + 1);
	for (int i = 0; i <= M; i++)
		t[i] = i * T / M;

	std::vector<double> S(N + 1);
	for (int j = 0; j <= N; j++)
		S[j] = j * L / N;

	Actif actif(K, r, sigma);

	// test du call
	Call callOption(K, T);
	EDPComplete edpCall(callOption, actif);
	Crank_Nicholson CN_Call(edpCall, N + 1, M + 1, S, t);
	std::vector<std::vector<double>> V_call = CN_Call.solve();

	// test du put
	Put putOption(K, T);
	EDPComplete edpPut(putOption, actif);
	Crank_Nicholson CN_Put(edpPut, N + 1, M + 1, S, t);
	std::vector<std::vector<double>> V_put = CN_Put.solve();

	// Affichage comparatif
	std::cout << std::fixed << std::setprecision(3);
	std::cout << "S      | Prix Call | Prix Put" << std::endl;
	std::cout << "-----------------------------" << std::endl;

	for (int i = 0; i <= N; i += N / 20)
	{
		std::cout << std::setw(6) << S[i] << " | "
				  << std::setw(9) << V_call[0][i] << " | "
				  << std::setw(8) << V_put[0][i] << std::endl;
	}

	return 0;
}