/**
 * @file Implicite.cpp
 * @brief Déclaration de la classe Implicite dérivée de DifferenceFinie
 */

#include "DifferenceFinie.hpp"
#include <vector>

/**
 * @file Implicite.cpp
 * @brief Implémentation de la classe Implicite dérivée de DifferenceFinie
 */

#include "DifferenceFinie.hpp"
#include <vector>
#include <cmath>

/**
 * @brief Résout l'EDP en utilisant la méthode implicite
 * @return Matrice des prix de l'option aux différents points de la grille
 */
std::vector<std::vector<double>> Implicite::solve()
{
	// Paramètres de l'actif
	double r = getEDP().getActif().r_;
	double sigma = getEDP().getActif().sigma_;

	// taile du systeme
	int size = N_ - 2;

	// Vecteurs de la matrice tridiagonale
	std::vector<double> l(size - 1, 0.0);
	std::vector<double> d(size, 0.0);
	std::vector<double> u(size - 1, 0.0);
	std::vector<double> b(size, 0.0);

	// Matrice des prix
	std::vector<std::vector<double>> V(M_, std::vector<double>(N_, 0.0));

	// Condition terminale (payoff)
	for (int i = 0; i < N_; ++i)
	{
		V[M_ - 1][i] = getEDP().getOption().payoff(L_[i]);
	}

	// Boucle sur le temps (de T vers 0)
	for (int m = M_ - 2; m >= 0; --m)
	{
		// Conditions aux bords
		V[m][0] = getEDP().getOption().lowerBoundary(t_[m], r);
		V[m][N_ - 1] = getEDP().getOption().upperBoundary(L_[N_ - 1], t_[m], r);

		// Calcul des coefficients pour Thomas
		for (int i = 1; i < N_ - 1; ++i)
		{
			int idx = i - 1; // Indice pour les vecteurs Thomas (0 à size-1)

			double Si = L_[i];
			double a = 0.5 * sigma * sigma * Si * Si / (dS_ * dS_) - 0.5 * r * Si / dS_;
			double b_diag = -sigma * sigma * Si * Si / (dS_ * dS_) - r;
			double c = 0.5 * sigma * sigma * Si * Si / (dS_ * dS_) + 0.5 * r * Si / dS_;

			// Remplissage de la Diagonale (1 - dt * L_diag)
			d[idx] = 1.0 - dt_ * b_diag;

			// Remplissage Sous-diagonale (- dt * L_sub)
			if (idx > 0)
			{
				l[idx - 1] = -dt_ * a;
			}

			// Remplissage Sur-diagonale (- dt * L_sup)
			if (idx < size - 1)
			{
				u[idx] = -dt_ * c;
			}

			// Remplissage de la second membre (V au temps m+1)
			b[idx] = V[m + 1][i];

			// Injection des conditions aux bords (termes connus au temps m qui passent à droite)
			if (i == 1)
			{
				// Le terme (-dt * a) * V[m][0] passe à droite et devient (+dt * a) * V[m][0]
				b[idx] += (dt_ * a) * V[m][0];
			}
			if (i == N_ - 2)
			{
				// Le terme (-dt * c) * V[m][N-1] passe à droite et devient (+dt * c) * V[m][N-1]
				b[idx] += (dt_ * c) * V[m][N_ - 1];
			}
		}

		// Résolution du système tridiagonal
		std::vector<double> V_new = ThomasAlgo(l, d, u, b);

		// Mise à jour des valeurs internes
		for (int i = 1; i < N_ - 1; ++i)
		{
			V[m][i] = V_new[i - 1];
		}
	}

	return V;
}