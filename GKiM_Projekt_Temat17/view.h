#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include "l_exceptions.h"
#include "menu_functions.h"

//buttons states
enum button_state { NONE, OVER, PRESSED, RELEASED, INACTIVE };

//return event states
struct Ret
{
	bool none;
	bool over;
	bool pressed;
	bool released;
	bool inactive;

	Ret() : none(false), over(false), pressed(false), released(false), inactive(false) {}
};

extern SDL_Surface *screen;
extern SDL_Event event;
extern bool inactive;
extern bool bmp;

class Button
{
private:
	SDL_Rect rectangle;
	SDL_Rect* texture_dimension; //na wartosc z texture_type


public:
	/*
	konstruktor klasy Button
	@param rect			podaje po�o�enie i wielko�� przycisku
	@param texture_dim	podaje po�o�enie na obrazie i rozmiar tekstury
	@EXCEPTIONS:		---
	*/
	Button(SDL_Rect rect, SDL_Rect* texture_dim);

	/*
	destruktor domy�lny klasy button
	@EXCEPTIONS:	---
	*/
	~Button() {}

	/*
	metoda zwracaj�ca warto�� rectangle (zawieraj�c� po�ozenie i wielko�� przycisku)
	@return			SDL-owy typ danych zawieraj�cy po�ozenie i wielko�� przycisku
	@EXCEPTIONS:	---
	*/
	SDL_Rect get_rectangle();

	/*
	metoda redefiniuj�ca parametry przycisku
	@param rect			podaje po�o�enie i wielko�� przycisku
	@param texture_dim	podaje po�o�enie na obrazie i rozmiar tekstury
	@EXCEPTIONS:		---
	*/
	void change_button(SDL_Rect rect, SDL_Rect* texture_dim);

	/*
	metoda wyswietlaj�ca przycisk na ekranie
	@param screen	definiuje okno w kt�rym przycisk zostanie narysowany 
	@EXCEPTIONS:	---
	*/
	void show(SDL_Surface* screen);

	/*
	metoda obs�uguj�ca eventy dla danego przycisku
	@event			struktura SDL_Event kt�ra obs�uguje eventy
	@return			warto�� kt�ra okre�la typ eventu odczytanego z danego przycisku
	@EXCEPTIONS:	---
	*/
	Ret handle_events(SDL_Event &event);
};

class Text
{
private:
	int x;
	int y;
	SDL_Surface* text;


public:
	/*
	konstruktor klasy Text
	@param x, y			definiuj� wyjsciowe polozenie tekstu
	@param tex			definuje tekst do wyswietlenia na ekranie
	@param color		definuje kolor tekstu wy�wietlanego
	@param font_num		definuje numer czcionki (wcze�niej wczytnej do zew�trznej tablicy) u�ytej do wyswetlenia tekstu
	@EXCEPTIONS:		---
	*/
	Text(int x, int y, const char* tex, SDL_Color color, int font_num);

	/*
	destruktor domy�lny klasy Text
	@EXCEPTIONS:	---
	*/
	~Text() {}

	/*
	metoda redefiniuj�ca parametry Tekstu
	@param x, y			definiuj� wyjsciowe polozenie tekstu
	@param name			definuje tekst do wyswietlenia na ekranie
	@param color		definuje kolor tekstu wy�wietlanego
	@param font_num		definuje numer czcionki (wcze�niej wczytnej do zew�trznej tablicy) u�ytej do wyswetlenia tekstu
	@EXCEPTIONS:		---
	*/
	void change_text(int x, int y, std::string name, SDL_Color color, int font_num);

	/*
	metoda redefiniuj�ca parametry Tekstu
	@param x, y			definiuj� wyjsciowe polozenie tekstu
	@param name			definuje tekst do wyswietlenia na ekranie
	@param color		definuje kolor tekstu wy�wietlanego
	@param font_num		definuje numer czcionki (wcze�niej wczytnej do zew�trznej tablicy) u�ytej do wyswetlenia tekstu
	@EXCEPTIONS:		---
	*/
	void change_text(int x, int y, const char* name, SDL_Color color, int font_num);

	/*
	metoda wyswietlaj�ca tekst na ekranie
	@param screen	definiuje okno w kt�rym tekst zostanie wypisany
	@EXCEPTIONS:	---
	*/
	void show(SDL_Surface* screen);
};

struct Menu
{
	std::vector<Button> buttons;
	std::vector<Text> texts;
};


//-----------------------funkcje--------------------

/*
funkcja inicjalizuj�ca tablic� typ�w tekstur
@EXCEPTIONS:	---
*/
void INIT_texture_type();

/*
funkcja wczytuj�ca tekstury przycisk�w z pliku, oraz czcionki
@EXCEPTIONS:	LoadImageException, LoadFontException
*/
void INIT_view();

/*
funkcja inicjalizuj�ca menu (przyciski i tesksty w g��wnym menu)
@EXCEPTIONS:	---
*/
void INIT_MENU();

/*
funkcja rysuj�ca wszystkie elementy menu g��wnego na ekran
@EXCEPTIONS:	---
*/
void MENU_show();

/*
funkcja obs�uguj�ca eventy, czyli ca�e dzia�anie menu
@EXCEPTIONS:	---
*/
void MENU_event();

/*
funkcja zwalniaj�ca pami�� zaalokowan� przez inicjalizacj� menu
@EXCEPTIONS:	---
*/
void CLEAN_MENU();

#endif // !VIEW_H