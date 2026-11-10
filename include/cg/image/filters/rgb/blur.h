#ifndef CG_IMAGE_FILTERS_RGB_BLUR_H
#define CG_IMAGE_FILTERS_RGB_BLUR_H

#include "cg/image/color_properties/color.h"

rgb_color* pad_rgb_image_replicate_edge(rgb_color* img, int WIDTH, int HEIGHT);
rgb_color* blur_rgb_image(rgb_color* img, int WIDTH, int HEIGHT);

#endif