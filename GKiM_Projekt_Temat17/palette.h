#ifndef PALETTE_H
#define PALETTE_H

#include <SDL.h>
#include <vector>
#include "SDL_functions.h"
#include <algorithm>

struct color_ocurrence {
	SDL_Color color;
	int occurrences;
	bool compared;
};

struct kod {
	int ile;
	int gdzie;
	Uint8 wartosc;
};


enum IMPOSED_PALETTE_TYPE{
	IMPOSED_PALETTE_1 = 1, 
	IMPOSED_PALETTE_2 = 2, 
	SHADERS_OF_GREY_PALETTE = 3
};

class imposed_palette
{
public:
	imposed_palette(IMPOSED_PALETTE_TYPE type);
	~imposed_palette() {}
	std::vector<SDL_Color> &returnPalette();
	IMPOSED_PALETTE_TYPE returnPaletteType();

private:
	std::vector<SDL_Color> palette;
	IMPOSED_PALETTE_TYPE palette_type;

	void init_palette1();
	void init_palette2();
	void init_palette3();
};

class dedicated_palette
{
public:
	dedicated_palette() {}
	~dedicated_palette() {}
	void search_palette(SDL_Surface *surface);
	std::vector<SDL_Color> &returnPalette();

private:
	std::vector<color_ocurrence> occurrences;
	std::vector<SDL_Color> palette;

	int already_occurred(SDL_Color pixel);
	void count_ocurreces(SDL_Surface *surface);
	double distance(SDL_Color colorA, SDL_Color colorB);
	color_ocurrence * closest_pair();
};


#endif // !PALETTE_H

