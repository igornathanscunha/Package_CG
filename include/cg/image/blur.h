#ifndef CG_IMAGE_BLUR_H
#define CG_IMAGE_BLUR_H

#include "cg/color.h"

rgb_color* pad_rgb_image_replicate_edge(rgb_color* img, int WIDTH, int HEIGHT);
rgb_color* blur_rgb_image(rgb_color* img, int WIDTH, int HEIGHT);
rgb_color average_of_nine_pixel(int x_i, int y_i, rgb_color* img, int WIDTH);

#endif