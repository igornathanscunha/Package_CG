#include <math.h>
#include "cg/math/rotation2d.h"

// Converte o angulo em graus para a unidade esperada por sin, cos e tan.
double degrees_to_radians(int angle)
{
    return angle * (acos(-1.0) / 180.0);
}

// Calcula cada componente da rotacao de um ponto em torno da origem.
int rotate_plan_2d_x(int x, int y, double radians)
{
    return (x * cos(radians)) - (y * sin(radians));
}

// Calcula cada componente da rotacao de um ponto em torno da origem.
int rotate_plan_2d_y(int x, int y, double radians)
{
    return (x * sin(radians)) + (y * cos(radians));
}

// Aplica a matriz de rotacao direta e arredonda o resultado para pixels inteiros.
point_2d rotate_plan_2d(int x, int y, double radians)
{
    return (point_2d){
        (int)round((x * cos(radians)) - (y * sin(radians))),
        (int)round((x * sin(radians)) + (y * cos(radians)))
    };
}

// Mapeia uma coordenada de destino de volta para a coordenada correspondente na origem.
point_2d rotate_inverse_plan_2d(int x, int y, double radians)
{
    return (point_2d){
        (int)round((x * cos(radians)) + (y * sin(radians))),
        (int)round(-(x * sin(radians)) + (y * cos(radians)))
    };
}

// Aproxima a rotacao por cisalhamentos sucessivos para reduzir cada etapa angular.
point_2d rotate_plan_2d_cisalhamento(int x, int y, int angle)
{
    angle %= 360;
    int step = 0;
    while (angle != 0)
    {
        if(angle >= 90)
            step = 90;
        else if (angle < 90)
            step = angle > 45 ? 45 : angle;

        if (angle < -45)
            step = -45;

        double radians = degrees_to_radians(step);
        x = x + round(-tan(radians / 2) * y);
        y = y + round(sin(radians) * x);
        x += round(-tan(radians / 2) * y);

        angle -= step;
    }
    return (point_2d){x, y};
}