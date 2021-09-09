#include <stdio.h>
#include <stdlib.h>
#include "imagen.h"

int main ()
{
    bmpInfoHeader info;
    unsigned char *imagenRGB;

    imagenRGB = abrirBMP("hoja.bmp", &info);
    displayInfo(&info);

    free(imagenRGB);
    return 0;
}