#ifndef IMG_HPP
#define IMG_HPP
#include <string>
#include <iostream>
#include <sstream>

struct RGBPixel{
	float r;
	float g;
	float b;
	float i;
	RGBPixel();
	RGBPixel(float red, float green, float blue);
    void operator= (float intensity);
    void calculate_intensity();
};
RGBPixel operator"" _p(const char* rgbi, size_t len);


struct MonoPixel{
	float i;
	MonoPixel();
	MonoPixel(float intensity);
};

class PixelGrid {
	RGBPixel* pixels;
	public:
	int rows, columns;
	PixelGrid(int r, int c){
		rows = r;
		columns = c;
		pixels = new RGBPixel[r*c];
	}
	//  image[row][col]
	RGBPixel* operator[](int i){
		return &pixels[i*columns];
	}
	PixelGrid convolve(PixelGrid kernel);
};

void printImage(std::string name, PixelGrid image);

bool operator==(const RGBPixel &lhs, const RGBPixel &rhs);
bool operator==(const RGBPixel &lhs, const int rhs);
bool operator==(const RGBPixel &lhs, const int* &rhs);
#endif
