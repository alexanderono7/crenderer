#include "tgaimage.h"
#include "model.h"
#include "geometry.h"
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
    int derror2 = std::abs(dy)*2;
    int error2 = 0;
    int y = y0;

    for (int x=x0; x<=x1; x++) {
        if (steep) {
            image.set(y, x, color);
        } else {
            image.set(x, y, color);
        }
        error2 += derror2;
        if (error2 > dx) {
            y += (y1>y0 ? 1:-1);
            error2 -= dx*2;
        }
    }
}

int main(int argc, char** argv) {
    //creation of new image object, completely black
	//TGAImage image(100, 100, TGAImage::RGB);
    //set random pixel to be red
	//image.set(52, 41, red);
    // Model object creation
    //Model *model = new Model("alksdjflskjd");
    int width = 1000;
    int height = 1000;

    // draw line
    //line(5, 5, 5, 50, image, blue);

    // Draw wireframe model
    Model *model = new Model("obj/african_head.obj");
	TGAImage image(width, height, TGAImage::RGB);
    printf("%d",model->nfaces());
    for (int i = 0; i < model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        for (int j=0; j<3; j++) {
            Vec3f v0 = model->vert(face[j]);
            Vec3f v1 = model->vert(face[(j+1)%3]);
            int x0 = (v0.x+1.)*width/2.;
            int y0 = (v0.y+1.)*height/2.;
            int x1 = (v1.x+1.)*width/2.;
            int y1 = (v1.y+1.)*height/2.;
            line(x0, y0, x1, y1, image, white);
        }
    }

	image.flip_vertically(); // i want to have the origin (0,0) at the left bottom corner of the image
	image.write_tga_file("output1.tga");
    delete model;
	return 0;
}

