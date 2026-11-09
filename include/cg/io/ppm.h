#ifndef CG_IO_PPM_H
#define CG_IO_PPM_H

#include <stdio.h>
#include <stdint.h>
#include "cg/image/rgb_image.h"

void clear_comments(FILE* file);
void extract_properties_rgb_image(FILE* fp, rgb_image* img);
FILE* open_archive_ppm(const char* name);
FILE* writing_archive_ppm(const char* name);
void load_image_in_matrix_rgb_color(FILE* fp, rgb_color* pixels, int WIDTH, int HEIGHT, uint8_t TYPE_IMG);
void generate_rgb_image_ppm(FILE* fp, rgb_color* pixels, int WIDTH, int HEIGHT, uint8_t TYPE_IMG, uint8_t CMAX);

#endif