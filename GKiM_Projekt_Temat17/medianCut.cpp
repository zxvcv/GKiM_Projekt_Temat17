#include "pch.h"
#include "medianCut.h"

subspace::subspace(Uint8 Rmin, Uint8 Rmax, Uint8 Gmin, Uint8 Gmax, Uint8 Bmin, Uint8 Bmax, short level)
{
	this->botBorder.r = Rmin;
	this->topBorder.r = Rmax;
	this->botBorder.g = Gmin;
	this->topBorder.g = Gmax;
	this->botBorder.b = Bmin;
	this->topBorder.b = Bmax;
	this->level = level;
	this->left = nullptr;
	this->right = nullptr;
}

void subspace::divide_to_64_subspaces(int*** colors)
{
	if (level < 7) {
		int Rmin = 255, Rmax = 0, Gmin = 255, Gmax = 0, Bmin = 255, Bmax = 0, Rrange, Grange, Brange, maxRange;

		Rrange = topBorder.r - botBorder.r;
		Grange = topBorder.g - botBorder.g;
		Brange = topBorder.b - botBorder.b;
		maxRange = max(max(Rrange, Grange), Brange);

		int* quanInComponent = nullptr;
		int mean, partition, colorQuan;

		int i, j, k;

		if (maxRange == Rrange) {
			quanInComponent = new int[topBorder.r - botBorder.r + 1];
			for (i = 0; i < topBorder.r - botBorder.r + 1; ++i) {
				quanInComponent[i] = 0;
			}

			colorQuan = 0;
			for (i = botBorder.r; i <= topBorder.r; ++i) {
				for (j = botBorder.g; j <= topBorder.g; ++j) {
					for (k = botBorder.b; k <= topBorder.b; ++k) {
						quanInComponent[i - botBorder.r] += colors[i][j][k];
						colorQuan += colors[i][j][k];
					}
				}
			}

			mean = colorQuan / 2;
			colorQuan = 0;
			i = 0;
			while (colorQuan < mean) {
				colorQuan += quanInComponent[i];
				++i;
			}

			if (abs(mean - colorQuan) > abs(mean - colorQuan - quanInComponent[i - 1])) {
				partition = i - 1;
			}
			else {
				partition = i;
			}

			//min i max dla lewej czesci
			for (i = botBorder.r; i >= 0 && i <= partition + botBorder.r && i <= 255; ++i) {
				for (j = botBorder.g; j >= 0 && j <= topBorder.g && j <= 255; ++j) {
					for (k = botBorder.b; k >= 0 && k <= topBorder.b && k <= 255; ++k) {
						if (colors[i][j][k] > 0) {
							if (j < Gmin) {
								Gmin = j;
							}
							if (k < Bmin) {
								Bmin = k;
							}
							if (j > Gmax) {
								Gmax = j;
							}
							if (k > Bmax) {
								Bmax = k;
							}
						}
					}
				}
			}
			left = new subspace(botBorder.r, partition + botBorder.r, Gmin, Gmax, Bmin, Bmax, level + 1);

			//min i max dla prawej czesci
			for (i = partition + botBorder.r + 1; i >= 0 && i <= topBorder.r && i <= 255; ++i) {
				for (j = botBorder.g; j >= 0 && j <= topBorder.g && j <= 255; ++j) {
					for (k = botBorder.b; k >= 0 && k <= topBorder.b && k <= 255; ++k) {
						if (colors[i][j][k] > 0) {
							if (j < Gmin) {
								Gmin = j;
							}
							if (k < Bmin) {
								Bmin = k;
							}
							if (j > Gmax) {
								Gmax = j;
							}
							if (k > Bmax) {
								Bmax = k;
							}
						}
					}
				}
			}
			right = new subspace(partition + botBorder.r + 1, topBorder.r, Gmin, Gmax, Bmin, Bmax, level + 1);

		}
		else if (maxRange == Grange) {
			quanInComponent = new int[topBorder.g - botBorder.g + 1];
			for (i = 0; i < topBorder.g - botBorder.g + 1; ++i) {
				quanInComponent[i] = 0;
			}

			colorQuan = 0;
			for (i = botBorder.r; i <= topBorder.r; ++i) {
				for (j = botBorder.g; j <= topBorder.g; ++j) {
					for (k = botBorder.b; k <= topBorder.b; ++k) {
						quanInComponent[j - botBorder.g] += colors[i][j][k];
						colorQuan += colors[i][j][k];
					}
				}
			}

			mean = colorQuan / 2;
			colorQuan = 0;
			i = 0;
			while (colorQuan < mean) {
				colorQuan += quanInComponent[i];
				++i;
			}

			if (abs(mean - colorQuan) > abs(mean - colorQuan - quanInComponent[i - 1])) {
				partition = i - 1;
			}
			else {
				partition = i;
			}

			//min i max dla lewej czesci
			for (i = botBorder.r; i >= 0 && i <= topBorder.r && i <= 255; ++i) {
				for (j = botBorder.g; j >= 0 && j <= partition + botBorder.g && j <= 255; ++j) {
					for (k = botBorder.b; k >= 0 && k <= topBorder.b && k <= 255; ++k) {
						if (colors[i][j][k] > 0) {
							if (i < Rmin) {
								Rmin = i;
							}
							if (k < Bmin) {
								Bmin = k;
							}
							if (i > Rmax) {
								Rmax = i;
							}
							if (k > Bmax) {
								Bmax = k;
							}
						}
					}
				}
			}

			left = new subspace(Rmin, Rmax, botBorder.g, partition + botBorder.g, Bmin, Bmax, level + 1);

			//min i max dla prawej czesci
			for (i = botBorder.r; i >= 0 && i <= topBorder.r && i <= 255; ++i) {
				for (j = partition + botBorder.g + 1; j >= 0 && j <= topBorder.g && j <= 255; ++j) {
					for (k = botBorder.b; k >= 0 && k <= topBorder.b && k <= 255; ++k) {
						if (colors[i][j][k] > 0) {
							if (i < Rmin) {
								Rmin = i;
							}
							if (k < Bmin) {
								Bmin = k;
							}
							if (i > Rmax) {
								Rmax = i;
							}
							if (k > Bmax) {
								Bmax = k;
							}
						}
					}
				}
			}

			right = new subspace(Rmin, Rmax, partition + botBorder.g + 1, topBorder.g, Bmin, Bmax, level + 1);
		}
		else {
			quanInComponent = new int[topBorder.b - botBorder.b + 1];
			for (i = 0; i < topBorder.b - botBorder.b + 1; ++i) {
				quanInComponent[i] = 0;
			}

			colorQuan = 0;
			for (i = botBorder.r; i <= topBorder.r; ++i) {
				for (j = botBorder.g; j <= topBorder.g; ++j) {
					for (k = botBorder.b; k <= topBorder.b; ++k) {
						quanInComponent[k - botBorder.b] += colors[i][j][k];
						colorQuan += colors[i][j][k];
					}
				}
			}

			mean = colorQuan / 2;
			colorQuan = 0;
			i = 0;
			while (colorQuan < mean) {
				colorQuan += quanInComponent[i];
				++i;
			}

			if (abs(mean - colorQuan) > abs(mean - colorQuan - quanInComponent[i - 1])) {
				partition = i - 1;
			}
			else {
				partition = i;
			}

			//min i max dla lewej czesci
			for (i = botBorder.r; i >= 0 && i <= topBorder.r && i <= 255; ++i) {
				for (j = botBorder.g; j >= 0 && j <= topBorder.g && j <= 255; ++j) {
					for (k = botBorder.b; k >= 0 && k <= partition + botBorder.b && k <= 255; ++k) {
						if (colors[i][j][k] > 0) {
							if (i < Rmin) {
								Rmin = i;
							}
							if (j < Gmin) {
								Gmin = j;
							}
							if (i > Rmax) {
								Rmax = i;
							}
							if (j > Gmax) {
								Gmax = j;
							}
						}
					}
				}
			}

			left = new subspace(Rmin, Rmax, Gmin, Gmax, botBorder.b, partition + botBorder.b, level + 1);


			//min i max dla prawej czesci
			for (i = botBorder.r; i >= 0 && i <= topBorder.r && i <= 255; ++i) {
				for (j = botBorder.g; j >= 0 && j <= topBorder.g && j <= 255; ++j) {
					for (k = partition + botBorder.b + 1; k >= 0 && k <= topBorder.b && k <= 255; ++k) {
						if (colors[i][j][k] > 0) {
							if (i < Rmin) {
								Rmin = i;
							}
							if (j < Gmin) {
								Gmin = j;
							}
							if (i > Rmax) {
								Rmax = i;
							}
							if (j > Gmax) {
								Gmax = j;
							}
						}
					}
				}
			}

			right = new subspace(Rmin, Rmax, Gmin, Gmax, partition + botBorder.b + 1, topBorder.b, level + 1);

		}

		left->divide_to_64_subspaces(colors);
		right->divide_to_64_subspaces(colors);

	}
}

void subspace::create_palette(vector<SDL_Color> &palette, int*** colors)
{
	unsigned long long int r = 0, g = 0, b = 0;
	int temporary;
	unsigned long long int all = 0;
	if (level == 6)
	{
		for (int i = botBorder.r; i <= topBorder.r; ++i) {
			for (int j = botBorder.g; j <= topBorder.g; ++j) {
				for (int k = botBorder.b; k <= topBorder.b; ++k) {
					temporary = colors[i][j][k];
					r += i * temporary;
					g += j * temporary;
					b += k * temporary;
					all += temporary;
				}
			}
		}
		SDL_Color kolor;
		if (all > 0) {
			kolor.r = r / all;
			kolor.g = g / all;
			kolor.b = b / all;
		}
		palette.push_back(kolor);
	}
	else
	{
		left->create_palette(palette, colors);
		right->create_palette(palette, colors);
	}
}


void load_dedicated_palette(SDL_Surface * picture, int width, int height, vector<SDL_Color> &tmpPalette)
{
	int*** colors = new int**[256];

	for (int i = 0; i < 256; ++i) {
		colors[i] = new int*[256];
		for (int j = 0; j < 256; ++j) {
			colors[i][j] = new int[256];
			for (int k = 0; k < 256; ++k) {
				colors[i][j][k] = 0;
			}
		}
	}

	Uint8 R, G, B,
		Rmin = getPixel_BMP(picture, 0, 0).r,
		Rmax = getPixel_BMP(picture, 0, 0).r,
		Gmin = getPixel_BMP(picture, 0, 0).g,
		Gmax = getPixel_BMP(picture, 0, 0).g,
		Bmin = getPixel_BMP(picture, 0, 0).b,
		Bmax = getPixel_BMP(picture, 0, 0).b;
	int j;
	for (int i = 0; i < width; ++i) {
		for (j = 0; j < height; ++j) {
			R = getPixel_BMP(picture, i, j).r;
			G = getPixel_BMP(picture, i, j).g;
			B = getPixel_BMP(picture, i, j).b;
			colors[R][G][B] += 1;
			if (R > Rmax)
				Rmax = R;
			else if (R < Rmin)
				Rmin = R;
			if (G > Gmax)
				Gmax = G;
			else if (G < Gmin)
				Gmin = G;
			if (B > Bmax)
				Bmax = B;
			else if (B < Bmin)
				Bmin = B;
		}
	}

	subspace* root = new subspace(Rmin, Rmax, Gmin, Gmax, Bmin, Bmax, 0);

	root->divide_to_64_subspaces(colors);

	//vector<SDL_Color> tmpPalette;
	root->create_palette(tmpPalette, colors);

	//for (int i = 0; i < 63; ++i) {
	//      palette[i] = tmpPalette.front();
	//      tmpPalette.erase(tmpPalette.begin());
	//}

}