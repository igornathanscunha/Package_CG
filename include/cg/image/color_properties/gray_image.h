#ifndef CG_IMAGE_GRAY_IMAGE_H
#define CG_IMAGE_GRAY_IMAGE_H

#include "color.h"

gray_color* create_a_matrix_from_an_gray_color(int WIDTH, int HEIGHT);
void coverte_rgb_color_in_gray_color(rgb_color* rgb, gray_color* gray, int WIDTH, int HEIGHT);
void initialize_gray_pixels_is_black(gray_color* pixels, int WIDTH, int HEIGHT);
void copy_matrix_gray_color(gray_color* copy,  gray_color* paste, int WIDTH, int HEIGHT);

#endif