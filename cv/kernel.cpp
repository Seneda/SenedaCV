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

float gauss(float x, float y, float sig) {
	float r = (1 / (2*PI*sig*sig)) * exp(-(pow(x,2)+pow(y,2))/(2*sig*sig));
	std::cout << "gauss " << "x" << x << "y" << y << " " << r << std::endl;
	return r;
}

PixelGrid<MonoPixel> gaussian(int size, float sig) {
	PixelGrid<MonoPixel> kernel = PixelGrid<MonoPixel>(size, size);
	FOR_PIXELS_IN_GRID(kernel)
		float x, y;
		x = c - size/2.0 + 0.5;
		y = r - size/2.0 + 0.5;
		kernel[r][c] = gauss(x, y, sig);
	END_FOR_PIXELS
	kernel.normalise();
	printImage("gaussian", kernel);
	return kernel;
}


