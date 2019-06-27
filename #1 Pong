#include "SDL.h"
#include <iostream>

bool running = 0;
SDL_Window* window;
SDL_Renderer* renderer;

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

void _init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("noob", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_BORDERLESS);
	if (!window)
		std::cout << "Couldn't create window: " << SDL_GetError();

	renderer = SDL_CreateRenderer(window, -1, SDL_VIDEO_OPENGL);
	if (!renderer)
		std::cout << "Couldn't create renderer: " << SDL_GetError();

	running = true;
}


bool W = false;
bool S = false;
bool UP = false;
bool DOWN = false;

bool lost = false;

bool directionX = false;
bool directionY = true;
int x = 400, y = 10;

int player1Y = 0;
int player2Y = 0;
void _tick() {
	if (lost)
		return;
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	if (!directionX && x == 30 && y >= player1Y && y <= player1Y + 140)
		directionX = 1;

	if (directionX && x == w - 30 && y >= player2Y && y <= player2Y + 140)
		directionX = 0;

	if (x == w && directionX)
		lost = 1;

	if (x == 0 && !directionX)
		lost = 1;

	if (y == h && directionY)
		directionY = 0;

	if (y == 0 && !directionY)
		directionY = 1;

	if (directionX)
		x+=5;
	else
		x-=5;
	
	if (directionY)
		y+=5;
	else
		y-=5;

	if (W)
		if (player1Y > 0)
			player1Y-=10;

	if (S)
		if (player1Y < h - 140)
			player1Y+=10;

	if (UP)
		if (player2Y > 0)
			player2Y-=10;

	if (DOWN)
		if (player2Y < h - 140)
			player2Y+=10;
}

void _render() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_Rect pos{ 20, player1Y, 10, 140};
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &pos);
	pos.y = player2Y;
	pos.x = w - 30;
	SDL_RenderFillRect(renderer, &pos);
	drawCircle(x, y, 10);
	SDL_RenderPresent(renderer);
}

void _pollEvents() {
	SDL_Event event = SDL_Event();
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			running = false;

		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_w:
				W = true;
				break;
			case SDLK_s:
				S = true;
				break;

			case SDLK_UP:
				UP = true;
				break;
			case SDLK_DOWN:
				DOWN = true;
				break;
			}
		}

		if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
			case SDLK_w:
				W = 0;
				break;
			case SDLK_s:
				S = 0;
				break;

			case SDLK_UP:
				UP = 0;
				break;
			case SDLK_DOWN:
				DOWN = 0;
				break;
			case SDLK_SPACE:
				if (lost) {
					x = 400;
					y = 10;
					directionX = 0;
					directionY = 1;
					lost = 0;
				}
				break;
			}
		}
	}
}

int main(int argc, char* argv[]) {
	_init();
	int FPS = 120;
	int Delay = 1000 / FPS;

	Uint32 start;
	int frameTime;

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
