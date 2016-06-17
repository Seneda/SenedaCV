#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <thread>
#include <unistd.h>
#include "../cv/ppm.hpp"
#include "../cv/kernel.hpp"

PPMImage edge(PPMImage image, float sigma);

using namespace std;


int main() {
    // open file
	std::ifstream file;
	file.open((char*)"instructions.txt", std::ifstream::in);

	//read image name
	string image_filename_string;
	std::getline(file, image_filename_string);
	cout << "Image: " << image_filename_string << endl;
	const char* image_filename = image_filename_string.c_str();

	PPMImage image = openImage(image_filename);


	PPMImage grad = edge(image, 0.5);

	grad.saveImage("grad.ppm");

}

void do_convolution(PPMImage image, PixelGrid<MonoPixel> kernel, PPMImage &output) {
	for (int i = 0; i < 3; i++){
		output = image.convolve(kernel);
	}
}

PPMImage edge(PPMImage image, float sigma=0.5) {
//	image = image.convolve(gaussian(8*sigma, sigma));

	PixelGrid<MonoPixel> x_kernel = readKernel("kernels/edge_x");
	PixelGrid<MonoPixel> y_kernel = readKernel("kernels/edge_y");
	PPMImage x_grad = PPMImage(image.magic, image.meta, image.rows - x_kernel.rows + 1,
							   image.columns - x_kernel.columns + 1);
	PPMImage y_grad = PPMImage(image.magic, image.meta, image.rows - y_kernel.rows + 1,
							   image.columns - y_kernel.columns + 1);

	std::cout << "Begin..." << std::endl;
	clock_t begin = clock();

	std::thread x(do_convolution, image, x_kernel, std::ref(x_grad));
	std::thread y(do_convolution, image, y_kernel, std::ref(y_grad));
	x.join();
	y.join();
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "Time :" << elapsed_secs << std::endl;
	sleep(10);
	std::cout << "Begin..." << std::endl;
	begin = clock();

	for (int i = 0; i < 3; i++) {
		do_convolution(image, x_kernel, x_grad);
		do_convolution(image, y_kernel, y_grad);
	}
	end = clock();
	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "Time :" << elapsed_secs << std::endl;

	PPMImage grad = PPMImage(image.magic, image.meta, x_grad.rows, x_grad.columns);
	PixelGrid<AnglePixel> ang = PixelGrid<AnglePixel>(grad.rows, grad.columns);

	FOR_PIXELS_IN_GRID(grad)
			grad[r][c] = sqrt(x_grad[r][c] * x_grad[r][c] +
							  y_grad[r][c] * y_grad[r][c]);
			ang[r][c] = atan2(y_grad[r][c], x_grad[r][c]) * 180 / PI + 180;
	END_FOR_PIXELS
	grad.autorange();
	return grad;
}