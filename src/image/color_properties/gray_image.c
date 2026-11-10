#include <stdio.h>
#include <stdlib.h>
#include "cg/image/color_properties/gray_image.h"

// Aloca um vetor linear para armazenar os pixels de uma imagem em tons de cinza.
gray_color* create_a_matrix_from_an_gray_color(int WIDTH, int HEIGHT)
{
    gray_color* pixels = malloc(WIDTH * HEIGHT * sizeof(gray_color));
    if (!pixels)
    {
        perror("Erro de alocacao de memoria, matriz preto e branco nao criada!\n");
        exit(0);
    }
    return pixels;
}

void coverte_rgb_color_in_gray_color(rgb_color* rgb, gray_color* gray, int WIDTH, int HEIGHT)
{
    for (int j = 0; j < HEIGHT; j++)
    {
        for (int i = 0; i < WIDTH; i++)
        {
            gray[j * WIDTH + i].scale = 0.2126 * rgb[j * WIDTH + i].r +
            0.7152 * rgb[j * WIDTH + i].g + 0.0722 * rgb[j * WIDTH + i].b;
        }
    }
    
}

void initialize_gray_pixels_is_black(gray_color* pixels, int WIDTH, int HEIGHT)
{
    // Inicializa o quadro de destino em preto para as areas sem pixels mapeados.
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            pixels[i * WIDTH + j] = (gray_color){0};
}

void copy_matrix_gray_color(gray_color* copy,  gray_color* paste, int WIDTH, int HEIGHT)
{
    // Copia os pixels e assume ownership da matriz temporaria, que e liberada aqui.
    for (int j = 0; j < HEIGHT; j++)
        for (int i = 0; i < WIDTH; i++)
            paste[j * WIDTH + i] = copy[j * WIDTH + i];
    free(copy);
}

