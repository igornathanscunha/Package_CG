#include <stdio.h>
#include <stdlib.h>
#include "cg/image/gray_image.h"

// Cria uma imagem Gray.
gray_image create_gray_image(int WIDTH, int HEIGHT, uint8_t TYPE, uint8_t CMAX)
{
    return (gray_image){
        WIDTH, HEIGHT, TYPE, CMAX,
        NULL
    };
}

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