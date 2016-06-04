#include "kernel.hpp"
#include <fstream>

PixelGrid readKernel(std::string filename){
	std::ifstream file;
	file.open(filename.c_str(), std::ifstream::in);
	int rows, cols;
	file >> cols >> rows;
	
	PixelGrid kernel(rows, cols);
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			float v;
			file >> v;
			Pixel pixel(v, v, v);
			kernel[i][j] = pixel;
		} 
	}
	return kernel;
}
