#include "pch.h"
#include "data_preparation.h"


void nearest_neighbor(SDL_Surface *surface, std::vector<SDL_Color> &palette, vector<Uint8> &output)
{
	unsigned short width = surface->w;
	unsigned short height = surface->h;

	output.clear();
	output.reserve(width*height);

	//informacje o najblizszym kolorze
	//dla ka¿dego piksela znajdujemy najbli¿szy kolor z palety i dodajemy go do tablicy output
	int najmniejszy;
	int index;
	int tempNajmniejszy;

	int i, j, k;
	SDL_Color kolor;
	for (i = 0; i < width; ++i) 
	{
		for (j = 0; j < height; ++j) 
		{
			kolor = getPixel_BMP(surface, i, j);
			// wpierw najblizszy kolor to pierwszy z palety
			najmniejszy = static_cast<int>(	(kolor.r - palette[0].r)*(kolor.r - palette[0].r) +
											(kolor.g - palette[0].g)*(kolor.g - palette[0].g) +
											(kolor.b - palette[0].b)*(kolor.b - palette[0].b));
			index = 0;

			//szukanie najblizszego koloru
			for (k = 1; k < 64; ++k) 
			{
				tempNajmniejszy = static_cast<int>(	(kolor.r - palette[k].r)*(kolor.r - palette[k].r) +
													(kolor.g - palette[k].g)*(kolor.g - palette[k].g) +
													(kolor.b - palette[k].b)*(kolor.b - palette[k].b));
				if (tempNajmniejszy < najmniejszy) 
				{
					najmniejszy = tempNajmniejszy;
					index = k;
				}
			}

			output.push_back(index);
		}
	}
}