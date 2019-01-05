#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <SDL.h>
#include "l_exceptions.h"
#include "SDL_functions.h"
#include "dithering.h"

using namespace std;

extern SDL_Surface *input_file;
extern SDL_Event event;

/*
...opis...
@param _		...
@return			...
@EXCEPTIONS:	---
*/
void BMPtoPC_ImposedPallete();

/*
...opis...
@param _		...
@return			...
@EXCEPTIONS:	---
*/
void BMPtoPC_ImposedPalleteDithering();

/*
...opis...
@param _		...
@return			...
@EXCEPTIONS:	---
*/
void BMPtoPC_DedicatedPallete();

/*
...opis...
@param _		...
@return			...
@EXCEPTIONS:	---
*/
void BMPtoPC_DedicatedPalleteDithering();

/*
...opis...
@param _		...
@return			...
@EXCEPTIONS:	---
*/
void BMPtoPC_ShadersOfGrey();

/*
...opis...
@param _		...
@return			...
@EXCEPTIONS:	---
*/
void BMPtoPC_ShadersOfGreyDithering();

/*
...opis...
@param _		...
@return			...
@EXCEPTIONS:	---
*/
void PCtoBMP();

#endif // !FUNCTIONS_H

