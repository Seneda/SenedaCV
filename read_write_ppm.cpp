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
	filename = (char*)"sample_images/gull.ppm";
	//cin >> filename;
	PPMImage image = openImage(filename);

	//printImage("Image", image);
	PixelGrid kernel = edge_x();
	printImage("Kernel", kernel);
	PPMImage output = image.convolve(kernel);
	std::cout << "Done convolving" << std::endl;
	//printImage("Kernel after convolve", kernel);
	//printImage("output", output);
	std::cout << output[389][76].i << std::endl;
	std::cout << output.min() << std::endl;
	output.normalise();
	saveImage(output);
	//printImage("output", output);
}
