#include "pch.h"
#include "SDL_functions.h"


void setPixel(SDL_Surface *surface, int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
	if ((x >= 0) && (x<width) && (y >= 0) && (y<height))
	{
		/* Zamieniamy poszczególne sk³adowe koloru na format koloru pixela */
		Uint32 pixel = SDL_MapRGB(surface->format, R, G, B);

		/* Pobieramy informacji ile bajtów zajmuje jeden pixel */
		int bpp = surface->format->BytesPerPixel;

		/* Obliczamy adres pixela */
		Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

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

SDL_Color getPixel_BMP(SDL_Surface *surface, int x, int y)
{
	/*
		konwerter przydatne https://online-converting.com/image/convert2bmp/

		- wszystkie obrazki konwertowalem z obrazek24.bmp

		- przy konwersji 24->16 zostaj¹ obciête mniejznacz¹ce bity to znaczy ¿e z obrazek24 z liczby 255 konwertujac do obrazek16
		otrzymamy 248 bo zapisuje na 5 bitach, a nie 8

		obrazki
		- liczba oznacza na ilu bitach zapisywane sa kolory
		- dodatkowa litera "A" oznacza ¿e jest RGBA, a nie tylko RGB

		- wszyskie obrazki, które stworzylem
		obrazek32.bmp
		obrazek32A.bmp
		obrazek24.bmp
		obrazek16.bmp   // proporcje kolorów RGB 5:5:5
		obrazek16b.bmp  // proporcje kolorów RGB 5:6:5 -> wiêcej o jeden bit dla sk³adowej G [zielonej]
		obrazek16A.bmp  // proporcje kolorów RGB 5:5:5
		obrazek8.bmp
		obrazek4.bmp
		obrazek1i.bmp   // indexed - cokolwiek to oznacza
		obrazek1m.bmp   // mono - to tez nie wiem... ale byly do wyboru to wzialem oba, roznia przy odczycie
		*/

	Uint32 bpp = surface->format->BytesPerPixel;
	SDL_PixelFormat *fmt;
	fmt = surface->format;


	Uint32 R, G, B;
	SDL_Color *color;

	Uint8 *p;
	switch (bpp)
	{
	case 1:
		SDL_LockSurface(surface);
		p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
		SDL_UnlockSurface(surface);
		color = &fmt->palette->colors[*p];
		R = color->r;
		G = color->g;
		B = color->b;
		break;

	case 2:
		SDL_LockSurface(surface);
		p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
		SDL_UnlockSurface(surface);

		R = *(Uint16 *)p & fmt->Rmask;
		R = R >> fmt->Rshift;
		R = R << fmt->Rloss;

		G = *(Uint16 *)p & fmt->Gmask;
		G = G >> fmt->Gshift;
		G = G << fmt->Gloss;

		B = *(Uint16 *)p & fmt->Bmask;
		B = B >> fmt->Bshift;
		B = B << fmt->Bloss;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			SDL_LockSurface(surface);
			p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
			SDL_UnlockSurface(surface);

			R = p[0];
			G = p[1];
			B = p[2];
		}
		else
		{
			SDL_LockSurface(surface);
			p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
			SDL_UnlockSurface(surface);

			R = p[2];
			G = p[1];
			B = p[0];
		}
		break;

	case 4:
		SDL_LockSurface(surface);
		p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
		SDL_UnlockSurface(surface);
		R = *(Uint32 *)p & fmt->Rmask;
		R = R >> fmt->Rshift;
		R = R << fmt->Rloss;

		G = *(Uint32 *)p & fmt->Gmask;
		G = G >> fmt->Gshift;
		G = G << fmt->Gloss;

		B = *(Uint32 *)p & fmt->Bmask;
		B = B >> fmt->Bshift;
		B = B << fmt->Bloss;
		break;

	default:
		R = 0;
		G = 0;
		B = 0;
		break;
	}
	return { (Uint8)R, (Uint8)G, (Uint8)B };
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

void zapiszBMP(SDL_Surface** surface, char const* nazwa)
{
	if (!surface)
	{
		SDL_FreeSurface(*surface);
		*surface = nullptr;
	}
	
	SDL_SaveBMP(*surface, nazwa);
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
	if (input_file_pc.is_open())
		input_file_pc.close();

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