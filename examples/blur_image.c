#include <stdio.h>
#include <stdlib.h>
#include "cg/image/filters/rgb/blur.h"
#include "cg/image/filters/gray/blur.h"
#include "cg/image/color_properties/rgb_image.h"
#include "cg/image/color_properties/gray_image.h"
#include "cg/image/image_properties.h"
#include "cg/image/image_type/ppm.h"

int main (int argc, char**argv){

    if (argc != 3)
    {
        fprintf(stderr, "Uso: %s <imagem_entrada.ppm> <int value blur> (saida: blur.ppm)\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE* file;
    image_properties image;

    file = open_archive_ppm(argv[1]);
    image = extract_properties_image(file);
    if (image.TYPE_IMG == 2 || image.TYPE_IMG == 5)
    {
        gray_color* pixels = create_a_matrix_from_an_gray_color(
            image.WIDTH, image.HEIGHT
        );
        load_image_in_matrix_gray_color(
            file, pixels,
            image.WIDTH, image.HEIGHT, image.TYPE_IMG
        );
        fclose(file);

        gray_color* blur;

        int intensity = atoi(argv[2]);

        while (intensity > 0)
        {
            blur = blur_gray_image(
                pixels, image.WIDTH, image.HEIGHT
            );
            copy_matrix_gray_color(
                blur, pixels,
                image.WIDTH, image.HEIGHT
            );
            intensity--;
        }

        file = writing_archive_ppm("blur_gray.ppm");
        generate_gray_image_ppm(
            file, pixels,
            image.WIDTH, image.HEIGHT,
            image.TYPE_IMG, image.CMAX
        );
        free(pixels);
    }

    if (image.TYPE_IMG == 3 || image.TYPE_IMG == 6)
    {
        // Reserva memoria para os pixels e carrega os dados da imagem.
        rgb_color* pixels = create_a_matrix_from_an_rgb_color(
            image.WIDTH, image.HEIGHT
        );
        load_image_in_matrix_rgb_color(
            file, pixels,
            image.WIDTH, image.HEIGHT, image.TYPE_IMG
        );
        fclose(file);
    
        rgb_color* blur;
        // Cada iteracao aplica mais uma passagem do filtro 3x3; nao altera o raio da janela.
        int intensity = atoi(argv[2]);
    
        while (intensity > 0)
        {
            // Calcula uma nova imagem borrada e copia o resultado para a imagem de trabalho.
            blur = blur_rgb_image(
                pixels, image.WIDTH, image.HEIGHT
            );
            copy_matrix_rgb_color(
                blur, pixels,
                image.WIDTH, image.HEIGHT
            );
            intensity--;
        }
        // A imagem final mantem as dimensoes e os metadados da imagem de entrada.
        file = writing_archive_ppm("blur_rgb.ppm");
        generate_rgb_image_ppm(
            file, pixels,
            image.WIDTH, image.HEIGHT,
            image.TYPE_IMG, image.CMAX
        );
        free(pixels);
    }
    
    fclose(file);
    return 0;
}