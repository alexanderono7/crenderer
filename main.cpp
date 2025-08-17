#include "tgaimage.h"
#include <cstdio>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor blue  = TGAColor(0, 0,   255,   255);

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
	bool steep = false;
    // if the line we are drawing is too steep, then temporarily transpose the image
    if(std::abs(x0-x1) < std::abs(y0-y1)){
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }

    // make it left-to-right if it is not 
    if (x0 > x1) { 
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dx = x1-x0;
    int dy = y1-y0;
    float derror = std::abs(dy/float(dx));
    float error = 0;
    int y = y0;

    for (int x=x0; x<=x1; x++) {
        if (steep) {
            image.set(y, x, color);
        } else {
            image.set(x, y, color);
        }
        error += derror;
        if (error > .5) {
            y += (y1>y0 ? 1:-1);
            error -= 1.;
        }
    }
}

int main(int argc, char** argv) {
    //creation of new image object, completely black
	TGAImage image(100, 100, TGAImage::RGB);
    //set random pixel to be red
	image.set(52, 41, red);

    // draw line
    line(0, 0, 25, 80, image, blue);
    line(0, 0, 80, 25, image, red);
    line(5, 5, 5, 50, image, blue);
	image.flip_vertically(); // i want to have the origin (0,0) at the left bottom corner of the image
	image.write_tga_file("output1.tga");
	return 0;
}

