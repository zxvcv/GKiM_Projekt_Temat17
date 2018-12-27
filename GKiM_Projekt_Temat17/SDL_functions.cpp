#include "pch.h"
#include "SDL_functions.h"


void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
	if ((x >= 0) && (x<width) && (y >= 0) && (y<height))
	{
		/* Zamieniamy poszczególne sk³adowe koloru na format koloru pixela */
		Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

		/* Pobieramy informacji ile bajtów zajmuje jeden pixel */
		int bpp = screen->format->BytesPerPixel;

		/* Obliczamy adres pixela */
		Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;

		/* Ustawiamy wartoœæ pixela, w zale¿noœci od formatu powierzchni*/
		switch (bpp)
		{
		case 1: //8-bit
			*p = pixel;
			break;

		case 2: //16-bit
			*(Uint16 *)p = pixel;
			break;

		case 3: //24-bit
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			}
			else {
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;

		case 4: //32-bit
			*(Uint32 *)p = pixel;
			break;

		}
		/* update the screen (aka double buffering) */
	}
}

SDL_Color getPixel(int x, int y) {
	SDL_Color color;
	Uint32 col = 0;
	if ((x >= 0) && (x<width) && (y >= 0) && (y<height)) {
		//determine position
		char* pPosition = (char*)screen->pixels;
		//offset by y
		pPosition += (screen->pitch*y);
		//offset by x
		pPosition += (screen->format->BytesPerPixel*x);
		//copy pixel data
		memcpy(&col, pPosition, screen->format->BytesPerPixel);
		//convert color
		SDL_GetRGB(col, screen->format, &color.r, &color.g, &color.b);
	}
	return (color);
}

void ladujBMP(char const* nazwa, int x, int y)
{
	SDL_Surface* bmp = SDL_LoadBMP(nazwa);
	if (!bmp)
	{
		printf("Unable to load bitmap: %s\n", SDL_GetError());
	}
	else
	{
		SDL_Rect dstrect;
		dstrect.x = x;
		dstrect.y = y;
		SDL_BlitSurface(bmp, 0, screen, &dstrect);
		SDL_Flip(screen);
		SDL_FreeSurface(bmp);
	}

}

void czyscEkran(Uint8 R, Uint8 G, Uint8 B)
{
	SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, R, G, B));
	SDL_Flip(screen);

}



void Funkcja1()
{
	//...

	SDL_Flip(screen);
}