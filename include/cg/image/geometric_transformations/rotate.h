#ifndef CG_IMAGE_ROTATE_H
#define CG_IMAGE_ROTATE_H

#include <stdbool.h>
#include "cg/image/color_properties/color.h"

void rotate_inverse_rgb_image_validate(rgb_color* rotate_image, rgb_color* pixels, int WIDTH, int HEIGHT, int angle);
rgb_color* rotate_rgb_image(rgb_color* pixels, int WIDTH, int HEIGHT, int angle, bool shearing);

#endif