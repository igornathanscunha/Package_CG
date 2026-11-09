#include <stdio.h>
#include <stdlib.h>
#include "cg/image/rgb_image.h"

// Cria uma imagem RGB e aloca a memoria necessaria para seus pixels.
rgb_image create_rgb_image(int WIDTH, int HEIGHT, uint8_t TYPE, uint8_t CMAX)
{
    return (rgb_image){
        WIDTH, HEIGHT, TYPE, CMAX,
        create_a_matrix_from_an_rgb_color(WIDTH, HEIGHT)
    };
}

// Aloca um vetor linear com espaco para WIDTH * HEIGHT pixels RGB.
rgb_color* create_a_matrix_from_an_rgb_color(int WIDTH, int HEIGHT)
{
    rgb_color* pixels = malloc(WIDTH * HEIGHT * sizeof(rgb_color));
    if (!pixels)
    {
        perror("Erro de alocacao de memoria, matriz rgb nao criada!\n");
        exit(0);
    }
    return pixels;
}

void initialize_rgb_pixels_is_black(rgb_color* pixels, int WIDTH, int HEIGHT)
{
    // Inicializa o quadro de destino em preto para as areas sem pixels mapeados.
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            pixels[i * WIDTH + j] = (rgb_color){0,0,0};
}

void copy_matrix_rgb_color(rgb_color* copy, rgb_color* paste, int WIDTH, int HEIGHT)
{
    // Copia os pixels e assume ownership da matriz temporaria, que e liberada aqui.
    for (int j = 0; j < HEIGHT; j++)
        for (int i = 0; i < WIDTH; i++)
            paste[j * WIDTH + i] = copy[j * WIDTH + i];
    free(copy);
}