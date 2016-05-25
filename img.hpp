#ifndef IMG_HPP
#define IMG_HPP
#include <string>
#include <iostream>

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
	Pixel(float r, float g, float b){
		this->r = r;
		this->g = g;
		this->b = b;
		this->i = (r+g+b)/3;
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


#endif
