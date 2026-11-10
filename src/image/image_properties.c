#include "cg/image/image_properties.h"

image_properties create_image_properties(unsigned int WIDTH, unsigned int HEIGHT,
    uint8_t TYPE_IMG, uint8_t CMAX)
{
    return (image_properties){WIDTH, HEIGHT, TYPE_IMG, CMAX};
}
image_properties extract_properties_image(FILE* fp)
{
    image_properties img;
    clear_comments(fp);
    fscanf(fp, "P%hhu\n", &img.TYPE_IMG);
    clear_comments(fp);
    fscanf(fp, "%u %u\n%hhu\n", &img.WIDTH, &img.HEIGHT, &img.CMAX);
    return img;
}

// Consome comentarios PPM iniciados por '#' e devolve o proximo caractere util.
void clear_comments(FILE* file)
{
    uint8_t caracter;
    while ((caracter=getc(file))=='#')
        while ((caracter=getc(file))!='\n');
    ungetc(caracter, file);
}