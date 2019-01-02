#include "pch.h"
#include "menu_functions.h"

void funkcja1()
{
	std::string name_save = filename;
	//inicjalizacja
	SDL_Color color_b, color_r, color_g;


	char ch;
	color_b.r = 0; color_b.g = 0; color_b.b = 0; //czarny
	color_r.r = 255; color_r.g = 0; color_r.b = 0; //czerwony
	color_g.r = 0; color_g.g = 255; color_g.b = 0; //zielony
	Text top_text(100, 20, "WPROWADZ NAZWE PLIKU TEKSTOWEGO,", color_b, 1);
	Text top_text2(100, 60, " I ZATWIERDZ KLAWISZEM ENTER", color_b, 1);
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
				if (event.key.keysym.sym == SDLK_MINUS && event.key.keysym.mod == KMOD_LSHIFT)
					filename.push_back('_');
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
						ch = event.key.keysym.sym-32;
					else
						ch = event.key.keysym.sym;
					filename.push_back(ch);
				}
				//klawisze znaczace (odpowiadaj�ce za dzia�anie)
				if (event.key.keysym.sym == SDLK_RETURN) //enter
					done = true;
				if (event.key.keysym.sym == SDLK_BACKSPACE)
					if(!filename.empty())
						filename.pop_back();
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					filename = name_save;
					done = true;
				}
				break;
			}

			inactive = false;
			try {
				ladujBMP(&input_file, filename.c_str(), 0, 0);
			}
			catch (std::exception &e) {
				inactive = true;
			}

			if (inactive == false)
				filename_text.change_text(25, 100, filename, color_g, 0);
			else
				filename_text.change_text(25, 100, filename, color_r, 0);
		}

		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 255, 255, 255));

		//wy�wietlanie element�w z Menu3
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
	event.quit.type = 0;
}

void funkcja2()
{
	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 50, 50, 50));
	
	cout << input_file << endl;
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
		SDL_Color color;

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

		color.r = 255; color.g = 255; color.b = 0;
		Menu2.texts.push_back(Text(25, 115, "paleta narzucona", color, 0));
		color.r = 255; color.g = 255; color.b = 0;
		Menu2.texts.push_back(Text(25, 175, "paleta narzucona + dithering", color, 0));
		color.r = 255; color.g = 255; color.b = 0;
		Menu2.texts.push_back(Text(25, 235, "paleta dedykowana", color, 0));
		color.r = 255; color.g = 255; color.b = 0;
		Menu2.texts.push_back(Text(25, 295, "paleta dedykowana + dithering", color, 0));
		color.r = 255; color.g = 255; color.b = 0;
		Menu2.texts.push_back(Text(25, 355, "odcienie szarosci", color, 0));
		color.r = 255; color.g = 255; color.b = 0;
		Menu2.texts.push_back(Text(25, 415, "odcienie szarosci + dithering", color, 0));
		color.r = 255; color.g = 0; color.b = 0;
		Menu2.texts.push_back(Text(25, 475, "powrot", color, 0));
		color.r = 0; color.g = 0; color.b = 0;
		Menu2.texts.push_back(Text(100, 20, "KONWERSJA   BMP -> PC", color, 1));
	}

	bool done = false;
	while (!done)
	{
		if (SDL_PollEvent(&event))
		{
			//obs�uga eventow z menu2
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
						case 4: // konwersja BMP -> PC odcienie szaro�ci
							BMPtoPC_ShadersOfGrey();
							break;
						case 5: // konwersja BMP -> PC odcienie szaro�ci + dithering
							BMPtoPC_ShadersOfGreyDithering();
							break;
						case 6: //powr�t
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

		//wy�wietlanie element�w z Menu2
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
		SDL_Color color;

		color.r = 0; color.g = 200; color.b = 0;
		Menu3.texts.push_back(Text(100, 20, "INFORMACJE", color, 1));
		color.r = 200; color.g = 200; color.b = 200;
		Menu3.texts.push_back(Text(25, 100, "linijka1", color, 0));
		color.r = 200; color.g = 200; color.b = 200;
		Menu3.texts.push_back(Text(25, 125, "linijka2", color, 0));
		color.r = 200; color.g = 200; color.b = 200;
		Menu3.texts.push_back(Text(25, 150, "linijka3", color, 0));
		color.r = 200; color.g = 200; color.b = 200;
		Menu3.texts.push_back(Text(25, 175, "linijka4", color, 0));
		color.r = 200; color.g = 200; color.b = 200;
		Menu3.texts.push_back(Text(25, 200, "linijka5", color, 0));
		color.r = 200; color.g = 200; color.b = 200;
		Menu3.texts.push_back(Text(25, 225, "linijka6", color, 0));
		color.r = 200; color.g = 200; color.b = 200;
		Menu3.texts.push_back(Text(25, 250, "linijka7", color, 0));
		color.r = 200; color.g = 200; color.b = 200;
		Menu3.texts.push_back(Text(25, 275, "linijka8", color, 0));
		color.r = 200; color.g = 200; color.b = 200;
		Menu3.texts.push_back(Text(25, 300, "linijka9", color, 0));
		color.r = 200; color.g = 200; color.b = 200;
		Menu3.texts.push_back(Text(25, 325, "linijka10", color, 0));
		color.r = 200; color.g = 200; color.b = 200;
		Menu3.texts.push_back(Text(25, 350, "...", color, 0));

		color.r = 200; color.g = 200; color.b = 200;
		Menu3.texts.push_back(Text(800, 625, "Projekt wykonali:", color, 0));
		color.r = 200; color.g = 200; color.b = 200;
		Menu3.texts.push_back(Text(800, 650, "  Karol Patko", color, 0));
		color.r = 200; color.g = 200; color.b = 200;
		Menu3.texts.push_back(Text(800, 675, "  Pawel Midura", color, 0));
		color.r = 200; color.g = 200; color.b = 200;
		Menu3.texts.push_back(Text(800, 700, "  Wojciech Maludzinski", color, 0));
		color.r = 200; color.g = 200; color.b = 200;
		Menu3.texts.push_back(Text(800, 725, "  Pawel Piskorz", color, 0));
	}

	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

	//wy�wietlanie element�w z Menu3
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