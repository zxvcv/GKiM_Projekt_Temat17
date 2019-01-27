#include "pch.h"
#include "files.h"

void PC_header::set_header(SDL_Surface *surface, int size_zakodowane, Palette &palette)
{
	p = 'P';
	c = 'C';
	width = surface->w;
	height = surface->h;
	offset = 14;
	dataLength = size_zakodowane;
	if(palette.returnPaletteType() == DEDICATED_PALETTE)
		file_size = offset + sizeof(SDL_Color) * 64 + size_zakodowane * sizeof(kod);
	else
		file_size = offset + sizeof(SDL_Color) * 64 + size_zakodowane * sizeof(kod);
	paletteNUM = static_cast<uint8_t>(palette.returnPaletteType());
	unused = 0;
}


void save_to_PC(SDL_Surface *surface, string outFileName, queue<kod> &zakodowane, PC_header &header, Palette &palette)
{
	std::ofstream zapis;
	
	zapis.open(outFileName, ios::binary | ios::out);
	if (!zapis.is_open())
	{
		cout << "nie otwarty!!!";
		clean_up();
		exit(EXIT_FAILURE);
	}

	//zapis nag³ówka
	zapis.write((char*)&(header), sizeof(header));
	
	zapis.seekp(header.offset, zapis.beg);
	if (header.paletteNUM == DEDICATED_PALETTE)
	{
		//zapis palety dedykowanej
		for(int i=0; i<64;++i)
			zapis.write((char*)&palette.returnPalette()[i], sizeof(SDL_Color));
		zapis.seekp(header.offset + sizeof(SDL_Color) * 64, zapis.beg);
	}
		
	//zapis danych
	kod val;
	while (!zakodowane.empty())
	{
		val = zakodowane.front();
		zakodowane.pop();
		zapis.write((char*)&val, sizeof(val));
	}

	zapis.close();
}

void get_from_PC(ifstream &ifile, PC_header &header, vector<kod> &zakodowane, Palette &palette)
{
	char *buff = nullptr;
	int buff_size;
	
	int ptr = 0;
	
	buff_size = sizeof(header);
	buff = new char[buff_size];
	
	ifile.seekg(0, ifile.beg);
	ifile.read(buff, buff_size);
	ptr += buff_size;

	header = *((PC_header*)(buff));
	delete[] buff;

	if (header.p != 'P' || header.c != 'C')
	{
		clean_up();
		cout << "err: it's, not a PC file" << endl;
		exit(EXIT_FAILURE);
	}

	palette.changePalette(IMPOSED_PALETTE);
	ifile.seekg(header.offset, ifile.beg);
	if (header.paletteNUM == DEDICATED_PALETTE)
	{
		//odczyt palety dedykowanej
		for (int i = 0; i < 64; ++i)
			ifile.read((char*)&palette.returnPalette()[i], sizeof(SDL_Color));
		ifile.seekg(header.offset + sizeof(SDL_Color) * 64, ifile.beg);
	}
	zakodowane.clear();
	zakodowane.resize(header.dataLength);

	buff_size = 5;
	buff = new char[buff_size];
	//czytanie danych
	kod val;
	ptr = ifile.tellg();
	for(int i=0; i<header.dataLength; ++i)
	{
		ifile.seekg(ptr, ifile.beg);
		ifile.read((char*)&val, sizeof(val));
		zakodowane[i] = val;
		ptr += sizeof(val);
	}

	delete[] buff;
}

void save_to_BMP(PC_header &header, vector<Uint8> &data, std::vector<SDL_Color> &palette)
{
	SDL_Surface *surface;

	surface = SDL_CreateRGBSurface(0, header.width, header.height, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);

	if (surface == NULL)
	{
		cout << "err creating surface" << endl;
		clean_up();
		exit(EXIT_FAILURE);
	}
	
	int data_num = 0;

	SDL_LockSurface(surface);
	
	for (int x = 0; x < surface->w; ++x)
	{
		for (int y = 0; y < surface->h; ++y)
		{
			setPixel(surface, x, y, palette[data[data_num]].r, palette[data[data_num]].g, palette[data[data_num]].b);
			++data_num;
		}
	}
	SDL_UnlockSurface(surface);

	zapiszBMP(&surface, "mojBMP.bmp");
}