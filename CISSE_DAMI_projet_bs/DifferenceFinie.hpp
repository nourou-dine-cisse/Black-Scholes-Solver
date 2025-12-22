/**
 * @file DifferenceFinie.hpp
 * @brief Déclaration de la classe DifferenceFinie et ses classes dérivées concrètes Crank_Nicholson et Implicite
 */

#ifndef DIFFERENCEFINIE_HPP
#define DIFFERENCEFINIE_HPP

#include "EDP.hpp"
#include <vector>

/**
 * @brief Resoution d'un système tridiagonal par la méthode de Thomas
 * @param l Vecteur des coefficients sous-diagonaux
 * @param d Vecteur des coefficients diagonaux
 * @param u Vecteur des coefficients sur-diagonaux
 * @param r Vecteur second membre
 * @return Vecteur solution du système tridiagonal
 */
std::vector<double> ThomasAlgo(const std::vector<double> &l, const std::vector<double> &d, const std::vector<double> &u, const std::vector<double> &r);

/**
 * @class DifferenceFinie
 * @brief Classe abstraite représentant la méthode différence finie pour résoudre une EDP
 */
class DifferenceFinie
{
protected:
	EDP &edp_;				// reference vers l'EDP associée à la méthode différence finie
	int N_;					// Nombre de points en espace
	int M_;					// Nombre de points en temps
	double dt_;				// Pas de temps
	double dS_;				// Pas d'espace des prix
	std::vector<double> L_; // Grille des prix du sous-jacent
	std::vector<double> t_; // Grille des temps
public:
	/**
	 * @brief Constructeur de la classe DifferenceFinie
	 * @param edp reference vers l'EDP associée à la méthode différence finie
	 * @param N Nombre de points en espace
	 * @param M Nombre de points en temps
	 * @param dt Pas de temps
	 * @param dS Pas d'espace des prix
	 * @param S Grille des prix de l'actif sous-jacent
	 * @param t Grille des temps
	 */
	DifferenceFinie(EDP &edp, int N, int M, const std::vector<double> &S, const std::vector<double> &t)
		: edp_(edp), N_(N), M_(M), L_(S), t_(t)
	{
		dt_ = t_[1] - t_[0];
		dS_ = L_[1] - L_[0];
	}

	/**
	 * @brief Méthode virtuelle pure pour résoudre l'EDP en utilisant la méthode différence finie
	 * @return Matrice des prix de l'option aux différents points de la grille
	 */
	virtual std::vector<std::vector<double>> solve() = 0;

	/**
	 * @brief Récupérer l'EDP associée à la méthode différence finie
	 * @return reference vers l'EDP associée
	 */
	EDP &getEDP() const { return edp_; }

	/**
	 * @brief Récupérer le nombre de points en espace
	 * @return Nombre de points en espace
	 */
	int getN() const { return N_; }

	/**
	 * @brief Récupérer le nombre de points en temps
	 * @return Nombre de points en temps
	 */
	int getM() const { return M_; }

	/**
	 * @brief Récupérer la grille des prix de l'actif sous-jacent
	 * @return Grille des prix de l'actif sous-jacent
	 */
	const std::vector<double> &getL() const { return L_; }

	/**
	 * @brief Récupérer la grille des temps
	 * @return Grille des temps
	 */
	const std::vector<double> &getT() const { return t_; }

	/**
	 * @brief Destructeur virtuel de la classe DifferenceFinie
	 */
	virtual ~DifferenceFinie() {}
};

/**
 * @class Crank_Nicholson
 * @brief Classe représentant la méthode de Crank-Nicholson pour résoudre une EDP
 */
class Crank_Nicholson : public DifferenceFinie
{
public:
	/**
	 * @brief Constructeur de la classe Crank_Nicholson
	 * @param edp reference vers l'EDP associée à la méthode différence finie
	 * @param N Nombre de points en espace
	 * @param M Nombre de points en temps
	 * @param S Grille des prix de l'actif sous-jacent
	 * @param t Grille des temps
	 */
	Crank_Nicholson(EDP &edp, int N, int M, const std::vector<double> &S, const std::vector<double> &t)
		: DifferenceFinie(edp, N, M, S, t) {}

	/**
	 * @brief Résout l'EDP en utilisant la méthode de Crank-Nicholson
	 * @return Matrice des prix de l'option aux différents points de la grille
	 */
	std::vector<std::vector<double>> solve() override;
};

/**
 * @class Implicite
 * @brief Classe représentant la méthode implicite pour résoudre une EDP
 */
class Implicite : public DifferenceFinie
{
public:
	/**
	 * @brief Constructeur de la classe Implicite
	 * @param edp reference vers l'EDP associée à la méthode différence finie
	 * @param N Nombre de points en espace
	 * @param M Nombre de points en temps
	 * @param S Grille des prix de l'actif sous-jacent
	 * @param t Grille des temps
	 */
	Implicite(EDP &edp, int N, int M, const std::vector<double> &S, const std::vector<double> &t)
		: DifferenceFinie(edp, N, M, S, t) {}

	/**
	 * @brief Résout l'EDP en utilisant la méthode implicite
	 * @return Matrice des prix de l'option aux différents points de la grille
	 */
	std::vector<std::vector<double>> solve() override;
};

#endif