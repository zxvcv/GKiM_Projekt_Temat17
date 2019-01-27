#include "pch.h"
#include "menu_functions.h"

void funkcja1()
{
	std::string name_save = filename;
	//inicjalizacja
	SDL_Color color_b, color_r, color_g;
	std::ifstream file;

	char ch;
	color_b.r = 0; color_b.g = 0; color_b.b = 0; //czarny
	color_r.r = 255; color_r.g = 0; color_r.b = 0; //czerwony
	color_g.r = 0; color_g.g = 255; color_g.b = 0; //zielony
	Text top_text(20, 20, "WPROWADZ NAZWE PLIKU TEKSTOWEGO,", color_b, 1);
	Text top_text2(20, 60, " I ZATWIERDZ KLAWISZEM ENTER", color_b, 1);
	Text filename_text(25, 100, filename.c_str(), color_b, 0);


	bool done = false;
	while (!done)
	{
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT: // exit if the window is closed
				clean_up();
				exit(EXIT_FAILURE);
				break;

			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_MINUS && !(event.key.keysym.mod == KMOD_LSHIFT || event.key.keysym.mod == KMOD_RSHIFT))
					filename.push_back('-');
				if (event.key.keysym.sym == SDLK_MINUS && (event.key.keysym.mod == KMOD_LSHIFT || event.key.keysym.mod == KMOD_RSHIFT))
					filename.push_back('_');
				if (event.key.keysym.sym == SDLK_SEMICOLON && !(event.key.keysym.mod == KMOD_LSHIFT || event.key.keysym.mod == KMOD_RSHIFT))
					filename.push_back(';');
				if (event.key.keysym.sym == SDLK_SEMICOLON && (event.key.keysym.mod == KMOD_LSHIFT || event.key.keysym.mod == KMOD_RSHIFT))
					filename.push_back(':');
				if (event.key.keysym.sym == SDLK_SPACE)
					filename.push_back(' ');
				if (event.key.keysym.sym == SDLK_PERIOD)
					filename.push_back('.');
				if (event.key.keysym.sym == SDLK_SLASH)
					filename.push_back('/');
				if (event.key.keysym.sym == SDLK_BACKSLASH)
					filename.push_back('\\');
				if (event.key.keysym.sym >= 48 && event.key.keysym.sym <= 57) //0-9
					filename.push_back(event.key.keysym.sym);
				if (event.key.keysym.sym >= 97 && event.key.keysym.sym <= 122) //a-z
				{
					if (event.key.keysym.mod == KMOD_LSHIFT)
						ch = event.key.keysym.sym - 32;
					else
						ch = event.key.keysym.sym;
					filename.push_back(ch);
				}
				//klawisze znaczace (odpowiadaj¹ce za dzia³anie)
				if (event.key.keysym.sym == SDLK_RETURN) //enter
					done = true;
				if (event.key.keysym.sym == SDLK_BACKSPACE)
					if (!filename.empty())
						filename.pop_back();
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					filename = name_save;
					done = true;
				}
				break;
			}

			//testowanie czy plik o podanej nazwie jest w folderze
			file.open(filename.c_str(), ios::in);
			if (!file.is_open())
			{
				inactive = true;
			}
			else
			{
				inactive = false;
				file.close();
			}

			//sprawdzanie rozszerzenia
			if (filename.find(".bmp") != filename.npos)
				bmp = true;
			else if (filename.find(".pc") != filename.npos)
				bmp = false;


			if (inactive == false)
				filename_text.change_text(25, 100, filename, color_g, 0);
			else
				filename_text.change_text(25, 100, filename, color_r, 0);
		}

		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 255, 255, 255));

		//wyœwietlanie elementów z Menu3
		{
			top_text.show(screen);
			top_text2.show(screen);
			filename_text.show(screen);
		}

		if (SDL_Flip(screen) == -1)
		{
			clean_up();
			exit(EXIT_FAILURE);
		}
	}

	//otwieranie pliow
	if (inactive == false && bmp == true)
	{
		try {
			ladujBMP(&input_file, filename.c_str(), 0, 0);
		}
		catch (std::exception &e) {
			clean_up();
			exit(EXIT_FAILURE);
		}
		if (input_file_pc.is_open())
			input_file_pc.close();
	}
	else if (inactive == false && bmp == false)
	{
		input_file_pc.open(filename.c_str(), ios::in | ios::binary);
		if (!input_file_pc.is_open())
		{
			clean_up();
			exit(EXIT_FAILURE);
		}
		if (input_file != nullptr)
			SDL_FreeSurface(input_file);
	}
	
	event.quit.type = 0;
}

void funkcja2()
{
	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 50, 50, 50));
	
	try {
		wyswietlBMP(input_file, 0, 0);
	}
	catch (std::exception &e) {
		clean_up();
		exit(EXIT_FAILURE);
	}

	if (SDL_Flip(screen) == -1)
	{
		clean_up();
		exit(EXIT_FAILURE);
	}

	bool done = false;
	while (!done)
	{
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT: // exit if the window is closed
				clean_up();
				exit(EXIT_FAILURE);
				break;

			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					done = true;
				break;
			}
		}
	}
	event.quit.type = 0;
}

void funkcja3()
{
	Menu Menu2;

	//inicjalizacja Menu2
	{
		SDL_Rect dim;
		SDL_Color color_y, color_r, color_b;

		dim.x = 10; dim.y = 100; dim.w = 300; dim.h = 50;
		Menu2.buttons.push_back(Button(dim, &texture_type[NONE]));
		dim.x = 10; dim.y = 160; dim.w = 300; dim.h = 50;
		Menu2.buttons.push_back(Button(dim, &texture_type[NONE]));
		dim.x = 10; dim.y = 220; dim.w = 300; dim.h = 50;
		Menu2.buttons.push_back(Button(dim, &texture_type[NONE]));
		dim.x = 10; dim.y = 280; dim.w = 300; dim.h = 50;
		Menu2.buttons.push_back(Button(dim, &texture_type[NONE]));
		dim.x = 10; dim.y = 340; dim.w = 300; dim.h = 50;
		Menu2.buttons.push_back(Button(dim, &texture_type[NONE]));
		dim.x = 10; dim.y = 400; dim.w = 300; dim.h = 50;
		Menu2.buttons.push_back(Button(dim, &texture_type[NONE]));
		dim.x = 10; dim.y = 460; dim.w = 300; dim.h = 50;
		Menu2.buttons.push_back(Button(dim, &texture_type[NONE]));

		color_y.r = 255; color_y.g = 255; color_y.b = 0;
		color_r.r = 255; color_r.g = 0; color_r.b = 0;
		color_b.r = 0; color_b.g = 0; color_b.b = 0;

		Menu2.texts.push_back(Text(25, 115, "paleta narzucona", color_y, 0));
		Menu2.texts.push_back(Text(25, 175, "paleta narzucona + dithering", color_y, 0));
		Menu2.texts.push_back(Text(25, 235, "paleta dedykowana", color_y, 0));
		Menu2.texts.push_back(Text(25, 295, "paleta dedykowana + dithering", color_y, 0));
		Menu2.texts.push_back(Text(25, 355, "odcienie szarosci", color_y, 0));
		Menu2.texts.push_back(Text(25, 415, "odcienie szarosci + dithering", color_y, 0));
		Menu2.texts.push_back(Text(25, 475, "powrot", color_r, 0));
		Menu2.texts.push_back(Text(100, 20, "KONWERSJA   BMP -> PC", color_b, 1));
	}

	bool done = false;
	while (!done)
	{
		if (SDL_PollEvent(&event))
		{
			//obs³uga eventow z menu2
			{
				Ret ret_val;

				//przyciski:
				for (int i = 0; i < Menu2.buttons.size(); ++i)
				{
					ret_val = Menu2.buttons[i].handle_events(event);
					if (ret_val.released == true)
					{
						switch (i)
						{
						case 0: // konwersja BMP -> PC paleta narzucona
							BMPtoPC_ImposedPallete();
							break;
						case 1: // konwersja BMP -> PC paleta narzucona + dithering
							BMPtoPC_ImposedPalleteDithering();
							break;
						case 2: // konwersja BMP -> PC paleta dedykowana
							BMPtoPC_DedicatedPallete();
							break;
						case 3: // konwersja BMP -> PC paleta dedykowana + dithering
							BMPtoPC_DedicatedPalleteDithering();
							break;
						case 4: // konwersja BMP -> PC odcienie szaroœci
							BMPtoPC_ShadersOfGrey();
							break;
						case 5: // konwersja BMP -> PC odcienie szaroœci + dithering
							BMPtoPC_ShadersOfGreyDithering();
							break;
						case 6: //powrót
							done = true;
							break;
						default:
							break;
						}
					}
				}
			}

			switch (event.type)
			{
			case SDL_QUIT: // exit if the window is closed
				clean_up();
				exit(EXIT_FAILURE);
				break;

			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					done = true;
				break;
			}
		}

		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 255, 255, 255));

		//wyœwietlanie elementów z Menu2
		{
			for (auto &i : Menu2.buttons)
				i.show(screen);
			for (auto &i : Menu2.texts)
				i.show(screen);
		}

		if (SDL_Flip(screen) == -1)
		{
			clean_up();
			exit(EXIT_FAILURE);
		}
	}
	event.quit.type = 0;
}

void funkcja4()
{
	// konwersja PC->BMP
	PCtoBMP();
}

void funkcja5()
{
	Menu Menu3;
	//inicjalizacja Menu2
	{
		SDL_Color color_g, color_s;

		color_g.r = 0; color_g.g = 200; color_g.b = 0; //zielony
		color_s.r = 200; color_s.g = 200; color_s.b = 200; //szary

		Menu3.texts.push_back(Text(100, 20, "INFORMACJE", color_g, 1));
		Menu3.texts.push_back(Text(25, 100, "   Program wykonuje operacje konwersji pliku BMP na plik PC. W tym celu wykorzystywane sa", color_s, 0));
		Menu3.texts.push_back(Text(25, 125, "algorytmy: wyszukiwania najblizszego sasiada, ditheringu, kompresji/dekompresji lz77,", color_s, 0));
		Menu3.texts.push_back(Text(25, 150, "wyszukiwania palety dedykowanej (median Cut), zapisu i odczytu do pliku BMP i PC.", color_s, 0));
		Menu3.texts.push_back(Text(25, 175, "", color_s, 0));
		Menu3.texts.push_back(Text(25, 200, "   Uzyte algorytmy zaleza od wybranego sposobu konwersji BMP -> PC, lub zapisanyc", color_s, 0));
		Menu3.texts.push_back(Text(25, 225, "w pliku PC danych w jaki sposób (jakimi algorytmami) zostal on zapisany.", color_s, 0));
		Menu3.texts.push_back(Text(25, 250, "", color_s, 0));
		Menu3.texts.push_back(Text(25, 275, "Plik wejsciowy: nazwa wybierana dowolnie w opcji \"wprowadz nazwe obrazka\"", color_s, 0));
		Menu3.texts.push_back(Text(25, 300, "Plik wyjsciowy: nazwa narzucona: ~/plik.pc,  ", color_s, 0));
		Menu3.texts.push_back(Text(25, 325, "", color_s, 0));
		Menu3.texts.push_back(Text(25, 350, "Przy wyborze nazwy pliku mo¿na pos³ugiwac sie literami (bez polskich znaków), cyframi,", color_s, 0));
		Menu3.texts.push_back(Text(25, 375, "   i podanymi znakami:    -    _    ;    :    (spacja)    .    /    \\", color_s, 0));
	

		Menu3.texts.push_back(Text(600, 475, "Projekt wykonali:", color_s, 0));
		Menu3.texts.push_back(Text(600, 500, "  Karol Patko", color_s, 0));
		Menu3.texts.push_back(Text(600, 525, "  Pawel Midura", color_s, 0));
		Menu3.texts.push_back(Text(600, 550, "  Wojciech Maludzinski", color_s, 0));
		Menu3.texts.push_back(Text(600, 575, "  Pawel Piskorz", color_s, 0));
	}

	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

	//wyœwietlanie elementów z Menu3
	{
		for (auto &i : Menu3.buttons)
			i.show(screen);
		for (auto &i : Menu3.texts)
			i.show(screen);
	}

	if (SDL_Flip(screen) == -1)
	{
		clean_up();
		exit(EXIT_FAILURE);
	}

	bool done = false;
	while (!done)
	{
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT: // exit if the window is closed
				clean_up();
				exit(EXIT_FAILURE);
				break;

			case SDL_KEYDOWN:
				done = true;
				break;
			}
		}
	}
	event.quit.type = 0;
}