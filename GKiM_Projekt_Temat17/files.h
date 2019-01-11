#ifndef FILES_H
#define FILES_H

#include <string>
#include <vector>
#include <queue>
#include <SDL.h>
#include "lz77.h"

using namespace std;

//extern SDL_Surface *input_file;

void save_to_PC(SDL_Surface *surface, string outFileName, queue<kod> &zakodowane);

#endif // !FILES_H
