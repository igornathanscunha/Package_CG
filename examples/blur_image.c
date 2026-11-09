#include <stdio.h>
#include <stdlib.h>
#include "cg/image/blur.h"
#include "cg/image/rgb_image.h"
#include "cg/io/ppm.h"

int main (int argc, char**argv){

    if (argc != 3)
    {
        fprintf(stderr, "Uso: %s <imagem_entrada.ppm> <int value blur> (saida: blur.ppm)\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE* file;
    rgb_image image;

    file = open_archive_ppm(argv[1]);
    extract_properties_rgb_image(file, &image);
    // Reserva memoria para os pixels e carrega os dados da imagem.
    image.pixels = create_a_matrix_from_an_rgb_color(image.WIDTH, image.HEIGHT);
    load_image_in_matrix_rgb_color(
        file, image.pixels,
        image.WIDTH, image.HEIGHT, image.TYPE_IMG
    );

    rgb_color* blur;
    // Cada iteracao aplica mais uma passagem do filtro 3x3; nao altera o raio da janela.
    int intensity = atoi(argv[2]);

    while (intensity > 0)
    {
        // Calcula uma nova imagem borrada e copia o resultado para a imagem de trabalho.
        blur = blur_rgb_image(
            image.pixels, image.WIDTH, image.HEIGHT
        );
        copy_matrix_rgb_color(
            blur, image.pixels,
            image.WIDTH, image.HEIGHT
        );
        intensity--;
    }
    // A imagem final mantem as dimensoes e os metadados da imagem de entrada.
    file = writing_archive_ppm("blur.ppm");
    generate_rgb_image_ppm(
        file, image.pixels,
        image.WIDTH, image.HEIGHT,
        image.TYPE_IMG, image.CMAX
    );

    return 0;
}