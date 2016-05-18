#include <string>
#ifndef PPM_H
#define PPM_H

struct Pixel{
	float r;
	float g;
	float b;
	Pixel() {
		r = 0;
		g = 0;
		b = 0;
	}
	Pixel(float r, float g, float b){
		this->r = r;
		this->g = g;
		this->b = b;
	}
};

class PixelGrid {
	Pixel* pixels;
	public:
	int height, width;
	std::string meta, magic;
	PixelGrid(std::string magic, std::string meta, int h, int w){
			this->meta = meta;
			this->magic = magic;
			height = h;
			width = w;
			pixels = new Pixel[h*w];
		}
	Pixel* operator[](int i){
		return &pixels[i*width];
	}
};

PixelGrid openImage(char* filename);

void printImage(PixelGrid image);

#endif
