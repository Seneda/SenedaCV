#include <string>
#include <vector>
#include "img.hpp"
#ifndef PPM_H
#define PPM_H


class PPMImage: public PixelGrid<RGBPixel> {
	public:
	
	std::string meta, magic;
	PPMImage(std::string magic, std::string meta, int rows, int cols)
	: PixelGrid(rows, cols)
	{
		this->meta = meta;
		this->magic = magic;
	}
	PPMImage convolve(const PixelGrid<MonoPixel> kernel)const;
	PPMImage apply_kernels(std::vector<PixelGrid<MonoPixel>> kernels);
	PPMImage resize(int rows, int columns)const;
	void saveImage(const char* name);
	void normalise();
	void magnitudise();
	void threshold(float thresh);
	float max();
	float min();
	float range(){
		if (this->max() == this->min()){
			return 1;
		}
		
		return this->max() - this->min();
	};
};

PPMImage openImage(const char* filename);

void printImage(std::string name, PPMImage image);

void saveImage(PPMImage image);



#endif
