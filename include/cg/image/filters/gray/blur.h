#ifndef CG_IMAGE_FILTERS_GRAY_BLUR_H
#define CG_IMAGE_FILTERS_GRAY_BLUR_H

#include "cg/image/color_properties/color.h"

gray_color* pad_gray_image_replicate_edge(gray_color* img, int WIDTH, int HEIGHT);
gray_color* blur_gray_image(gray_color* img, int WIDTH, int HEIGHT);

#endif