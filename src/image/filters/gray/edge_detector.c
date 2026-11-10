#include <stdlib.h>
#include "cg/image/filters/gray/edge_detector.h"

gray_color* edges_detector_gray_image(gray_color* img, gray_color* blur, int WIDTH, int HEIGHT)
{
    gray_color* edges = create_a_matrix_from_an_gray_color(
        WIDTH, HEIGHT
    );
    for (int j = 0; j < HEIGHT; j++)
    {
        for (int i = 0; i < WIDTH; i++)
        {
            int result = (int)img[j * WIDTH + i].scale - (int)blur[j * WIDTH + i].scale;
            edges[j * WIDTH + i].scale = (uint8_t)abs(result);
        }
    }
    return edges;
}

