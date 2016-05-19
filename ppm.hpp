#include <string>
#include "img.hpp"
#ifndef PPM_H
#define PPM_H


class PPMImage: public PixelGrid {
	public:
	
	std::string meta, magic;
	PPMImage(std::string magic, std::string meta, int h, int w)
	: PixelGrid(w, h)
	{
		this->meta = meta;
		this->magic = magic;
	}
};

PPMImage openImage(char* filename);

void printImage(PPMImage image);

#endif
