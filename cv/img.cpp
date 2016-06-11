#include "img.hpp"

RGBPixel::RGBPixel() {
        r = 0;
        g = 0;
        b = 0;
        i = 0;
    }
RGBPixel::RGBPixel(float red, float green, float blue){
        r = red;
        g = green;
        b = blue;
        calculate_intensity();
    }
void RGBPixel::calculate_intensity(){
        i = (r+g+b)/3;
    }
void RGBPixel::operator= (float intensity) {
    float ratio = intensity / i;
    i = intensity;
    r *= ratio;
    g *= ratio;
    b *= ratio;
}
RGBPixel operator "" _rgb(const char *rgbi, size_t len) {
    RGBPixel pixel;
    std::istringstream iss(rgbi);
    iss >> pixel.r;
    iss >> pixel.g;
    iss >> pixel.b;
    iss >> pixel.i;
    return pixel;
};
RGBPixel::operator float () {
    return i;
};

MonoPixel::MonoPixel() {
    i = 0;
}
MonoPixel::MonoPixel(float intensity) {
    i = intensity;
}
void MonoPixel::operator= (float intensity) {
    i = intensity;
}
MonoPixel::operator float() {
    return i;
}


bool operator==(const RGBPixel &lhs, const RGBPixel &rhs) {
    std::cout << "PIXEL COMPARE" << std::endl;
    std::cout << lhs.r << " " << rhs.r << std::endl;
    std::cout << lhs.g << " " << rhs.g << std::endl;
    std::cout << lhs.b << " " << rhs.b << std::endl;
    std::cout << lhs.i << " " << rhs.i << std::endl;
    return (lhs.r == rhs.r and
            lhs.g == rhs.g and
            lhs.b == rhs.b and
            lhs.i == rhs.i);
}
bool operator==(const MonoPixel &lhs, const MonoPixel &rhs) {
    return (lhs.i == rhs.i);
}
bool operator==(const RGBPixel &lhs, const MonoPixel &rhs) {
    return (lhs.i == rhs.i);
}

void printImage(std::string name, PixelGrid<MonoPixel> image){
	std::cout << std::endl << name << std::endl;
	for (int r = 0; r < image.rows; r++){
		for (int c = 0; c < image.columns; c++){
			std::cout << "  ";
			std::cout << image[r][c].i << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

template<class T>
bool PixelGrid<T>::operator==(float* values) {
    for (int i = 0; i < rows * columns; i++) {
        if (not (pixels[i] == values[i])) {
            std::cout << i << ' ' << pixels[i].i << ' ' << values[i] << std::endl;
            return false;
        }
    }
    return true;
}

template<class T>
void PixelGrid<T>::normalise() {
    float sum_0 = sum();
    if (sum_0 == 0) {
        sum_0 = 1;
    }
    FOR_PIXELS
        (*this)[r][c].i /= sum_0;
    END_FOR_PIXELS
}
template<class T>
float PixelGrid<T>::sum() {
    float sum = 0;
    FOR_PIXELS
        sum += (*this)[r][c].i;
    END_FOR_PIXELS
    return sum;
}

template class PixelGrid<MonoPixel>;


