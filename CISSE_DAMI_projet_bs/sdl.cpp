/**
 * @file sdl.cpp
 * @brief Implémentation de la classe Sdl
 */

#include "sdl.hpp"
#include <iostream>

/**
 * @brief Constructeur de la classe Sdl
 * @param height longeur de la fenêtre
 * @param width largeur de la fenêtre
 * @param titre titre de la fenêtre
 */
Sdl::Sdl(int height, int width, std::string titre)
	: height_(height), width_(width), titre_(titre), running_(true)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Erreur Init SDL" << std::endl;
		running_ = false;
	}

	// Création de la fenêtre
	window_ = SDL_CreateWindow(
		titre_.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width_,
		height_,
		SDL_WINDOW_SHOWN);

	// Crétion du renderer
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
}

/**
 * @brief Destructeur de la classe Sdl
 */
Sdl::~Sdl()
{
	// Détruire renderer_
	SDL_DestroyRenderer(renderer_);

	// Détruire window
	SDL_DestroyWindow(window_);

	// Quitter SDL
	SDL_Quit();
}

/**
 * @brief gère le flag pour l'ouverture de la fenêtre
 */
bool Sdl::isRunning()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			running_ = false;
		}
	}
	return running_;
}

/**
 * @brief nettoyage de la fenêtre
 */
void Sdl::clear()
{
	SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
	SDL_RenderClear(renderer_);
}

/**
 * @brief dessine la courbe sur la fenêtre
 * @param x prix de l'actif sous-jacent
 * @param y valeurs de l'option
 * @param x_max prix maximum de l'actif
 * @param y_max valeur maximum de l'option
 * @param color couleur de la courbe
 */
void drawCurve(const std::vector<double> &x, const std::vector<double> &y, double x_max, double y_max, SDL_Color color)
{
	return;
}