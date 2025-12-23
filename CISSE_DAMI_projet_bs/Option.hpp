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
	 * @brief Méthode virtuelle pure pour la condition de frontière inférieure
	 * @param t Temps actuel
	 * @param r Taux d'intérêt sans risque
	 * @return Valeur de la condition de frontière inférieure
	 */
	virtual double lowerBoundary(double t, double r) const = 0;

	/**
	 * @brief Méthode virtuelle pure pour la condition de frontière supérieure
	 * @param S_max Prix maximum du sous-jacent
	 * @param t Temps actuel
	 * @param r Taux d'intérêt sans risque
	 * @return Valeur de la condition de frontière supérieure
	 */
	virtual double upperBoundary(double S_max, double t, double r) const = 0;

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

	/**
	 * @brief Condition de frontière inférieure pour l'option d'achat
	 * @param t Temps actuel
	 * @param r Taux d'intérêt sans risque
	 * @return Valeur de la condition de frontière inférieure
	 */
	double lowerBoundary(double t, double r) const override;

	/**
	 * @brief Condition de frontière supérieure pour l'option d'achat
	 * @param S_max Prix maximum du sous-jacent
	 * @param t Temps actuel
	 * @param r Taux d'intérêt sans risque
	 * @return Valeur de la condition de frontière supérieure
	 */
	double upperBoundary(double S_max, double t, double r) const override;
};

/**
 * @class Put
 * @brief Classe représentant une option de vente (put)
 */
class Put : public Option
{
public:
	/**
	 * @brief Constructeur de la classe Put
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

	/**
	 * @brief Condition de frontière inférieure pour l'option de vente
	 * @param t Temps actuel
	 * @param r Taux d'intérêt sans risque
	 * @return Valeur de la condition de frontière inférieure
	 */
	double lowerBoundary(double t, double r) const override;

	/**
	 * @brief Condition de frontière supérieure pour l'option de vente
	 * @param S_max Prix maximum du sous-jacent
	 * @param t Temps actuel
	 * @param r Taux d'intérêt sans risque
	 * @return Valeur de la condition de frontière supérieure
	 */
	double upperBoundary(double S_max, double t, double r) const override;
};

/**
 * @struct Actif
 * @brief Structure représentant les paramètres d'un actif sous-jacent
 */

struct Actif
{
	double S0_;			 // Prix initial de l'actif sous-jacent
	double r_ = 0.1;	 // Taux d'intérêt sans risque
	double sigma_ = 0.1; // Volatilité de l'actif sous-jacent

	/**
	 * @brief Constructeur de la structure Actif
	 * @param S0_ Prix initial de l'actif sous-jacent
	 * @param r_ Taux d'intérêt sans risque
	 * @param sigma_ Volatilité de l'actif sous-jacent
	 */
	Actif(double S0_, double r_ = 0.1, double sigma_ = 0.1) : S0_(S0_), r_(r_), sigma_(sigma_) {}
};

#endif