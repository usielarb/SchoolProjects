#!/bin/bash

GPIOS=(14 15 18 23 24 25 8)
DIGITO0=(1 1 1 1 1 1 0)
DIGITO1=(1 1 0 0 0 0 0)
DIGITO2=(1 0 1 1 0 1 1)
DIGITO3=(1 1 1 0 0 1 1)
DIGITO4=(1 1 0 0 1 0 1)
DIGITO5=(0 1 1 0 1 1 1)
DIGITO6=(0 1 1 1 1 1 1)
DIGITO7=(1 1 0 0 0 1 1)
DIGITO8=(1 1 1 1 1 1 1)
DIGITO9=(1 1 1 0 1 1 1)

function habilitaGPIOS ()
{
    for i in ${GPIOS[*]}
    do 
        if  [ ! -d /sys/class/gpio/gpio$i ]
        then 
            echo $i > /sys/class/gpio/export
        fi
    done
    sleep 1
}

function deshabilitaGPIOS ()
{
    for i in ${GPIOS[*]}
    do 
        if  [ -d /sys/class/gpio/gpio$i ]
        then 
            echo $i > /sys/class/gpio/unexport
        fi
    done
}

function configuraGPIOS ()
{
    for i in ${GPIOS[*]}
    do 
        echo "out" > /sys/class/gpio/gpio$i/direction
    done
    sleep 1
}

function guion ()
{
    for j in 0 1
    do
        for i in 0 1 2 3 4 5 
        do 
            echo "0" > /sys/class/gpio/gpio$GPIOS[$i]/value
        done
        echo "1" > /sys/class/gpio/gpio$GPIOS[7]/value
        sleep 1
    done
}
function boletausiel ()
{
    for j in 2 0 1 5 0 3 0 0 6 9
    do
        for i in 0 1 2 3 4 5 6
        do 
            echo $DIGITO$j[$i] > /sys/class/gpio/gpio$GPIOS[$i]/value
        done
        sleep 1
    done
}
function boletaeli ()
{
    for j in 2 0 1 5 0 3 0 0 6 9
    do
        for i in 0 1 2 3 4 5 6
        do 
            echo $DIGITO$j[$i] > /sys/class/gpio/gpio$GPIOS[$i]/value
        done
        sleep 1
    done
}
function boletajoel ()
{
    for j in 2 0 1 5 0 3 0 0 6 9
    do
        for i in 0 1 2 3 4 5 6
        do 
            echo $DIGITO$j[$i] > /sys/class/gpio/gpio$GPIOS[$i]/value
        done
        sleep 1
    done
}


habilitaGPIOS
configuraGPIOS
boletausiel
guion
boletaeli
guion
boletajoel
deshabilitaGPIOS
exit 0
            
            