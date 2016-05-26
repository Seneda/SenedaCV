#include <iostream>
#include <string>
#include <fstream>
#include "ppm.hpp"
#include "kernel.hpp"
using namespace std;

int main() {
	string magic, meta;
	std::cout << "Start" << std::endl;
	string filename_string;
	cin >> filename_string;
	cout << filename_string << endl;
	const char* filename = filename_string.c_str();
	PPMImage image = openImage(filename);

	//printImage("Image", image);
	PixelGrid kernel = edge_x_big();
	printImage("Kernel", kernel);
	PPMImage output = image.convolve(kernel);
	
	//kernel = edge_y();
	//printImage("Kernel", kernel);
	//output = output.convolve(kernel);
	
	//std::cout << output.min() << std::endl;
	output.magnitudise();
	output.threshold(0.3);
	output.normalise();
	output.saveImage();
	//printImage("output", output);
}
