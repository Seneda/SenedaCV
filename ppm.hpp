#include <string>
#include "img.hpp"
#ifndef PPM_H
#define PPM_H


class PPMImage: public PixelGrid {
	public:
	
	std::string meta, magic;
	PPMImage(std::string magic, std::string meta, int rows, int cols)
	: PixelGrid(rows, cols)
	{
		this->meta = meta;
		this->magic = magic;
	}
	PPMImage convolve(PixelGrid kernel);
	void normalise();
	float max();
	float min();
	float range(){
		if (this->max() == this->min()){
			return 1;
		}
		
		return this->max() - this->min();
	};
};

PPMImage openImage(char* filename);

void printImage(std::string name, PPMImage image);

void saveImage(PPMImage image);

#endif
