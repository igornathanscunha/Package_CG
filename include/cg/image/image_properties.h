#ifndef CG_IMAGE_PROPERTIES_H
#define CG_IMAGE_PROPERTIES_H

#include <stdio.h>
#include <stdint.h>
#include "cg/image/color_properties/color.h"
#include "cg/image/image_type/ppm.h"

// Representa uma imagem RGB armazenada em um vetor linear de pixels.
typedef struct image_properties
{
    unsigned int WIDTH;
    unsigned int HEIGHT;
    uint8_t TYPE_IMG;
    uint8_t CMAX;
}image_properties;

image_properties create_image_properties(unsigned int WIDTH, unsigned int HEIGHT, uint8_t TYPE_IMG, uint8_t CMAX);
image_properties extract_properties_image(FILE* fp);
void clear_comments(FILE* file);

#endif