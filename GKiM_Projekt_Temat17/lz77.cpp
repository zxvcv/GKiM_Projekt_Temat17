#include "pch.h"
#include "lz77.h"
#include <list>


void lz77_compression(vector<Uint8> &input, queue<kod> &coded)
{
	long long int lengSlownika = 128;
	//long long int lengSlownika = 2048;
	//unsigned int lengSlownika = 16384;

	kod out;
	long long int pos = 0; //wskaznik aktualnego polozenia
	long long int data_left = input.size(); //iloœc pozosta³ych danych do wysweitlenia
	
	long long int bSlownik; //poczatek slownika
	long long int eSlownik; //koniec slownika

	long long int match; //ilosc miejsc gdize nast¹pi³o dopasowanie przed aktualna pozycja
	long long int match_old;
	long long int lMatch; //dlugosc dopasowania
	long long int lMatch_old;
	long long int lMatch2; //do wielokrotnego dopasowania wartosci gdy "wyjdziemy za bufor"

	while (data_left > 1)
	{
		bSlownik = (pos <= lengSlownika) ? 0 : pos - lengSlownika;
		eSlownik = pos;

		match = 0;
		match_old = 0;
		lMatch = 0;
		lMatch_old = 0;
		lMatch2 = 0;

		for (long long int i = bSlownik; i < eSlownik; ++i) //przejscie po slowniku
		{
			if (input[i] == input[pos])
			{
				match = i - pos;

				lMatch = lMatch2 = 0;
				while (input[i + lMatch2] == input[pos + lMatch])
				{
					++lMatch; ++lMatch2;
					if (i + lMatch2 >= eSlownik)
						lMatch2 = 0;

					if (pos + lMatch == input.size() - 1)
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
		if (pos + lMatch_old < input.size());
			out.wartosc = input[pos + lMatch_old];
			coded.push(out);

		data_left -= lMatch_old + 1;
		pos += lMatch_old + 1;
	}
}

void lz77_decompression(vector<kod> &zakodowane, PC_header &header, vector<Uint8> &data)
{
	data.clear();
	data.resize(header.width*header.height);
	
	int data_num = 0;
	int ptr1 = 0;
	int match_size = 0;
	for (auto i : zakodowane)
	{
		ptr1 = i.gdzie;
		for (int j = 0; j < i.ile; ++j)
		{
			data[data_num+j] = data[data_num + ptr1];
			++ptr1;
			if (ptr1 == 0)
				ptr1 = i.gdzie;
		}
		data_num += i.ile;
		data[data_num] = i.wartosc;
		++data_num;
	}
}