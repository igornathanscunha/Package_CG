#include <stdio.h>
#include <stdlib.h>
#include "cg/image/image_properties.h"
#include "cg/image/image_type/ppm.h"
#include "cg/image/filters/gray/edge_detector.h"

int main (int argc, char** argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Uso: %s <imagem_original.pgm> <imagem_borrada.pgm>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE* file;
    file = open_archive_ppm(argv[1]);
    image_properties image = extract_properties_image(file);

    if (image.TYPE_IMG != 2 && image.TYPE_IMG != 5)
    {
        fprintf(stderr, "A imagem original precisa estar em formato P2 ou P5.\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    gray_color* pixels = create_a_matrix_from_an_gray_color(image.WIDTH, image.HEIGHT);
    load_image_in_matrix_gray_color(
        file, pixels,
        image.WIDTH, image.HEIGHT,
        image.TYPE_IMG
    );
    fclose(file);

    file = open_archive_ppm(argv[2]);
    image_properties blur_properties = extract_properties_image(file);
    if (blur_properties.WIDTH != image.WIDTH ||
        blur_properties.HEIGHT != image.HEIGHT ||
        (blur_properties.TYPE_IMG != 2 && blur_properties.TYPE_IMG != 5))
    {
        fprintf(stderr, "A imagem borrada deve ser P2 ou P5 e ter as mesmas dimensoes da original.\n");
        fclose(file);
        free(pixels);
        return EXIT_FAILURE;
    }

    gray_color* blur = create_a_matrix_from_an_gray_color(
        blur_properties.WIDTH, blur_properties.HEIGHT
    );
    load_image_in_matrix_gray_color(
        file, blur,
        blur_properties.WIDTH, blur_properties.HEIGHT,
        blur_properties.TYPE_IMG
    );
    fclose(file);

    // Edges detector
    gray_color* edges = edges_detector_gray_image(
        pixels, blur,
        image.WIDTH, image.HEIGHT
    );

    // create image
    file = writing_archive_ppm("edges.ppm");
    generate_gray_image_ppm(
        file, edges,
        image.WIDTH, image.HEIGHT,
        image.TYPE_IMG, image.CMAX
    );

    free(pixels);
    free(blur);
    free(edges);
    fclose(file);
    return 0;
}