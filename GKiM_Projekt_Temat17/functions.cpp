#include "pch.h"
#include "functions.h"

SDL_Color ImposedPalette[64] = {	{   0,   0,   0 }, {   0,   0,  85 }, {   0,   0, 171 }, {   0,   0, 255 },
									{   0,  85,   0 }, {   0,  85,  85 }, {   0,  85, 171 }, {   0,  85, 255 },
									{   0, 171,   0 }, {   0, 171,  85 }, {   0, 171, 171 }, {   0, 171, 255 },
									{   0, 255,   0 }, {   0, 255,  85 }, {   0, 255, 171 }, {   0, 255, 255 },
									{  85,   0,   0 }, {  85,   0,  85 }, {  85,   0, 171 }, {  85,   0, 255 },
									{  85,  85,   0 }, {  85,  85,  85 }, {  85,  85, 171 }, {  85,  85, 255 },
									{  85, 171,   0 }, {  85, 171,  85 }, {  85, 171, 171 }, {  85, 171, 255 },
									{  85, 255,   0 }, {  85, 255,  85 }, {  85, 255, 171 }, {  85, 255, 255 },
									{ 171,   0,   0 }, { 171,   0,  85 }, { 171,   0, 171 }, { 171,   0, 255 },
									{ 171,  85,   0 }, { 171,  85,  85 }, { 171,  85, 171 }, { 171,  85, 255 },
									{ 171, 171,   0 }, { 171, 171,  85 }, { 171, 171, 171 }, { 171, 171, 255 },
									{ 171, 255,   0 }, { 171, 255,  85 }, { 171, 255, 171 }, { 171, 255, 255 },
									{ 255,   0,   0 }, { 255,   0,  85 }, { 255,   0, 171 }, { 255,   0, 255 },
									{ 255,  85,   0 }, { 255,  85,  85 }, { 255,  85, 171 }, { 255,  85, 255 },
									{ 255, 171,   0 }, { 255, 171,  85 }, { 255, 171, 171 }, { 255, 171, 255 },
									{ 255, 255,   0 }, { 255, 255,  85 }, { 255, 255, 171 }, { 255, 255, 255 } };

SDL_Color ImposedPalette2[64] = {	{   0,   0,   0 }, {   0,   0,  65 }, {   0,   0, 128 }, {   0,   0, 192 },
									{   0,  65,   0 }, {   0,  65,  65 }, {   0,  65, 128 }, {   0,  65, 192 },
									{   0, 128,   0 }, {   0, 128,  65 }, {   0, 128, 128 }, {   0, 128, 192 },
									{   0, 192,   0 }, {   0, 192,  65 }, {   0, 192, 128 }, {   0, 192, 192 },
									{  65,   0,   0 }, {  65,   0,  65 }, {  65,   0, 128 }, {  65,   0, 192 },
									{  65,  65,   0 }, {  65,  65,  65 }, {  65,  65, 128 }, {  65,  65, 192 },
									{  65, 128,   0 }, {  65, 128,  65 }, {  65, 128, 128 }, {  65, 128, 192 },
									{  65, 192,   0 }, {  65, 192,  65 }, {  65, 192, 128 }, {  65, 192, 192 },
									{ 128,   0,   0 }, { 128,   0,  65 }, { 128,   0, 128 }, { 128,   0, 192 },
									{ 128,  65,   0 }, { 128,  65,  65 }, { 128,  65, 128 }, { 128,  65, 192 },
									{ 128, 128,   0 }, { 128, 128,  65 }, { 128, 128, 128 }, { 128, 128, 192 },
									{ 128, 192,   0 }, { 128, 192,  65 }, { 128, 192, 128 }, { 128, 192, 192 },
									{ 192,   0,   0 }, { 192,   0,  65 }, { 192,   0, 128 }, { 192,   0, 192 },
									{ 192,  65,   0 }, { 192,  65,  65 }, { 192,  65, 128 }, { 192,  65, 192 },
									{ 192, 128,   0 }, { 192, 128,  65 }, { 192, 128, 128 }, { 192, 128, 192 },
									{ 192, 192,   0 }, { 192, 192,  65 }, { 192, 192, 128 }, { 192, 192, 192 } };


void BMPtoPC_ImposedPallete()
{
	cout << "konwersja BMP -> PC paleta narzucona" << endl;

	//---------------------
	//zamiana z 24bitow na 6bitow z palet¹ narzucon¹ (ImposedPalette)
	//LZ77
	//zapis dp pliku pc
	//---------------------
}

void BMPtoPC_ImposedPalleteDithering()
{
	cout << "konwersja BMP -> PC paleta narzucona + dithering" << endl;

	Uint8 **output = dithering(input_file, ImposedPalette);
	Uint8 **output2 = dithering(input_file, ImposedPalette2);
	//dane z tabeli output aby otrzymac kolor pobieramy nastêpuj¹co: (0 : 255)
	//		paleta[output[i][j]].r	//dla r
	//		paleta[output[i][j]].g	//dla g
	//		paleta[output[i][j]].b	//dla b
	//je¿eli potrzenujemy bitów koloru z palety to uzywamy funkcji: (0 : 3)
	//		getR(output[i][j])		//dla r
	//		getG(output[i][j])		//dla g
	//		getB(output[i][j])		//dla b
	

	////przyk³adowe wypisanie danych z tablicy output
	//SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
	//for (int i = 0; i < input_file->w; ++i)
	//	for (int j = 0; j < input_file->h; ++j)
	//		setPixel(i, j, ImposedPalette[output[i][j]].r, ImposedPalette[output[i][j]].g, ImposedPalette[output[i][j]].b);
	//for (int i = 0; i < input_file->w; ++i)
	//	for (int j = 0; j < input_file->h; ++j)
	//		setPixel(i, j+ input_file->h, ImposedPalette2[output2[i][j]].r, ImposedPalette2[output2[i][j]].g, ImposedPalette2[output2[i][j]].b);
	//bool done = false;
	//while (!done)
	//{
	//	if (SDL_PollEvent(&event))
	//	{
	//		switch (event.type)
	//		{
	//		case SDL_QUIT: // exit if the window is closed
	//			done = true;
	//			break;
	//		case SDL_KEYDOWN:
	//			if (event.key.keysym.sym == SDLK_ESCAPE)
	//				done = true;
	//			if (event.key.keysym.sym == SDLK_b)
	//				czyscEkran(0, 0, 10);
	//			break;
	//		}
	//	}
	//	if (SDL_Flip(screen) == -1)
	//	{
	//		clean_up();
	//		exit(EXIT_FAILURE);
	//	}
	//}



	//---------------------
	//LZ77
	//zapis dp pliku pc
	//---------------------



	//for (int i = 0; i < input_file->w; ++i)
	//	delete[] output[i];
	//delete[] output;
	//for (int i = 0; i < input_file->w; ++i)
	//	delete[] output2[i];
	//delete[] output2;
}

void BMPtoPC_DedicatedPallete()
{
	cout << "konwersja BMP -> PC paleta dedykowana" << endl;

	//---------------------
	//zamiana z 24bitow na 6bitow z palet¹ dedykowan¹ (DedicatedPallete)
	//LZ77
	//zapis dp pliku pc
	//---------------------

}

void BMPtoPC_DedicatedPalleteDithering()
{
	cout << "konwersja BMP -> PC paleta dedykowana + dithering" << endl;

	//Uint8 **output = dithering(input_file, --- );


	//---------------------
	//LZ77
	//zapis dp pliku pc
	//---------------------


	//for (int i = 0; i < input_file->w; ++i)
	//	delete[] output[i];
	//delete[] output;
}

void BMPtoPC_ShadersOfGrey()
{
	cout << "konwersja BMP -> PC odcienie szaroœci" << endl;

	//---------------------
	//zamiana z 24bitow na 6bitow z palet¹ w skali szaroœci
	//LZ77
	//zapis dp pliku pc
	//---------------------
}

void BMPtoPC_ShadersOfGreyDithering()
{
	cout << "konwersja BMP -> PC odcienie szaroœci + dithering" << endl;
	
	//Uint8 **output = dithering(input_file, --- );


	//---------------------
	//LZ77
	//zapis dp pliku pc
	//---------------------


	//for (int i = 0; i < input_file->w; ++i)
	//	delete[] output[i];
	//delete[] output;
}

void PCtoBMP()
{
	cout << "konwersja PC -> BMP" << endl;
}