#include "c_img.h"
#include <stdio.h>
#include <math.h>

//#include "UofTPresidentMericGertler.bin"

void create_img(struct rgb_img **im, size_t height, size_t width){
    *im = (struct rgb_img *)malloc(sizeof(struct rgb_img));
    (*im)->height = height;
    (*im)->width = width;
    (*im)->raster = (uint8_t *)malloc(3 * height * width);
}


int read_2bytes(FILE *fp){
    uint8_t bytes[2];
    fread(bytes, sizeof(uint8_t), 1, fp);
    fread(bytes+1, sizeof(uint8_t), 1, fp);
    return (  ((int)bytes[0]) << 8)  + (int)bytes[1];
}

void write_2bytes(FILE *fp, int num){
    uint8_t bytes[2];
    bytes[0] = (uint8_t)((num & 0XFFFF) >> 8);
    bytes[1] = (uint8_t)(num & 0XFF);
    fwrite(bytes, 1, 1, fp);
    fwrite(bytes+1, 1, 1, fp);
}

void read_in_img(struct rgb_img **im, char *filename){
    FILE *fp = fopen(filename, "rb");
    size_t height = read_2bytes(fp);
    size_t width = read_2bytes(fp);
    create_img(im, height, width);
    fread((*im)->raster, 1, 3*width*height, fp);
    fclose(fp);
}

void write_img(struct rgb_img *im, char *filename){
    FILE *fp = fopen(filename, "wb");
    write_2bytes(fp, im->height);
    write_2bytes(fp, im->width);
    fwrite(im->raster, 1, im->height * im->width * 3, fp);
    fclose(fp);
}

uint8_t get_pixel(struct rgb_img *im, int y, int x, int col){
    return im->raster[3 * (y*(im->width) + x) + col];
}

void set_pixel(struct rgb_img *im, int y, int x, int r, int g, int b){
    im->raster[3 * (y*(im->width) + x) + 0] = r;
    im->raster[3 * (y*(im->width) + x) + 1] = g;
    im->raster[3 * (y*(im->width) + x) + 2] = b;
}

void destroy_image(struct rgb_img *im)
{
    free(im->raster);
    free(im);
}


void print_grad(struct rgb_img *grad){
    int height = grad->height;
    int width = grad->width;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            printf("%d\t", get_pixel(grad, i, j, 0));
        }
    printf("\n");    
    }
}

void change_colour(struct rgb_img *im, double mult){
    uint8_t num1;
    uint8_t num2;
    uint8_t num3;
    for(int i = 0; i < im->width; i++){
        for(int j = 0; j < im->height; j++){
            num1 = get_pixel(im, j, i, 0);
            num2 = get_pixel(im, j, i, 1);
            num3 = get_pixel(im, j, i, 2);
            num1 = (((double)num1*mult) > 255)? 255 : (int8_t)(num1*mult);
            num2 = (((double)num2*mult/2) > 255)? 255 : (int8_t)(num2*mult);
            num3 = (((double)num3*mult/3) > 255)? 255 : (int8_t)(num3*mult);
            set_pixel(im, j, i, num1, num2, num3); 
        }
    }
}

int main(){
    // struct rbg_img *im;
    // read_in_img(&im, "UofTPresidentMericGertler.bin");
    // change_colour(im, 1.9);
    // char filename[200];
    // sprintf(filename, "img3.bin", 2);
    // write_img(im, filename);

    return 0;
}
