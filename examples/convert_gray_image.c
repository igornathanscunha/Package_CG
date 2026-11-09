#include <stdio.h>
#include <stdlib.h>
#include "cg/image/gray_image.h"
#include "cg/io/ppm.h"

int main (int argc, char** argv)
{
    FILE* file;
    rgb_image image;

    file = open_archive_ppm(argv[1]);
    image = extract_properties_rgb_image(file);
    // Reserva memoria para os pixels e carrega os dados da imagem.
    image.pixels = create_a_matrix_from_an_rgb_color(image.WIDTH, image.HEIGHT);
    load_image_in_matrix_rgb_color(
        file, image.pixels,
        image.WIDTH, image.HEIGHT, image.TYPE_IMG
    );
    fclose(file);

    gray_color* image_gray = create_a_matrix_from_an_gray_color(
        image.WIDTH, image.HEIGHT
    );
    coverte_rgb_color_in_gray_color(
        image.pixels, image_gray,
        image.WIDTH, image.HEIGHT
    );

    file = writing_archive_ppm("gray.ppm");
    generate_gray_image_ppm(
        file, image_gray,
        image.WIDTH, image.HEIGHT,
        2, image.CMAX
    );

    free(image.pixels);
    free(image_gray);
    fclose(file);
    return 0;
}