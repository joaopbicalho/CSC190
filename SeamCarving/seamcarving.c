#include <stdlib.h>
#include <stdio.h>
#include "seamcarving.h"
#include <math.h>

void calc_energy(struct rgb_img *im, struct rgb_img **grad){
    int height = im->height;
    int width = im->width;
    create_img(grad, height, width);
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            int h_up = y + 1;
            int h_down = y - 1;
            int w_right = x + 1;
            int w_left = x - 1;

            if (h_up >= height) {
               h_up = 0;
            }if (h_down < 0){
                h_down = height -1;
            }if ( width <= w_right){
                w_right = 0;
            }if (w_left < 0){
                w_left = width - 1;
            }
            int test = get_pixel(im, y, x, 0);
            int R_x = get_pixel(im, y, w_right, 0) - get_pixel(im, y, w_left, 0);
            int G_x = get_pixel(im, y, w_right, 1) - get_pixel(im, y,  w_left, 1);
            int B_x = get_pixel(im, y, w_right, 2) - get_pixel(im, y, w_left, 2);
            int R_y = get_pixel(im, h_up, x, 0) - get_pixel(im, h_down, x, 0);
            int G_y = get_pixel(im, h_up, x, 1) - get_pixel(im, h_down, x, 1);
            int B_y = get_pixel(im, h_up, x, 2) - get_pixel(im, h_down, x, 2);
            
            int d2_x = pow(R_x, 2) + pow(G_x, 2) + pow(B_x, 2);
            int d2_y = pow(R_y, 2) + pow(G_y, 2) + pow(B_y, 2);
            int energy = sqrt(d2_x + d2_y);
            uint8_t energy_f = (uint8_t)(energy/10);
            set_pixel(*grad, y, x, energy_f, energy_f, energy_f);
        }
    }
}

double min(double x, double y, double z){
    double min1 = (x < y) ? x : y;
    return (min1 < z) ? min1 : z;
}

void dynamic_seam(struct rgb_img *grad, double **best_arr){
    int height = grad->height;
    int width = grad->width;
    *best_arr = (double *)malloc(height * width * (sizeof(double)));
    //(*best_arr)[0] =  get_pixel(grad, 0, 0, 0);
    //printf("%f\n", (*best_arr)[0]);
    double min_path, left, right, abv;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if (i == 0){
                (*best_arr)[j] = get_pixel(grad, 0, j, 0);
                //printf("%f\t", (*best_arr)[j]);
            }else{
                if (j == 0 ){
                    abv = (*best_arr)[(i-1)*width+j];
                    right = (*best_arr)[(i-1)*width+j+1];
                    min_path = (abv < right) ? abv : right;
                    //printf("\nmin_path = %f\n", min_path);
                    (*best_arr)[i*width+j] = get_pixel(grad, i, j, 0) + min_path;
                    //printf("%f\t", (*best_arr)[i*width+j]);
                }else if (j == width - 1){
                    abv = (*best_arr)[(i-1)*width+j];
                    left = (*best_arr)[(i-1)*width+j-1];
                    min_path = (abv < left) ? abv : left;
                    (*best_arr)[i*width+j] = get_pixel(grad, i, j, 0) + min_path;
                    //printf("%f\n", (*best_arr)[i*width+j]);
                }else{
                    abv = (*best_arr)[(i-1)*width+j];
                    left = (*best_arr)[(i-1)*width+j-1];
                    right = (*best_arr)[(i-1)*width+j+1];
                    min_path = min(abv, left, right);
                    (*best_arr)[i*width+j] = get_pixel(grad, i, j, 0) + min_path;
                    //printf("%f\t", (*best_arr)[i*width+j]);
                }
            }
            //printf("\n %f", (*best_arr[i*width+j]));
        }
    } 
}

void recover_path(double *best, int height, int width, int **path){
    int i = height - 1;
    *path = (int *)malloc(height * (sizeof(int)));
    int min_row_index = 0;
    int index_below;
    double left, right, up, min_dir;

    if (i == height - 1){
        for (int j = 0; j < width; j++){
            if (best[i*width+j] < best[i*width+(min_row_index)]){
                //printf("\t%f", best[i*width+j]);
                min_row_index = j;
                //printf("\tmin_row_index = %d", min_row_index);
            // }else if (best[i*width+j] >= best[i*width+(min_row_index)]){
            //     printf("\t%f", best[i*width+j]);
            //     printf("\tmin_row_index = %d", min_row_index);
            // }
            }if (j == width - 1){
                //printf("\t min_row index = %f", min_row_index);
                (*path)[i] = min_row_index;
                //printf("\t path = %d",(*path)[i]);
            }
        }
    }
    for (i = height -2; i >= 0 ; i--){ 
        index_below = (*path)[i+1];
        //printf("\n index below = %d", index_below);
        up = best[(i)*width+(index_below)];
        //printf("\n up = %f", up);
        left = best[(i)*width+(index_below)-1];
        //printf("\n left = %f", left);
        right = best[(i)*width+(index_below)+1];
        //printf("\n right = %f", right);
        min_dir = min(left, up, right);
        if (min_dir == up){
            min_row_index = index_below;
        }else if (min_dir == left){
            min_row_index = index_below - 1;
        }else if (min_dir == right){
            min_row_index = index_below + 1;
        }
        (*path)[i] = min_row_index;
    }
    // for (i=0; i<height; i++){
    //     printf("%d\t",(*path)[i]); 
    // }
}

void remove_seam(struct rgb_img *src, struct rgb_img **dest, int *path){
    int height = src->height;
    int width = src->width;
    create_img(dest, height, width-1);
    uint8_t p_g, p_b, p_r;
    int x_new = 0;
    for (int y = 0; y < height; y++){
        x_new = 0;
        for (int x = 0; x < width; x++){
            //printf("\n path at %d = %d", y, path[y]);
            if ((path)[y] != x){
                p_r = get_pixel(src, y, x, 0);
                p_g = get_pixel(src, y, x, 1);
                p_b = get_pixel(src, y, x, 2);
                set_pixel((*dest), y, x_new, p_r, p_g, p_b);
                x_new++;
            }
        }
    }
}

