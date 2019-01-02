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

void ladujBMP(SDL_Surface** bmp, char const* nazwa, int x, int y)
{
	if (!bmp)
	{
		SDL_FreeSurface(*bmp);
		*bmp = nullptr;
	}

	*bmp = SDL_LoadBMP(nazwa);

	if (!*bmp)
		throw MyRuntimeExceptions::LoadImageException(SDL_GetError());
}

void wyswietlBMP(SDL_Surface* bmp, int x, int y)
{
	if (!bmp)
		throw MyRuntimeExceptions::ReadImageException(SDL_GetError());

	SDL_Rect offset;
	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(bmp, 0, screen, &offset);
}

void czyscEkran(Uint8 R, Uint8 G, Uint8 B)
{
	SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, R, G, B));
	SDL_Flip(screen);
}

void clean_up()
{
	if (buttons_texture != nullptr)
		SDL_FreeSurface(buttons_texture);
	if (screen != nullptr)
		SDL_FreeSurface(screen);
	if (input_file != nullptr)
		SDL_FreeSurface(input_file);

	//Quit SDL_ttf
	TTF_Quit();

	//Quit SDL
	SDL_Quit();
}

bool init_SDL()
{
	//Initialize all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "Unable to init SDL: " << SDL_GetError() << std::endl;
		return false;
	}

	// create basic window
	screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if (!screen)
	{
		std::cout << "Unable to set video: " << SDL_GetError() << std::endl;
		return false;
	}

	//Set the window caption
	SDL_WM_SetCaption("Button Test", NULL);

	//inicjalizacjia SDL_tff
	if (TTF_Init() < 0)
		return false;

	//If everything initialized fine
	return true;
}