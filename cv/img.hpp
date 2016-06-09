#ifndef IMG_HPP
#define IMG_HPP
#include <string>
#include <iostream>
#include <sstream>

struct Pixel{
	float r;
	float g;
	float b;
	float i;
	Pixel() {
		r = 0;
		g = 0;
		b = 0;
		i = 0;
	}
	Pixel(float red, float green, float blue){
		r = red;
		g = green;
		b = blue;
		calculate_intensity();
	}
    void operator= (float intensity);
    void calculate_intensity(){
        i = (r+g+b)/3;
    }
};

class PixelGrid {
	Pixel* pixels;
	public:
	int rows, columns;
	PixelGrid(int r, int c){
		rows = r;
		columns = c;
		pixels = new Pixel[r*c];
	}
	//  image[row][col]
	Pixel* operator[](int i){
		return &pixels[i*columns];
	}
	PixelGrid convolve(PixelGrid kernel);
};

void printImage(std::string name, PixelGrid image);

bool operator==(const Pixel &lhs, const Pixel &rhs);
bool operator==(const Pixel &lhs, const int rhs);
bool operator==(const Pixel &lhs, const int* &rhs);
Pixel operator"" _p(const char* rgbi, size_t len);
#endif
