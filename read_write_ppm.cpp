#include <iostream>
#include <string>
#include <fstream>
#include "ppm.hpp"
#include "kernel.hpp"
using namespace std;

int main() {
	char* filename;
	string magic, meta;
	std::cout << "Start" << std::endl;
	filename = (char*)"sample_images/smile.ppm";
	//cin >> filename;
	PPMImage image = openImage(filename);

	printImage("Image", image);
	PixelGrid kernel = no_change();
	PPMImage output = image.convolve(kernel);
	printImage("Kernel after convolve", kernel);
	//cout << output[0][0].i << std::endl;
	printImage("output", output);
	output.normalise();
	saveImage(output);
	printImage("output", output);
}
