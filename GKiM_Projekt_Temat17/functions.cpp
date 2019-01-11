#include "pch.h"
#include "functions.h"


void BMPtoPC_ImposedPallete()
{
	cout << "konwersja BMP -> PC paleta narzucona" << endl;
	
	vector<Uint8> data;
	queue<kod> zakodowane;

	imposed_palette palette(IMPOSED_PALETTE_1);


		cout << "nearest_neighbor <start>" << endl;
	nearest_neighbor(input_file, palette.returnPalette(), data);
		cout << "nearest_neighbor <end>" << endl;
		cout << "lz77_conversion <start>" << endl;
	lz77_conversion(input_file, data, zakodowane);
		cout << "lz77_conversion <end>" << endl;
		cout << "save_to_PC <start>" << endl;
	save_to_PC(input_file, "plik.pc", zakodowane);
		cout << "save_to_PC <end>" << endl;
}

void BMPtoPC_ImposedPalleteDithering()
{
	cout << "konwersja BMP -> PC paleta narzucona + dithering" << endl;

	vector<Uint8> data;
	queue<kod> zakodowane;

	imposed_palette palette(IMPOSED_PALETTE_1);

	
	dithering(input_file, palette.returnPalette(), data);
	lz77_conversion(input_file, data, zakodowane);
	save_to_PC(input_file, "plik.pc", zakodowane);

}

void BMPtoPC_DedicatedPallete()
{
	cout << "konwersja BMP -> PC paleta dedykowana" << endl;

	vector<Uint8> data;
	queue<kod> zakodowane;
	
	dedicated_palette palette;
	palette.search_palette(input_file);

	
	nearest_neighbor(input_file, palette.returnPalette(), data);
	lz77_conversion(input_file, data, zakodowane);
	save_to_PC(input_file, "plik.pc", zakodowane);
}

void BMPtoPC_DedicatedPalleteDithering()
{
	cout << "konwersja BMP -> PC paleta dedykowana + dithering" << endl;

	vector<Uint8> data;
	queue<kod> zakodowane;

	dedicated_palette palette;
	palette.search_palette(input_file);

	
	dithering(input_file, palette.returnPalette(), data);
	lz77_conversion(input_file, data, zakodowane);
	save_to_PC(input_file, "plik.pc", zakodowane);
}

void BMPtoPC_ShadersOfGrey()
{
	cout << "konwersja BMP -> PC odcienie szaroœci" << endl;

	vector<Uint8> data;
	queue<kod> zakodowane;

	imposed_palette palette(SHADERS_OF_GREY_PALETTE);

	nearest_neighbor(input_file, palette.returnPalette(), data);
	lz77_conversion(input_file, data, zakodowane);
	save_to_PC(input_file, "plik.pc", zakodowane);
}

void BMPtoPC_ShadersOfGreyDithering()
{
	cout << "konwersja BMP -> PC odcienie szaroœci + dithering" << endl;
	
	vector<Uint8> data;
	queue<kod> zakodowane;

	imposed_palette palette(SHADERS_OF_GREY_PALETTE);

	
	dithering(input_file, palette.returnPalette(), data);
	lz77_conversion(input_file, data, zakodowane);
	save_to_PC(input_file, "plik.pc", zakodowane);
}

void PCtoBMP()
{
	cout << "konwersja PC -> BMP" << endl;
}