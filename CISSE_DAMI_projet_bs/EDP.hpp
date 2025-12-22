/**
 * @EDP.hpp
 * @brief Déclaration de la classe abstraite EDP et de ses classes dérivées concrètes EDPComplete et EDPReduite
 */
#include "Option.hpp"

#ifndef EDP_HPP
#define EDP_HPP

/**
 * @class EDP
 * @brief Classe abstraite représentant une équation aux dérivées partielles (EDP)
 */
class EDP
{
protected:
	Option &option_; // reference vers l'option associée à l'EDP
	Actif &actif_;	 // reference vers l'actif sous-jacent associé à l'EDP
public:
	/**
	 * @brief Constructeur de la classe EDP
	 * @param option reference vers l'option associée à l'EDP
	 * @param actif reference vers l'actif sous-jacent associé à l'EDP
	 */
	EDP(Option &option, Actif &actif) : option_(option), actif_(actif) {}

	/**
	 * @brief récupérer l'option associée à l'EDP
	 * @return reference vers l'option associée à l'EDP
	 */
	Option &getOption() const { return option_; }

	/**
	 * @brief récupérer l'actif sous-jacent associé à l'EDP
	 * @return reference vers l'actif sous-jacent associé à l'EDP
	 */
	Actif &getActif() const { return actif_; }

	/**
	 * @brief Destructeur virtuel de la classe EDP
	 */
	virtual ~EDP() {}
};

/**
 * @class EDPComplete
 * @brief Classe représentant l'EDP complète de Black-Scholes
 */
class EDPComplete : public EDP
{
public:
	/**
	 * @brief Constructeur de la classe EDPComplete
	 * @param option reference vers l'option associée à l'EDP
	 * @param actif reference vers l'actif sous-jacent associé à l'EDP
	 */
	EDPComplete(Option &option, Actif &actif) : EDP(option, actif) {}
};

/**
 * @class EDPReduite
 * @brief Classe représentant l'EDP réduite de Black-Scholes
 */
class EDPReduite : public EDP
{
public:
	/**
	 * @brief Constructeur de la classe EDPReduite
	 * @param option reference vers l'option associée à l'EDP
	 * @param actif reference vers l'actif sous-jacent associé à l'EDP
	 */
	EDPReduite(Option &option, Actif &actif) : EDP(option, actif) {}
};

#endif