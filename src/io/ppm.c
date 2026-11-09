#include <stdio.h>
#include <stdlib.h>
#include "cg/io/ppm.h"

// Consome comentarios PPM iniciados por '#' e devolve o proximo caractere util.
void clear_comments(FILE* file)
{
    uint8_t caracter;
    while ((caracter=getc(file))=='#')
        while ((caracter=getc(file))!='\n');
    ungetc(caracter, file);
}

rgb_image extract_properties_rgb_image(FILE* fp)
{
    rgb_image img;
    clear_comments(fp);
    fscanf(fp, "P%hhu\n", &img.TYPE_IMG);
    clear_comments(fp);
    fscanf(fp, "%u %u\n%hhu\n", &img.WIDTH, &img.HEIGHT, &img.CMAX);
    return img;
}

FILE* open_archive_ppm(const char* name)
{
    FILE* fp = fopen(name, "r");
    if (!fp)
    {
        perror(name);
        exit(1);
    }
    return fp;
}

FILE* writing_archive_ppm(const char* name)
{
    FILE* fp = fopen(name, "w");
    if (!fp)
    {
        perror(name);
        exit(2);
    }
    return fp;
}

// Carrega os pixels do arquivo: P3 usa valores textuais e P6 usa bytes binarios.
void load_image_in_matrix_rgb_color(FILE* fp, rgb_color* pixels, int WIDTH, int HEIGHT, uint8_t TYPE_IMG)
{
    if (TYPE_IMG == 3)
    {
        for (int i = 0; i < HEIGHT; i++)
            for (int j = 0; j < WIDTH; j++)
                fscanf(fp, "%hhu %hhu %hhu",
                       &pixels[i * WIDTH + j].r,
                       &pixels[i * WIDTH + j].g,
                       &pixels[i * WIDTH + j].b);
    }
    else if (TYPE_IMG == 6)
    {
        for (int i = 0; i < HEIGHT; i++)
            for (int j = 0; j < WIDTH; j++)
            {
                unsigned char rgb[3];
                fread(rgb, 1, 3, fp);

                pixels[i * WIDTH + j].r = rgb[0];
                pixels[i * WIDTH + j].g = rgb[1];
                pixels[i * WIDTH + j].b = rgb[2];
            }
    }
    else
    {
        // Em formato invalido, encerra o processo.
        perror("Formato de arquivo invalido!\n");
        exit(1);
    }
}

// Escreve o cabecalho PPM e serializa os pixels no formato indicado.
void generate_rgb_image_ppm(FILE* fp, rgb_color* pixels,
    int WIDTH, int HEIGHT, uint8_t TYPE_IMG, uint8_t CMAX)
{
    fprintf(fp, "P%hhu\n", TYPE_IMG);
    fprintf(fp, "%u %u\n%hhu\n", WIDTH, HEIGHT, CMAX);
    for (int j = 0; j < HEIGHT; j++)
    {
        for (int i = 0; i < WIDTH; i++)
        {
            if (TYPE_IMG == 3)
            {
                fprintf(fp, "%hhu ", pixels[j * WIDTH + i].r);
                fprintf(fp, "%hhu ", pixels[j * WIDTH + i].g);
                fprintf(fp, "%hhu ", pixels[j * WIDTH + i].b);
            }
            else if (TYPE_IMG == 6)
            {
                fprintf(fp, "%c", pixels[j * WIDTH + i].r);
                fprintf(fp, "%c", pixels[j * WIDTH + i].g);
                fprintf(fp, "%c", pixels[j * WIDTH + i].b);
            }
        }
    }
}

// Escreve o cabecalho PPM e serializa os pixels no formato indicado.
void generate_gray_image_ppm(FILE* fp, gray_color* pixels,
    int WIDTH, int HEIGHT, uint8_t TYPE_IMG, uint8_t CMAX)
{
    fprintf(fp, "P%hhu\n", TYPE_IMG);
    fprintf(fp, "%u %u\n%hhu\n", WIDTH, HEIGHT, CMAX);
    for (int j = 0; j < HEIGHT; j++)
    {
        for (int i = 0; i < WIDTH; i++)
        {
            if (TYPE_IMG == 2)
            {
                fprintf(fp, "%hhu ", pixels[j * WIDTH + i].scale);
            }
            else if (TYPE_IMG == 5)
            {
                fprintf(fp, "%c", pixels[j * WIDTH + i].scale);
            }
        }
    }
}