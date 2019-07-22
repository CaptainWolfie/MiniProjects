/*
 * Library used: SDL 2.0
 *
 * Target:
 *   Create circles with random Size,
 *   random position inside a bigger circle and random color
 *
 * Project status: Created
*/

#include "SDL.h"
#include <iostream>
#include <vector>

// for random numbers
#include <cstdlib>
#include <ctime>

bool running = 0;
SDL_Window* window;
SDL_Renderer* renderer;
struct Color {
	int red, green, blue;
	Color(int red, int green, int blue) : red(red), green(green), blue(blue) {}
};
struct circle {
	int size;
	Color color;
	int x, y, radius;
	double degree;
	circle(int size, Color color, int x, int y, double degree, int radius) : radius(radius), degree(degree), size(size), color(color), x(x), y(y) {}
};
std::vector<circle> circles;

void drawCircle(int x, int y, int radius) {
	for (int w = 0; w < radius * 2; w++) {
		for (int h = 0; h < radius * 2; h++) {
			int dx = radius - w; // horizontal offset
			int dy = radius - h; // vertical offset
			if ((dx * dx + dy * dy) <= (radius * radius)) {
				SDL_RenderDrawPoint(renderer, x + dx, y + dy);
			}
		}
	}
}

int getRandomNumber(int max) {
	int r = (rand() % max) + 1;
	return r;
}

int maxCircles = 300;
int circleRadius = 300;

void _init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("noob", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, circleRadius * 2, circleRadius * 2, SDL_WINDOW_BORDERLESS);
	if (!window)
		std::cout << "Couldn't create window: " << SDL_GetError();

	renderer = SDL_CreateRenderer(window, -1, SDL_VIDEO_OPENGL);
	if (!renderer)
		std::cout << "Couldn't create renderer: " << SDL_GetError();

	running = true;

	// create the circles
	int i = 0;
	srand((int)time(0));
	while (++i < maxCircles) {
		double degree = getRandomNumber(360);
		int radius = getRandomNumber(circleRadius);
		int x = (int) (radius * cos(degree));
		int y = (int) (radius * sin(degree));

		int size = getRandomNumber(10) + 3;
		Color color = Color(getRandomNumber(255), getRandomNumber(255), getRandomNumber(255));
		circle newCircle = circle( size, color, x, y, degree, radius);
		circles.push_back(newCircle);
	}
}

void _tick() {
	for (unsigned int i = 0; i < circles.size(); i++) {
		double degree = circles.at(i).degree - 0.01;
		circles.at(i).degree -= 0.01;
		int radius = circles.at(i).radius;
		circles.at(i).x = (int)(radius * cos(degree));
		circles.at(i).y = (int)(radius * sin(degree));
	}
}

void _render() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	for (unsigned int i = 0; i < circles.size(); i++) {
		SDL_SetRenderDrawColor(renderer,circles.at(i).color.red, circles.at(i).color.green, circles.at(i).color.blue, 255);

		drawCircle(circleRadius + circles.at(i).x, circleRadius + circles.at(i).y, circles.at(i).size);
	}

	SDL_RenderPresent(renderer);
}

void _pollEvents() {
	SDL_Event event = SDL_Event();
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			running = false;
	}
}

int main(int argc, char* argv[]) {
	_init();

	Uint32 start;
	int frameTime;

	const int FPS = 60;
	const int Delay = 1000 / FPS;
	while (running) {
		start = SDL_GetTicks();

		_pollEvents();
		_tick();
		_render();

		frameTime = SDL_GetTicks() - start;
		if (Delay > frameTime)
			SDL_Delay(Delay - frameTime);
	}
	return 0;
}
