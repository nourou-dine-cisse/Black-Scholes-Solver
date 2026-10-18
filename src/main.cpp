/**
 * \file main.cpp
 * \brief Programme principal de résolution numérique de l’équation de Black-Scholes
 */

/**
 * \mainpage Black-Scholes Solver
 *
 * Implémentation C++ de la résolution numérique de l’équation de Black-Scholes
 * par méthodes aux différences finies.
 *
 * Méthodes implémentées :
 * - Schéma de Crank–Nicolson
 * - Schéma implicite
 *
 * Options traitées :
 * - Call européen
 * - Put européen
 *
 * Sorties :
 * - Prix numériques
 * - Erreur entre schémas
 * - Visualisation graphique SDL
 */

#include <iostream>
#include <vector>
#include <cmath>
#include "EDP.hpp"
#include "Option.hpp"
#include "Sdl.hpp"
#include "DifferenceFinie.hpp"

/**
 * \brief Point d’entrée du programme
 *
 * Le programme :
 * - définit les paramètres du marché
 * - construit les grilles
 * - résout les EDP complètes et réduites
 * - compare les résultats
 * - affiche les courbes et erreurs
 *
 * \return 0 si exécution normale
 */

int main()
{
	// Paramètres de l'option et du marché
	double T = 1.0;		// maturité
	double r = 0.1;		// taux d'intérêt
	double sigma = 0.1; // volatilité
	double K = 100.0;	// prix d'exercice
	double L = 300.0;	// prix maximal de l'actif
	int M = 1000;		// nombre de pas de temps
	int N = 1000;		// nombre de pas de l'actif

	// Grilles de temps et de prix
	std::vector<double> t(M + 1);
	for (int i = 0; i <= M; ++i)
		t[i] = i * T / M;

	std::vector<double> S(N + 1);
	for (int j = 0; j <= N; ++j)
		S[j] = j * L / N;

	// Actif sous-jacent
	Actif actif(K, r, sigma);

	// Création des options
	Call callOption(K, T);
	Put putOption(K, T);

	// Résolution des EDP complètes (Crank-Nicholson)
	EDPComplete edpCall(callOption, actif);
	EDPComplete edpPut(putOption, actif);
	Crank_Nicholson CN_Call(edpCall, N + 1, M + 1, S, t);
	Crank_Nicholson CN_Put(edpPut, N + 1, M + 1, S, t);
	auto V_call_CN = CN_Call.solve(); // prix call
	auto V_put_CN = CN_Put.solve();	  // prix put

	// Résolution des EDP réduites (implicite)
	EDPReduite edpCallImp(callOption, actif);
	EDPReduite edpPutImp(putOption, actif);
	Implicite Imp_Call(edpCallImp, N + 1, M + 1, S, t);
	Implicite Imp_Put(edpPutImp, N + 1, M + 1, S, t);
	auto V_call_imp = Imp_Call.solve(); // prix call implicite
	auto V_put_imp = Imp_Put.solve();	// prix put implicite

	// Calcul des erreurs entre Crank-Nicholson et implicite
	std::vector<double> erreur_call(N + 1), erreur_put(N + 1);
	double max_err_call = 0.0, max_err_put = 0.0;
	for (int j = 0; j <= N; ++j)
	{
		erreur_call[j] = std::abs(V_call_CN[0][j] - V_call_imp[0][j]);
		erreur_put[j] = std::abs(V_put_CN[0][j] - V_put_imp[0][j]);
		max_err_call = std::max(max_err_call, erreur_call[j]);
		max_err_put = std::max(max_err_put, erreur_put[j]);
	}

	// Affichage des erreurs maximales
	std::cout << "Erreur max Call : " << max_err_call << "\n";
	std::cout << "Erreur max Put  : " << max_err_put << "\n";

	// Initialisation des 4 fenêtres avec des titres et positions différents
	// Note : Si votre classe Sdl permet de passer la position, c'est idéal.
	// Sinon, elles s'empileront par défaut.
	Sdl winCallPrix(900, 800, "Call - Prix (CN vs Implicite)");
	Sdl winCallErr(900, 800, "Call - Erreur");
	Sdl winPutPrix(900, 800, "Put - Prix (CN vs Implicite)");
	Sdl winPutErr(900, 800, "Put - Erreur");

	SDL_Color rouge = {255, 0, 0, 255}, bleu = {0, 0, 255, 255}, vert = {0, 150, 0, 255};
	double maxY_Call = L, maxY_Put = K * 1.1;

	bool keepRunning = true;
	while (keepRunning)
	{
		// 1. Gestion des événements (pour toutes les fenêtres)
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			// Si on ferme n'importe quelle fenêtre ou qu'on appuie sur Echap
			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
				keepRunning = false;
		}

		// 2. Rendu de la fenêtre Call Prix
		winCallPrix.clear();
		winCallPrix.drawCurve(S, V_call_CN[0], L, maxY_Call, rouge);
		winCallPrix.drawCurve(S, V_call_imp[0], L, maxY_Call, bleu);
		winCallPrix.present();

		// 3. Rendu de la fenêtre Call Erreur
		winCallErr.clear();
		winCallErr.drawCurve(S, erreur_call, L, max_err_call, vert);
		winCallErr.present();

		// 4. Rendu de la fenêtre Put Prix
		winPutPrix.clear();
		winPutPrix.drawCurve(S, V_put_CN[0], L, maxY_Put, rouge);
		winPutPrix.drawCurve(S, V_put_imp[0], L, maxY_Put, bleu);
		winPutPrix.present();

		// 5. Rendu de la fenêtre Put Erreur
		winPutErr.clear();
		winPutErr.drawCurve(S, erreur_put, L, max_err_put, vert);
		winPutErr.present();

		// Pause
		SDL_Delay(10);
	}

	return 0;
}