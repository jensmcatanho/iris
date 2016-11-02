/*
-----------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2016 Jean Michel Catanho

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
-----------------------------------------------------------------------------
*/
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>

#include "World.h"

using namespace std;

struct RGBType {
	double r, g, b;
	
};

void save_bitmap(const char *filename, int w, int h, int dpi, shared_ptr<World> world) {
	FILE *f;
	int k = w * h;
	int s = 4 * k;
	int filesize = 54 + s;
	double factor = 39.375;
	int m = static_cast<int>(factor);
	int ppm = dpi * m;
	
	unsigned char bmpfileheader[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
	unsigned char bmpinfoheader[40] =  {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};
	
	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize>>8);
	bmpfileheader[4] = (unsigned char)(filesize>>16);
	bmpfileheader[5] = (unsigned char)(filesize>>24);
	
	bmpinfoheader[4] = (unsigned char)(w);
	bmpinfoheader[5] = (unsigned char)(w>>8);
	bmpinfoheader[6] = (unsigned char)(w>>16);
	bmpinfoheader[7] = (unsigned char)(w>>24);
	
	bmpinfoheader[8] = (unsigned char)(h);
	bmpinfoheader[9] = (unsigned char)(h>>8);
	bmpinfoheader[10] = (unsigned char)(h>>16);
	bmpinfoheader[11] = (unsigned char)(h>>24);
	
	bmpinfoheader[21] = (unsigned char)(s);
	bmpinfoheader[22] = (unsigned char)(s>>8);
	bmpinfoheader[23] = (unsigned char)(s>>16);
	bmpinfoheader[24] = (unsigned char)(s>>24);
	
	bmpinfoheader[25] = (unsigned char)(ppm);
	bmpinfoheader[26] = (unsigned char)(ppm>>8);
	bmpinfoheader[27] = (unsigned char)(ppm>>16);
	bmpinfoheader[28] = (unsigned char)(ppm>>24);
	
	bmpinfoheader[29] = (unsigned char)(ppm);
	bmpinfoheader[30] = (unsigned char)(ppm>>8);
	bmpinfoheader[31] = (unsigned char)(ppm>>16);
	bmpinfoheader[32] = (unsigned char)(ppm>>24);
	
	fopen_s(&f, filename, "wb");
	fwrite(bmpfileheader, 1, 14, f);
	fwrite(bmpinfoheader, 1, 40, f);
	
	for (int i = 0; i < k; i++) {		
		double red = (world->m_Pixels[i].r) * 255;
		double green = (world->m_Pixels[i].g) * 255;
		double blue = (world->m_Pixels[i].b) * 255;
		
		unsigned char color[4] = {(int)floor(blue), (int)floor(green),(int)floor(red)};
		
		fwrite(color, 1, 3, f);
		
	}
	
	fclose(f);
	
}

int thisone;

int main(int argc, char *argv[]) {
	std::shared_ptr<World> w(new World());
	
	w->Build();
	w->RenderScene();
	int dpi = 72;

	save_bitmap("scene.bmp", w->m_ViewPlane.m_Width, w->m_ViewPlane.m_Height, dpi, w);	

	Logger::SaveLog();

	return EXIT_SUCCESS;
}

/*int main(int argc, char *argv[]) {
	int dpi = 72;
	int width = 640;
	int height = 480;
	int n = width * height;
	RGBType *pixels = new RGBType[n];
	
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			thisone = y*width + x;
			
			pixels[thisone].r = 1;
			pixels[thisone].g = 0;
			pixels[thisone].b = 0;
			
		}
		
	}
	
	save_bitmap("scene.bmp", width, height, dpi, pixels);
	
	return 0;
};
*/
