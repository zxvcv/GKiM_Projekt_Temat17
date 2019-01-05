#include "pch.h"
#include "dithering.h"


Uint8 getR(Uint8 val) { return val & 0b00110000; }
Uint8 getG(Uint8 val) { return val & 0b00001100; }
Uint8 getB(Uint8 val) { return val & 0b00000011; }


Uint8 **dithering(SDL_Surface *surface, SDL_Color *palette)
{
	int width = input_file->w;
	int height = input_file->h;

	//tablica danych wyjsciowych
	Uint8 **output = new Uint8 *[width];
	for (int i = 0; i < width; ++i)
		output[i] = new Uint8[height];

	//tworzenie i inicjalizowanie zerami tablicy bledow
	kolor blad;
	kolor ** bledy = new kolor *[width + 2];
	for (int i = 0; i < width + 2; ++i) 
	{
		bledy[i] = new kolor[height + 2];
	}

	for (int i = 0; i < width + 2; ++i) 
	{
		for (int j = 0; j < height + 2; ++j) 
		{
			bledy[i][j].r = 0;
			bledy[i][j].g = 0;
			bledy[i][j].b = 0;
		}
	}

	int przesuniecie = 1;

	//informacje o najblizszym kolorze
	int najmniejszy;
	int index;
	int tempNajmniejszy;

	

	int k;
	SDL_Color kolor;
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			kolor = getPixel_BMP(surface, i, j);

			// wpierw najblizszy kolor to pierwszy z palety
			najmniejszy = static_cast<int>(	(kolor.r + bledy[i + przesuniecie][j].r - palette[0].r)*(kolor.r + bledy[i + przesuniecie][j].r - palette[0].r) +
											(kolor.g + bledy[i + przesuniecie][j].g - palette[0].g)*(kolor.g + bledy[i + przesuniecie][j].g - palette[0].g) +
											(kolor.b + bledy[i + przesuniecie][j].b - palette[0].b)*(kolor.b + bledy[i + przesuniecie][j].b - palette[0].b));
			index = 0;

			//szukanie najblizszego koloru
			for (k = 1; k < 64; ++k) 
			{
				tempNajmniejszy = static_cast<int>( (kolor.r + bledy[i + przesuniecie][j].r - palette[k].r)*(kolor.r + bledy[i + przesuniecie][j].r - palette[k].r) + 
													(kolor.g + bledy[i + przesuniecie][j].g - palette[k].g)*(kolor.g + bledy[i + przesuniecie][j].g - palette[k].g) + 
													(kolor.b + bledy[i + przesuniecie][j].b - palette[k].b)*(kolor.b + bledy[i + przesuniecie][j].b - palette[k].b) );
				if (tempNajmniejszy < najmniejszy) 
				{
					najmniejszy = tempNajmniejszy;
					index = k;
				}
			}

			output[i][j] = getR(palette[index].r) | getG(palette[index].g) | getB(palette[index].b);
			

			blad.r = kolor.r - palette[index].r;
			blad.g = kolor.g - palette[index].g;
			blad.b = kolor.b - palette[index].b;

			bledy[i + przesuniecie + 1][j].r += (blad.r * 7.0 / 16);
			bledy[i + przesuniecie - 1][j + 1].r += (blad.r * 3.0 / 16);
			bledy[i + przesuniecie][j + 1].r += (blad.r * 5.0 / 16);
			bledy[i + przesuniecie + 1][j + 1].r += (blad.r * 1.0 / 16);

			bledy[i + przesuniecie + 1][j].g += (blad.g * 7.0 / 16);
			bledy[i + przesuniecie - 1][j + 1].g += (blad.g * 3.0 / 16);
			bledy[i + przesuniecie][j + 1].g += (blad.g * 5.0 / 16);
			bledy[i + przesuniecie + 1][j + 1].g += (blad.g * 1.0 / 16);

			bledy[i + przesuniecie + 1][j].b += (blad.b * 7.0 / 16);
			bledy[i + przesuniecie - 1][j + 1].b += (blad.b * 3.0 / 16);
			bledy[i + przesuniecie][j + 1].b += (blad.b * 5.0 / 16);
			bledy[i + przesuniecie + 1][j + 1].b += (blad.b * 1.0 / 16);
		}
	}

	for (int i = 0; i < width + 2; ++i)
		delete[] bledy[i];
	delete[] bledy;

	return output;
}