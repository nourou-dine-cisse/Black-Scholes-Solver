/**
 * @file CrankNicholson.cpp
 * @brief Implémentation de la classe Crank_Nicholson dérivée de DifferenceFinie
 */

#include "DifferenceFinie.hpp"
#include <vector>
#include <cmath>

/**
 * @brief Resoution d'un système tridiagonal par la méthode de Thomas
 * @param l Vecteur des coefficients sous-diagonaux
 * @param d Vecteur des coefficients diagonaux
 * @param u Vecteur des coefficients sur-diagonaux
 * @param r Vecteur second membre
 * @return Vecteur solution du système tridiagonal
 */

std::vector<double> ThomasAlgo(const std::vector<double> &l, const std::vector<double> &d, const std::vector<double> &u, const std::vector<double> &r)
{
	int n = r.size();					// Taille du système
	std::vector<double> c_prime(n - 1); // Vecteur des coefficients modifiés sur-diagonaux
	std::vector<double> r_prime(n);		// Vecteur des second membres modifiés

	// Étape avant forward
	c_prime[0] = u[0] / d[0];
	r_prime[0] = r[0] / d[0];

	// Forward elimination
	for (int i = 1; i < n; ++i)
	{
		double temp = d[i] - l[i - 1] * c_prime[i - 1];
		if (i < n - 1)
		{
			c_prime[i] = u[i] / temp;
		}
		r_prime[i] = (r[i] - l[i - 1] * r_prime[i - 1]) / temp;
	}

	// Back substitution
	std::vector<double> x(n);
	x[n - 1] = r_prime[n - 1];
	for (int i = n - 2; i >= 0; --i)
	{
		x[i] = r_prime[i] - c_prime[i] * x[i + 1];
	}
	return x;
}

/**
 * @brief Résout l'EDP en utilisant la méthode de Crank-Nicholson
 * @return Matrice des prix de l'option aux différents points de la grille
 */
std::vector<std::vector<double>> Crank_Nicholson::solve()
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

			// Remplissage de la Diagonale
			d[idx] = 1.0 - (dt_ / 2.0) * b_diag;

			// Remplissage Sous-diagonale
			if (idx > 0)
			{
				l[idx - 1] = -(dt_ / 2.0) * a;
			}

			// Remplissage Sur-diagonale
			if (idx < size - 1)
			{
				u[idx] = -(dt_ / 2.0) * c;
			}

			// Remplissage de la second membre
			b[idx] = (dt_ / 2.0 * a) * V[m + 1][i - 1] +
					 (1.0 + dt_ / 2.0 * b_diag) * V[m + 1][i] +
					 (dt_ / 2.0 * c) * V[m + 1][i + 1];

			// Injection des conditions aux bords (termes connus au temps m)
			if (i == 1)
			{
				b[idx] += (dt_ / 2.0 * a) * V[m][0];
			}
			if (i == N_ - 2)
			{
				b[idx] += (dt_ / 2.0 * c) * V[m][N_ - 1];
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
