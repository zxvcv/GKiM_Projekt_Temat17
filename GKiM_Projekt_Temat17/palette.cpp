#include "pch.h"
#include "palette.h"


//-----------------imposed_palette-----------------

imposed_palette::imposed_palette(IMPOSED_PALETTE_TYPE type): palette_type(type)
{
	switch (type)
	{
	case IMPOSED_PALETTE_1:
		this->init_palette1();
		break;
	case IMPOSED_PALETTE_2:
		this->init_palette2();
		break;
	case SHADERS_OF_GREY_PALETTE:
		this->init_palette3();
		break;
	default:
		break;
	}
}

std::vector<SDL_Color> &imposed_palette::returnPalette()
{
	return palette;
}

IMPOSED_PALETTE_TYPE imposed_palette::returnPaletteType()
{
	return palette_type;
}

void imposed_palette::init_palette1()
{
	
	palette = { {   0,   0,   0 }, {   0,   0,  85 }, {   0,   0, 171 }, {   0,   0, 255 },
				{   0,  85,   0 }, {   0,  85,  85 }, {   0,  85, 171 }, {   0,  85, 255 },
				{   0, 171,   0 }, {   0, 171,  85 }, {   0, 171, 171 }, {   0, 171, 255 },
				{   0, 255,   0 }, {   0, 255,  85 }, {   0, 255, 171 }, {   0, 255, 255 },
				{  85,   0,   0 }, {  85,   0,  85 }, {  85,   0, 171 }, {  85,   0, 255 },
				{  85,  85,   0 }, {  85,  85,  85 }, {  85,  85, 171 }, {  85,  85, 255 },
				{  85, 171,   0 }, {  85, 171,  85 }, {  85, 171, 171 }, {  85, 171, 255 },
				{  85, 255,   0 }, {  85, 255,  85 }, {  85, 255, 171 }, {  85, 255, 255 },
				{ 171,   0,   0 }, { 171,   0,  85 }, { 171,   0, 171 }, { 171,   0, 255 },
				{ 171,  85,   0 }, { 171,  85,  85 }, { 171,  85, 171 }, { 171,  85, 255 },
				{ 171, 171,   0 }, { 171, 171,  85 }, { 171, 171, 171 }, { 171, 171, 255 },
				{ 171, 255,   0 }, { 171, 255,  85 }, { 171, 255, 171 }, { 171, 255, 255 },
				{ 255,   0,   0 }, { 255,   0,  85 }, { 255,   0, 171 }, { 255,   0, 255 },
				{ 255,  85,   0 }, { 255,  85,  85 }, { 255,  85, 171 }, { 255,  85, 255 },
				{ 255, 171,   0 }, { 255, 171,  85 }, { 255, 171, 171 }, { 255, 171, 255 },
				{ 255, 255,   0 }, { 255, 255,  85 }, { 255, 255, 171 }, { 255, 255, 255 } };

}

void imposed_palette::init_palette2()
{
	palette = { {   0,   0,   0 }, {   0,   0,  64 }, {   0,   0, 128 }, {   0,   0, 192 },
				{   0,  64,   0 }, {   0,  64,  64 }, {   0,  64, 128 }, {   0,  64, 192 },
				{   0, 128,   0 }, {   0, 128,  64 }, {   0, 128, 128 }, {   0, 128, 192 },
				{   0, 192,   0 }, {   0, 192,  64 }, {   0, 192, 128 }, {   0, 192, 192 },
				{  64,   0,   0 }, {  64,   0,  64 }, {  64,   0, 128 }, {  64,   0, 192 },
				{  64,  64,   0 }, {  64,  64,  64 }, {  64,  64, 128 }, {  64,  64, 192 },
				{  64, 128,   0 }, {  64, 128,  64 }, {  64, 128, 128 }, {  64, 128, 192 },
				{  64, 192,   0 }, {  64, 192,  64 }, {  64, 192, 128 }, {  64, 192, 192 },
				{ 128,   0,   0 }, { 128,   0,  64 }, { 128,   0, 128 }, { 128,   0, 192 },
				{ 128,  64,   0 }, { 128,  64,  64 }, { 128,  64, 128 }, { 128,  64, 192 },
				{ 128, 128,   0 }, { 128, 128,  64 }, { 128, 128, 128 }, { 128, 128, 192 },
				{ 128, 192,   0 }, { 128, 192,  64 }, { 128, 192, 128 }, { 128, 192, 192 },
				{ 192,   0,   0 }, { 192,   0,  64 }, { 192,   0, 128 }, { 192,   0, 192 },
				{ 192,  64,   0 }, { 192,  64,  64 }, { 192,  64, 128 }, { 192,  64, 192 },
				{ 192, 128,   0 }, { 192, 128,  64 }, { 192, 128, 128 }, { 192, 128, 192 },
				{ 192, 192,   0 }, { 192, 192,  64 }, { 192, 192, 128 }, { 192, 192, 192 } };

}

void imposed_palette::init_palette3()
{
	palette = { {   0,   0,   0 }, {   4,   4,   4 }, {   8,   8,   8 }, {  12,  12,  12 },
				{  16,  16,  16 }, {  20,  20,  20 }, {  24,  24,  24 }, {  28,  28,  28 },
				{  32,  32,  32 }, {  36,  36,  36 }, {  40,  40,  40 }, {  44,  44,  44 },
				{  48,  48,  48 }, {  52,  52,  52 }, {  56,  56,  56 }, {  60,  60,  60 },
				{  64,  64,  64 }, {  68,  68,  68 }, {  72,  72,  72 }, {  76,  76,  76 },
				{  80,  80,  80 }, {  84,  84,  84 }, {  88,  88,  88 }, {  92,  92,  92 },
				{  96,  96,  96 }, { 100, 100, 100 }, { 104, 104, 104 }, { 108, 108, 108 },
				{ 112, 112, 112 }, { 116, 116, 116 }, { 120, 120, 120 }, { 124, 124, 124 },
				{ 128, 128, 128 }, { 132, 132, 132 }, { 136, 136, 136 }, { 140, 140, 140 },
				{ 144, 144, 144 }, { 148, 148, 148 }, { 152, 152, 152 }, { 156, 156, 156 },
				{ 160, 160, 160 }, { 164, 164, 164 }, { 168, 168, 168 }, { 172, 172, 172 },
				{ 176, 176, 176 }, { 180, 180, 180 }, { 184, 184, 184 }, { 188, 188, 188 },
				{ 192, 192, 192 }, { 196, 196, 196 }, { 200, 200, 200 }, { 204, 204, 204 },
				{ 208, 208, 208 }, { 212, 212, 212 }, { 216, 216, 216 }, { 220, 220, 220 },
				{ 224, 224, 224 }, { 228, 228, 228 }, { 232, 232, 232 }, { 236, 236, 236 },
				{ 240, 240, 240 }, { 244, 244, 244 }, { 248, 248, 248 }, { 252, 252, 252 } };
}


//-----------------dedicated_palette-----------------

int dedicated_palette::already_occurred(SDL_Color pixel)
{
	for (int i = 0; i < occurrences.size() - 1; i++)
	{
		if ((occurrences[i].color.r == pixel.r) && (occurrences[i].color.g == pixel.g) && (occurrences[i].color.b == pixel.b))
		{
			return i;
		}
	}
	return -1;
}

void dedicated_palette::count_ocurreces(SDL_Surface * surface)
{
	int width = input_file->w;
	int height = input_file->h;
	/*
	SDL_Color pixel = getPixel_BMP(surface, 0, 0);
	if (occurrences.empty()) {
		color_ocurrence newOccurrence;
		newOccurrence.color = pixel;
		newOccurrence.occurrences = 1;
		newOccurrence.compared = false;
		occurrences.emplace_back(newOccurrence);
	}
	*/
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			SDL_Color pixel = getPixel_BMP(surface, i, j);
			int occurrenceIndex = already_occurred(pixel);

			if (occurrenceIndex == -1 || occurrences.empty()) {
				color_ocurrence newOccurrence;
				newOccurrence.color = pixel;
				newOccurrence.occurrences = 1;
				newOccurrence.compared = false;
				occurrences.emplace_back(newOccurrence);
			}
			else {
				occurrences[occurrenceIndex].occurrences++;
			}

		}
	}
}

double dedicated_palette::distance(SDL_Color colorA, SDL_Color colorB)
{
	int r = (colorA.r - colorB.r) * (colorA.r - colorB.r);
	int g = (colorA.g - colorB.g) * (colorA.g - colorB.g);
	int b = (colorA.b - colorB.b) * (colorA.b - colorB.b);

	return sqrt(r + g + b);
}

color_ocurrence * dedicated_palette::closest_pair()
{
	color_ocurrence * pair = new color_ocurrence[2];
	double minDistance = 442; //przekatna szescianu RGB zaokraglona w gore

	for (int i = 0; i < occurrences.size() - 1; i++)
	{
		color_ocurrence colorA = occurrences[i];
		if (colorA.compared == true)
			continue;
		for (int j = i + 1; j < occurrences.size(); j++) {

			color_ocurrence colorB = occurrences[j];
			if (colorB.compared == true)
				continue;
			if (distance(colorA.color, colorB.color) < minDistance) {

				minDistance = distance(colorA.color, colorB.color);
				pair[0] = colorA;
				pair[1] = colorB;
			}
		}
	}

	return pair;
}

void dedicated_palette::search_palette(SDL_Surface *surface)
{
	count_ocurreces(surface);
	while (palette.size() < 64) {
		color_ocurrence * pair;
		pair = closest_pair();
		if (pair[0].occurrences < pair[1].occurrences)
			palette.emplace_back(pair[1].color);
		else
			palette.emplace_back(pair[0].color);
	}
}

std::vector<SDL_Color> &dedicated_palette::returnPalette()
{
	return palette;
}