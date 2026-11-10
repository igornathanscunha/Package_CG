#ifndef CG_COLOR_H
#define CG_COLOR_H

#include <stdint.h>

// Um pixel em escala de cinza possui um unico componente de intensidade.
typedef struct gray_color
{
    uint8_t scale;
}gray_color;

// Um pixel RGB possui componentes separados para vermelho, verde e azul.
typedef struct rgb_color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
}rgb_color;

#endif