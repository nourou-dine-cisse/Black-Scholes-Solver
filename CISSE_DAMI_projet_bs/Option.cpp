/**
 * @file Option.cpp
 * @brief Implémentation des classes dérivées de Option : Call et Put
 */

#include "Option.hpp"
#include <cmath>

/**
 * @brief Calcule le payoff de l'option d'achat
 * @param S Prix du sous-jacent à l'échéance
 * @return Payoff de l'option d'achat
 */
double Call::payoff(double S) const
{
	if ((S - K_) > 0)
	{
		return S - K_;
	}
	return 0.0;
}

/**
 * @brief Condition de frontière inférieure pour l'option d'achat
 * @param t Temps actuel
 * @param r Taux d'intérêt sans risque
 * @return Valeur de la condition de frontière inférieure
 */
double Call::lowerBoundary(double t, double r) const
{
	return 0.0;
}

/**
 * @brief Condition de frontière supérieure pour l'option d'achat
 * @param S_max Prix maximum du sous-jacent
 * @param t Temps actuel
 * @param r Taux d'intérêt sans risque
 * @return Valeur de la condition de frontière supérieure
 */
double Call::upperBoundary(double S_max, double t, double r) const
{
	return S_max - K_ * exp(-r * (T_ - t));
}

/**
 * @brief Calcule le payoff de l'option de vente
 * @param S Prix du sous-jacent à l'échéance
 * @return Payoff de l'option d'achat
 */
double Put::payoff(double S) const
{
	if ((K_ - S) > 0)
	{
		return K_ - S;
	}
	return 0.0;
}

/**
 * @brief Condition de frontière inférieure pour l'option de vente
 * @param t Temps actuel
 * @param r Taux d'intérêt sans risque
 * @return Valeur de la condition de frontière inférieure
 */
double Put::lowerBoundary(double t, double r) const
{
	return K_ * exp(-r * (T_ - t));
}

/**
 * @brief Condition de frontière supérieure pour l'option de vente
 * @param S_max Prix maximum du sous-jacent
 * @param t Temps actuel
 * @param r Taux d'intérêt sans risque
 * @return Valeur de la condition de frontière supérieure
 */
double Put::upperBoundary(double S_max, double t, double r) const
{
	return 0;
}