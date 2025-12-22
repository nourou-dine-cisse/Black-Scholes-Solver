/**
 * @file Option.cpp
 * @brief Implémentation des classes dérivées de Option : Call et Put
 */

#include "Option.hpp"

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
