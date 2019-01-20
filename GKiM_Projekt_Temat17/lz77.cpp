#include "pch.h"
#include "lz77.h"
#include <list>

/* destruktor w razie w nazwa_vektora.~vector<int>(); */

void lz77_conversion(SDL_Surface *surface, vector<Uint8> &output, queue<kod> &zakodowane)
{
	unsigned short width = surface->w;
	unsigned short height = surface->h;
	int dlugoscSlownika = 16384;
	int dlugoscWejscia = 512;

	kod znak;
	int i, j, k;

	Uint8 temp = output[0];

	output.insert(output.begin(), dlugoscSlownika, temp);

	int pSlownika = 0;
	int kSlownika = dlugoscSlownika - 1;

	int pWejscia = dlugoscSlownika;
	int kWejscia = dlugoscSlownika + dlugoscWejscia - 1;

	int indexWejscia = pWejscia;

	int tile;
	int tgdzie;
	int ile = 0;
	int gdzie;
	int wartosc;
	bool flaga;

	int rOutput = output.size();

	if (kWejscia >= output.size()) {
		kWejscia = output.size() - 1;
	}

	znak.ile = 0;
	znak.gdzie = 0;
	znak.wartosc = /*indexWejscia < output.size() ?*/ output[indexWejscia]/* : 14*/;
	zakodowane.push(znak);
	pSlownika += 1;
	kSlownika += 1;
	pWejscia += 1;
	kWejscia += 1;

	if (kWejscia >= output.size()) {
		kWejscia = output.size() - 1;
	}
	if (kSlownika >= output.size()) {
		kSlownika = output.size() - 1;
	}

	list<int> znaki[64];
	list<int> ostatnie;

	for (i = pSlownika; i <= kSlownika; ++i) {
		znaki[output[i]].push_back(i);
	}

	for (i = 0; i < dlugoscWejscia; ++i) {
		ostatnie.push_back(output[i]);
	}

	Uint8 test;

	for (i = indexWejscia; i < rOutput; ++i) {
		ile = 0;
		gdzie = 0;
		tile = 0;
		tgdzie = 0;

		test = output[pWejscia];

		for (list<int>::iterator it = znaki[test].begin(); it != znaki[test].end(); ++it) {
			if (output[*it] == output[pWejscia]) {
				tile = 0;
				tgdzie = pWejscia - *it;

				flaga = true;

				//przeszukuje dalsza czesc slownika
				for (k = *it; k < kWejscia && flaga == true && pWejscia + tile <= kWejscia; ++k) {

					if (output[k] == output[pWejscia + tile]) {
						++tile;
					}
					else {
						flaga = false;
					}
				}

				if (tile > ile) {
					ile = tile;
					gdzie = tgdzie;
				}
			}
		}


		int end = kSlownika + ile + 1;

		if (end >= output.size()) {
			end = output.size() - 1;
		}

		if (kSlownika + 1 < output.size()) {
			for (k = kSlownika + 1; k <= end; ++k) {
				znaki[output[k]].push_back(k);
				ostatnie.push_back(output[k]);
			}
		}

		if (kSlownika + 1 < output.size()) {
			for (k = kSlownika + 1; k <= end; ++k) {
				znaki[ostatnie.front()].pop_front();
				ostatnie.pop_front();
			}
		}

		znak.ile = ile;
		znak.gdzie = gdzie;
		indexWejscia = indexWejscia + ile + 1;
		znak.wartosc = indexWejscia < output.size() ? output[indexWejscia] : 14;
		zakodowane.push(znak);

		pSlownika += ile + 1;
		kSlownika += ile + 1;
		pWejscia += ile + 1;
		kWejscia += ile + 1;
		if (kWejscia >= output.size()) {
			kWejscia = output.size() - 1;
		}
		if (kSlownika >= output.size()) {
			kSlownika = output.size() - 1;
		}
		i += ile;
	}
}

void lz77_conversion2(SDL_Surface *surface, vector<Uint8> &output, queue<kod> &zakodowane)
{
	long long int lengSlownika = 2048;
	//unsigned int lengSlownika = 16384;

	kod out;
	long long int pos = 0; //wskaznik aktualnego polozenia
	long long int data_left = output.size(); //iloœc pozosta³ych danych do wysweitlenia

	while (data_left != 0)
	{
		long long int bSlownik = pos <= lengSlownika ? 0 : pos - lengSlownika; //poczatek slownika
		long long int eSlownik = pos; //koniec slownika

		long long int match = 0; //ilosc miejsc gdize nast¹pi³o dopasowanie przed aktualna pozycja
		long long int match_old = 0;
		long long int lMatch = 0; //dlugosc dopasowania
		long long int lMatch_old = 0;
		long long int lMatch2; //do wielokrotnego dopasowania wartosci gdy "wyjdziemy za bufor"

		for (long long int i = bSlownik; i < eSlownik; ++i) //przejscie po slowniku
		{
			if (data_left == 1)
				break;
			lMatch = lMatch2 = 0;

			if (output[i + lMatch] == output[pos + lMatch])
			{
				match = i - pos;

				while (output[i + lMatch2] == output[pos + lMatch])
				{
					++lMatch; ++lMatch2;
					if (i + lMatch2 >= eSlownik)
						lMatch2 = 0;

					if (lMatch == data_left - 1)
						break;
				}

				if (lMatch >= lMatch_old)
				{
					match_old = match;
					lMatch_old = lMatch;
				}
			}
		}

		out.ile = lMatch_old;
		out.gdzie = match_old;
		out.wartosc = output[pos + lMatch_old];
		zakodowane.push(out);

		data_left -= lMatch_old + 1;
		pos += lMatch_old + 1;
	}
}