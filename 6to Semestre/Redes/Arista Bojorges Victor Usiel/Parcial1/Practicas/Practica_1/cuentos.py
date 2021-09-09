from threading import Thread
import threading
from os import scandir, getcwd
import os

#se crea una clase que hereda de Thread para poder retornar valores
class ThreadWithReturnValue(Thread):
    def __init__(self, group=None, target=None, name=None,args=(), kwargs={}, Verbose=None):
        Thread.__init__(self, group, target, name, args, kwargs)
        self._return = None
    def run(self):
        #print(type(self._target))
        if self._target is not None:
            self._return = self._target(*self._args,**self._kwargs)
    def join(self, *args):
        Thread.join(self, *args)
        return self._return

#getcwd regresa la ruta absoluta actual,scandir devuelve un objeto iterable con los objetos dentro del directorio especificado
def ls(ruta = os.path.abspath("cuentos")):
    #devuelve una lista con los nombres de los archivos del directorio actual sin contar a el archivo cuentos.py
    #scandir devuelve un arreglo con los archivos y directorios de la ruta especificada
    return [os.path.abspath("cuentos/"+arch.name) for arch in scandir(ruta) if (arch.is_file() and arch.name != "cuentos.py")]

def contar_palabras(rutas,palabras,inicio,fin):
    #se crea un arreglo que contendra la cantidad de veces que se repite palabras[i]
    cantidad = list()
    for i in range(0,len(palabras)+1):
        cantidad.append(0)
    
    #primer for para los archivos que le tocan al hilo
    for i in range(inicio,fin):
        archivo = open(rutas[i],"r")
        #segundo for para las lineas del archivo
        for linea in archivo.readlines():
            aux_palabras = linea.split(" ")
            cantidad[len(palabras)] = cantidad[len(palabras)] + len(aux_palabras)
            #tercer for para las palabras de una linea
            for j in range(len(palabras)):
                #cuarto for para contar las palabras
                for palabra in aux_palabras:
                    #quitar el caracter de salto de linea a las palabras
                    if palabra.endswith('\n'):
                        palabra = palabra[:-1]
                    if palabras[j] == palabra:
                        cantidad[j] = cantidad[j] + 1 
                    
    return cantidad

#lista de archivos en el directorio actual
rutas = ls()

n_hilos = int(input("ingrese numero de hilos"))
#lista de palabras a buscar
palabras = list()
n_palabras= int(input("¿cuantas palabras quieres buscar?"))
for i in range(n_palabras):
    palabras.append(input("ingresa palabra a buscar: "))

resto = len(rutas)%n_hilos
archivos_hilo = len(rutas)//n_hilos

#arreglo de hilos
hilos = list()
#el primer hilo tendra que encargarse de los archivos por hilo (archivos_hilo) + resto (esto si sobran archivos)
hilo0 = ThreadWithReturnValue(target=contar_palabras, args=(rutas,palabras,0,resto+archivos_hilo))
hilo0.start()
hilos.append(hilo0)

inicio = archivos_hilo + resto

#ciclo para asignarle los archivos que le tocan a cada hilo
for i in range(1,n_hilos):
    hilo = ThreadWithReturnValue(target=contar_palabras, args=(rutas,palabras,inicio,inicio+archivos_hilo))
    hilos.append(hilo)
    hilo.start()
    inicio = inicio + archivos_hilo

resultado = list()

for hilo in hilos:
    #se añade a la lista de resultados la lista que regresa el hilo
    resultado.append(hilo.join())

#final es una lista que contendra el conteo de todas las palabras y el total de palabras del archivo
final = list()
for i in range(len(palabras)+1):
    final.append(0)

for i in range(n_hilos):
    for j in range(len(palabras)+1):
        #se suman los resultados de los hilos
        final[j] = final[j] + resultado[i][j]

print("")
print("Estadisticas:")
print("")

for i in range(len(palabras)+1):
    if i < len(palabras):
        print(palabras[i]+":",final[i],"porcentaje:",(final[i]/final[len(palabras)])*100,"%")
    else:
        print("total de palabras:",final[i])