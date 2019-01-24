#include "pch.h"
#include "view.h"

const char* texture_name = "Data/buttons.bmp";
const char* font_name1 = "Data/abhaya-libre/AbhayaLibre-Regular.ttf";
const int FONTS_NUM = 2;
const int font_size[FONTS_NUM] = { 20, 40 };


SDL_Surface *buttons_texture = nullptr;
TTF_Font* text_font[FONTS_NUM] = { nullptr, nullptr };

std::vector<SDL_Rect> texture_type;

Menu A_Menu;

//--------class Button-------

Button::Button(SDL_Rect rect, SDL_Rect* texture_dim)
{
	rectangle = rect;
	texture_dimension = texture_dim;
}

SDL_Rect Button::get_rectangle()
{
	return rectangle;
}

void Button::change_button(SDL_Rect rect, SDL_Rect* texture_dim)
{
	rectangle = rect;
	texture_dimension = texture_dim;
}

void Button::show(SDL_Surface* screen)
{
	SDL_Rect offset;
	offset.x = rectangle.x;
	offset.y = rectangle.y;

	SDL_BlitSurface(buttons_texture, texture_dimension, screen, &offset);
}

Ret Button::handle_events(SDL_Event &event)
{
	int x = 0, y = 0;
	Ret ret_val;

	if (event.type == SDL_MOUSEMOTION) //mouse move
	{
		x = event.motion.x;
		y = event.motion.y;

		if ((x > rectangle.x) && (x < rectangle.x + rectangle.w) && (y > rectangle.y) && (y < rectangle.y + rectangle.h)) //mouse over the button
		{
			texture_dimension = &texture_type[OVER];
			ret_val.over = true;
		}
		else
		{
			texture_dimension = &texture_type[NONE];
			ret_val.none = true;
		}
	}
	if (event.type == SDL_MOUSEBUTTONDOWN) //mouse button pressed
	{
		if (event.button.button == SDL_BUTTON_LEFT) //left mouse button
		{
			x = event.button.x;
			y = event.button.y;

			if ((x > rectangle.x) && (x < rectangle.x + rectangle.w) && (y > rectangle.y) && (y < rectangle.y + rectangle.h)) //mouse over the button
			{
				texture_dimension = &texture_type[PRESSED];
				ret_val.pressed = true;
			}
		}
	}
	if (event.type == SDL_MOUSEBUTTONUP) //mouse button released
	{
		if (event.button.button == SDL_BUTTON_LEFT) //left mouse button
		{
			x = event.button.x;
			y = event.button.y;

			if ((x > rectangle.x) && (x < rectangle.x + rectangle.w) && (y > rectangle.y) && (y < rectangle.y + rectangle.h)) //mouse over the button
			{
				texture_dimension = &texture_type[RELEASED];
				ret_val.released = true;
			}
		}
	}
	if (inactive == true)
	{
		//texture_dimension = &texture_type[INACTIVE];
		ret_val.inactive = true;
	}
	return ret_val;
}




//--------class Text-------

Text::Text(int x, int y, const char* tex, SDL_Color color, int font_num)
{
	this->x = x;
	this->y = y;
	text = TTF_RenderText_Blended(text_font[font_num], tex, color);
}

void Text::change_text(int x, int y, std::string name, SDL_Color color, int font_num)
{
	SDL_FreeSurface(text);
	this->x = x;
	this->y = y;
	text = TTF_RenderText_Blended(text_font[font_num], name.c_str(), color);
}

void Text::change_text(int x, int y, const char* name, SDL_Color color, int font_num)
{
	SDL_FreeSurface(text);
	this->x = x;
	this->y = y;
	text = TTF_RenderText_Blended(text_font[font_num], name, color);
}

void Text::show(SDL_Surface* screen)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(text, NULL, screen, &offset);
}





//-----------------------funkcje--------------------

void INIT_texture_type()
{
	texture_type.push_back(SDL_Rect());
	texture_type[NONE].x = 0;
	texture_type[NONE].y = 0;
	texture_type[NONE].w = 300;
	texture_type[NONE].h = 50;

	texture_type.push_back(SDL_Rect());
	texture_type[OVER].x = 0;
	texture_type[OVER].y = 50;
	texture_type[OVER].w = 300;
	texture_type[OVER].h = 50;

	texture_type.push_back(SDL_Rect());
	texture_type[PRESSED].x = 0;
	texture_type[PRESSED].y = 100;
	texture_type[PRESSED].w = 300;
	texture_type[PRESSED].h = 50;
	
	texture_type.push_back(SDL_Rect());
	texture_type[RELEASED].x = 0;
	texture_type[RELEASED].y = 150;
	texture_type[RELEASED].w = 300;
	texture_type[RELEASED].h = 50;

	texture_type.push_back(SDL_Rect());
	texture_type[INACTIVE].x = 0;
	texture_type[INACTIVE].y = 200;
	texture_type[INACTIVE].w = 300;
	texture_type[INACTIVE].h = 50;
}

void INIT_view()
{
	//inicjalizacja tekstury
	if (buttons_texture != NULL)
		throw MyRuntimeExceptions::LoadImageException("texture already loaded");


	SDL_Surface* loadedImage = NULL;
	loadedImage = SDL_LoadBMP(texture_name);

	if (loadedImage != NULL)
	{
		buttons_texture = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);

		if (buttons_texture != NULL)
		{
			SDL_SetColorKey(buttons_texture, SDL_SRCCOLORKEY, SDL_MapRGB(buttons_texture->format, 0, 0xFF, 0xFF));
		}
	}
	if (buttons_texture == NULL)
		throw MyRuntimeExceptions::LoadImageException();


	//inicjalizacja czcionek
	//czcionka 0
	if (text_font[0] != NULL)
		throw MyRuntimeExceptions::LoadFontException("font already loaded");

	text_font[0] = TTF_OpenFont(font_name1, font_size[0]);

	if (text_font[0] == NULL)
		throw MyRuntimeExceptions::LoadFontException("error while loading font 0");

	//czcionka 1
	if (text_font[1] != NULL)
		throw MyRuntimeExceptions::LoadFontException("font already loaded");

	text_font[1] = TTF_OpenFont(font_name1, font_size[1]);

	if (text_font[1] == NULL)
		throw MyRuntimeExceptions::LoadFontException("error while loading font 1");
}

void INIT_MENU()
{
	INIT_texture_type();
	
	try {
		INIT_view();
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		getchar();
		clean_up();
		exit(EXIT_FAILURE);
	}
	
	SDL_Rect dim;
	SDL_Color color_y, color_r, color_b;

	dim.x = 10; dim.y = 100; dim.w = 300; dim.h = 50;
	A_Menu.buttons.push_back(Button(dim, &texture_type[NONE]));
	dim.x = 10; dim.y = 160; dim.w = 300; dim.h = 50;
	A_Menu.buttons.push_back(Button(dim, &texture_type[INACTIVE]));
	dim.x = 10; dim.y = 220; dim.w = 300; dim.h = 50;
	A_Menu.buttons.push_back(Button(dim, &texture_type[INACTIVE]));
	dim.x = 10; dim.y = 280; dim.w = 300; dim.h = 50;
	A_Menu.buttons.push_back(Button(dim, &texture_type[INACTIVE]));
	dim.x = 10; dim.y = 340; dim.w = 300; dim.h = 50;
	A_Menu.buttons.push_back(Button(dim, &texture_type[INACTIVE]));
	dim.x = 10; dim.y = 450; dim.w = 300; dim.h = 50;
	A_Menu.buttons.push_back(Button(dim, &texture_type[NONE]));

	color_y.r = 255; color_y.g = 255; color_y.b = 0;
	color_r.r = 255; color_r.g = 0; color_r.b = 0;
	color_b.r = 0; color_b.g = 0; color_b.b = 0;

	A_Menu.texts.push_back(Text(25, 115, "wprowadz nazwe obrazka", color_y, 0));
	A_Menu.texts.push_back(Text(25, 175, "rysuj obrazek", color_y, 0));
	A_Menu.texts.push_back(Text(25, 235, "konwersja  BMP -> PC", color_y, 0));
	A_Menu.texts.push_back(Text(25, 295, "konwersja  PC -> BMP", color_y, 0));
	A_Menu.texts.push_back(Text(25, 355, "informacje", color_y, 0));
	A_Menu.texts.push_back(Text(25, 465, "KONIEC", color_r, 0));
	A_Menu.texts.push_back(Text(100, 20, "MENU", color_b, 1));
}

void MENU_show()
{
	for (auto &i : A_Menu.buttons)
		i.show(screen);
	for (auto &i : A_Menu.texts)
		i.show(screen);
}

void MENU_event()
{
	Ret ret_val;

	//przyciski:
	for(int i=0; i< A_Menu.buttons.size(); ++i)
	{
		ret_val = A_Menu.buttons[i].handle_events(event);
		if (inactive == true && i != 0 && i != 4 && i != 5)
			A_Menu.buttons[i].change_button(A_Menu.buttons[i].get_rectangle(), &texture_type[INACTIVE]);
		if (inactive == false && bmp == true && i != 0 && i != 1 && i != 2 && i != 4 && i != 5)
			A_Menu.buttons[i].change_button(A_Menu.buttons[i].get_rectangle(), &texture_type[INACTIVE]);
		if (inactive == false && bmp == false && i != 0 && i != 3 && i != 4 && i != 5)
			A_Menu.buttons[i].change_button(A_Menu.buttons[i].get_rectangle(), &texture_type[INACTIVE]);
		if (ret_val.released == true && ( inactive == false || i == 5 || i == 4 || i == 0))
		{
			switch (i)
			{
			case 0:
				funkcja1();
				break;
			case 1:
				if(inactive == false && bmp == true)
					funkcja2();
				break;
			case 2:
				if (inactive == false && bmp == true)
					funkcja3();
				break;
			case 3:
				if (inactive == false && bmp == false)
					funkcja4();
				break;
			case 4:
				funkcja5();
				break;
			case 5:
				clean_up();
				exit(EXIT_SUCCESS);
				break;
			default:
				break;
			}
		}
	}
}

void CLEAN_MENU()
{
	SDL_FreeSurface(buttons_texture);
}