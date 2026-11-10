#include <stdlib.h>
#include "cg/image/filters/gray/blur.h"
#include "cg/image/color_properties/gray_image.h"

static gray_color average_of_nine_pixel(int x_i, int y_i, gray_color* img, int WIDTH);

// Acrescenta uma camada que replica os pixels das bordas para a janela 3x3.
gray_color* pad_gray_image_replicate_edge(gray_color* img, int WIDTH, int HEIGHT)
{
    // A camada extra permite ler vizinhos mesmo nos pixels do contorno.
    int WIDTH_B = WIDTH + 2;
    int HEIGHT_B = HEIGHT + 2;
    gray_color* border_img = create_a_matrix_from_an_gray_color(
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
gray_color* blur_gray_image(gray_color* img, int WIDTH, int HEIGHT)
{
    gray_color* border = pad_gray_image_replicate_edge(
        img, WIDTH, HEIGHT
    );
    gray_color* blur = create_a_matrix_from_an_gray_color(
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
static gray_color average_of_nine_pixel(int x_i, int y_i, gray_color* img, int WIDTH)
{
    // A coordenada (x_i, y_i) aponta para o pixel central na imagem sem padding.
    int x = x_i + 1;
    int y = y_i + 1;
    unsigned int sum = 0;
    for (int j = -1; j <= 1; j++)
        for (int i = -1; i <= 1; i++)
        {
            sum += img[(y+j) * WIDTH + (x+i)].scale;
        }
    uint8_t average = sum / 9;
    return (gray_color){average};
}
