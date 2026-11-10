#include "cg/image/geometric_transformations/rotate.h"
#include "cg/image/color_properties/rgb_image.h"
#include "cg/geometry/geometric_transformations/rotation2d.h"

void rotate_inverse_rgb_image_validate(rgb_color* rotate_image, rgb_color* pixels, int WIDTH, int HEIGHT, int angle)
{
    int WIDTH_RI = WIDTH * 2;
    int HEIGHT_RI = HEIGHT * 2;
    int center_x = WIDTH / 2;
    int center_y = HEIGHT / 2;
    int center_ri_x = WIDTH_RI / 2;
    int center_ri_y = HEIGHT_RI / 2;

    double radians = degrees_to_radians(angle);

    // Para cada pixel de destino, procura a coordenada correspondente na imagem original.
    for (int j = 0; j < HEIGHT_RI; j++)
    {
        for (int i = 0; i < WIDTH_RI; i++)
        {
            point_2d point = rotate_inverse_plan_2d(
                i - center_ri_x, j - center_ri_y, radians
            );
            int x = point.x + center_x;
            int y = point.y + center_y;

            if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
                continue;

            rotate_image[j * (WIDTH_RI) + i].r = pixels[y * WIDTH + x].r;
            rotate_image[j * (WIDTH_RI) + i].g = pixels[y * WIDTH + x].g;
            rotate_image[j * (WIDTH_RI) + i].b = pixels[y * WIDTH + x].b;
        }
    }
}

// Rotaciona em torno do centro e escolhe a transformacao pelo parametro shearing.
rgb_color* rotate_rgb_image(rgb_color* pixels, int WIDTH, int HEIGHT, int angle, bool shearing)
{
    int WIDTH_RI = WIDTH * 2;
    int HEIGHT_RI = HEIGHT * 2;
    rgb_color* rotate_image = create_a_matrix_from_an_rgb_color(WIDTH_RI, HEIGHT_RI);
    initialize_rgb_pixels_is_black(rotate_image, WIDTH_RI, HEIGHT_RI);
    int center_x = WIDTH / 2;
    int center_y = HEIGHT / 2;
    int center_ri_x = WIDTH_RI / 2;
    int center_ri_y = HEIGHT_RI / 2;

    if(!shearing)
    {
        double radians = degrees_to_radians(angle);

        // A transformacao direta leva os pixels de origem para o quadro ampliado.
        for (int j = 0; j < HEIGHT; j++)
        {
            for (int i = 0; i < WIDTH; i++)
            {
                point_2d point = rotate_plan_2d(
                    i - center_x, j - center_y, radians
                );
                int x_ri = point.x + center_ri_x;
                int y_ri = point.y + center_ri_y;

                if (x_ri < 0 || x_ri >= WIDTH_RI || y_ri < 0 || y_ri >= HEIGHT_RI)
                    continue;

                rotate_image[y_ri * (WIDTH_RI) + x_ri].r = pixels[j * WIDTH + i].r;
                rotate_image[y_ri * (WIDTH_RI) + x_ri].g = pixels[j * WIDTH + i].g;
                rotate_image[y_ri * (WIDTH_RI) + x_ri].b = pixels[j * WIDTH + i].b;
            }
        }
        rotate_inverse_rgb_image_validate(rotate_image, pixels, WIDTH, HEIGHT, angle);
    }
    else
    {
        // A alternativa aplica a rotacao por etapas de cisalhamento.
        for (int j = 0; j < HEIGHT; j++)
        {
            for (int i = 0; i < WIDTH; i++)
            {
                point_2d point = rotate_plan_2d_cisalhamento(
                    i - center_x, j - center_y, angle
                );
                int x_ri = point.x + center_ri_x;
                int y_ri = point.y + center_ri_y;

                if (x_ri < 0 || x_ri >= WIDTH_RI || y_ri < 0 || y_ri >= HEIGHT_RI)
                    continue;

                rotate_image[y_ri * (WIDTH_RI) + x_ri].r = pixels[j * WIDTH + i].r;
                rotate_image[y_ri * (WIDTH_RI) + x_ri].g = pixels[j * WIDTH + i].g;
                rotate_image[y_ri * (WIDTH_RI) + x_ri].b = pixels[j * WIDTH + i].b;
            }
        }
    }
    return rotate_image;
}