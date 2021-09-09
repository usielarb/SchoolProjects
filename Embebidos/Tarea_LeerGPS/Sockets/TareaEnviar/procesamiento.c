#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct datosf
{
    char lat[20], lon[20], time[20];
    char lonV, latV;
};

struct datosf encVal()
{
    FILE *file;
    struct datosf tem;
    char aux, word[10], latVChar, lonVChar, latChar[20] = "", lonChar[20]= "", timeChar[20]= "" ;
    float lat, lon, time ;

    strcpy(latChar,"");
    strcpy(lonChar,"");
    strcpy(timeChar,"");

    int i;
    file = fopen("nmea.txt", "r");
    while((aux = getc(file)) != EOF)
    {
        if (aux == '$' )
        {
            fgets(word, 6, file);
            if (strcmp(word,"GPGGA") == 0)
                {
                    i = 0;
                    //printf(">%s\n", word);
                    aux = getc(file);
                    while((aux = getc(file)) != ',')
                    {
                        timeChar[i] = aux;
                        i++;
                    }
                    //printf("1 %s\n", timeChar);  
                    i = 0;                  
                    while((aux = getc(file)) != ',')
                    {
                        latChar[i] = aux;
                        i++;
                    }
                    //printf("2 %s\n", latChar);   
                    latVChar = getc(file); 
                    //printf("3 %c\n", latVChar);
                    aux = getc(file);
                    i = 0;
                    while((aux = getc(file)) != ',')
                    {
                        lonChar[i] = aux;
                        //printf ("%c", aux);
                        i++;
                    }
                    //printf("\n");
                    //printf("4 %s\n", lonChar);   
                    lonVChar = getc(file);   
                    //printf("5 %c\n", lonVChar);   
                    break;
                }
        }
    }
    lat = atof(latChar);
    lon = atof(lonChar);
    time = atof(timeChar);

    stpcpy(tem.lat , latChar);
    stpcpy(tem.time , timeChar);
    stpcpy(tem.lon , lonChar);
    //tem.lon = lonChar;
    //tem.time = timeChar;
    tem.lonV = lonVChar;
    tem.latV = latVChar;

    printf("######\n");
    return (tem);
}