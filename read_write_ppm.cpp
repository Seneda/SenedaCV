#include <iostream>
#include <string>
#include <fstream>
#include "ppm.hpp"
using namespace std;

int main() {
	char* filename;
	string magic, meta;
	filename = (char*)"sample_images/smile.ppm";
	//cin >> filename;
	PPMImage image = openImage(filename);
	PixelGrid kernel(2,2);
	kernel[0][0].i = -1;
	kernel[1][0].i = -1;
	kernel[0][1].i = 1;
	kernel[1][1].i = 1;
	std::cout << kernel[0][0].i << std::endl;
	std::cout << kernel[0][1].i << std::endl;
	std::cout << kernel[1][0].i << std::endl;
	std::cout << kernel[1][1].i << std::endl;

	PPMImage output = image.convolve(kernel);
	output.normalise();
	cout << output[0][0].i << std::endl;
	printImage(output);
	
}
