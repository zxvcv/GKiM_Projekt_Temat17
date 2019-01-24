#include "pch.h"
#include "functions.h"


void BMPtoPC_ImposedPallete()
{
	cout << "[INFO] konwersja BMP -> PC paleta narzucona" << endl;
	
	vector<Uint8> data;
	queue<kod> zakodowane;

	imposed_palette palette(IMPOSED_PALETTE_1);

	tp time1;
	duration time2;

	
	//nearest_neighbor
	cout << "[INFO] nearest_neighbor <start>" << endl;
	time1 = std::chrono::system_clock::now();

	nearest_neighbor(input_file, palette.returnPalette(), data);
		
	time2 = std::chrono::system_clock::now() - time1;
	cout << "[INFO] nearest_neighbor <end>, czas: "<< time2.count() << endl;

	//lz77_compression
	cout << "[INFO] lz77_compression <start>" << endl;
	time1 = std::chrono::system_clock::now();

	lz77_compression(data, zakodowane);

	time2 = std::chrono::system_clock::now() - time1;
	cout << "[INFO] lz77_compression <end>, czas: " << time2.count() << endl;
		
	//save_to_PC
	cout << "[INFO] save_to_PC <start>" << endl;
	time1 = std::chrono::system_clock::now();
	
	save_to_PC(input_file, "plik.pc", zakodowane);
	
	time2 = std::chrono::system_clock::now() - time1;
	cout << "[INFO] save_to_PC <end>, czas: " << time2.count() << endl;
}

void BMPtoPC_ImposedPalleteDithering()
{
	cout << "[INFO] konwersja BMP -> PC paleta narzucona + dithering" << endl;

	vector<Uint8> data;
	queue<kod> zakodowane;
	
	imposed_palette palette(IMPOSED_PALETTE_1);

	tp time1;
	duration time2;

	//nearest_neighbor
	cout << "[INFO] dithering <start>" << endl;
	time1 = std::chrono::system_clock::now();

	dithering(input_file, palette.returnPalette(), data);

	time2 = std::chrono::system_clock::now() - time1;
	cout << "[INFO] dithering <end>, czas: " << time2.count() << endl;

	//lz77_compression
	cout << "[INFO] lz77_compression <start>" << endl;
	time1 = std::chrono::system_clock::now();

	lz77_compression(data, zakodowane);

	time2 = std::chrono::system_clock::now() - time1;
	cout << "[INFO] lz77_compression <end>, czas: " << time2.count() << endl;
	
	//save_to_PC
	cout << "[INFO] save_to_PC <start>" << endl;
	time1 = std::chrono::system_clock::now();

	save_to_PC(input_file, "plik.pc", zakodowane);

	time2 = std::chrono::system_clock::now() - time1;
	cout << "[INFO] save_to_PC <end>, czas: " << time2.count() << endl;
}

void BMPtoPC_DedicatedPallete()
{
	cout << "[INFO] konwersja BMP -> PC paleta dedykowana" << endl;

	
}

void BMPtoPC_DedicatedPalleteDithering()
{
	cout << "[INFO] konwersja BMP -> PC paleta dedykowana + dithering" << endl;

	
}

void BMPtoPC_ShadersOfGrey()
{
	cout << "[INFO] konwersja BMP -> PC odcienie szaroœci" << endl;

	
}

void BMPtoPC_ShadersOfGreyDithering()
{
	cout << "[INFO] konwersja BMP -> PC odcienie szaroœci + dithering" << endl;
	
	
}

void PCtoBMP()
{
	cout << "[INFO] konwersja PC -> BMP" << endl;
	
	vector<kod> zakodowane;
	vector<Uint8> data;
	file_PC_header header;
	imposed_palette palette(IMPOSED_PALETTE_1);

	tp time1;
	duration time2;

	//get_from_PC
	cout << "[INFO] get_from_PC <start>" << endl;
	time1 = std::chrono::system_clock::now();
	
	get_from_PC(input_file_pc, header, zakodowane);
	
	time2 = std::chrono::system_clock::now() - time1;
	cout << "[INFO] get_from_PC <end>, czas: " << time2.count() << endl;
		
	//lz77_decompression
	cout << "[INFO] lz77_decompression <start>" << endl;
	time1 = std::chrono::system_clock::now();
	
	lz77_decompression(zakodowane, header, data);
	
	time2 = std::chrono::system_clock::now() - time1;
	cout << "[INFO] lz77_decompression <end>, czas: " << time2.count() << endl;

	//save_to_BMP
	cout << "[INFO] save_to_BMP <start>" << endl;
	time1 = std::chrono::system_clock::now();

	save_to_BMP(header, data, palette.returnPalette());

	time2 = std::chrono::system_clock::now() - time1;
	cout << "[INFO] save_to_BMP <end>, czas: " << time2.count() << endl;
}