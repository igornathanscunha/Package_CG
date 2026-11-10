#include <stdio.h>
#include <stdlib.h>
#include "cg/image/color_properties/gray_image.h"
#include "cg/image/image_type/ppm.h"
#include "cg/image/image_properties.h"

int main (int argc, char** argv)
{
    FILE* file;
    image_properties image;

    file = open_archive_ppm(argv[1]);
    image = extract_properties_image(file);
    // Reserva memoria para os pixels e carrega os dados da imagem.
    rgb_color* pixels = create_a_matrix_from_an_rgb_color(image.WIDTH, image.HEIGHT);
    load_image_in_matrix_rgb_color(
        file, pixels,
        image.WIDTH, image.HEIGHT, image.TYPE_IMG
    );
    fclose(file);

    gray_color* pixels_gray = create_a_matrix_from_an_gray_color(
        image.WIDTH, image.HEIGHT
    );
    coverte_rgb_color_in_gray_color(
        pixels, pixels_gray,
        image.WIDTH, image.HEIGHT
    );

    file = writing_archive_ppm("gray.ppm");
    generate_gray_image_ppm(
        file, pixels_gray,
        image.WIDTH, image.HEIGHT,
        2, image.CMAX
    );

    free(pixels);
    free(pixels_gray);
    fclose(file);
    return 0;
}