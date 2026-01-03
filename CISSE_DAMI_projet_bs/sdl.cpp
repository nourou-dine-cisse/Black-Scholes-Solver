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
	if (renderer_)
		SDL_DestroyRenderer(renderer_);

	// Détruire window
	if (window_)
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
void Sdl::drawCurve(const std::vector<double> &x, const std::vector<double> &y, double x_max, double y_max, SDL_Color color)
{
	if (x.empty() || y.empty())
	{ // si aucunes données n'est renseignées
		return;
	}

	// la marge
	int margin = 50;

	// Zone de dessin utile
	double draw_width = width_ - 2 * margin;
	double draw_height = height_ - 2 * margin;

	// tracer des axes gradués
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255); // noir pour les axes

	// Axe Y
	SDL_RenderDrawLine(renderer_, margin, margin, margin, height_ - margin);

	// Axe X
	SDL_RenderDrawLine(renderer_, margin, height_ - margin, width_ - margin, height_ - margin);

	// Graduation de la courbe
	for (int i = 0; i <= 5; i++)
	{
		int x_grad = margin + (i * draw_width / 5);
		SDL_RenderDrawLine(renderer_, x_grad, height_ - margin, x_grad, height_ - margin + 5);

		int y_grad = (height_ - margin) - (i * draw_height / 5);
		SDL_RenderDrawLine(renderer_, margin - 5, y_grad, margin, y_grad);

		// Tracé de la courbe
		SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a); // configuration de la couleur
		for (size_t i = 0; i < x.size() - 1; ++i)
		{
			// Calcul du point 1
			double ratio_x1 = x[i] / x_max;
			double ratio_y1 = y[i] / y_max;

			// projection
			int pixel_x1 = margin + (int)(ratio_x1 * draw_width);

			// Inversion Y
			int pixel_y1 = (height_ - margin) - (int)(ratio_y1 * draw_height);

			// Calcul du point 2
			double ratio_x2 = x[i + 1] / x_max;
			double ratio_y2 = y[i + 1] / y_max;

			int pixel_x2 = margin + (int)(ratio_x2 * draw_width);
			int pixel_y2 = (height_ - margin) - (int)(ratio_y2 * draw_height);

			// Tracé du segment
			SDL_RenderDrawLine(renderer_, pixel_x1, pixel_y1, pixel_x2, pixel_y2);
		}
	}
}