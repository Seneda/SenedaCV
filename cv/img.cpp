#include <cmath>
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
    if (i) {
        float ratio = intensity / i;
        i = intensity;
        r *= ratio;
        g *= ratio;
        b *= ratio;
    } else {
        i = intensity;
        r = intensity;
        g = intensity;
        b = intensity;
    }
}

RGBPixel::operator float () {
    return i;
};

void RGBPixel::operator+=(float change) {
    r += change;
    g += change;
    b += change;
}

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

void MonoPixel::operator+=(float change) {
    i += change;
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

//bool operator==(const RGBPixel &lhs, const MonoPixel &rhs) {
//    return (lhs.i == rhs.i);
//}

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

bool operator==(const RGBPixel &lhs, const std::string &rhs) {
    std::istringstream iss(rhs);
    float r, g, b, i;
    iss >> r;
    iss >> g;
    iss >> b;
    iss >> i;
    return ((lhs.r == r) and (lhs.g== g) and (lhs.b == b) and (lhs.i == i)) ;
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

template<class T>
void PixelGrid<T>::autorange() {
    float offset = min();
    std::cout << offset << std::endl;
    if (offset < 0) {
        FOR_PIXELS
            (*this)[r][c].i += -1*offset;
        END_FOR_PIXELS
    }
}

template<class T>
float PixelGrid<T>::max() {
    float max = 0;
    FOR_PIXELS
        if ((*this)[r][c].i > max) {
            max = (*this)[r][c].i;
        }
    END_FOR_PIXELS
    return max;
}

template<class T>
float PixelGrid<T>::max_abs() {
    float max = 0;
    FOR_PIXELS
        float abs_val = abs((*this)[r][c].i);
        if (abs_val > max) {
            max = abs_val;
        }
    END_FOR_PIXELS
    return max;
}

template<class T>
float PixelGrid<T>::min() {
    float min = 0;
    FOR_PIXELS
        if ((*this)[r][c].i < min) {
            min = (*this)[r][c].i;
        }
    END_FOR_PIXELS
    return min;
}

template<class T>
float PixelGrid<T>::min_abs() {
    float min = 0;
    FOR_PIXELS
        float abs_val = abs((*this)[r][c].i);
        if (abs_val < min) {
            min = abs_val;
        }
    END_FOR_PIXELS
    return min;
}


PixelGrid<MonoPixel> ConvertToMonopixel(PixelGrid<RGBPixel> old) {
    PixelGrid<MonoPixel> pixel_grid = PixelGrid<MonoPixel>(old.rows, old.columns);
    FOR_PIXELS_IN_GRID(old)
        pixel_grid[r][c] = MonoPixel(old[r][c].i);
    END_FOR_PIXELS
    return pixel_grid;
}

bool operator==(const AnglePixel &lhs, const float rhs) {
    return (lhs.i == rhs);
}


template<class T>
PixelGrid<T> PixelGrid<T>::resize(int out_rows, int out_columns){
    PixelGrid<T> output = PixelGrid<T>(out_rows, out_columns);

    for (int r=0; r < out_rows; r++){
        for (int c=0; c < out_columns; c++){
            // Convert r,c into old style coordinates
            float r_real = (float)r / out_rows * rows;
            float c_real = (float)c / out_columns * columns;
            int r_0 = floor(r_real);
            int r_1 = ceil(r_real);
            int c_0 = floor(c_real);
            int c_1 = ceil(c_real);
            float r_d = r_real - r_0;
            float c_d = c_real - c_0;
            /*   tl--t------tr
             *   |   |      |
             *   |---p------|
             *   |   |      |
             *   |   |      |
             *   |   |      |
             *   bl--b------br  */
            float tl, tr, bl, br;
            tl = (*this)[r_0][c_0].i;
            tr = (*this)[r_0][c_1].i;
            bl = (*this)[r_1][c_0].i;
            br = (*this)[r_1][c_1].i;
            float t, b, p;
            t = tr + (tr - tl)*c_d;
            b = br + (br - bl)*c_d;
            p = b + (b - t)*r_d;
            output[r][c] = p;
            // r / rows * this->rows() same for cols
            // find the 4 vals adjacent and the distances from each
            // Do a weighted sum (possibly split into x and y separately)
            // Set output[r][c] = val;
        }
    }
    return output;
}





AnglePixel::AnglePixel() {
    i = 0;
}
AnglePixel::AnglePixel(float angle) {
    i = angle;
}

void AnglePixel::operator=(float intensity) {
    i = intensity;
}

void AnglePixel::operator+=(float intensity) {
    i += intensity;
}

AnglePixel::operator float() {
    return i;
}


template class PixelGrid<MonoPixel>;
template class PixelGrid<RGBPixel>;
template class PixelGrid<AnglePixel>;