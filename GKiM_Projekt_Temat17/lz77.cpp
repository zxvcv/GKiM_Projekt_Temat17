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