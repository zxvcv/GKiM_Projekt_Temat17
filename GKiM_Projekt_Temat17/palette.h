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
	int16_t ile;
	int16_t gdzie;
	Uint8 wartosc;
};


enum PALETTE_TYPE {
	IMPOSED_PALETTE = 1,
	DEDICATED_PALETTE = 2,
	SHADERS_OF_GREY_PALETTE = 3
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

class Palette
{
private:
	std::vector<SDL_Color> palette;
	PALETTE_TYPE type;

	void init_palette1();
	void init_palette2();
	void init_palette3();

public:
	Palette() {}
	Palette(PALETTE_TYPE type);
	~Palette() {}
	void changePalette(PALETTE_TYPE type);
	std::vector<SDL_Color> &returnPalette();
	PALETTE_TYPE returnPaletteType();
	int getSize();
};


#endif // !PALETTE_H

