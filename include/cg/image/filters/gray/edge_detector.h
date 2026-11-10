#ifndef CG_IMAGE_FILTERS_GRAY_EDGE_DETECTOR_H
#define CG_IMAGE_FILTERS_GRAY_EDGE_DETECTOR_H

#include "cg/image/color_properties/gray_image.h"

gray_color* edges_detector_gray_image(gray_color* img, gray_color* blur, int WIDTH, int HEIGHT);

#endif