#include "pch.h"
#include "lz77.h"

void lz77_conversion(SDL_Surface *surface, vector<Uint8> &output, vector<kod> &zakodowane)
{
	cout << "przed konwersja" << endl; //DEBUG
	unsigned short width = surface->w;
	unsigned short height = surface->h;


	vector<Uint8> slownik;
	vector<Uint8> wejscie;
	//vector<kod> zakodowane;
	kod znak;
	int i, j, k;
	int dlugoscSlownika = 32768;
	int dlugoscWejscia = 256;

	//wypelniam bufor wejsciowy pierwszymi znakami
	for (i = 0; i < 256 && i < output.size(); ++i)
		wejscie.push_back(output[i]);

	//wypelniam slownik pierwszym znakiem
	for (i = 0; i < dlugoscSlownika; ++i)
		slownik.push_back(wejscie[0]);
	
	znak.ile = 0;
	znak.gdzie = 0;
	znak.wartosc = wejscie[0];
	zakodowane.push_back(znak);

	int tile;
	int tgdzie;
	int ile = 0;
	int gdzie;
	int wartosc;
	int indexWejscia;
	bool flaga;
	for (int w = ile; w >= 0 && !wejscie.empty(); --w) 
	{
		//przekladam pierwszy element bufora wejscia do slownika
		slownik.push_back(wejscie[0]);

		//usuwam pierwszy element wejscia ktory przelozylem do slownik
		wejscie.erase(wejscie.begin());

		//dodaje do wejscia kolejny element
		if (i < output.size())
			wejscie.push_back(output[i]);
	}
	cout << "wejscie: " << wejscie.size() << endl;
	cout << "output: " << output.size() << endl;
	//przechodze po dalszych wartosciach
	for (i = 256; !wejscie.empty() /*i < output.size() - dlugoscWejscia*/; ++i) 
	{
		ile = 0;
		gdzie = 0;
		tile = 0;
		tgdzie = 0;

		//przechodze po wartoscia slownika
		for (j = 0; j < slownik.size() && !wejscie.empty(); ++j) 
		{
			indexWejscia = 0;
			if (slownik[j] == wejscie[indexWejscia]) 
			{
				tile = 0;
				tgdzie = slownik.size() - j;

				flaga = true;
				for (k = j; (k < slownik.size()) && (flaga == true) && indexWejscia < wejscie.size(); ++k) 
				{
					if (slownik[k] == wejscie[indexWejscia]) 
					{
						++tile;
						++indexWejscia;
					}
					else 
					{
						flaga = false;
					}
				}

				if (tile > ile) 
				{
					ile = tile;
					gdzie = tgdzie;
				}
			}
		}

		znak.ile = ile;
		znak.gdzie = gdzie;
		znak.wartosc = ile < wejscie.size() ? wejscie[ile] : 14;
		zakodowane.push_back(znak);
		for (int w = ile; w >= 0 && !wejscie.empty(); --w) {
			//przekladam pierwszy element bufora wejscia do slownika
			slownik.push_back(wejscie[0]);

			//usuwam pierwszy element wejscia ktory przelozylem do slownik
			wejscie.erase(wejscie.begin());

			//dodaje do wejscia kolejny element
			if (i < output.size()) {
				wejscie.push_back(output[i]);
			}
		}
	}
	cout << "po konwersji" << endl; //DEBUG
}