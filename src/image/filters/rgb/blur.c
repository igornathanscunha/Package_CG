#include <stdlib.h>
#include "cg/image/filters/rgb/blur.h"
#include "cg/image/color_properties/rgb_image.h"

static rgb_color average_of_nine_pixel(int x_i, int y_i, rgb_color* img, int WIDTH);

// Acrescenta uma camada que replica os pixels das bordas para a janela 3x3.
rgb_color* pad_rgb_image_replicate_edge(rgb_color* img, int WIDTH, int HEIGHT)
{
    // A camada extra permite ler vizinhos mesmo nos pixels do contorno.
    int WIDTH_B = WIDTH + 2;
    int HEIGHT_B = HEIGHT + 2;
    rgb_color* border_img = create_a_matrix_from_an_rgb_color(
        WIDTH_B,
        HEIGHT_B
    );

    for (int j = 0; j < HEIGHT_B; j++)
    {
        for (int i = 0; i < WIDTH_B; i++)
        {
            int source_x = i == 0 ? 0 : (i == WIDTH_B - 1 ? WIDTH - 1 : i - 1);
            int source_y = j == 0 ? 0 : (j == HEIGHT_B - 1 ? HEIGHT - 1 : j - 1);
            border_img[j * WIDTH_B + i] = img[source_y * WIDTH + source_x];
        }
    }
    return border_img;
}

// Executa uma passagem do filtro de media 3x3 e devolve uma nova matriz.
rgb_color* blur_rgb_image(rgb_color* img, int WIDTH, int HEIGHT)
{
    rgb_color* border = pad_rgb_image_replicate_edge(
        img, WIDTH, HEIGHT
    );
    rgb_color* blur = create_a_matrix_from_an_rgb_color(
        WIDTH, HEIGHT
    );

    // O centro da janela corresponde ao pixel original deslocado pela camada extra.
    for (int j = 0; j < HEIGHT; j++)
    {
        for (int i = 0; i < WIDTH; i++)
        {
            blur[j * WIDTH + i] = average_of_nine_pixel(i, j, border, WIDTH + 2);
        }
    }
    free(border);
    return blur;
}

// Calcula a media independente dos canais RGB na vizinhanca 3x3 do pixel.
static rgb_color average_of_nine_pixel(int x_i, int y_i, rgb_color* img, int WIDTH)
{
    // A coordenada (x_i, y_i) aponta para o pixel central na imagem sem padding.
    int x = x_i + 1;
    int y = y_i + 1;
    unsigned int sum_r = 0;
    unsigned int sum_g = 0;
    unsigned int sum_b = 0;
    for (int j = -1; j <= 1; j++)
        for (int i = -1; i <= 1; i++)
        {
            sum_r += img[(y+j) * WIDTH + (x+i)].r;
            sum_g += img[(y+j) * WIDTH + (x+i)].g;
            sum_b += img[(y+j) * WIDTH + (x+i)].b;
        }
    uint8_t average_r = sum_r / 9;
    uint8_t average_g = sum_g / 9;
    uint8_t average_b = sum_b / 9;
    return (rgb_color){average_r, average_g, average_b};
}

