#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Pixel{
	float r;
	float g;
	float b;
	Pixel(){
		r = 0;
		g = 0;
		b = 0;
	}
	Pixel(float r, float g, float b){
		this->r = r;
		this->g = g;
		this->b = b;
	}
};

class PixelGrid {
	int height, width;
	Pixel* pixels;
	public:
		PixelGrid(int h, int w){
			height = h;
			width = w;
			pixels = new Pixel[h*w];
		}
	Pixel* operator[](int i){
		return &pixels[i*width];
	}
};

int main() {
	char* filename;
	string magic, meta;
	int h, w;
	cin >> filename;
	ifstream file;
	file.open(filename, ifstream::in);
	getline(file, magic);
	getline(file, meta);
	file >> h >> w;
	cout << magic << endl;
	cout << meta << endl;
	cout << h << ' ' << w << endl;
	PixelGrid image(h,w);
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			float r, g, b;
			file >> r >> g >> b;
			cout << (int)r*2 << ' ' << (int)g << ' ' << (int)b/5 << "  ";
			Pixel pixel(r, g, b);
			image[i][j] = pixel;
		} 
		
		cout << endl;
	}
}
