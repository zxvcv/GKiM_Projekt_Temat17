#ifndef FILES_H
#define FILES_H

#include <string>
#include <vector>
#include <queue>
#include <SDL.h>
#include "lz77.h"

using namespace std;

class PC_header {
public:
	uint8_t p;
	uint8_t c;

	uint16_t width;
	uint16_t height;
	uint16_t offset;

	uint32_t dataLength;
	uint32_t file_size;
	uint8_t paletteNUM;
	uint8_t unused;

	PC_header() {}
	void set_header(SDL_Surface *surface, int size_zakodowane, Palette &palette);
};


/*
funkcja zapisuj¹ca dane do pliku o rozszerzeniu PC
@param surface		wskaznik do obiektu z ktorego zostanie pobrany naglowek (wczesniejszy plik BMP)
@param outFileName	nazwa pliku wyjsciowego
@param zakodowane	tablica z zakodowanymi wartoœciami
@param palette_type	typ uzytej palety
@EXCEPTIONS:	---
*/
void save_to_PC(SDL_Surface *surface, string outFileName, queue<kod> &zakodowane, PC_header &header, Palette &palette);

/*
funkcja wykonujaca operacjê ditheringu
@param ifile		obiekt otwartego pliku PC
@param header		struktura nag³ówka pobranzego z pliku
@param zakodowane	tablica pobranych zakodowanych wartosci z pliku PC
@EXCEPTIONS:	---
*/
void get_from_PC(ifstream &ifile, PC_header &header, vector<kod> &zakodowane, Palette &palette);

/*
funkcja zapisujaca dane do pliku BMP
@param header		struktura nag³ówka zapisywanego do pliku
@param outFileName	nazwa pliku wyjsciowego
@param data			tablica danych do zapisaniaa do pliku
@param palette		tablica palety kolorów u¿ytych do zapisania wartoœci w pliku PC
@EXCEPTIONS:		---
*/
void save_to_BMP(PC_header &header, string outFileName, vector<Uint8> &data, std::vector<SDL_Color> &palette);

#endif // !FILES_H
