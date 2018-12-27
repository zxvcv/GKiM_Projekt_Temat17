#pragma once
#include <SDL.h>

extern SDL_Surface *screen;
extern int width;
extern int height;
extern char const* tytul;

/*
funkcja ustawiaj¹ca piksel w oknie
@param x, y		definiuj¹ po³o¿enie piksela
@param R, G, B	definuj¹ kolor ustawianego piksela
*/
void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B);

/*
funkcja pobieraj¹ca kolor piksela z okna
@param x, y		definiuj¹ po³o¿enie piksela
@return			SDL-owy typ danych w którym zaweira kolor piksela na podanym po³o¿eniu
*/
SDL_Color getPixel(int x, int y);

/*
funkcja ³aduj¹ca obraz w pliku BMP
@param nazwa	definiuje nazwê pliku który ma byæ otwarty
@param x,y		definuj¹ polozenie obrazu
*/
void ladujBMP(char const* nazwa, int x, int y);

/*
funkcja czyszcz¹ca onko (wypelniaj¹ca okno jednolitym wybranym kolorem)
@param R, G, B	definuj¹ kolor
*/
void czyscEkran(Uint8 R, Uint8 G, Uint8 B);

//-----------------------------------------------------------------

/*
funkcja tymczasowo bez zawartoœci, mozê byæ zdefiniowana przez u¿ytkownika
*/
void Funkcja1();