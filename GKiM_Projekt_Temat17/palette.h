#ifndef PALETTE_H
#define PALETTE_H

#include <SDL.h>
#include <vector>
#include <algorithm>
#include "SDL_functions.h"
#include "medianCut.h"

extern SDL_Surface *input_file;

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

