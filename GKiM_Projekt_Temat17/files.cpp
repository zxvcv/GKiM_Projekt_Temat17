#include "pch.h"
#include "files.h"

void save_to_PC(SDL_Surface *surface, string outFileName, queue<kod> &zakodowane, PALETTE_TYPE palette_type)
{
	PC_header header;
	header.p = 'P';
	header.c = 'C';
	header.width = surface->w;
	header.height = surface->h;
	header.offset = 13;
	header.dataLength = zakodowane.size();
	header.file_size = 15 + zakodowane.size() * 9;
	header.paletteNUM = static_cast<uint16_t>(palette_type);
	header.unused = 0;

	std::ofstream zapis;
	try {
		zapis.open(outFileName, ios::binary);
	}
	catch (std::exception &e) {
		clean_up();
		exit(EXIT_FAILURE);
	}

	//zapis nag³ówka
	zapis.write((char*)&(header), sizeof(header));
	
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

void get_from_PC(ifstream &ifile, PC_header &header, vector<kod> &zakodowane)
{
	char *buff = nullptr;
	int buff_size;
	
	int ptr = 0;
	
	buff_size = sizeof(header);
	buff = new char[buff_size];
	
	ifile.seekg(0, ifile.beg);
	ifile.read(buff, buff_size); //mozna zrobic bajt przerwy (wtedy usunac -1)
	ptr += buff_size;


	header = *((PC_header*)(buff));
	delete[] buff;

	if (header.p != 'P' || header.c != 'C')
	{
		clean_up();
		cout << "err: it's, not a PC file" << endl;
		exit(EXIT_FAILURE);
	}


	zakodowane.clear();
	zakodowane.resize(header.dataLength);

	buff_size = 5;
	buff = new char[buff_size];
	//czytanie danych
	kod val;

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