#include "pch.h"
#include "medianCut.h"

subspace::subspace(Uint8 Rmin, Uint8 Rmax, Uint8 Gmin, Uint8 Gmax, Uint8 Bmin, Uint8 Bmax, short level) 
{
	this->Rd = Rmin;
	this->Rg = Rmax;
	this->Gd = Gmin;
	this->Gg = Gmax;
	this->Bd = Bmin;
	this->Bg = Bmax;
	this->level = level;
	this->left = nullptr;
	this->right = nullptr;
}

void subspace::divide_to_64_subspaces(int*** colors) 
{
	if (level < 7) {
		int Rmin = 255, Rmax = 0;
		int Gmin = 255, Gmax = 0;
		int Bmin = 255, Bmax = 0;

		int Rrange, Grange, Brange;
		Rrange = Rg - Rd;
		Grange = Gg - Gd;
		Brange = Bg - Bd;

		if (max(max(Rrange, Grange), Brange) == Rrange) {

			int* quanInComponent = new int[Rg - Rd + 1];
			for (int i = 0; i < Rg - Rd + 1; ++i) {
				quanInComponent[i] = 0;
			}

			int colorQuan = 0;
			for (int i = Rd; i <= Rg; ++i) {
				for (int j = Gd; j <= Gg; ++j) {
					for (int k = Bd; k <= Bg; ++k) {
						quanInComponent[i - Rd] += colors[i][j][k];
					}
				}
			}

			for (int i = 0; i < Rg - Rd + 1; ++i) {
				colorQuan += quanInComponent[i];
			}

			unsigned long long int mean = colorQuan / 2;
			colorQuan = 0;
			int partition;
			int i = 0;
			while (colorQuan < mean) {
				colorQuan += quanInComponent[i];
				++i;
			}
			partition = i;

			//Gmin Gmax
			for (int i = Rd; i <= partition + Rd; ++i) {
				for (int j = Gd; j <= Gg; ++j) {
					for (int k = Bd; k <= Bg; ++k) {
						if (colors[i][j][k] > 0 && j < Gmin) {
							Gmin = j;
						}
						if (colors[i][j][k] > 0 && j > Gmax) {
							Gmax = j;
						}
					}
				}
			}

			//Bmin Bmax
			for (int i = Rd; i <= partition + Rd; ++i) {
				for (int j = Gd; j <= Gg; ++j) {
					for (int k = Bd; k <= Bg; ++k) {
						if (colors[i][j][k] > 0 && k < Bmin) {
							Bmin = k;
						}
						if (colors[i][j][k] > 0 && k > Bmax) {
							Bmax = k;
						}
					}
				}
			}

			left = new subspace(Rd, partition + Rd, Gmin, Gmax, Bmin, Bmax, level + 1);
			//Gmin Gmax
			for (int i = partition + Rd + 1; i <= Rg; ++i) {
				for (int j = Gd; j <= Gg; ++j) {
					for (int k = Bd; k <= Bg; ++k) {
						if (colors[i][j][k] > 0 && j < Gmin) {
							Gmin = j;
						}
						if (colors[i][j][k] > 0 && j > Gmax) {
							Gmax = j;
						}
					}
				}
			}

			//Bmin Bmax
			for (int i = partition + Rd + 1; i <= Rg; ++i) {
				for (int j = Gd; j <= Gg; ++j) {
					for (int k = Bd; k <= Bg; ++k) {
						if (colors[i][j][k] > 0 && k < Bmin) {
							Bmin = k;
						}
						if (colors[i][j][k] > 0 && k > Bmax) {
							Bmax = k;
						}
					}
				}
			}

			right = new subspace(partition + Rd + 1, Rg, Gmin, Gmax, Bmin, Bmax, level + 1);
		}
		else if (max(max(Rrange, Grange), Brange) == Grange) {
			int* quanInComponent = new int[Gg - Gd + 1];
			for (int i = 0; i < Gg - Gd + 1; ++i) {
				quanInComponent[i] = 0;
			}

			int colorQuan = 0;
			for (int i = Rd; i <= Rg; ++i) {
				for (int j = Gd; j <= Gg; ++j) {
					for (int k = Bd; k <= Bg; ++k) {
						quanInComponent[j - Gd] += colors[i][j][k];
					}
				}
			}

			for (int i = 0; i < Gg - Gd + 1; ++i) {
				colorQuan += quanInComponent[i];
			}

			int srednia = colorQuan / 2;
			colorQuan = 0;
			int partition;
			int i = 0;
			while (colorQuan < srednia) {
				colorQuan += quanInComponent[i];
				++i;
			}
			partition = i;

			//Rmin Rmax
			for (int i = Rd; i <= Rg; ++i) {
				for (int j = Gd; j <= partition + Gd; ++j) {
					for (int k = Bd; k <= Bg; ++k) {
						if (colors[i][j][k] > 0 && i < Rmin) {
							Rmin = i;
						}
						if (colors[i][j][k] > 0 && i > Rmax) {
							Rmax = i;
						}
					}
				}
			}

			//Bmin Bmax
			for (int i = Rd; i <= Rg; ++i) {
				for (int j = Gd; j <= partition + Gd; ++j) {
					for (int k = Bd; k <= Bg; ++k) {
						if (colors[i][j][k] > 0 && k < Bmin) {
							Bmin = k;
						}
						if (colors[i][j][k] > 0 && k > Bmax) {
							Bmax = k;
						}
					}
				}
			}

			left = new subspace(Rmin, Rmax, Gd, partition + Gd, Bmin, Bmax, level + 1);

			//Rmin Rmax
			for (int i = Rd; i <= Rg; ++i) {
				for (int j = partition + Gd + 1; j <= Gg; ++j) {
					for (int k = Bd; k <= Bg; ++k) {
						if (colors[i][j][k] > 0 && i < Rmin) {
							Rmin = i;
						}
						if (colors[i][j][k] > 0 && i > Rmax) {
							Rmax = i;
						}
					}
				}
			}


			//Bmin Bmax
			for (int i = Rd; i <= Rg; ++i) {
				for (int j = partition + Gd + 1; j <= Gg; ++j) {
					for (int k = Bd; k <= Bg; ++k) {
						if (colors[i][j][k] > 0 && k < Bmin) {
							Bmin = k;
						}
						if (colors[i][j][k] > 0 && k > Bmax) {
							Bmax = k;
						}
					}
				}
			}

			right = new subspace(Rmin, Rmax, partition + Gd + 1, Gg, Bmin, Bmax, level + 1);
		}
		else {

			int* quanInComponent = new int[Bg - Bd + 1];
			for (int i = 0; i < Bg - Bd + 1; ++i) {
				quanInComponent[i] = 0;
			}

			int colorQuan = 0;
			for (int i = Rd; i <= Rg; ++i) {
				for (int j = Gd; j <= Gg; ++j) {
					for (int k = Bd; k <= Bg; ++k) {
						quanInComponent[k - Bd] += colors[i][j][k];
						colorQuan += colors[i][j][k];
					}
				}
			}

			int mean = colorQuan / 2;
			colorQuan = 0;
			int partition;
			int i = 0;
			while (colorQuan < mean) {
				colorQuan += quanInComponent[i];
				++i;
			}
			partition = i;



			//Rmin Rmax
			for (int i = Rd; i <= Rg; ++i) {
				for (int j = Gd; j <= Gg; ++j) {
					for (int k = Bd; k <= partition + Bd; ++k) {
						if (colors[i][j][k] > 0 && i < Rmin) {
							Rmin = i;
						}
						if (colors[i][j][k] > 0 && i > Rmax) {
							Rmax = i;
						}
					}
				}
			}

			//Gmin Gmax
			for (int i = Rd; i <= Rg; ++i) {
				for (int j = Gd; j <= Gg; ++j) {
					for (int k = Bd; k <= partition + Bd; ++k) {
						if (colors[i][j][k] > 0 && j < Gmin) {
							Gmin = j;
						}
						if (colors[i][j][k] > 0 && j > Gmax) {
							Gmax = j;
						}
					}
				}
			}

			left = new subspace(Rmin, Rmax, Gmin, Gmax, Bd, partition + Bd, level + 1);

			//Rmin Rmax
			for (int i = Rd; i <= Rg; ++i) {
				for (int j = Gd; j <= Gg; ++j) {
					for (int k = partition + Bd + 1; k <= Bg; ++k) {
						if (colors[i][j][k] > 0 && i < Rmin) {
							Rmin = i;
						}
						if (colors[i][j][k] > 0 && i > Rmax) {
							Rmax = i;
						}
					}
				}
			}

			//Gmin Gmax
			for (int i = Rd; i <= Rg; ++i) {
				for (int j = Gd; j <= Gg; ++j) {
					for (int k = partition + Bd + 1; k <= Bg; ++k) {
						if (colors[i][j][k] > 0 && j < Gmin) {
							Gmin = j;
						}
						if (colors[i][j][k] > 0 && j > Gmax) {
							Gmax = j;
						}
					}
				}
			}

			right = new subspace(Rmin, Rmax, Gmin, Gmax, partition + Bd + 1, Bg, level + 1);

		}

		left->divide_to_64_subspaces(colors);
		right->divide_to_64_subspaces(colors);

	}
}

void subspace::create_palette(vector<SDL_Color> &palette, int*** colors)
{
	unsigned long long int RR = 0;
	unsigned long long int GG = 0;
	unsigned long long int BB = 0;
	int temp;
	unsigned long long int all = 0;
	if (level == 6) {
		for (int i = Rd; i <= Rg; ++i) {
			for (int j = Gd; j <= Gg; ++j) {
				for (int k = Bd; k <= Bg; ++k) {
					temp = colors[i][j][k];
					RR += temp * i;
					GG += temp * j;
					BB += temp * k;
					all += temp;
				}
			}
		}
		SDL_Color kolor;
		if (all > 0) {
			kolor.r = RR / all;
			kolor.g = GG / all;
			kolor.b = BB / all;
		}
		palette.push_back(kolor);
	}
	else {
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

	Uint8 R, G, B;
	Uint8 Rmin = 255, Rmax = 0, Gmin = 255, Gmax = 0, Bmin = 255, Bmax = 0;
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			R = getPixel_BMP(picture, i, j).r;
			G = getPixel_BMP(picture, i, j).g;
			B = getPixel_BMP(picture, i, j).b;
			colors[R][G][B] += 1;
			if (R > Rmax)
				Rmax = R;
			if (R < Rmin)
				Rmin = R;
			if (G > Gmax)
				Gmax = G;
			if (G < Gmin)
				Gmin = G;
			if (B > Bmax)
				Bmax = B;
			if (B < Bmin)
				Bmin = B;
		}
	}

	subspace* root = new subspace(Rmin, Rmax, Gmin, Gmax, Bmin, Bmax, 0);

	root->divide_to_64_subspaces(colors);

	//vector<SDL_Color> tmpPalette;
	root->create_palette(tmpPalette, colors);

	//for (int i = 0; i < 63; ++i) {
	//	palette[i] = tmpPalette.front();
	//	tmpPalette.erase(tmpPalette.begin());
	//}

}