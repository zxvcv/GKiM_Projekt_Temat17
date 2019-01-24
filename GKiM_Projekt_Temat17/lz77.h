#ifndef LZ77_H
#define LZ77_H

using namespace std;

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <SDL.h>
#include "SDL_functions.h"
#include "palette.h"
#include "files.h"


extern struct file_PC_header;

/*
funkcja kompresujaca dane wedlug algorytmu lz77
@param input	tablica danych wejsciowych do zakodowania
@param coded	lista która zawiera kolejno wszystkie zakodowane dane
@EXCEPTIONS:	---
*/
void lz77_compression(vector<Uint8> &input, queue<kod> &coded);

/*
funkcja wykonujaca operacjê ditheringu
@param zakodowane	tablica zawierajaca dane zakodowane do odkodowania
@param header		nag³owek pliku PC który zosta³ odczytany z pliku
@param data			tablica danych wyjsciowych (odkodowanych)
@EXCEPTIONS:	---
*/
void lz77_decompression(vector<kod> &zakodowane, file_PC_header &header, vector<Uint8> &data);


#endif // !LZ77_H

