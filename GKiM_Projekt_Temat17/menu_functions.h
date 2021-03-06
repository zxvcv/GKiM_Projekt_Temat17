#ifndef MENU_FUNCTIONS_H
#define MENU_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <SDL_ttf.h>
#include <SDL.h>
#include "l_exceptions.h"
#include "view.h"
#include "functions.h"
#include "SDL_functions.h"

extern SDL_Surface *screen;
extern SDL_Event event;
extern std::vector<SDL_Rect> texture_type;
extern std::string filename;
extern SDL_Surface *input_file;
extern bool inactive;
extern bool bmp;
extern std::ifstream input_file_pc;

/*
funkcja przycisku 1 menu, pobierajaca i zapisująca nazwę pliku wejściowego
@EXCEPTIONS:	---
*/
void funkcja1();

/*
funkcja przycisku 2 menu, rysująca załadowany obrazek
@EXCEPTIONS:	---
*/
void funkcja2();

/*
funkcja przycisku 3 menu, realizująca kolejne menu wyboru typu konwersji pliku BMP na PC
@EXCEPTIONS:	---
*/
void funkcja3();

/*
funkcja przycisku 4 menu, realizująca konwersje z PC na BMP
@EXCEPTIONS:	---
*/
void funkcja4();

/*
funkcja przycisku 5 menu, wyswietlajaca informacje o programie
@EXCEPTIONS:	---
*/
void funkcja5();

#endif // !MENU_FUNCTIONS_H