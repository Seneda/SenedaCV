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
	
	
	
	printImage(image);
	
}
