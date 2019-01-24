#ifndef FILES_H
#define FILES_H

#include <string>
#include <vector>
#include <queue>
#include <SDL.h>
#include "lz77.h"

using namespace std;

struct file_PC_header {
	uint8_t p;
	uint8_t c;

	uint16_t width;
	uint16_t height;
	uint16_t offset;

	uint16_t dataLength;
	uint16_t file_size;
	uint8_t paletteNUM;
	uint8_t unused;
};


/*
funkcja zapisuj¹ca dane do pliku o rozszerzeniu PC
@param surface		wskaznik do obiektu z ktorego zostanie pobrany naglowek (wczesniejszy plik BMP)
@param outFileName	nazwa pliku wyjsciowego
@param zakodowane	tablica z zakodowanymi wartoœciami
@EXCEPTIONS:	---
*/
void save_to_PC(SDL_Surface *surface, string outFileName, queue<kod> &zakodowane);

/*
funkcja wykonujaca operacjê ditheringu
@param ifile		obiekt otwartego pliku PC
@param header		struktura nag³ówka pobranzego z pliku
@param zakodowane	tablica pobranych zakodowanych wartosci z pliku PC
@EXCEPTIONS:	---
*/
void get_from_PC(ifstream &ifile, file_PC_header &header, vector<kod> &zakodowane);

/*
funkcja zapisujaca dane do pliku BMP
@param header	struktura nag³ówka zapisywanego do pliku
@param data		tablica danych do zapisaniaa do pliku
@param palette	tablica palety kolorów u¿ytych do zapisania wartoœci w pliku PC
@EXCEPTIONS:	---
*/
void save_to_BMP(file_PC_header &header, vector<Uint8> &data, std::vector<SDL_Color> &palette);

#endif // !FILES_H
