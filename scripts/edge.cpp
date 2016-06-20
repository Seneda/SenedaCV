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

void do_convolution(const PPMImage &image, const PixelGrid<MonoPixel> &kernel, PPMImage &output) {
	for (int i = 0; i < 1; i++){
		output = image.convolve(kernel);
	}
}

PPMImage edge(const PPMImage image, float sigma=0.5) {
//	image = image.convolve(gaussian(8*sigma, sigma));
	std::cout << "Begin..." << std::endl;
	clock_t end;
	clock_t begin;
    #define START std::cout << "Timing..." << std::endl;  begin = clock();
	#define TIME end = clock(); std::cout << "Time :" << double(end - begin) / CLOCKS_PER_SEC/1 << std::endl;

	START
	const PixelGrid<MonoPixel> x_kernel = readKernel("kernels/edge_x");
	const PixelGrid<MonoPixel> y_kernel = readKernel("kernels/edge_y");
	PPMImage x_grad = PPMImage(image.magic, image.meta, 0, 0);
	PPMImage y_grad = PPMImage(image.magic, image.meta, 0, 0);

	TIME
	START

//	std::thread x(do_convolution, image, x_kernel, std::ref(x_grad));
//	std::thread y(do_convolution, image, y_kernel, std::ref(y_grad));
//	x.join();
//	y.join();

	TIME

	START

//	do_convolution(image, x_kernel, x_grad);
//    do_convolution(image, y_kernel, y_grad);
    x_grad = image.convolve(x_kernel);
    y_grad = image.convolve(y_kernel);

	TIME


	PPMImage grad = PPMImage(image.magic, image.meta, x_grad.rows, x_grad.columns);
	PixelGrid<AnglePixel> ang = PixelGrid<AnglePixel>(grad.rows, grad.columns);
	PixelGrid<RGBPixel> color = image.resize(grad.rows, grad.columns);
	FOR_PIXELS_IN_GRID(grad)
			float i = sqrt(x_grad[r][c].i *
                                   x_grad[r][c].i +
                                   y_grad[r][c].i *
                                           y_grad[r][c].i)/100;
			grad[r][c].r = i*color[r][c].r;
			grad[r][c].g = i*color[r][c].g;
			grad[r][c].b = i*color[r][c].b;
            grad[r][c].calculate_intensity();
			ang[r][c] = atan2(y_grad[r][c], x_grad[r][c]) * 180 / PI + 180;
	END_FOR_PIXELS
	std::cout << "suppressing" << std::endl;
	PPMImage edges = PPMImage(grad.magic, grad.meta, grad.rows, grad.columns);
    float threshold = grad.max_abs() * 0.0;
	FOR_PIXELS_IN_GRID(grad)
			int r_p, c_p, r_n, c_n;
		    int dir = round(ang[r][c].i/45);
			if ((dir == 0) or (dir == 8)){
				r_p = r;
				c_p = c + 1;
				r_n = r;
				c_n = c - 1;
			} else if (dir == 1){
				r_p = r + 1;
				c_p = c + 1;
				r_n = r - 1;
				c_n = c - 1;
			} else if (dir == 2){
				r_p = r + 1;
				c_p = c;
				r_n = r - 1;
				c_n = c;
			} else if (dir == 3){
				r_p = r + 1;
				c_p = c - 1;
				r_n = r - 1;
				c_n = c + 1;
			} else if (dir == 4){
				r_p = r;
				c_p = c - 1;
				r_n = r;
				c_n = c + 1;
			} else if (dir == 5){
				r_p = r - 1;
				c_p = c - 1;
				r_n = r + 1;
				c_n = c + 1;
			} else if (dir == 6){
				r_p = r - 1;
				c_p = c;
				r_n = r + 1;
				c_n = c;
			} else if (dir == 7){
				r_p = r - 1;
				c_p = c + 1;
				r_n = r + 1;
				c_n = c - 1;
			}
			if ((grad.rows - 1 > r) and (r > 0) and (grad.columns - 1 > c) and (c > 0)) {

//                std::cout << grad.rows << " " << grad.columns << std::endl;
//                std::cout << r << " " << c << "   " << r << " " << c << std::endl;
//                std::cout << r_p << " " << c_p << "   " << r_n << " " << c_n << std::endl;
                if (abs(grad[r][c] >= threshold) and
                        (grad[r][c].i > grad[r_p][c_p].i) and
                    (grad[r][c].i > grad[r_n][c_n].i)) {
					edges[r][c].g = 1;
				} else {
					edges[r][c].g = 0;
				}
//                std::cout << edges[r][c].i;
//                std::cout << grad[r_n][c_n].i << " " << grad[r][c].i << " " << grad[r_n][c_n].i << " " << std::endl << std::endl;

            }
	END_FOR_PIXELS

	grad.autorange();
	return edges;
}