#ifndef SDL_FUNCTIONS_H
#define SDL_FUNCTIONS_H

#include <iostream>
#include <SDL_ttf.h>
#include <SDL.h>
#include "l_exceptions.h"

extern SDL_Surface *screen;
extern SDL_Surface *buttons_texture;
extern SDL_Surface *input_file;
extern const int width;
extern const int height;
extern char const* tytul;


/*
funkcja ustawiaj¹ca piksel w oknie
@param x, y		definiuj¹ po³o¿enie piksela
@param R, G, B	definuj¹ kolor ustawianego piksela
@EXCEPTIONS:	---
*/
void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B);

/*
funkcja pobieraj¹ca kolor piksela z okna
@param x, y		definiuj¹ po³o¿enie piksela
@return			SDL-owy typ danych w którym zaweira kolor piksela na podanym po³o¿eniu
@EXCEPTIONS:	---
*/
SDL_Color getPixel(int x, int y);

/*
funkcja pobieraj¹ca kolor piksela z obiektu SDL_Surface
@param surface	definiuje obiekt z którego odczytywane s¹ piksele
@param x, y		definiuj¹ po³o¿enie piksela
@return			SDL-owy typ danych w którym zaweira kolor piksela na podanym po³o¿eniu
@EXCEPTIONS:	---
*/
SDL_Color getPixel_BMP(SDL_Surface *surface, int x, int y);

/*
funkcja ³aduj¹ca obraz w pliku BMP
@param bmp		definuje SDL_Surface do kótrej ³adujemy plik
@param nazwa	definiuje nazwê pliku który ma byæ otwarty
@param x,y		definuj¹ polozenie obrazu
@EXCEPTIONS:	LoadImageException
*/
void ladujBMP(SDL_Surface** bmp, char const* nazwa, int x, int y);

/*
funkcja wyswietlajaca w oknie za³adowany wczeœniej obraz w formacie BMP
@param bmp		definuje SDL_Surface z której wyswietlamy obraz
@param x,y		definuj¹ polozenie obrazu na ekranie
@EXCEPTIONS:	ReadImageException
*/
void wyswietlBMP(SDL_Surface* bmp, int x, int y);

/*
funkcja czyszcz¹ca onko (wypelniaj¹ca okno jednolitym wybranym kolorem)
@param R, G, B	definuj¹ kolor
@EXCEPTIONS:	---
*/
void czyscEkran(Uint8 R, Uint8 G, Uint8 B);

/*
funkcja usuwaj¹ca wszytkie rzeczy aby poprawnie zakoñczyæ dzia³anie programu
@EXCEPTIONS:	---
*/
void clean_up();

/*
funkcja inicjalizuj¹ca bibliotekê SDL i SDL_ttf
@return			true gdy inicjalizacja przebieg³a pomyœlnie, flase gdy nie uda³o siê przeprowadziæ inicjalizacji
@EXCEPTIONS:	---
*/
bool init_SDL();

#endif // !SDL_FUNCTIONS_H