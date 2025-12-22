/**
 * @file CrankNicholson.cpp
 * @brief Implémentation de la classe Crank_Nicholson dérivée de DifferenceFinie
 */

#include "DifferenceFinie.hpp"
#include <vector>

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
	// Implémentation de la méthode de Crank-Nicholson
	// Les parametres de l'EDP
	double r = getEDP().getActif().r;
	double sigma = getEDP().getActif().sigma;

	// Initialisation des vecteurs de la matrice tridiagonale
	std::vector<double> u(N_ - 2, 0.0);
	std::vector<double> d(N_ - 1, 0.0);
	std::vector<double> l(N_ - 2, 0.0);

	// remplissage des coefficients de la matrice
}