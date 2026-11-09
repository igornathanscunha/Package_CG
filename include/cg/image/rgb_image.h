#ifndef CG_IMAGE_RGB_IMAGE_H
#define CG_IMAGE_RGB_IMAGE_H

#include <stdint.h>
#include "cg/color.h"

// Representa uma imagem RGB armazenada em um vetor linear de pixels.
typedef struct rgb_image
{
    unsigned int WIDTH;
    unsigned int HEIGHT;
    uint8_t TYPE_IMG;
    uint8_t CMAX;
    rgb_color* pixels;
}rgb_image;

rgb_image create_rgb_image(int WIDTH, int HEIGHT, uint8_t TYPE, uint8_t CMAX);
rgb_color* create_a_matrix_from_an_rgb_color(int WIDTH, int HEIGHT);
// rgb_color* draw_border_rgb_image(rgb_color* img, int WIDTH, int HEIGHT);
void initialize_rgb_pixels_is_black(rgb_color* pixels, int WIDTH, int HEIGHT);
void copy_matrix_rgb_color(rgb_color* copy, rgb_color* paste, int WIDTH, int HEIGHT);

#endif