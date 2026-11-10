#include <stdio.h>
#include <stdlib.h>
#include "cg/image/geometric_transformations/rotate.h"
#include "cg/image/color_properties/rgb_image.h"
#include "cg/image/image_type/ppm.h"
#include "cg/image/image_properties.h"


int main (int argc, char **argv)
{
    // O primeiro argumento identifica a imagem de entrada; o segundo, a de saida.
    FILE* file;
    image_properties image;

    // Le o cabecalho PPM, ignorando comentarios antes dos campos.
    file = fopen(argv[1], "r");
    clear_comments(file);
    fscanf(file, "P%hhu\n", &image.TYPE_IMG);
    clear_comments(file);
    fscanf(file, "%u %u\n%hhu\n", &image.WIDTH, &image.HEIGHT, &image.CMAX);

    // Reserva memoria para os pixels e carrega os dados.
    rgb_color* pixels = create_a_matrix_from_an_rgb_color(image.WIDTH, image.HEIGHT);
    load_image_in_matrix_rgb_color(
        file, pixels,
        image.WIDTH, image.HEIGHT, image.TYPE_IMG
    );
    fclose(file);

    rgb_color* rotate_img;
    // Angulo em graus; false usa a matriz de rotacao e true usa cisalhamento.
    int angle = 30;

    // Grava a imagem com os mesmos dados e dimensoes da entrada.
    file = fopen(argv[2], "w");
    rotate_img = rotate_rgb_image(
        pixels, image.WIDTH, image.HEIGHT, angle, false
    );

    generate_rgb_image_ppm(
        file, rotate_img,
        image.WIDTH * 2, image.HEIGHT * 2,
        image.TYPE_IMG, image.CMAX
    );
    fclose(file);


    // Libera a matriz alocada para armazenar os pixels.
    free(pixels);
    free(rotate_img);
    return 0;
}