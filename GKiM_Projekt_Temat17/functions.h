#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <SDL.h>
#include "l_exceptions.h"
#include "SDL_functions.h"
#include "dithering.h"
#include "palette.h"
#include "lz77.h"
#include "files.h"
#include "data_preparation.h"
#include <chrono> //debug

using namespace std;
using tp = std::chrono::time_point<std::chrono::system_clock>; //debug
using duration = std::chrono::duration<float>; //debug

using tp = std::chrono::time_point<std::chrono::system_clock>;
using duration = std::chrono::duration<float>;

extern SDL_Surface *input_file;
extern ifstream input_file_pc;


/*
funkcja wykonujaca konwersjê BMP do PC przy pomocy palety narzuconej
@EXCEPTIONS:	---
*/
void BMPtoPC_ImposedPallete();

/*
funkcja wykonujaca konwersjê BMP do PC przy pomocy palety narzuconej i ditheringu
@EXCEPTIONS:	---
*/
void BMPtoPC_ImposedPalleteDithering();

/*
funkcja wykonujaca konwersjê BMP do PC przy pomocy palety dedykowanej
@EXCEPTIONS:	---
*/
void BMPtoPC_DedicatedPallete();

/*
funkcja wykonujaca konwersjê BMP do PC przy pomocy palety dedykowanej i ditheringu
@EXCEPTIONS:	---
*/
void BMPtoPC_DedicatedPalleteDithering();

/*
funkcja wykonujaca konwersjê BMP do PC przy pomocy palety skali szaroœci
@EXCEPTIONS:	---
*/
void BMPtoPC_ShadersOfGrey();

/*
funkcja wykonujaca konwersjê BMP do PC przy pomocy palety skali szaroœci i ditheringu
@EXCEPTIONS:	---
*/
void BMPtoPC_ShadersOfGreyDithering();

/*
funkcja wykonujaca konwersjê PC do BMP
@EXCEPTIONS:	---
*/
void PCtoBMP();

#endif // !FUNCTIONS_H

