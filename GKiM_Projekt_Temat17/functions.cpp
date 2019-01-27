#include "pch.h"
#include "functions.h"


void BMPtoPC_ImposedPallete()
{
	cout << "[INFO] konwersja BMP -> PC paleta narzucona" << endl;
	
	vector<Uint8> data;
	queue<kod> zakodowane;
	Palette palette(IMPOSED_PALETTE);
	PC_header header;

	tp time1;
	duration time2;

	
	//nearest_neighbor
	cout << "[INFO] nearest_neighbor <start>" << endl;
	time1 = chrono::system_clock::now();

	nearest_neighbor(input_file, palette.returnPalette(), data);
		
	time2 = chrono::system_clock::now() - time1;
	cout << "[INFO] nearest_neighbor <end>, czas: "<< time2.count() << endl;

	//lz77_compression
	cout << "[INFO] lz77_compression <start>" << endl;
	time1 = chrono::system_clock::now();

	lz77_compression(data, zakodowane);

	time2 = chrono::system_clock::now() - time1;
	cout << "[INFO] lz77_compression <end>, czas: " << time2.count() << endl;
	
	//ustawianie nag³ówka
	header.set_header(input_file, zakodowane.size(), palette);

	//save_to_PC
	cout << "[INFO] save_to_PC <start>" << endl;
	time1 = chrono::system_clock::now();
	
	save_to_PC(input_file, "plik.pc", zakodowane, header, palette);
	
	time2 = chrono::system_clock::now() - time1;
	cout << "[INFO] save_to_PC <end>, czas: " << time2.count() << endl;



	//wyœwietlenie informacji o pliku wynikowym
	//cout<< "[OUTPUT] "<<"plik.pc"<<
}

void BMPtoPC_ImposedPalleteDithering()
{
	cout << "[INFO] konwersja BMP -> PC paleta narzucona + dithering" << endl;

	vector<Uint8> data;
	queue<kod> zakodowane;
	Palette palette(IMPOSED_PALETTE);
	PC_header header;

	tp time1;
	duration time2;

	//nearest_neighbor
	cout << "[INFO] dithering <start>" << endl;
	time1 = chrono::system_clock::now();

	dithering(input_file, palette.returnPalette(), data);

	time2 = chrono::system_clock::now() - time1;
	cout << "[INFO] dithering <end>, czas: " << time2.count() << endl;

	//lz77_compression
	cout << "[INFO] lz77_compression <start>" << endl;
	time1 = chrono::system_clock::now();

	lz77_compression(data, zakodowane);

	time2 = chrono::system_clock::now() - time1;
	cout << "[INFO] lz77_compression <end>, czas: " << time2.count() << endl;
	
	//ustawianie nag³ówka
	header.set_header(input_file, zakodowane.size(), palette);

	//save_to_PC
	cout << "[INFO] save_to_PC <start>" << endl;
	time1 = chrono::system_clock::now();

	save_to_PC(input_file, "plik.pc", zakodowane, header, palette);

	time2 = chrono::system_clock::now() - time1;
	cout << "[INFO] save_to_PC <end>, czas: " << time2.count() << endl;
}

void BMPtoPC_DedicatedPallete()
{
	cout << "[INFO] konwersja BMP -> PC paleta dedykowana" << endl;

	vector<Uint8> data;
	queue<kod> zakodowane;
	PC_header header;

	tp time1;
	duration time2;

	//obliczanie palety dedykowanej
	cout << "[INFO] dedicated_palette <start>" << endl;
	time1 = chrono::system_clock::now();

	Palette palette(DEDICATED_PALETTE);

	time2 = chrono::system_clock::now() - time1;
	cout << "[INFO] dedicated_palette <end>, czas: " << time2.count() << endl;

	//nearest_neighbor
	cout << "[INFO] nearest_neighbor <start>" << endl;
	time1 = chrono::system_clock::now();

	nearest_neighbor(input_file, palette.returnPalette(), data);

	time2 = chrono::system_clock::now() - time1;
	cout << "[INFO] nearest_neighbor <end>, czas: " << time2.count() << endl;

	//lz77_compression
	cout << "[INFO] lz77_compression <start>" << endl;
	time1 = chrono::system_clock::now();

	lz77_compression(data, zakodowane);

	time2 = chrono::system_clock::now() - time1;
	cout << "[INFO] lz77_compression <end>, czas: " << time2.count() << endl;

	//ustawianie nag³ówka
	header.set_header(input_file, zakodowane.size(), palette);

	//save_to_PC
	cout << "[INFO] save_to_PC <start>" << endl;
	time1 = chrono::system_clock::now();

	save_to_PC(input_file, "plik.pc", zakodowane, header, palette);

	time2 = chrono::system_clock::now() - time1;
	cout << "[INFO] save_to_PC <end>, czas: " << time2.count() << endl;
}

void BMPtoPC_DedicatedPalleteDithering()
{
	cout << "[INFO] konwersja BMP -> PC paleta dedykowana + dithering" << endl;

	
	vector<Uint8> data;
	queue<kod> zakodowane;
	PC_header header;

	tp time1;
	duration time2;

	//obliczanie palety dedykowanej
	cout << "[INFO] dedicated_palette <start>" << endl;
	time1 = chrono::system_clock::now();

	Palette palette(DEDICATED_PALETTE);

	time2 = chrono::system_clock::now() - time1;
	cout << "[INFO] dedicated_palette <end>, czas: " << time2.count() << endl;

	//nearest_neighbor
	cout << "[INFO] dithering <start>" << endl;
	time1 = chrono::system_clock::now();

	dithering(input_file, palette.returnPalette(), data);

	time2 = chrono::system_clock::now() - time1;
	cout << "[INFO] dithering <end>, czas: " << time2.count() << endl;

	//lz77_compression
	cout << "[INFO] lz77_compression <start>" << endl;
	time1 = chrono::system_clock::now();

	lz77_compression(data, zakodowane);

	time2 = chrono::system_clock::now() - time1;
	cout << "[INFO] lz77_compression <end>, czas: " << time2.count() << endl;

	//ustawianie nag³ówka
	header.set_header(input_file, zakodowane.size(), palette);

	//save_to_PC
	cout << "[INFO] save_to_PC <start>" << endl;
	time1 = chrono::system_clock::now();

	save_to_PC(input_file, "plik.pc", zakodowane, header, palette);

	time2 = chrono::system_clock::now() - time1;
	cout << "[INFO] save_to_PC <end>, czas: " << time2.count() << endl;
}

void BMPtoPC_ShadersOfGrey()
{
	cout << "[INFO] konwersja BMP -> PC odcienie szaroœci" << endl;

	vector<Uint8> data;
	queue<kod> zakodowane;
	PC_header header;
	Palette palette(SHADERS_OF_GREY_PALETTE);

	tp time1;
	duration time2;


	//nearest_neighbor
	cout << "[INFO] nearest_neighbor <start>" << endl;
	time1 = chrono::system_clock::now();

	nearest_neighbor(input_file, palette.returnPalette(), data);

	time2 = chrono::system_clock::now() - time1;
	cout << "[INFO] nearest_neighbor <end>, czas: " << time2.count() << endl;

	//lz77_compression
	cout << "[INFO] lz77_compression <start>" << endl;
	time1 = chrono::system_clock::now();

	lz77_compression(data, zakodowane);

	time2 = chrono::system_clock::now() - time1;
	cout << "[INFO] lz77_compression <end>, czas: " << time2.count() << endl;

	//ustawianie nag³ówka
	header.set_header(input_file, zakodowane.size(), palette);

	//save_to_PC
	cout << "[INFO] save_to_PC <start>" << endl;
	time1 = chrono::system_clock::now();

	save_to_PC(input_file, "plik.pc", zakodowane, header, palette);

	time2 = chrono::system_clock::now() - time1;
	cout << "[INFO] save_to_PC <end>, czas: " << time2.count() << endl;
}

void BMPtoPC_ShadersOfGreyDithering()
{
	cout << "[INFO] konwersja BMP -> PC odcienie szaroœci + dithering" << endl;

	vector<Uint8> data;
	queue<kod> zakodowane;
	PC_header header;
	Palette palette(SHADERS_OF_GREY_PALETTE);

	tp time1;
	duration time2;

	//nearest_neighbor
	cout << "[INFO] dithering <start>" << endl;
	time1 = chrono::system_clock::now();

	dithering(input_file, palette.returnPalette(), data);

	time2 = chrono::system_clock::now() - time1;
	cout << "[INFO] dithering <end>, czas: " << time2.count() << endl;

	//lz77_compression
	cout << "[INFO] lz77_compression <start>" << endl;
	time1 = chrono::system_clock::now();

	lz77_compression(data, zakodowane);

	time2 = chrono::system_clock::now() - time1;
	cout << "[INFO] lz77_compression <end>, czas: " << time2.count() << endl;

	//ustawianie nag³ówka
	header.set_header(input_file, zakodowane.size(), palette);

	//save_to_PC
	cout << "[INFO] save_to_PC <start>" << endl;
	time1 = chrono::system_clock::now();

	save_to_PC(input_file, "plik.pc", zakodowane, header, palette);

	time2 = chrono::system_clock::now() - time1;
	cout << "[INFO] save_to_PC <end>, czas: " << time2.count() << endl;
}

void PCtoBMP()
{
	cout << "[INFO] konwersja PC -> BMP" << endl;
	
	vector<kod> zakodowane;
	vector<Uint8> data;
	PC_header header;
	Palette palette;

	tp time1;
	duration time2;

	//get_from_PC
	cout << "[INFO] get_from_PC <start>" << endl;
	time1 = chrono::system_clock::now();
	
	get_from_PC(input_file_pc, header, zakodowane, palette);
	
	time2 = chrono::system_clock::now() - time1;
	cout << "[INFO] get_from_PC <end>, czas: " << time2.count() << endl;


	switch (header.paletteNUM)
	{
	case IMPOSED_PALETTE:
		palette.changePalette(IMPOSED_PALETTE);
		break;
	case DEDICATED_PALETTE:
		break;
	case SHADERS_OF_GREY_PALETTE:
		palette.changePalette(SHADERS_OF_GREY_PALETTE);
		break;
	default:
		break;
	}

	//lz77_decompression
	cout << "[INFO] lz77_decompression <start>" << endl;
	time1 = chrono::system_clock::now();
	
	lz77_decompression(zakodowane, header, data);
	
	time2 = chrono::system_clock::now() - time1;
	cout << "[INFO] lz77_decompression <end>, czas: " << time2.count() << endl;

	//save_to_BMP
	cout << "[INFO] save_to_BMP <start>" << endl;
	time1 = chrono::system_clock::now();

	save_to_BMP(header, data, palette.returnPalette());

	time2 = chrono::system_clock::now() - time1;
	cout << "[INFO] save_to_BMP <end>, czas: " << time2.count() << endl;
}