#include "pch.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <SDL_ttf.h>
#include <SDL.h>
#include <math.h>
#define pi 3.14
#include <time.h>
#include "SDL_functions.h"
#include "view.h"
#include "l_exceptions.h"

#ifdef main
#undef main
#endif // main

using namespace std;

const int width = 800;
const int height = 600;
char const* tytul = "Projekt Temat 17";

SDL_Surface *screen = nullptr;
SDL_Event event;

SDL_Surface *input_file = nullptr;
ifstream input_file_pc;
string filename;
bool inactive = true;
bool bmp = false;

extern SDL_Surface *buttons_texture;


int main(int argc, char* argv[])
{
	if (init_SDL() == false)
		return 1;

	INIT_MENU();


    bool done = false;
    while(!done)
    {
        if (SDL_PollEvent(&event))
        {
			MENU_event();

            switch (event.type)
            {
                
            case SDL_QUIT: // exit if the window is closed
                done = true;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    done = true;
                if (event.key.keysym.sym == SDLK_b)
					czyscEkran(0, 0, 10);
				break;
            }
        }

		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));

		MENU_show();

		if (SDL_Flip(screen) == -1)
		{
			clean_up();
			return 1;
		}
    }

	clean_up();

	cout << "Exited cleanly" << endl;
    return 0;
}
