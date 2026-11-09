#ifndef CG_IMAGE_GRAY_IMAGE_H
#define CG_IMAGE_GRAY_IMAGE_H

#include "cg/color.h"

// Representa uma imagem em tons de cinza; cada pixel armazena um nivel.
typedef struct gray_image
{
    int WIDTH;
    int HEIGHT;
    uint8_t TYPE_IMG;
    uint8_t CMAX;
    gray_color* pixels;
}gray_image;

gray_image create_gray_image(int WIDTH, int HEIGHT, uint8_t TYPE, uint8_t CMAX);
gray_color* create_a_matrix_from_an_gray_color(int WIDTH, int HEIGHT);
void coverte_rgb_color_in_gray_color(rgb_color* rgb, gray_color* gray, int WIDTH, int HEIGHT);

#endif