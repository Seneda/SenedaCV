#include "kernel.hpp"
#include <fstream>

PixelGrid<MonoPixel> readKernel(std::string filename){
	std::ifstream file;
	file.open(filename.c_str(), std::ifstream::in);
	int rows, cols;
	file >> cols >> rows;
	
	PixelGrid<MonoPixel> kernel(rows, cols);
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			float v;
			file >> v;
			RGBPixel pixel(v, v, v);
			kernel[i][j] = pixel;
		} 
	}
	return kernel;
}
