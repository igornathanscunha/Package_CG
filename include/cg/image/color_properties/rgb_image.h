#ifndef CG_IMAGE_RGB_IMAGE_H
#define CG_IMAGE_RGB_IMAGE_H

#include <stdint.h>
#include "color.h"

rgb_color* create_a_matrix_from_an_rgb_color(int WIDTH, int HEIGHT);
void initialize_rgb_pixels_is_black(rgb_color* pixels, int WIDTH, int HEIGHT);
void copy_matrix_rgb_color(rgb_color* copy, rgb_color* paste, int WIDTH, int HEIGHT);

#endif