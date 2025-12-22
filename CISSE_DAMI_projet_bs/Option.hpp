/**
 * @file Option.hpp
 * @brief Declartation de la classe abstraite Option et ses classes dérivées concrètes Call et Put
 */

#ifndef OPTION_HPP
#define OPTION_HPP

/**
 * @class Option
 * @brief Classe abstraite représentant une option financière
 */

class Option
{
protected:
	double K_; // Prix d'exercice de l'option
	double T_; // Date d'échéance de l'option
public:
	/**
	 * @brief Constructeur de la classe Option
	 * @param K Prix d'exercice de l'option (Strike)
	 * @param T Date d'échéance de l'option
	 */
	Option(double K, double T) : K_(K), T_(T) {}

	/**
	 * @brief Méthode virtuelle pure pour calculer le payoff de l'option
	 * @param S Prix du sous-jacent à l'échéance
	 * @return Payoff de l'option
	 */
	virtual double payoff(double S) const = 0;

	/**
	 * @brief getteur pour le prix d'exercice (strike)
	 * @return Prix d'exercice de l'option (strike)
	 */
	double getK() const { return K_; }

	/**
	 * @brief getteur pour la date d'échéance
	 * @return Date d'échéance de l'option
	 */
	double getT() const { return T_; }

	/**
	 * @brief Destructeur virtuel de la classe Option
	 */
	virtual ~Option() {}
};

/**
 * @class Call
 * @brief Classe représentant une option d'achat (call)
 */
class Call : public Option
{
public:
	/**
	 * @brief Constructeur de la classe Call
	 * @param K Prix d'exercice de l'option (strike)
	 * @param T Date d'échéance de l'option
	 */
	Call(double K, double T) : Option(K, T) {}

	/**
	 * @brief Calcule le payoff de l'option d'achat
	 * @param S Prix du sous-jacent à l'échéance
	 * @return Payoff de l'option d'achat
	 */
	double payoff(double S) const override;
};

/**
 * @class Put
 * @brief Classe représentant une option de vente (put)
 */
class Put : public Option
{
public:
	/**
	 * @brief Constructeur de la classe Call
	 * @param K Prix d'exercice de l'option (strike)
	 * @param T Date d'échéance de l'option
	 */
	Put(double K, double T) : Option(K, T) {}

	/**
	 * @brief Calcule le payoff de l'option de vente
	 * @param S Prix du sous-jacent à l'échéance
	 * @return Payoff de l'option d'achat
	 */
	double payoff(double S) const override;
};

/**
 * @struct Actif
 * @brief Structure représentant les paramètres d'un actif sous-jacent
 */

struct Actif
{
	double S0;			// Prix initial de l'actif sous-jacent
	double r = 0.1;		// Taux d'intérêt sans risque
	double sigma = 0.1; // Volatilité de l'actif sous-jacent
};

#endif