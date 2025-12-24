/**
 * @file sdl.hpp
 * @brief Déclaration de la class sdl pour l'affichage des courbes de la prix des options en fonction du prix de l'actif sous-jacent
 */

#ifndef SDL_HPP
#define SDL_HPP

#include <SDL2/SDL.h>
#include <vector>
#include <string>

/**
 * @class sdl
 * @brief class sdl pour l'affichage des courbes de la prix des options en fonction du prix de l'actif sous-jacent
 */
class Sdl
{
private:
	SDL_Window *window_;
	SDL_Render *renderer_;
	int height_;
	int width_;
	bool running_;
	std::string titre_;

public:
	/**
	 * @brief Constructeur de la classe Sdl
	 * @param height longeur de la fenêtre
	 * @param width largeur de la fenêtre
	 * @param titre titre de la fenêtre
	 */
	Sdl(int height, int width, std::string titre_);

	/**
	 * @brief Destructeur de la classe Sdl
	 */
	~Sdl();

	/**
	 * @brief
	 */
	SDL_Renderer *present()
	{
		SDL_RenderPresent(renderer_);
	}

	/**
	 * @brief gère le flag pour l'ouverture de la fenêtre
	 */
	bool isRunning();

	/**
	 * @brief dessine la courbe sur la fenêtre
	 * @param x prix de l'actif sous-jacent
	 * @param y valeurs de l'option
	 * @param x_max prix maximum de l'actif
	 * @param y_max valeur maximum de l'option
	 * @param color couleur de la courbe
	 */
	void drawCurve(const std::vector<double> &x, const std::vector<double> &y, double x_max, double y_max, SDL_Color color);

	/**
	 * @brief nettoyage de la fenêtre
	 */
	void clear();
}
#endif