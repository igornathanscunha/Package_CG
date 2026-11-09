#include <stdio.h>
#include <stdlib.h>
#include "cg/image/gray_image.h"

// Aloca um vetor linear para armazenar os pixels de uma imagem em tons de cinza.
gray_color* create_a_matrix_from_an_gray_color(int WIDTH, int HEIGHT)
{
    gray_color* pixels = malloc(WIDTH * HEIGHT * sizeof(rgb_color));
    if (!pixels)
    {
        perror("Erro de alocacao de memoria, matriz preto e branco nao criada!\n");
        exit(0);
    }
    return pixels;
}