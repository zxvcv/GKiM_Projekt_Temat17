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
	@param rect			podaje po³o¿enie i wielkoœæ przycisku
	@param texture_dim	podaje po³o¿enie na obrazie i rozmiar tekstury
	@EXCEPTIONS:		---
	*/
	Button(SDL_Rect rect, SDL_Rect* texture_dim);

	/*
	destruktor domyœlny klasy button
	@EXCEPTIONS:	---
	*/
	~Button() {}

	/*
	metoda zwracaj¹ca wartoœæ rectangle (zawieraj¹c¹ po³ozenie i wielkoœæ przycisku)
	@return			SDL-owy typ danych zawieraj¹cy po³ozenie i wielkoœæ przycisku
	@EXCEPTIONS:	---
	*/
	SDL_Rect get_rectangle();

	/*
	metoda redefiniuj¹ca parametry przycisku
	@param rect			podaje po³o¿enie i wielkoœæ przycisku
	@param texture_dim	podaje po³o¿enie na obrazie i rozmiar tekstury
	@EXCEPTIONS:		---
	*/
	void change_button(SDL_Rect rect, SDL_Rect* texture_dim);

	/*
	metoda wyswietlaj¹ca przycisk na ekranie
	@param screen	definiuje okno w którym przycisk zostanie narysowany 
	@EXCEPTIONS:	---
	*/
	void show(SDL_Surface* screen);

	/*
	metoda obs³uguj¹ca eventy dla danego przycisku
	@event			struktura SDL_Event która obs³uguje eventy
	@return			wartoœæ która okreœla typ eventu odczytanego z danego przycisku
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
	@param x, y			definiuj¹ wyjsciowe polozenie tekstu
	@param tex			definuje tekst do wyswietlenia na ekranie
	@param color		definuje kolor tekstu wyœwietlanego
	@param font_num		definuje numer czcionki (wczeœniej wczytnej do zewêtrznej tablicy) u¿ytej do wyswetlenia tekstu
	@EXCEPTIONS:		---
	*/
	Text(int x, int y, const char* tex, SDL_Color color, int font_num);

	/*
	destruktor domyœlny klasy Text
	@EXCEPTIONS:	---
	*/
	~Text() {}

	/*
	metoda redefiniuj¹ca parametry Tekstu
	@param x, y			definiuj¹ wyjsciowe polozenie tekstu
	@param name			definuje tekst do wyswietlenia na ekranie
	@param color		definuje kolor tekstu wyœwietlanego
	@param font_num		definuje numer czcionki (wczeœniej wczytnej do zewêtrznej tablicy) u¿ytej do wyswetlenia tekstu
	@EXCEPTIONS:		---
	*/
	void change_text(int x, int y, std::string name, SDL_Color color, int font_num);

	/*
	metoda redefiniuj¹ca parametry Tekstu
	@param x, y			definiuj¹ wyjsciowe polozenie tekstu
	@param name			definuje tekst do wyswietlenia na ekranie
	@param color		definuje kolor tekstu wyœwietlanego
	@param font_num		definuje numer czcionki (wczeœniej wczytnej do zewêtrznej tablicy) u¿ytej do wyswetlenia tekstu
	@EXCEPTIONS:		---
	*/
	void change_text(int x, int y, const char* name, SDL_Color color, int font_num);

	/*
	metoda wyswietlaj¹ca tekst na ekranie
	@param screen	definiuje okno w którym tekst zostanie wypisany
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
funkcja inicjalizuj¹ca tablicê typów tekstur
@EXCEPTIONS:	---
*/
void INIT_texture_type();

/*
funkcja wczytuj¹ca tekstury przycisków z pliku, oraz czcionki
@EXCEPTIONS:	LoadImageException, LoadFontException
*/
void INIT_view();

/*
funkcja inicjalizuj¹ca menu (przyciski i tesksty w g³ównym menu)
@EXCEPTIONS:	---
*/
void INIT_MENU();

/*
funkcja rysuj¹ca wszystkie elementy menu g³ównego na ekran
@EXCEPTIONS:	---
*/
void MENU_show();

/*
funkcja obs³uguj¹ca eventy, czyli ca³e dzia³anie menu
@EXCEPTIONS:	---
*/
void MENU_event();

/*
funkcja zwalniaj¹ca pamiêæ zaalokowan¹ przez inicjalizacjê menu
@EXCEPTIONS:	---
*/
void CLEAN_MENU();

#endif // !VIEW_H