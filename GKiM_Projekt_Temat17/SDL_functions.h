#pragma once
#include <SDL.h>

extern SDL_Surface *screen;
extern int width;
extern int height;
extern char const* tytul;

/*
funkcja ustawiaj�ca piksel w oknie
@param x, y		definiuj� po�o�enie piksela
@param R, G, B	definuj� kolor ustawianego piksela
*/
void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B);

/*
funkcja pobieraj�ca kolor piksela z okna
@param x, y		definiuj� po�o�enie piksela
@return			SDL-owy typ danych w kt�rym zaweira kolor piksela na podanym po�o�eniu
*/
SDL_Color getPixel(int x, int y);

/*
funkcja �aduj�ca obraz w pliku BMP
@param nazwa	definiuje nazw� pliku kt�ry ma by� otwarty
@param x,y		definuj� polozenie obrazu
*/
void ladujBMP(char const* nazwa, int x, int y);

/*
funkcja czyszcz�ca onko (wypelniaj�ca okno jednolitym wybranym kolorem)
@param R, G, B	definuj� kolor
*/
void czyscEkran(Uint8 R, Uint8 G, Uint8 B);

//-----------------------------------------------------------------

/*
funkcja tymczasowo bez zawarto�ci, moz� by� zdefiniowana przez u�ytkownika
*/
void Funkcja1();