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
	string kernel_name;
	cin >> kernel_name;
	PixelGrid kernel = readKernel(kernel_name.c_str());
	printImage("Kernel", kernel);
	PPMImage output = image.convolve(kernel);

	output.magnitudise();
	output.normalise();
	output.saveImage();
}
