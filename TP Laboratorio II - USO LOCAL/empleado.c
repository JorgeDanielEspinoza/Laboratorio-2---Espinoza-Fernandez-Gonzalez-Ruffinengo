#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "empleado.h"
#include "ventas.h"
#include "auto.h"
#include "cliente.h"

void cargarArchivo (char nombre_archivo[],nodoEmpleado*lista)
{
    FILE*archivo=fopen(nombre_archivo,"ab");
    stEmpleado aux;
    if(archivo)
    {
        while(lista!=NULL)
        {
            aux=lista->dato;
            fwrite(&aux,sizeof(stEmpleado),1,archivo);
            lista=lista->sig;
        }
        fclose(archivo);
    }
}
nodoEmpleado*agregarEmpleado(nodoEmpleado*lista)
{
    stEmpleado aux;
    char continuar ='s';
    nodoEmpleado*nuevonodo;
    while(continuar=='s')
    {
        cargarEmpleado(&aux);
        nuevonodo=crearNodoEmpleado(aux);
        lista=agregaalppioEmpleado(lista,nuevonodo);

        printf("Desea agregar mas empleados? 's':\n");
        fflush(stdin);
        scanf("%c",&continuar);
    }
    return lista;
}
void cargarEmpleado(stEmpleado*aux)
{
    printf("ID: \n");
    scanf("%d",&aux->idEmpleado);
    printf("Nombre: \n");
    fflush(stdin);
    scanf("%s",aux->nombre);
    printf("Apellido: \n");
    fflush(stdin);
    scanf("%s",aux->apellido);
    printf("DNI: \n");
    scanf("%d",&aux->dni);
}
nodoEmpleado*inicEmpleado()
{
    return NULL;
}
nodoEmpleado*crearNodoEmpleado(stEmpleado aux)
{
    nodoEmpleado*nuevonodo=(nodoEmpleado*)malloc(sizeof(nodoEmpleado));
    nuevonodo->dato=aux;
    nuevonodo->sig=inicEmpleado();
    return nuevonodo;
}
nodoEmpleado*agregaalppioEmpleado(nodoEmpleado*lista,nodoEmpleado*nuevonodo)
{
    if(lista==NULL)
    {
        lista=nuevonodo;
    }
    else
    {
        nuevonodo->sig=lista;
        lista=nuevonodo;
    }
    return lista;
}
void verEmpleados(char nombre_archivo[])
{
    FILE*archivo=fopen(nombre_archivo,"rb");
    stEmpleado aux;
    if(archivo)
    {
        while(fread(&aux,sizeof(stEmpleado),1,archivo)>0)
        {
            verUnEmpleado(aux);
        }
        fclose(archivo);
    }
}
void verUnEmpleado (stEmpleado aux)
{
    printf("Id Empleado: %d\n",aux.idEmpleado);
    printf("Nombre: %s\n",aux.nombre);
    printf("Apellido: %s\n",aux.apellido);
    printf("DNI: %d\n",aux.dni);
}




