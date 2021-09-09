#!/bin/bash

sshpass -p "Contraseñ0n" scp -P 14729 -r  ../09_image_server  pi@2.tcp.ngrok.io:~/embebidos/
