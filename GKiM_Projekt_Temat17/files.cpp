#include "pch.h"
#include "files.h"

void save_to_PC(SDL_Surface *surface, string outFileName, queue<kod> &zakodowane)
{
	unsigned short width = surface->w;
	unsigned short height = surface->h;

	std::ofstream zapis;
	zapis.open(outFileName, ios::binary);

	char p = 'P';
	char c = 'C';
	char znakPalety = '1';
	unsigned int dlugoscPoZakodowaniu = zakodowane.size();
	unsigned short offset = 13;
	unsigned short wielkoscPlikuWBajtach = 15 + zakodowane.size() * 9;

	zapis.write((char*)&(p), sizeof(p));
	zapis.write((char*)&(c), sizeof(c));
	zapis.write((char*)&(width), sizeof(width));
	zapis.write((char*)&(height), sizeof(height));
	zapis.write((char*)&(offset), sizeof(offset));
	zapis.write((char*)&(dlugoscPoZakodowaniu), sizeof(dlugoscPoZakodowaniu));
	zapis.write((char*)&(wielkoscPlikuWBajtach), sizeof(wielkoscPlikuWBajtach));
	zapis.write((char*)&(znakPalety), sizeof(znakPalety));
	while (!zakodowane.empty())
	{
		zapis.write((char*)&(zakodowane.front().ile), sizeof(zakodowane.front().ile));
		zapis.write((char*)&(zakodowane.front().gdzie), sizeof(zakodowane.front().gdzie));
		zapis.write((char*)&(zakodowane.front().wartosc), sizeof(zakodowane.front().wartosc));
		zakodowane.pop();
	}

	zapis.close();
}