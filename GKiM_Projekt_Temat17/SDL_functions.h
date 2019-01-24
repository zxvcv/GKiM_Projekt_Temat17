#ifndef SDL_FUNCTIONS_H
#define SDL_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <SDL_ttf.h>
#include <SDL.h>
#include "l_exceptions.h"


extern SDL_Surface *screen;
extern SDL_Surface *buttons_texture;
extern SDL_Surface *input_file;
extern const int width;
extern const int height;
extern char const* tytul;
extern std::ifstream input_file_pc;

/*
funkcja ustawiaj�ca piksel w oknie
@param surface	definuje powierzchnie SDL na ktorej bedziemy rysowac piksele
@param x, y		definiuj� po�o�enie piksela
@param R, G, B	definuj� kolor ustawianego piksela
@EXCEPTIONS:	---
*/
void setPixel(SDL_Surface *surface, int x, int y, Uint8 R, Uint8 G, Uint8 B);

/*
funkcja pobieraj�ca kolor piksela z okna
@param x, y		definiuj� po�o�enie piksela
@return			SDL-owy typ danych w kt�rym zaweira kolor piksela na podanym po�o�eniu
@EXCEPTIONS:	---
*/
SDL_Color getPixel(int x, int y);

/*
funkcja pobieraj�ca kolor piksela z obiektu SDL_Surface
@param surface	definiuje obiekt z kt�rego odczytywane s� piksele
@param x, y		definiuj� po�o�enie piksela
@return			SDL-owy typ danych w kt�rym zaweira kolor piksela na podanym po�o�eniu
@EXCEPTIONS:	---
*/
SDL_Color getPixel_BMP(SDL_Surface *surface, int x, int y);

/*
funkcja �aduj�ca obraz w pliku BMP
@param bmp		definuje SDL_Surface do k�trej �adujemy plik
@param nazwa	definiuje nazw� pliku kt�ry ma by� otwarty
@param x,y		definuj� polozenie obrazu
@EXCEPTIONS:	LoadImageException
*/
void ladujBMP(SDL_Surface** bmp, char const* nazwa, int x, int y);

/*
funkcja zapisujaca obraz do pliku BMP
@param surface	powierzchnia SDL z kt�rej rysujemy obraz
@param nazwa	definiuje nazw� pliku do kt�rego dane maj� byc zapisane
@EXCEPTIONS:	---
*/
void zapiszBMP(SDL_Surface** surface, char const* nazwa);

/*
funkcja wyswietlajaca w oknie za�adowany wcze�niej obraz w formacie BMP
@param bmp		definuje SDL_Surface z kt�rej wyswietlamy obraz
@param x,y		definuj� polozenie obrazu na ekranie
@EXCEPTIONS:	ReadImageException
*/
void wyswietlBMP(SDL_Surface* bmp, int x, int y);

/*
funkcja czyszcz�ca onko (wypelniaj�ca okno jednolitym wybranym kolorem)
@param R, G, B	definuj� kolor
@EXCEPTIONS:	---
*/
void czyscEkran(Uint8 R, Uint8 G, Uint8 B);

/*
funkcja usuwaj�ca wszytkie otrzowone elementy (jesli potrzebne) aby poprawnie zampnac program
@EXCEPTIONS:	---
*/
void clean_up();

/*
funkcja inicjalizuj�ca bibliotek� SDL i SDL_ttf
@return			true gdy inicjalizacja przebieg�a pomy�lnie, flase gdy nie uda�o si� przeprowadzi� inicjalizacji
@EXCEPTIONS:	---
*/
bool init_SDL();

#endif // !SDL_FUNCTIONS_H